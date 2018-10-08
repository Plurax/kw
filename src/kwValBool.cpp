#include <kw/kwValBool.h>

kwValBool::kwValBool()
{
    m_Value = false;
}


kwValBool::kwValBool(bool p_value)
{
    m_Value = p_value;
}


kwValBool::~kwValBool()
{
}


bool kwValBool::getValue()
{
    return m_Value;
}


std::ostream& operator<< (std::ostream& stream, const kwValBool& _valbool)
{
    stream << (_valbool.m_Value);

    return stream;
}


kwValString kwValBool::asString()
{
    if (m_Value)
        return kwValString("true");
    else
        return kwValString("false");
}


json kwValBool::toJson()
{
    json j = m_Value;
    return j;
}
