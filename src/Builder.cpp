#include "Builder.hpp"

Builder::Builder(InOutParameter parameter) :
    m_ioParameter{ std::move(parameter) }
{
}
