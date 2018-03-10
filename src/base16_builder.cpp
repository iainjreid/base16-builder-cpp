#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <boost/filesystem.hpp>

#include "git2.h"
#include "git2/clone.h"
#include "mstch/mstch.hpp"

#define fs boost::filesystem

using namespace std;

string git_source = "https://github.com";

void ShowUsage() {
  cout <<
    "Usage: base16-builder\n\n"
    "Options:\n"
    "  -h,--help               Show this help message\n"
    "  -s,--scheme SCHEMA      Specify the schema\n"
    "  -t,--template TEMPLATE  Specify the template\n";

  exit(1);
}

void ShowError(string message) {
  cout << "Error: " + message << endl;

  exit(1);
}

int CloneRepository(string repository_path, string local_path) {
  git_repository       *clone         = NULL;
  git_clone_options     clone_opts    = GIT_CLONE_OPTIONS_INIT;
  git_checkout_options  checkout_opts = GIT_CHECKOUT_OPTIONS_INIT;
  
  const string repository_url = git_source + "/" + repository_path;
  int error;
  
  error = git_clone(&clone, repository_url.c_str(), local_path.c_str(), &clone_opts);
  
  if (error != 0) {
    const git_error *err = giterr_last();
	
    if (err) printf("ERROR %d: %s\n", err->klass, err->message);
    else printf("ERROR %d: no detailed info\n", error);
  }
  else if (clone) git_repository_free(clone);
  return error;
}

fs::path GetAsset(fs::path base_path, fs::path repository_path) {
  fs::path asset_path = base_path / repository_path;
  
  if (!fs::is_directory(asset_path)) {
    CloneRepository(repository_path.string(), asset_path.string());
  }

  return asset_path;
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
    ShowError("Please provide both a scheme and a template");
  }

  git_libgit2_init();
  
  const fs::path scheme_path   = GetAsset(base16_schemes_dir, base16_scheme);
  const fs::path template_path = GetAsset(base16_templates_dir, base16_template);

  git_libgit2_shutdown();
}

