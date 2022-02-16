#include <ngl/cluster.hpp>

#include <ngl/shape_cluster.hpp>
#include <ngl/log.hpp>
#include <ngl/lang.hpp>
#include <nds/encoder/graph.hpp>

namespace ngl
{
    cluster::cluster(std::string name, std::string source)
        : name_{ std::move(name) }
        , source_{ std::move(source) }
        , graph_{}
        , ast_{ new ngl::lang::root_description }
        , lexer_{ ngl::get_shape_cluster() }
        , root_{}
    {
        root_ = graph_.add<ngl::lang::expression>(ngl::lang::root_description{});
        node_ = root_;
    }

    void cluster::process()
    {
        ngl_info("Process cluster {}", name_);
        lexer_.process();
    }

    ngl::graph& cluster::graph()
    {
        return graph_;
    }


    ngl::node cluster::root()
    {
        return root_;
    }



    ngl::node cluster::node()
    {
        return node_;
    }
} // ngl