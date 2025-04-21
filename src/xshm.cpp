#include "xwrap/window.hpp"
#include <X11/X.h>
#include <X11/Xlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <X11/extensions/XShm.h>
#include <cassert>
#include "xwrap/utils.hpp"

// TODO: get this function work
namespace xwrap {
XImage* XwrapWindow::get_xshm_image(XImage* image) {
  XShmGetImage(display, window, image, 0, 0, AllPlanes);

  return image;
}
} // namespace xwrap
