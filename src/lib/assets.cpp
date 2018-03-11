#include <stdlib.h>
#include <boost/filesystem.hpp>

#include "git2.h"
#include "git2/clone.h"

#define fs boost::filesystem

struct Asset::Private {
    const std::string local_path = "https://github.com";
    const std::string git_source = "https://github.com";

    static char CreateLocalPath(std::string username, std::string repository) {
        return (git_source + "/" + username + "/" + repository).c_str();
    }

    static char CreateRepositoryUrl(std::string username, std::string repository) {
        return (git_source + "/" + username + "/" + repository).c_str();
    }
};

void Asset::Clone(std::string username, std::string repository) {
    const git_repository       *clone         = NULL;
    const git_clone_options     clone_opts    = GIT_CLONE_OPTIONS_INIT;
    const git_checkout_options  checkout_opts = GIT_CHECKOUT_OPTIONS_INIT;

    const char repository_url = GetRepositoryUrl(username, repository);

    error = git_clone(&clone, GetRepositoryUrl(username, repository), local_path.c_str(), &clone_opts);
}
/*
 * Clone an asset.
 */
int CloneAsset(string repository_path, string local_path) {
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

/*
 * Retrieve an Asset from the filesystem, and if it doesn't exist clone it.
 */
fs::path GetAsset(fs::path base_path, fs::path repository_path) {
  fs::path asset_path = base_path / repository_path;

  if (!fs::is_directory(asset_path)) {
    CloneAsset(repository_path.string(), asset_path.string());
  }

  return asset_path;
}

