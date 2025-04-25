#include "xwrap/window.hpp"
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/Xdamage.h>
#include <X11/extensions/damagewire.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <X11/extensions/XShm.h>
#include <cassert>

namespace xwrap {
void XwrapWindow::get_xshm_image() {
  XShmGetImage(display, window, image, 0, 0, AllPlanes);
}

void XwrapWindow::begin_get_image() {
  int screen = DefaultScreen(display);
  auto attr = this->get_attributes();

  XDamageQueryExtension(display, &damage_event, &damage_error);

  damage = XDamageCreate(display, window, XDamageReportNonEmpty);

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

  XwrapImage xim;
  xim.pixels = image->data;
  xim.height = image->height;
  xim.width = image->width;

  return xim;
}

std::optional<XwrapImage> XwrapWindow::try_get_image() {
  XEvent event;
  XNextEvent(display, &event);
  if (event.type == damage_event + XDamageNotify) {
    return this->get_image();
  }
  return {};
}

} // namespace xwrap
