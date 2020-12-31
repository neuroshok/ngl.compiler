#include "lexer.hpp"

TEST(parser, basic)
{
    ngl::shape_cluster shapes;
    auto letter = shapes.add_element<ngl::shape_range>('a', 'z');
    auto plus = shapes.add_element('+');

    auto add = shapes.add<ngl::shape_sequence>("add", letter, plus, letter);

    /*!
        add
       / | \
     a   +   b
     */
    {
        ngl::lexer lx{ shapes };

        std::string data{ "a+b" };
        lx.process(data);

        std::vector<std::string> v;
        lx.graph().targets(lx.first_node(), [&](auto&& n)
        {
            v.push_back(*n);
        });
        ASSERT_TRUE( lx.graph().count_nodes() == 5 );
        EXPECT_TRUE( *lx.first_node() == "add" );
        EXPECT_TRUE( v[0] == "a" );
        EXPECT_TRUE( v[1] == "+" );
        EXPECT_TRUE( v[2] == "b" );
    }
}