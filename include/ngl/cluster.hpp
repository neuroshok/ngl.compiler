#ifndef COMPILER_INCLUDE_NGL_CLUSTER_HPP_NGL
#define COMPILER_INCLUDE_NGL_CLUSTER_HPP_NGL

#include <ngl/lexer.hpp>
#include <ngl/graph.hpp>
#include <ngl/lang.hpp>

namespace ngl
{
    class cluster
    {
    public:
        cluster(std::string name, std::string source);

        void process();

        ngl::lang::root_description* ast() { return ast_; }

        ngl::graph& graph();
        ngl::node root();
        ngl::node node();

    private:
        std::string name_;
        std::string source_;
        ngl::graph graph_;
        ngl::lexer lexer_;
        ngl::node root_;
        ngl::node node_;
        ngl::lang::root_description* ast_ = nullptr;
    };
} // ngl

#endif // COMPILER_INCLUDE_NGL_CLUSTER_HPP_NGL