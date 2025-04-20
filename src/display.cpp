#include "xwrap/display.hpp"

namespace xwrap {

Display* XwrapDisplay(std::string display) {
  return XOpenDisplay(display.c_str());
};

Display* XwrapDisplay() {
  return XOpenDisplay(NULL);
};

} // namespace xwrap
