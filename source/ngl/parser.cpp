#include <ngl/parser.hpp>

#include <ngl/lang.hpp>

#include <bitset>
#include "ngl/log.hpp"

namespace ngl
{
    parser::parser(ngl::shape_cluster shape_cluster)
    {
        shape_clusters_.emplace_back(std::move(shape_cluster));
        root_ = graph_.add<ngl::lang::expression>(ngl::lang::root_description{});
    }

    void parser::process(std::string_view data)
    {
        data_ = data;
        process();
    }

    void parser::process()
    {
        ngl::node current_ = root_;

        uint64_t vector_iterator = 0;
        std::bitset<64> shape_state;
        std::bitset<64> scalar_state;
        std::bitset<64> vector_state;
        std::bitset<64> testing_state;

        shapes_.clear();
        shapes_.reserve(data_.size());

        if (shape_clusters_.empty()) ngl_error("Parser requires at least 1 shape_cluster");
        auto& shape_cluster = shape_clusters_[0];
        auto& shape_data = shape_cluster.datas();

        for (int i = 0; i < data_.size(); ++i)
        {
            std::string debug;
            shape_state.reset();
            testing_state.reset();
            const auto& element = data_[i];

            std::cout << "\n" << element;

            for (size_t shape_it = 0; shape_it < shape_data.size(); ++shape_it)
            {
                auto& shape = shape_data[shape_it];
                bool match = false;

                 //std::cout << "\n" << shape_it << " " << shape_data[shape_it].name << " ";

                switch (static_cast<ngl::shape_type>(shape.type))
                {
                    case shape_type::space:

                        break;

                    case shape_type::scalar_element:
                        match = (element == shape.data);
                        shape_state[shape.index] = match;
                        vector_state = 0;

                        break;

                    case shape_type::scalar_range:
                        match = (element >= (shape.data >> 8u) && element <= ((shape.data << 56u) >> 56u));
                        shape_state[shape.index] = match;

                        break;

                    case shape_type::logical_or:
                        match = shape_state.to_ullong() & shape.data;
                        shape_state[shape.index] = match;

                        break;
                    case shape_type::logical_not:
                        match = !(shape_state.to_ullong() & shape.data);
                        shape_state[shape.index] = match;

                        break;

                    case shape_type::vector_many:
                        match = shape_state[shape.data];
                        shape_state[shape.index] = match;
                        vector_state[shape.index] = match;

                        break;

                    case shape_type::vector_sequence: {
                        auto sequence_shapes = shape_cluster.vector_data(shape.data);
                        bool try_next = false;
                        bool try_reset = false;

                        start_sequence:

                        // sequence end with all shapes matching
                        if (shape.vector_index == sequence_shapes.size())
                        {
                            debug = " END";
                            shape.vector_index = 0;
                            continue;
                        }

                        ngl_assert(shape.vector_index < sequence_shapes.size());

                        auto current_shape_id = sequence_shapes[shape.vector_index];
                        bool current_match = shape_state.to_ullong() & current_shape_id;

                        shape_state[shape.index] = current_match;
                        //vector_state[shape.index] = current_match;
                        testing_state[shape.index] = current_match;

                        // current sequence doesn't match anymore, advance to next
                        if (!current_match)
                        {
                            if (try_reset) continue;

                            // try next shape in sequence failed, try reset
                            if (try_next)
                            {
                                shape.vector_index = 0;
                                try_reset = true;
                                goto start_sequence;
                            }

                            // reset sequence with next shape
                            ++shape.vector_index;
                            try_next = true;
                            goto start_sequence;
                        }

                        break;
                    }
                }
            }
            std::cout << " | S_" << std::bitset<24>{ shape_state.to_ullong() };
            std::cout << " | V_" << std::bitset<24>{ vector_state.to_ullong() };
            std::cout << " | T_" << std::bitset<24>{ testing_state.to_ullong() };
            std::cout << debug;
        }
    }

    void parser::add(ngl::shape_cluster& shape_cluster)
    {
        shape_clusters_.emplace_back(shape_cluster);
    }

    void parser::add_shape(uint64_t shape_id, const std::string& name, ngl::location location)
    {
        ngl::shape shape;
        shape.id = shape_id;
        shape.name = name;
        shape.location = location;
        shapes_.emplace_back(std::move(shape));
        //parse();
    }

    const ngl::node& parser::root() const { return root_; }
    const std::vector<shape>& parser::shapes() const { return shapes_; }

    std::string_view parser::shape_view(int index) const
    {
        return data_.substr(shapes_[index].location.origin, shapes_[index].location.size);
    }

    std::string parser::to_string(const shape& shape) const
    {
        //std::string str = shape.name + "(" + std::string(data_.substr(shape.location.origin, shape.location.size)) + ")";
        std::string str = std::string(data_.substr(shape.location.origin, shape.location.size));

        return str;
    }
    std::string parser::to_string() const
    {
        std::string str;

        for (const auto& shape : shapes_)
        {
            str += to_string(shape) + " ";
        }
        return str;
    }
} // ngl