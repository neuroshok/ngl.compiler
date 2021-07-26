#ifndef COMPILER_INCLUDE_NGL_CLI_HPP_NGL
#define COMPILER_INCLUDE_NGL_CLI_HPP_NGL

#include <ngl/compiler.hpp>

#include <ngl/compiler.hpp>
#include <ncs/ncs.hpp>

namespace ngl
{
    struct cli : public ncs::basic_cli<cli>
    {
        cli(std::string module_name, ngl::compiler& c) : ncs::basic_cli<cli>(std::move(module_name)), compiler{ c } {}

        ngl::compiler& compiler;
    };
} // ngl

ncs_root(nc_commands, ngl::cli)
    ncs_command(ncs_module)
        ncs_required(path, std::string, "File or folder path to build")
        ncs_flag(g, "Display program graph")
    ncs_command_(ncs_module, [this](auto&& input){ std::cout << input[ncs_module.path]; }, "")

    ncsi::command help{ this, "help", [this]{ cli.help(); }, "Display this help" };
    ncsi::command version{ this, "version", [this]{ std::cout << cli.compiler.version(); }, "Display compiler version" };

    ncs_command(build)
        ncs_flag(g, "Display program graph")
    ncs_command_(build, [this](auto&& input){ std::cout << "Build " << input[build.g]; }, "Build a file or a project")

    ncs_command(edge)
        ncs_required(source, std::string, "Source")
        ncs_required(target, std::string, "Target")
    ncs_command_(edge, [this](auto&& input){ std::cout << "Add edge"; }, "Add an edge between source and target")

    ncs_node(entity)
        ncs_command(add)
        ncs_command_(add, [this](auto&& input){ std::cout << "Add entity"; }, "Add a new entity")
    ncs_node_(entity)

    ncs_node(project)
        ncs_command(add)
            ncs_required(name, std::string, "Project name")
            ncs_optional(shape, std::string, "ngl", "Project concept to use")
        ncs_command_(add, [this](auto&& input){ cli.compiler.process("test"); }, "Add a new project")

        ncs_command(del)
            ncs_required(name, std::string, "Project name")
        ncs_command_(del, [this](auto&& input){ std::cout << "delete project"; }, "Delete a project")
    ncs_node_(project)
ncs_root_()

#endif // COMPILER_INCLUDE_NGL_CLI_HPP_NGL
