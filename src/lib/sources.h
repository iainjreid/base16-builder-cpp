#ifndef BASE16_BUILDER_SOURCES_H
#define BASE16_BUILDER_SOURCES_H

#include <string>
#include <yaml-cpp/node/node.h>

class Sources {
private:
    struct Private;
    YAML::Node scheme_sources, template_sources;

public:
    void LoadSchemes(std::string);

    void LoadTemplates(std::string);

    bool ValidateScheme(std::string);

    bool ValidateTemplate(std::string);
};

#endif //BASE16_BUILDER_SOURCES_H
