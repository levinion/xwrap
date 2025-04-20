#include "xwrap/window.hpp"
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>
#include <linux/input.h>

namespace xwrap {
void XwrapWindow::send_key(Key key, bool press) {
  auto keycode = usb_hid_to_evdev()[static_cast<int>(key)];
  XTestFakeKeyEvent(display, keycode + 8, press, CurrentTime);
  XFlush(display);
}

void XwrapWindow::send_button(MouseButton button, bool press) {
  XTestFakeButtonEvent(display, (unsigned int)button, press, CurrentTime);
  XFlush(display);
}

void XwrapWindow::set_cursor_position(int x, int y) {
  XTestFakeMotionEvent(display, 0, x, y, CurrentTime);
  XFlush(display);
}

void XwrapWindow::set_cursor_relative_position(int xrel, int yrel) {
  XTestFakeRelativeMotionEvent(display, xrel, yrel, CurrentTime);
  XFlush(display);
}

void XwrapWindow::send_mouse_wheel(float y) {
  if (y > 0) {
    this->send_button(MouseButton::X1, true);
    this->send_button(MouseButton::X1, false);
  } else {
    this->send_button(MouseButton::X2, true);
    this->send_button(MouseButton::X2, false);
  }
  XFlush(display);
}
} // namespace xwrap
