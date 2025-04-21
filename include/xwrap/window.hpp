#include <opencv2/opencv.hpp>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/extensions/XShm.h>
#include <X11/extensions/Xdamage.h>
#include <string>
#include <vector>
#include "display.hpp"
#include "keys.hpp"

namespace xwrap {

class XwrapPixel {
public:
  float r, g, b;
};

class XwrapImage {
public:
  cv::Mat* image;
  XwrapPixel get_pixel(int x, int y);
  void show();
};

class XwrapWindow {
public:
  Display* display;
  Window window;
  int br, base;
  static XwrapWindow from_focused(Display* display);
  static XwrapWindow from_root(Display* display);
  std::string get_name();
  XWindowAttributes get_attributes();
  void begin_get_image();
  XwrapImage get_image();
  void end_get_image();
  void set_override_redirect();
  void allow_passthrough();
  void unmap();
  void map();
  void set_focus();
  XwrapWindow get_overlay_window();
  void fullscreen(bool flag);
  std::vector<XwrapWindow> get_children();

  //event
  void send_key(Key key, bool press);
  void send_button(MouseButton button, bool press);
  void set_cursor_position(int x, int y);
  void set_cursor_relative_position(int xrel, int yrel);
  void send_mouse_wheel(float y);

  XShmSegmentInfo shminfo;
  XImage* image;

private:
  void get_xshm_image();
  XImage* get_x11_image();
};
} // namespace xwrap
