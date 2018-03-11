#include <stdio.h>

#include "lib/assets.cpp"

void ShowUsage() {
  std::cout <<
    "Usage: base16-builder install\n\n"
    "Options:\n"
    "  -h,--help            Show this help message\n"
    "  -s,--scheme    NAME  Specify the scheme name\n"
    "  -t,--template  NAME  Specify the template name\n";

  exit(1);
}

void Run(int argc, char *argv[]) {
  const struct option long_opts[] = {
    { "help",     0, 0, 'h' },
    { "scheme",   1, 0, 's' },
    { "template", 1, 0, 't' }
  };

  int opt;

  while ((opt = getopt_long(argc, argv, "hs:t:", long_opts, nullptr)) != -1) {
    switch (opt) {
      case 's':
        base16_scheme = optarg;
        break;
      case 't':
        base16_template = optarg;
        break;
      case 'h':
        ShowUsage();
    }
  }
}

