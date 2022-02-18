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
        ngl::parser lx{ shapes };

        std::string data{ "a+b" };
        lx.process(data);

        std::vector<nds::node_ptr<ngl::lang::expression>> v;
        lx.graph().targets(lx.root(), [&](auto&& n)
        {
            v.push_back(n);
        });
        ASSERT_TRUE( lx.graph().count_nodes() == 5 );
        EXPECT_TRUE( str_equal(lx.root(), "add") );
        EXPECT_TRUE( str_equal(v[0], "a") );
        EXPECT_TRUE( str_equal(v[1], "+") );
        EXPECT_TRUE( str_equal(v[2], "b") );
    }
}

TEST(parser, subshape)
{
    ngl::shape_cluster shapes;
    auto A = shapes.add_element('a');
    auto B = shapes.add_element('b');
    auto underscore = shapes.add_element('_');

    auto subshape = shapes.add<ngl::shape_sequence>("subshape", A, underscore);
    auto shape = shapes.add<ngl::shape_sequence>("shape", subshape, B);

    /*!
          shape
         |     \
      subshape  B
         | \
        A   _
     */
    {
        ngl::parser lx{ shapes };

        std::string data{ "a_b" };
        lx.process(data);

        std::vector<nds::node_ptr<ngl::lang::expression>> v;
        lx.graph().targets(lx.root(), [&](auto&& n)
        {
            v.push_back(n);
        });
        ASSERT_TRUE( lx.graph().count_nodes() == 5 );
        EXPECT_TRUE( str_equal(lx.root(), "add"));
        EXPECT_TRUE( str_equal(v[0], "a") );
        EXPECT_TRUE( str_equal(v[1], "+") );
        EXPECT_TRUE( str_equal(v[2], "b") );
    }
}