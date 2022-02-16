#ifndef INCLUDE_NGL_CONCRETIZER_LLVM_HPP_NC
#define INCLUDE_NGL_CONCRETIZER_LLVM_HPP_NC

#include <ngl/concretizer.hpp>
#include <ngl/cluster.hpp>
#include <ngl/lang.hpp>
#include <ngl/program_graph.hpp>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

namespace ngl
{
    struct nconcept
    {
        std::vector<nconcept*> concepts;
    };

    struct nc_entity
    {
        std::vector<nconcept> concepts;
    };

    using namespace llvm;

    class llvm_concretizer : public concretizer
    {
    public:
        llvm_concretizer()
            : builder_{ context_ }
            , module_{ std::make_unique<Module>("test", context_) }
        {}



    private:
        ngl::cluster* cluster_ = nullptr;
        nc::program_graph graph_;

        LLVMContext context_;
        IRBuilder<> builder_;
        std::unique_ptr<Module> module_;
    };
} // ngl

#endif // INCLUDE_NGL_CONCRETIZER_LLVM_HPP_NC