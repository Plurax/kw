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

bool kwValBool::operator== (const kwValBool &right) const
{
	return this->m_Value == right.m_Value;
}


kwValString kwValBool::asString() const
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
