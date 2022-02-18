#include <ngl/shape.hpp>

#include <ngl/shape_cluster.hpp>

namespace ngl
{
    std::string shape_name(const ngl::shape_cluster& shape_cluster, uint64_t parser_state, uint64_t match_state)
    {
        std::string name;
        auto shape_id = parser_state & (~parser_state << 1u);
        if (bit_count(shape_id) > 1) name = "shape";
        else if (parser_state != 0) name = shape_cluster.name_of(shape_id);
        else name = "element"; //shape_cluster.name_of(match_state);
        return name;
    }
} // ngl