#include "xwrap/window.hpp"
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <X11/extensions/XShm.h>
#include <cassert>
#include "xwrap/utils.hpp"

namespace xwrap {
void XwrapWindow::get_xshm_image() {
  XShmGetImage(display, window, image, 0, 0, AllPlanes);
}

void XwrapWindow::begin_get_image() {
  int screen = DefaultScreen(display);
  auto attr = this->get_attributes();

  auto image = XShmCreateImage(
    display,
    attr.visual,
    attr.depth,
    ZPixmap,
    NULL,
    &shminfo,
    attr.width,
    attr.height
  );

  shminfo.shmid = shmget(
    IPC_PRIVATE,
    image->bytes_per_line * image->height,
    IPC_CREAT | 0777
  );

  shminfo.shmaddr = image->data = (char*)shmat(shminfo.shmid, 0, 0);
  shminfo.readOnly = False;

  XShmAttach(display, &shminfo);
  this->image = image;
}

void XwrapWindow::end_get_image() {
  XShmDetach(display, &shminfo);
  shmdt(shminfo.shmaddr);
  shmctl(shminfo.shmid, IPC_RMID, 0);
  XDestroyImage(image);
}

XwrapImage XwrapWindow::get_image() {
  // Get XImage

  this->get_xshm_image();

  // Get Mat
  auto attr = this->get_attributes();

  // cv::parallel_for_(
  //   cv::Range(0, attr.width),
  //   cv::ParallelLoopBodyLambdaWrapper([&](const cv::Range& range) {
  //     for (int x = range.start; x < range.end; ++x) {
  //       for (int y = 0; y < attr.height; ++y) {
  //         auto pixel = XGetPixel(image, x, y);
  //         unsigned char blue = pixel & image->blue_mask;
  //         unsigned char green = (pixel & image->green_mask) >> 8;
  //         unsigned char red = (pixel & image->red_mask) >> 16;
  //         *mat.ptr<cv::Vec3b>(y, x) = { blue, green, red };
  //       }
  //     }
  //   })
  // );

  XwrapImage xim;
  xim.pixels = image->data;
  xim.height = image->height;
  xim.width = image->width;

  return xim;
}

} // namespace xwrap
