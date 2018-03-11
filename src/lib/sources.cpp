#include <yaml-cpp/yaml.h>

#include "sources.h"

struct Sources::Private {
    static YAML::Node scheme_sources, template_sources;

    static bool Validate(const std::string source_name, const YAML::Node sources_map) {
        return sources_map[source_name].as<bool>(false);
    }
};

void Sources::LoadSchemes(const std::string sources_path) {
    Private::scheme_sources = YAML::LoadFile(sources_path);
}

void Sources::LoadTemplates(const std::string sources_path) {
    Private::template_sources = YAML::LoadFile(sources_path);
}

bool Sources::ValidateScheme(const std::string scheme_name) {
    return Private::Validate(scheme_name, Private::scheme_sources);
}

bool Sources::ValidateTemplate(const std::string template_name) {
    return Private::Validate(template_name, Private::template_sources);
}
