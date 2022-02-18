#include <ngl/parser.hpp>
#include <ngl/shape_cluster.hpp>

#include <ngl/lang.hpp>
#include <nds/encoder/graph.hpp>

namespace nds::encoders
{
    template<> template<>
    inline std::string dot<>::node_name<ngl::lang::expression>(const ngl::lang::expression& v)
    {
        return v.str();
    }
}

int main()
{
    try
    {
        //ngl::lexer lx{ ngl::get_shape_cluster() };
        ngl::shape_cluster shapes;

        auto space = shapes.add_element<ngl::shape_space>(' ');

        auto letter = shapes.add_fragment<ngl::shape_range>('a', 'z');
        auto digit = shapes.add_fragment<ngl::shape_range>('0', '9');
        auto ob = shapes.add_fragment<ngl::shape_element>('{');
        auto cb = shapes.add_fragment<ngl::shape_element>('}');

        auto S = shapes.add_fragment<ngl::shape_element>('s');
        auto T = shapes.add_fragment<ngl::shape_element>('t');
        auto R = shapes.add_fragment<ngl::shape_element>('r');
        auto U = shapes.add_fragment<ngl::shape_element>('u');
        auto C = shapes.add_fragment<ngl::shape_element>('c');
        auto structt = shapes.add_element<ngl::shape_sequence>(S, T, R, U, C, T);

        auto colon = shapes.add_element(':');
        auto underscore = shapes.add_element('_');
        auto identifier_symbol = shapes.add_fragment<ngl::shape_or>(letter, digit);
        //auto many_identifier_symbol = shapes.add_fragment<ngl::shape_many>(identifier_symbol);

        auto many = shapes.add_fragment<ngl::shape_many>("many", letter);


        //auto raw_identifier = shapes.add<ngl::shape_sequence>("raw_identifier", letter, digit);
        auto raw_identifier2 = shapes.add<ngl::shape_sequence>("struct", ob, many, cb);
        //auto path_edge = shapes.add<ngl::shape_sequence>("id_edge_path", colon, raw_identifier);

        //auto path_identifier = shapes.add<ngl::shape_sequence>("path_identifier", raw_identifier, path_edge);

        //auto SD = shapes.add<ngl::shape_sequence>("SD", path_identifier, space, raw_identifier);

//       auto VD = shapes.add_parser(ngl::shape_sequence(raw_identifier, space, raw_identifier, ob, cb), "VD");

        //auto g = shapes.add(ngl::shape_or(SD, VD), "SD");

        // TEST
        // multiple rule true at same time
        // down rules
        // up rules
/*
        auto letter = shapes.add_fragment<ngl::shape_range>("letter", 'a', 'z');
        auto raw_id = shapes.add_element<ngl::shape_sequence>("raw_id", letter, id_symbol);
        shapes.add<ngl::shape_sequence>("name", raw_id, raw_id);
        shapes.add<ngl::shape_sequence>("add", raw_id, ngl::shape_ignore(plus), raw_id);*/

        /*
        P000000000000101000000000
        0000000000000100000000000 path_ident
        0000000000000001000000000 raw_ident

        path_id raw_id
        path_id id_edge
        path_id id_edge raw_id
*/

        shapes.display();

        ngl::parser parser{ shapes };

        /*
        std::string data = R"(
        ngl:shape scalar_description
        {
            ngc:sequence<ngs:identifier ngs:raw_identifier>
        }
        )";*/

        std::string data = "_{aa{aa}_";

        parser.process(data);

        std::cout << "\n";
        nds::encoders::dot<>::encode<nds::console>(parser.graph());
    }
    catch (const std::exception& e)
    {
        std::cout << e.what();
    }

    return 0;
}

/*
     SD
     |     \
    PID     RID
 /   |   \
RID EDGE RID

 ngl:concept zeta
     |        \
ngl:concept     zeta
 /   |   \
ngl  :   concept

1000 SD
1100 PID
1110 PID RID
1101 PID EDGE
1110 PID RID
1010 RID


 */

/*
L, NB, L
n 0001 I0 S M1 I++
0 0010 I1 V M1
0 0010 I1 V M1
n 0001 I1 V M0
                I++ I2 S M1*/