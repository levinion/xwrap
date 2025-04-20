#include <mutex>
#include <opencv2/highgui.hpp>
#include <X11/extensions/composite.h>
#include <X11/extensions/damagewire.h>
#include <X11/extensions/shapeconst.h>
#include <xwrap/window.hpp>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cassert>
#include <print>
#include <string>
#include <thread>
#include <vector>
#include "tasklet/tasklet.hpp"
#include <xwrap/utils.hpp>
#include <X11/extensions/Xcomposite.h>
#include <X11/extensions/XShm.h>
#include <X11/extensions/Xfixes.h>
#include <X11/extensions/shape.h>
#include <X11/extensions/Xdamage.h>

namespace xwrap {
XwrapWindow XwrapWindow::from_focused(Display* display) {
  Window focused;
  int unknown;
  XGetInputFocus(display, &focused, &unknown);
  XwrapWindow window;
  window.display = display;
  window.window = focused;
  return window;
}

XwrapWindow XwrapWindow::from_root(Display* display) {
  auto root = RootWindow(display, DefaultScreen(display));
  XwrapWindow window;
  window.display = display;
  window.window = root;
  return window;
}

std::string XwrapWindow::get_name() {
  char* name;
  XFetchName(display, window, &name);
  std::string name_str;
  if (name == nullptr)
    name_str = "";
  else
    name_str = name;
  XFree(name);
  return name_str;
}

XWindowAttributes XwrapWindow::get_attributes() {
  XWindowAttributes window_attributes;
  XGetWindowAttributes(display, window, &window_attributes);
  return window_attributes;
}

XImage* XwrapWindow::get_x11_image() {
  auto attributes = this->get_attributes();
  return XGetImage(
    display,
    this->window,
    0,
    0,
    attributes.width,
    attributes.height,
    AllPlanes,
    ZPixmap
  );
}

void XwrapWindow::allow_passthrough() {
  XserverRegion region = XFixesCreateRegion(display, NULL, 0);

  XFixesSetWindowShapeRegion(display, window, ShapeBounding, 0, 0, 0);
  XFixesSetWindowShapeRegion(display, window, ShapeInput, 0, 0, region);

  // XFixesDestroyRegion(display, region);
}

void XwrapWindow::set_override_redirect() {
  XSetWindowAttributes attr;
  attr.override_redirect = 1;
  attr.event_mask = SubstructureRedirectMask | SubstructureNotifyMask
    | KeyReleaseMask | PointerMotionMask;
  XChangeWindowAttributes(display, window, CWOverrideRedirect, &attr);
  XChangeWindowAttributes(display, window, CWEventMask, &attr);
}

void XwrapWindow::unmap() {
  XUnmapWindow(display, window);
}

void XwrapWindow::map() {
  XMapWindow(display, window);
}

void XwrapWindow::set_focus() {
  XSetInputFocus(display, window, RevertToParent, CurrentTime);
}

XwrapWindow XwrapWindow::get_overlay_window() {
  auto w = XCompositeGetOverlayWindow(display, window);
  return XwrapWindow { display, w };
}

XwrapImage XwrapWindow::get_image() {
  // Get XImage
  XImage* image = nullptr;
  image = this->get_x11_image();
  if (image == nullptr) {
    panic("no support method to grab window surface");
  }

  // Get Mat
  auto attr = this->get_attributes();
  auto mat = cv::Mat(attr.height, attr.width, CV_8UC3);

  // auto pool = tasklet::ThreadPool();

  // split by parts
  auto parts = 1;
  for (int i = 0; i < parts; i++) {
    // pool.add_task([=, &mat]() {
    for (int x = attr.width * i / parts; x < attr.width * (i + 1) / parts;
         x++) {
      for (int y = 0; y < attr.height; y++) {
        auto pixel = XGetPixel(image, x, y);
        unsigned char blue = pixel & image->blue_mask;
        unsigned char green = (pixel & image->green_mask) >> 8;
        unsigned char red = (pixel & image->red_mask) >> 16;
        mat.at<cv::Vec3b>(y, x) = { blue, green, red };
      }
    }
    // });
  }
  // pool.wait();

  XDestroyImage(image);
  return XwrapImage { mat };
}

// this is a fake fullscreen -> equals to maximize
void XwrapWindow::fullscreen(bool flag) {
  if (flag) {
    auto root = XwrapWindow::from_root(this->display);
    auto attr = root.get_attributes();
    XMoveResizeWindow(display, window, 0, 0, attr.width, attr.height);
  }
}

std::vector<XwrapWindow> XwrapWindow::get_children() {
  Window* children;
  unsigned int len;
  Window root, parent;
  XQueryTree(display, window, &root, &parent, &children, &len);
  std::vector<XwrapWindow> v;
  for (int i = 0; i < len; i++) {
    auto child = *(children + i);
    v.push_back(XwrapWindow { display, child });
  }
  return v;
}

} // namespace xwrap

namespace xwrap {
XwrapPixel XwrapImage::get_pixel(int x, int y) {
  auto pixel = image.at<cv::Vec3b>(y, x);
  auto b = (float)pixel[0];
  auto g = (float)pixel[1];
  auto r = (float)pixel[2];
  return XwrapPixel { r, g, b };
}

void XwrapImage::show() {
  cv::imshow("Demo", image);
  while (1) {
    auto k = cv::waitKey(0);
    if (k == 'q')
      break;
  }
}

} // namespace xwrap
