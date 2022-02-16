#ifndef COMPILER_INCLUDE_NGL_GRAPH_HPP_NGL
#define COMPILER_INCLUDE_NGL_GRAPH_HPP_NGL

#include <nds/graph.hpp>

#include <string>

namespace ngl
{
    namespace lang
    {
        struct expression;
    } // lang
    struct edges
    {
        struct has{int id = 8;};
        struct is{int id = 9; std::string truc; };
    };

    using Nodes = nds::graph_nodes<ngl::lang::expression>;
    using Edges = nds::graph_edges<edges::is, edges::has>;

    using graph = nds::graph<Nodes, Edges>;

    template<class T>
    using node_ptr = nds::node_ptr<T>;

    using node = nds::node_ptr<ngl::lang::expression>;
} // ngl

#endif // COMPILER_INCLUDE_NGL_GRAPH_HPP_NGL