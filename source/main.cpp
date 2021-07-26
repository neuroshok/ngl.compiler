#include <ngl/cli.hpp>

int main(int argc, const char* argv[])
{
    ngl::compiler compiler;
    ngl::cli cli{ argv[0], compiler };
    nc_commands commands{ cli };

    cli.process(argc, argv);

    return 0;
}