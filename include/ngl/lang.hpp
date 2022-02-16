#ifndef COMPILER_INCLUDE_NGL_LANG_HPP_NGL
#define COMPILER_INCLUDE_NGL_LANG_HPP_NGL

#include <ngl/graph.hpp>

#include <vector>
#include <iostream>
namespace ngl 
{
    class conceptualizer;
} // ngl
namespace ngl::lang
{
    struct expression
    {
        virtual void process(ngl::conceptualizer* cc) {   };
    };

    struct parameterized_identifier;

    struct identifier : expression
    {
        auto* first() { return path.front(); }
        auto* last() { return path.back(); }
        std::vector<parameterized_identifier*> path;

        void process(ngl::conceptualizer* cc) override;
    };

    struct parameterized_identifier : expression
    {
        std::string name;
        std::vector<expression*> parameters;

        explicit parameterized_identifier(std::string name_) : name{ std::move(name_) } {}

        void process(ngl::conceptualizer* cc) override;
    };

    struct root_description : expression
    {
        std::vector<lang::expression*> descriptions;

        void process(ngl::conceptualizer* cc) override;
    };

    struct scalar_description : expression
    {
        lang::identifier* descriptor{};
        lang::identifier* identifier{};

        void process(ngl::conceptualizer* cc) override;
    };

    struct vector_description : expression
    {
        lang::identifier* descriptor{};
        lang::identifier* identifier{};
        std::vector<lang::expression*> descriptions;

        vector_description() = default;
        void process(ngl::conceptualizer* cc) override;
    };

} // ngl

#endif // COMPILER_INCLUDE_NGL_LANG_HPP_NGL