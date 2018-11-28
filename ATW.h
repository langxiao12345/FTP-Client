#pragma once
#include <string>

#ifdef _UNICODE
#define TtoA WtoA
#define AtoT AtoW
//#else
//#define TtoA(a) a
//#define AtoT(w) w
#endif

std::string WtoA(const wchar_t* pwszSrc);
std::string WtoA(const std::wstring &strSrc);

std::string AtoW(const char* pszSrc);
std::string AtoW(const std::string &strSrc);

std::string WtoUTF8(const wchar_t* pwszSrc);
std::string WtoUTF8(const std::wstring &strSrc);

std::string UTF8toW(const char* pszSrc);
std::string UTF8toW(const std::string &strSr);

// 检测一个以 null 结尾的字符串是否是UTF-8, 如果返回0, 也只表示这个串刚好符合UTF8的编码规则.
// 返回值说明: 
// 1 -> 输入字符串符合UTF-8编码规则
// -1 -> 检测到非法的UTF-8编码首字节
// -2 -> 检测到非法的UTF-8字节编码的后续字节.
int IsTextUTF8(const char* pszSrc); 