#ifndef INCLUDE_NGL_PROGRAM_GRAPH_HPP_NC
#define INCLUDE_NGL_PROGRAM_GRAPH_HPP_NC

#include <vector>
#include <vector>

namespace nc
{
    struct node
    {
    };

    struct nconcept
    {
        std::string name;
        std::vector<nconcept*> concepts;
    };

    struct entity
    {
        std::string name;
        std::vector<nc::nconcept*> concepts;
    };

    struct program_graph
    {
        nc::entity* entity(const std::string& name)
        {
            auto it = std::find_if(entities.begin(), entities.end(), [&name](const auto& e) { return e->name == name; });
            if (it != entities.end()) return *it;
            else return nullptr;
        }

        //! get the entity concept from an identifier
        nc::nconcept* nconcept(ngl::lang::identifier* id)
        {
            if (!id->path.empty())
            {
                // get the entity
                auto e = entity(id->path[0]->name);
                if (!e) return nullptr;

                auto searching_concepts = e->concepts;
                decltype(searching_concepts)::iterator it;
                for (int i = 1; i < id->path.size(); ++i)
                {
                    auto nested_id = id->path[i];
                    it = std::find_if(searching_concepts.begin(), searching_concepts.end(), [&nested_id](const auto& item) { return item->name == nested_id->name; });
                    if (it == searching_concepts.end())
                    {
                        throw std::logic_error("concept does not exist: " + id->last()->name);
                    }
                    else searching_concepts = (*it)->concepts;
                }
                return *it;
            }
            return nullptr;
        }

        std::vector<nc::entity*> entities;
    };
} // ngl

#endif // INCLUDE_NGL_PROGRAM_GRAPH_HPP_NC