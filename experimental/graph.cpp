#include <nds/encoder/graph.hpp>
#include <nds/graph.hpp>
#include <ngl/cluster.hpp>
#include <ngl/conceptualizer.hpp>
#include <ngl/lang.hpp>
#include <ngl/print.hpp>

namespace nds::encoders
{
    template<> template<>
    inline std::string dot<>::node_name<std::string>(const std::string& v)
    {
        return v;
    }
}

using namespace std::string_literals;

int main()
{
    ngl::cluster cluster{ "cluster", "" };
    auto& g = cluster.graph();

    auto ast = cluster.ast();

    /*
    ngl ngl { concept cluster }
    ngl:concept:integer v

     */

    auto ngl = new ngl::lang::vector_description;
    ngl->descriptor = new ngl::lang::identifier;
    ngl->identifier = new ngl::lang::identifier;
    ngl->descriptor->path.emplace_back(new ngl::lang::parameterized_identifier{ "ngl" });
    ngl->identifier->path.emplace_back(new ngl::lang::parameterized_identifier{ "ngl" });
    ngl->descriptions.emplace_back(new ngl::lang::parameterized_identifier{ "concept" });
    ngl->descriptions.emplace_back(new ngl::lang::parameterized_identifier{ "cluster" });
    ast->descriptions.emplace_back(ngl);

    auto descriptor = new ngl::lang::identifier;
    descriptor->path.emplace_back(new ngl::lang::parameterized_identifier{ "ngl" });
    descriptor->path.emplace_back(new ngl::lang::parameterized_identifier{ "concept" });
    descriptor->path.emplace_back(new ngl::lang::parameterized_identifier{ "integer" });

    auto id = new ngl::lang::identifier;
    id->path.emplace_back(new ngl::lang::parameterized_identifier{ "v" });

    auto sd = new ngl::lang::scalar_description;
    sd->descriptor = descriptor;
    sd->identifier = id;
    ast->descriptions.emplace_back(sd);
/*
    auto nvd = g.add<ngl::lang::description>(std::move(vd), cluster.root());
    auto nsd = g.add<ngl::lang::description>(ngl::lang::scalar_description{}, cluster.root());
    auto nvdsd = g.add<ngl::lang::description>(ngl::lang::scalar_description{}, nvd);*/



    ngl::internal_conceptualizer cc;
    cc.process(cluster);
    std::cout << ngl::to_string(cc.graph());
    //nds::encoders::dot<>::encode<nds::console>(cc.graph());

    return 0;
}