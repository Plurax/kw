/*
 * kwValFixedPoint.cpp
 *
 *  Created on: 13.11.2013
 *      Author: chuhlich
 */

#include "kwDebug.h"
#include "kwValFixedPoint.h"
#include <string>
#include <cstring>

const short kwValFixedPoint::precN[7] = { 2, 4, 6, 8, 10, 12};
const long long kwValFixedPoint::precNScalings[7] = { 100, 10000, 1000000, 100000000, 10000000000, 1000000000000};


kwValFixedPoint::kwValFixedPoint()
{
	m_isEmpty = true;
	m_Precision = enumValFixedPointPrec::prec11N6;
	m_lValue = 0;
}


kwValFixedPoint::~kwValFixedPoint()
{
}

/**
 * This constructor can be used to initialize ValFixedPoint by using a string from an XML
 * The String should note the precision - otherwise the default prec11N6 is taken as in empty constructor.
 * To avoid confusion, the dot is ignored!
 * @param _string
 */
kwValFixedPoint::kwValFixedPoint(kwValString _string)
{
	char* tmpBuffer = new char[50]; // should be enough
	const char* c_str = _string.c_str();
	strncpy(tmpBuffer, c_str, 49);
	LOG_TRACE << "Got raw string " << tmpBuffer;

	char* ptr = strchr(tmpBuffer, '.');

	if (ptr != NULL)
	{
		while ((isdigit(*(ptr+1))) && (*ptr != '\0'))
		{
			*ptr = *(ptr+1);
			ptr++;
		}
		*ptr = '\0'; // terminate number string
		ptr++;
	}

	LOG_TRACE << "mod string " << tmpBuffer;
	sscanf(tmpBuffer, "%ld", &m_lValue);

	m_Precision = enumValFixedPointPrec::prec11N6;

	if (*ptr == ' ') // skip space
		ptr++;
 	if (strlen(ptr) > 0)
		m_Precision = getPrecisionFromString(ptr);
	m_isEmpty = false;
	delete[] tmpBuffer;
}

kwValFixedPoint::kwValFixedPoint(enumValFixedPointPrec prec)
{
	m_isEmpty = true;
	m_Precision = prec;
}

kwValFixedPoint::kwValFixedPoint(long in, enumValFixedPointPrec prec)
{
	m_lValue = in;
	m_Precision = prec;
	m_isEmpty = false;
}

std::string kwValFixedPoint::asString() const
{
	int i;
	char tmp[21] = "";
	
	if (m_isEmpty)
	{
		return kwValString("unset Object kwValFixedPoint!");
	}

	snprintf(tmp, 20, "%ld", m_lValue);

	int len = strlen(tmp);
	for (i = len; i > (len - precN[ static_cast<int>(m_Precision)]); i--)
	{
		tmp[i]=tmp[i-1];
	}
	tmp[i] = '.';

	return std::string(tmp);
}

bool kwValFixedPoint::operator >= (const kwValFixedPoint right)
{
	if (this->m_Precision == right.m_Precision)
	{
		return this->m_lValue >= right.m_lValue;
	}
	return false;
}

bool kwValFixedPoint::operator > (const kwValFixedPoint right)
{
	return m_lValue > right.m_lValue;
}

bool kwValFixedPoint::operator <= (const kwValFixedPoint right)
{
	return m_lValue <= right.m_lValue;
}

bool kwValFixedPoint::operator < (const kwValFixedPoint right)
{
	return m_lValue < right.m_lValue;
}

kwValFixedPoint& kwValFixedPoint::operator = (kwValFixedPoint const& right)
{
	if (this != &right)
	{
		this->m_isEmpty = right.m_isEmpty;
		this->m_lValue = right.m_lValue;
		this->m_Precision = right.m_Precision;
	}
	return *this;
}

