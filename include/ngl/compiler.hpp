#ifndef COMPILER_INCLUDE_NGL_COMPILER_HPP_NGL
#define COMPILER_INCLUDE_NGL_COMPILER_HPP_NGL

#include <ngl/conceptualizer.hpp>
#include <ngl/graph.hpp>

#include <llvm/Support/CommandLine.h>

#include <bitset>
#include <string>
#include <unordered_map>

#include <nds/encoder/graph.hpp>

namespace nds::encoders
{
    template<> template<>
    inline std::string dot<>::node_name<std::string>(const std::string& v)
    {
        return v;
    }
}

namespace ngl
{
    class compiler
    {
    public:
        enum class flags { none = 0, debug, graph, nongl, trace };
        enum class params { output };

        compiler();

        void init();

        void add_flag(flags);
        void set_flags(unsigned int);
        bool has_flag(flags flag);

        void add_param(params, std::string value);

        void process(std::string file_path);
        void error(const std::string&);

        void set_file(std::string);

        [[nodiscard]] std::string_view version() const;

    private:
        std::string file_path_;
        std::bitset<64> flags_;
        std::unordered_map<params, std::string> params_;

        std::unique_ptr<ngl::conceptualizer> conceptualizer_;
    };
} // ngl

#endif // COMPILER_INCLUDE_NGL_COMPILER_HPP_NGL