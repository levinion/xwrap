#include <xwrap/xwrap.h>
#include <cassert>
#include <iostream>
#include <print>

using namespace xwrap;

int main() {
  auto window = XwrapWindow::from_focused();
  std::cout << window.get_name() << std::endl;
  auto size = window.get_size();
  std::println("{} {}", size.width, size.height);
  auto image = window.get_image();
  auto pixel = image.get_pixel(300, 200);
  std::println("{} {} {}", pixel.r, pixel.g, pixel.b);
  image.show();
}
