#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <boost/filesystem.hpp>

#include "git2.h"
#include "git2/clone.h"
#include "mstch/mstch.hpp"
#include "lib/error.h"

#define fs boost::filesystem

using namespace std;

string git_source = "https://github.com";

void ShowUsage() {
  cout <<
    "Usage: base16-builder\n\n"
    "Commands:\n"
    "  install  Specify the schema\n"
    "  update   Specify the template\n";

  exit(1);
}

int main(int argc, char* argv[]) {
  if (argc == 1) {
    ShowUsage();
  }

  const fs::path base16_root          = getenv("HOME");
  const fs::path base16_schemes_dir   = base16_root / ".base16-schemes";
  const fs::path base16_templates_dir = base16_root / ".base16-templates";

  const struct option long_opts[] = {
    { "help",     0, 0, 'h' },
    { "scheme",   1, 0, 's' },
    { "template", 1, 0, 't' },
  };

  int opt;
  string base16_scheme, base16_template;

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

  if (base16_scheme.empty() || base16_template.empty()) {
      const std::string asd= "Please provide both a scheme and a template";
      (new Error(1, asd))->Fatal();
  }

  git_libgit2_init();
  
  const fs::path scheme_path   = GetAsset(base16_schemes_dir, base16_scheme);
  const fs::path template_path = GetAsset(base16_templates_dir, base16_template);

  git_libgit2_shutdown();
}

