#include "SniperMgr.h"
#include <iostream>

int main(int argc, char *argv[])
{
  if ( argc != 2 ) {
      std::cout << "Usage: " << argv[0] << "  option.txt" << std::endl;
      return 1;
  }

  SniperMgr mgr(argv[1]);

  if ( mgr.initialize() ) {
      mgr.run();
  }

  mgr.finalize();

  return 0;
}
