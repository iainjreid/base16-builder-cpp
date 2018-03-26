#ifndef BASE16_BUILDER_ASSETS_H
#define BASE16_BUILDER_ASSETS_H

#include <string>
#include <boost/filesystem.hpp>

#define fs boost::filesystem

namespace Assets {
  std::string local_path;
  std::string git_source;

  void Clone(std::string, std::string);
  fs::path Retrieve(fs::path, fs::path);
};

#endif //BASE16_BUILDER_ASSETS_H
