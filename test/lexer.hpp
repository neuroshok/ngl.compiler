#include <gtest/gtest.h>
#include <ngl/parser.hpp>
#include <ngl/lang.hpp>

#define LX_EXPECT(...) EXPECT_TRUE(test_tokens(lx, __VA_ARGS__))

inline bool str_equal(nds::node_ptr<ngl::lang::expression> node, const std::string& value)
{
    return node->str() == value;
}

template<std::size_t... Is, class... Ts>
::testing::AssertionResult has_tokens(const ngl::parser& parser, std::index_sequence<Is...>, Ts&&... ts)
{
    bool match_size = parser.shapes().size() == sizeof...(ts);
    if (!match_size) return ::testing::AssertionFailure() << "input size : " << parser.shapes().size() << " expected size : " << sizeof...(ts) << "\nOutput: " << parser.to_string();

    std::vector<nds::node_ptr<ngl::lang::expression>> v;
    parser.graph().targets(parser.root(), [&](auto&& n) { v.push_back(n); });


    bool match_tokens = ((parser.shape_view(Is) == v[Is]->str()) && ...);
    if (match_tokens) return ::testing::AssertionSuccess();
    else
    {
        return ::testing::AssertionFailure() << "tokens : " << parser.to_string();
    }
}

template<class... Ts>
auto test_tokens(const ngl::parser& parser, Ts&&... ts)
{
    return has_tokens(parser, std::make_index_sequence<sizeof...(Ts)>{}, std::forward<Ts>(ts)...);
}