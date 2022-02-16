#ifndef INCLUDE_NGL_PRINT_HPP_NC
#define INCLUDE_NGL_PRINT_HPP_NC

#include <ngl/program_graph.hpp>

namespace ngl
{
    std::string to_string(const nc::program_graph& graph)
    {
        std::string out;
        out += "\n######## program_graph ########";
        for (const auto& entity : graph.entities)
        {
            out += "\n# Entity " + entity->name;

            std::function<void(decltype(entity->concepts))> display;
            int level = 0;
            display = [&](auto&& concepts)
            {
                ++level;
                for (const auto& nconcept : concepts)
                {
                     out += "\n";
                    for (int i = 0; i < level - 1; ++i) out += "  ";
                    out += "- " + nconcept->name;
                    display(nconcept->concepts);
                    --level;
                }
            };

            out += "\n# Concepts";
            display(entity->concepts);
        }
        return out;
    }
} // ngl

#endif // INCLUDE_NGL_PRINT_HPP_NC