kwValFixedPoint kwValFixedPoint::operator + (const kwValFixedPoint& right)
{
	if (this->m_isEmpty || right.m_isEmpty)
	{
		THROW_TECHNICAL_EXCEPTION(2, "Operation not allowed - object NULL");
	}
	if (this->m_Precision != right.m_Precision)
	{
		THROW_TECHNICAL_EXCEPTION(3, "Operation not allowed - Precision differs between objects");
	}

	return kwValFixedPoint(this->m_lValue + right.m_lValue, this->m_Precision);
}

kwValFixedPoint& kwValFixedPoint::operator += (kwValFixedPoint const& right)
{
	if (this->m_isEmpty || right.m_isEmpty)
	{
		THROW_TECHNICAL_EXCEPTION(2, "Operation not allowed - object NULL");
	}
	if (this->m_Precision != right.m_Precision)
	{
		THROW_TECHNICAL_EXCEPTION(3, "Operation not allowed - Precision differs between objects");
	}

	this->m_lValue += right.m_lValue;
	return *this;
}

kwValFixedPoint kwValFixedPoint::operator - (const kwValFixedPoint& right)
{
	if (this->m_isEmpty || right.m_isEmpty)
	{
		THROW_TECHNICAL_EXCEPTION(2, "Operation not allowed - object NULL");
	}
	if (this->m_Precision != right.m_Precision)
	{
		THROW_TECHNICAL_EXCEPTION(3, "Operation not allowed - Precision differs between objects");
	}

	return kwValFixedPoint(this->m_lValue - right.m_lValue, this->m_Precision);
}

kwValFixedPoint& kwValFixedPoint::operator -= (kwValFixedPoint const& right)
{
	if (this->m_isEmpty || right.m_isEmpty)
	{
		THROW_TECHNICAL_EXCEPTION(2, "Operation not allowed - object NULL");
	}
	if (this->m_Precision != right.m_Precision)
	{
		THROW_TECHNICAL_EXCEPTION(3, "Operation not allowed - Precision differs between objects");
	}

	this->m_lValue -= right.m_lValue;
	return *this;
}

kwValFixedPoint kwValFixedPoint::operator * (const kwValFixedPoint& right)
{
	if (this->m_isEmpty || right.m_isEmpty)
	{
		THROW_TECHNICAL_EXCEPTION(2, "Operation not allowed - object NULL");
	}
	if (this->m_Precision != right.m_Precision)
	{
		THROW_TECHNICAL_EXCEPTION(3, "Operation not allowed - Precision differs between objects");
	}

	// As we assure that the precision is the same for both objects, we divide once by the precision to get the result corrected
	return kwValFixedPoint((this->m_lValue * right.m_lValue) / precNScalings[static_cast<unsigned long>(this->m_Precision)], this->m_Precision);
}


kwValFixedPoint kwValFixedPoint::operator / (const kwValFixedPoint& right)
{
	if (this->m_isEmpty || right.m_isEmpty)
	{
		THROW_TECHNICAL_EXCEPTION(2, "Operation not allowed - object NULL");
	}
	if (this->m_Precision != right.m_Precision)
	{
		THROW_TECHNICAL_EXCEPTION(3, "Operation not allowed - Precision differs between objects");
	}

	return kwValFixedPoint((this->m_lValue / right.m_lValue) * precNScalings[static_cast<unsigned long>(this->m_Precision)], this->m_Precision);

}

/**
 *	This will convert between different precision settings. There is no rounding made!
 */
