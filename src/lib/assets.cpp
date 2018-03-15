#include <stdlib.h>
#include <boost/filesystem.hpp>

#include "git2.h"
#include "git2/clone.h"
#include "error.h"

#define fs boost::filesystem

struct Asset::Private {
    const std::string local_path = getenv("HOME");;
    const std::string git_source = "https://github.com";

    static char CreateLocalPath(std::string username, std::string repository) {
        return (local_path + "/" + username + "/" + repository).c_str();
    }

    static char CreateRepositoryUrl(std::string username, std::string repository) {
        return (git_source + "/" + username + "/" + repository).c_str();
    }
};

void Asset::Clone(std::string username, std::string repository) {
    const git_repository       *clone         = NULL;
    const git_clone_options     clone_opts    = GIT_CLONE_OPTIONS_INIT;
    const git_checkout_options  checkout_opts = GIT_CHECKOUT_OPTIONS_INIT;

    const char local_path     = CreateLocalPath(username, repository)
    const char repository_url = CreateRepositoryUrl(username, repository);

    int error = git_clone(&clone, repository_url, local_path, &clone_opts);

    if (error != 0) {
        (new Error(1, "Git error"))->Fatal();
    }

    git_repository_free(clone);
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

