#include "tohex.h"

/**
 * #purpose	: 字符转十六进制
 * #note	: 不适用于汉字字符
 * #param ch    : 要转换成十六进制的字符
 * #return	: 接收转换后的字符串
 */
std::string chToHex(unsigned char ch)
{
	const std::string hex = "0123456789ABCDEF";
 
	std::stringstream ss;
	ss << hex[ch >> 4] << hex[ch & 0xf];
 
	return ss.str();
}
 
/**
 * #purpose	: 字符串转十六进制字符串
 * #note	: 可用于汉字字符串
 * #param str		: 要转换成十六进制的字符串
 * #param separator	: 十六进制字符串间的分隔符
 * #return	: 接收转换后的字符串
 */
std::string strToHex(std::string str, std::string separator = "")
{
	const std::string hex = "0123456789ABCDEF";
	std::stringstream ss;
 
	for (std::string::size_type i = 0; i < str.size(); ++i)
    {
	    ss << hex[(unsigned char)str[i] >> 4] << hex[(unsigned char)str[i] & 0xf] << separator;
    }
	
	return ss.str();
}

/*
std::string hexToHex(std::string str)

char hexToCh(std::string hex)
{
	const std::string hex = "0123456789ABCDEF";
 
	std::stringstream ss;
	ss << hex[ch >> 4] << hex[ch & 0xf];
 
	return ss.str();
}

Hex2Char(unsigned int n)
{
	char ch;
	if(n>=0 && n<=9)	ch = 48 + n;
	else if(n>=10 && n<=15)	ch = 65 - 10 + n;
	else ch = -1;
 
	return ch;
}
*/