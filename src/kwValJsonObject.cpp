#include <kw/kwValJsonObject.h>


kwValJsonObject::kwValJsonObject()
{
}


kwValJsonObject::kwValJsonObject(json val)
{
    m_Value = val;
}


kwValJsonObject::~kwValJsonObject()
{
}


json kwValJsonObject::getValue()
{
    return m_Value;
}


std::ostream& operator<< (std::ostream& stream, const kwValJsonObject& _valbool)
{
    stream << (_valbool.m_Value.dump());
    return stream;
}


kwValString kwValJsonObject::asString()
{
    return kwValString(m_Value.dump());
}


json kwValJsonObject::toJson()
{
    return m_Value;
}
