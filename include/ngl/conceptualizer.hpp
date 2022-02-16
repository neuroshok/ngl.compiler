#ifndef COMPILER_INCLUDE_NGL_CONCEPTUALIZER_HPP_NGL
#define COMPILER_INCLUDE_NGL_CONCEPTUALIZER_HPP_NGL

#include <ngl/cluster.hpp>
#include <ngl/lang.hpp>
#include <ngl/program_graph.hpp>

namespace ngl
{
    class conceptualizer
    {
    public:
        conceptualizer() = default;
        virtual ~conceptualizer() = default;
        virtual void process(ngl::cluster&) = 0;
        virtual void process(ngl::lang::identifier*) = 0;
        virtual void process(ngl::lang::parameterized_identifier*) = 0;
        virtual void process(ngl::lang::root_description*) = 0;
        virtual void process(ngl::lang::scalar_description*) = 0;
        virtual void process(ngl::lang::vector_description*) = 0;
    };
    
    class internal_conceptualizer : public conceptualizer
    {
    public:
        internal_conceptualizer() = default;

        void process(ngl::lang::identifier* d)
        {
            if (!d->path.empty()) std::cout << "\n- id " << d->first()->name;
        }

        void process(ngl::lang::parameterized_identifier* d)
        {
            std::cout << "\n- parameterized_identifier " << d->name;

            for (const auto& parameter : d->parameters)
            {
                parameter->process(this);
            }
        }

        void process(ngl::lang::scalar_description* d)
        {
            std::cout << "\n- scalar_description";
            d->identifier->process(this);
            d->descriptor->process(this);

            auto descriptor = d->descriptor->last()->name;
            std::cout << "\n- descriptor " << d->descriptor->last()->name;

            nc::nconcept* c = graph_.nconcept(d->descriptor);
            std::cout << "\nname : " << c->name;



            //std::vector<identifier, identifier, identifier

            if (d->descriptor->last()->name == "concept")
            {
                // get the intrinsic for specific concept
                // concretize["ngl:concept:add"] == ngi:add == ngl:intrinsic:add
                // concretize["ngl:concept:integer"] == ngi:integer == ngl:intrinsic:integer
            }
            //Instruction* Add = BinaryOperator::Create(Instruction::Add, Two, Three, "addresult");
        }

        void process(ngl::lang::root_description* root)
        {
            std::cout << "\n- root";

            for (const auto& description : root->descriptions)
            {
                description->process(this);
            }
        }
        void process(ngl::lang::vector_description* d)
        {
            std::cout << "\n- vector_description";
            auto descriptor = d->descriptor->first()->name;
            auto identifier = d->identifier->first()->name;
            std::cout << "\n_" << d->descriptor->first()->name;
            std::cout << "\n_" << d->identifier->first()->name;
            if (descriptor == identifier && d->descriptor->path.size() == 1)
            {
                auto e = new nc::entity{ descriptor };
                graph_.entities.push_back(e);
                auto c = new nc::nconcept{ "concept" };
                c->concepts.push_back(new nc::nconcept{ "integer" });
                e->concepts.push_back(c);
                e->concepts.push_back(new nc::nconcept{ "cluster" });
            }


            for (const auto& description : d->descriptions)
            {
                description->process(this);
            }
        }

        void process(ngl::cluster& cluster) override
        {
            std::cout << "\nconceptualizer process: " ;
            try
            {
                cluster.ast()->process(this);
            } catch (const std::exception& e) { std::cout << "\ncompiler error " << e.what(); }
        }

        [[nodiscard]] nc::program_graph& graph() { return graph_; }

    private:
        nc::program_graph graph_;
    };
} // ngl

#endif // COMPILER_INCLUDE_NGL_CONCEPTUALIZER_HPP_NGL