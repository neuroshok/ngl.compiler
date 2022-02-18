#include <nds/graph.hpp>
#include <ngl/cluster.hpp>
#include <ngl/lexer.hpp>
#include <ngl/shape_cluster.hpp>

using namespace std::string_literals;

int main()
{
    try
    {
        ngl::shape_cluster shapes;
        auto A = shapes.add_element('a');
        auto B = shapes.add_element('b');
        auto underscore = shapes.add_element('_');

        auto subshape = shapes.add<ngl::shape_sequence>("subshape", A, underscore);
        auto shape = shapes.add<ngl::shape_sequence>("shape", subshape, B);

        ngl::lexer lx{ shapes };

        std::string data{ "a_b" };
        lx.process(data);

        std::vector<std::decay_t<decltype(lx.root().get()->get())>> v;
        lx.graph().targets(lx.root(), [&](auto&& n) { v.push_back(*n); });

        std::cout << "\n" << lx.to_string();

    } catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}