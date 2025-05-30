#pragma once

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/extensions/XShm.h>
#include <X11/extensions/Xdamage.h>
#include <optional>
#include <string>
#include <vector>
#include "xwrap/display.hpp"
#include "keys.hpp"
#include "xwrap/image.hpp"

namespace xwrap {

class XwrapPixel {
public:
  float r, g, b;
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
  std::optional<XwrapImage> try_get_image();
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
  Damage damage;

  int damage_event;
  int damage_error;

private:
  void get_xshm_image();
  XImage* get_x11_image();
};
} // namespace xwrap
