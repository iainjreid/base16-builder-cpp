#ifndef BASE16_BUILDER_ASSETS_H
#define BASE16_BUILDER_ASSETS_H

#include <string>

class Assets {
private:
    struct Private;
    std::string git_source;

public:
    void Clone(std::string, std::string);
};

#endif //BASE16_BUILDER_ASSETS_H
