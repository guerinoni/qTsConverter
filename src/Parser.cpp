#include "Parser.hpp"

Parser::Parser(InOutParameter &&parameter) :
    m_ioParameter{ std::move(parameter) }
{
}
