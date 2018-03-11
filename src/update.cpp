#include <stdio.h>

void ShowUsage() {
  std::cout <<
    "Usage: base16-builder update\n\n"
    "Options:\n"
    "  -h,--help            Show this help message\n"
    "  -s,--scheme    NAME  Specify the scheme name\n"
    "  -t,--template  NAME  Specify the template name\n";

  exit(1);
}

void Run(int argc, char *argv[]) {
  
}
