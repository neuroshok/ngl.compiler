#ifndef INCLUDE_NGL_PARSER_HPP_NC
#define INCLUDE_NGL_PARSER_HPP_NC

#include <ngl/graph.hpp>
#include <ngl/shape_cluster.hpp>

#include <string>
#include <vector>
#include <cstdint>

namespace ngl
{
    struct location
    {
        size_t origin;
        size_t size;
    };

    struct shape
    {
        uint64_t id{};
        std::string name;
        ngl::location location{};
    };

    class parser
    {
    public:
        using element_type = char;

        explicit parser() = default;
        explicit parser(ngl::shape_cluster);

        void process();
        void process(std::string_view);
        void process(const char*) = delete;

        void add(ngl::shape_cluster&);
        void add_shape(uint64_t shape_id, const std::string& name, ngl::location);

        [[nodiscard]] const ngl::graph& graph() const { return graph_; }
        [[nodiscard]] const ngl::node& root() const;
        [[nodiscard]] const std::vector<shape>& shapes() const;
        [[nodiscard]] std::string_view shape_view(int index) const;

        [[nodiscard]] std::string to_string(const shape&) const;
        [[nodiscard]] std::string to_string() const;

    private:
        std::string_view data_;
        std::vector<ngl::shape_cluster> shape_clusters_;
        std::vector<ngl::shape> shapes_;

        ngl::graph graph_;
        ngl::node root_;
    };
} // ngl

#endif // INCLUDE_NGL_PARSER_HPP_NC