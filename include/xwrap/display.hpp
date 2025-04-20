#pragma once

#include <string>
#include <X11/X.h>
#include <X11/Xlib.h>

namespace xwrap {
Display* XwrapDisplay(std::string display);
Display* XwrapDisplay();

} // namespace xwrap
