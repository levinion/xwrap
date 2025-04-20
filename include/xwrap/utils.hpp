#include <iostream>
#define Debug 1
#define panic(info) \
  std::cout << "[panic] " << info << std::endl; \
  exit(2);
#if Debug == 1
  #define info(info) std::cout << "[info] " << info << std::endl;
#else
  #define info(info)
#endif
