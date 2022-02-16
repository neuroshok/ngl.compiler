#include <ngl/lang.hpp>

#include <ngl/conceptualizer.hpp>

namespace ngl::lang
{
    void identifier::process(ngl::conceptualizer* cc) { cc->process(this); }
    void parameterized_identifier::process(ngl::conceptualizer* cc) { cc->process(this); }
    void root_description::process(ngl::conceptualizer* cc) { cc->process(this); }
    void scalar_description::process(ngl::conceptualizer* cc) { cc->process(this); }
    void vector_description::process(ngl::conceptualizer* cc) { cc->process(this); }
} // ngl:lang