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
XImage* XwrapWindow::get_xshm_image(
  int x,
  int y,
  unsigned int width,
  unsigned int height
) {
  int screen = DefaultScreen(display);
  auto attributes = this->get_attributes();

  XShmSegmentInfo shminfo;
  XImage* image = XShmCreateImage(
    display,
    attributes.visual,
    attributes.depth,
    ZPixmap,
    NULL,
    &shminfo,
    width,
    height
  );

  // 分配共享内存
  shminfo.shmid = shmget(
    IPC_PRIVATE,
    image->bytes_per_line * image->height,
    IPC_CREAT | 0777
  );
  shminfo.shmaddr = image->data = (char*)shmat(shminfo.shmid, 0, 0);
  shminfo.readOnly = False;

  // 附加共享内存
  XShmAttach(display, &shminfo);

  // 获取图像数据
  XShmGetImage(display, window, image, 0, 0, AllPlanes);

  // 在此处处理 image->data 中的图像数据

  // 分离并释放共享内存
  XShmDetach(display, &shminfo);
  shmdt(shminfo.shmaddr);
  shmctl(shminfo.shmid, IPC_RMID, 0);

  return image;
}
} // namespace xwrap