kwValFixedPoint kwValFixedPoint::getWithNewPrecision(enumValFixedPointPrec prec)
{
	if (this->m_isEmpty)
	{
		return kwValFixedPoint(prec);
	}

	switch ( static_cast<int>(prec) -  static_cast<int>(this->m_Precision))
	{
	case 2:
		return kwValFixedPoint(this->m_lValue * precNScalings[0], prec);
		break;
	case 4:
		return kwValFixedPoint(this->m_lValue * precNScalings[1], prec);
		break;
	case 6:
		return kwValFixedPoint(this->m_lValue * precNScalings[2], prec);
		break;
	case 8:
		return kwValFixedPoint(this->m_lValue * precNScalings[3], prec);
		break;
	case 10:
		return kwValFixedPoint(this->m_lValue * precNScalings[4], prec);
		break;
	case 12:
		return kwValFixedPoint(this->m_lValue * precNScalings[5], prec);
		break;

	case -2:
		return kwValFixedPoint(this->m_lValue / precNScalings[0], prec);
		break;
	case -4:
		return kwValFixedPoint(this->m_lValue / precNScalings[1], prec);
		break;
	case -6:
		return kwValFixedPoint(this->m_lValue / precNScalings[2], prec);
		break;
	case -8:
		return kwValFixedPoint(this->m_lValue / precNScalings[3], prec);
		break;
	case -10:
		return kwValFixedPoint(this->m_lValue / precNScalings[4], prec);
		break;
	case -12:
		return kwValFixedPoint(this->m_lValue / precNScalings[5], prec);
		break;
	default:
	{
		THROW_TECHNICAL_EXCEPTION(22, "Error in precision conversion!");
	}
	}

}


kwValString kwValFixedPoint::getType()
{
	return kwValString("kwValFixedPoint");
}


std::ostream& operator<< (std::ostream& stream, const kwValFixedPoint& _valfixedpoint)
{
	const kwValString str = kwValString(_valfixedpoint.asString());
	stream << str;
	return stream;
}


enumValFixedPointPrec kwValFixedPoint::getPrecisionFromString(char* _str)
{
// Default is prec13N4
	enumValFixedPointPrec retval  = enumValFixedPointPrec::prec13N4;

	if (0 == strcmp(_str, enumValFixedPointPrecNames[static_cast<unsigned long>(enumValFixedPointPrec::prec15N2)]))
	{
		retval = enumValFixedPointPrec::prec15N2;
		LOG_TRACE << "MATCH on prec15N2";
	}
	if (0 == strcmp(_str, enumValFixedPointPrecNames[static_cast<unsigned long>(enumValFixedPointPrec::prec13N4)]))
	{
		retval =  enumValFixedPointPrec::prec13N4;
		LOG_TRACE << "MATCH on prec13N4";
	}
	if (0 == strcmp(_str, enumValFixedPointPrecNames[static_cast<unsigned long>(enumValFixedPointPrec::prec11N6)]))
	{
		retval =  enumValFixedPointPrec::prec11N6;
		LOG_TRACE << "MATCH on prec11N6";
	}
	if (0 == strcmp(_str, enumValFixedPointPrecNames[static_cast<unsigned long>(enumValFixedPointPrec::prec9N8)]))
	{
		retval =  enumValFixedPointPrec::prec9N8;
		LOG_TRACE << "MATCH on prec9N8";
	}
	if (0 == strcmp(_str, enumValFixedPointPrecNames[static_cast<unsigned long>(enumValFixedPointPrec::prec7N10)]))
	{
		retval =  enumValFixedPointPrec::prec7N10;
		LOG_TRACE << "MATCH on prec7N10";
	}
	if (0 == strcmp(_str, enumValFixedPointPrecNames[static_cast<unsigned long>(enumValFixedPointPrec::prec5N12)]))
	{
		retval =  enumValFixedPointPrec::prec5N12;
		LOG_TRACE << "MATCH on prec5N12";
	}

	LOG_TRACE << "retval = " << static_cast<unsigned long>(retval);
	return retval;
}

float kwValFixedPoint::asFloat()
{
	return ((float)m_lValue) / (float)precNScalings[static_cast<unsigned long>(this->m_Precision)];
}

kwValString kwValFixedPoint::asString()
{
    return kwValString(asString());
}

enumValFixedPointPrec kwValFixedPoint::getPrecision()
{
	return m_Precision;
}


json kwValFixedPoint::toJson()
{
    json j;
    return j;
}
