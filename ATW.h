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

// ���һ���� null ��β���ַ����Ƿ���UTF-8, �������0, Ҳֻ��ʾ������պ÷���UTF8�ı������.
// ����ֵ˵��: 
// 1 -> �����ַ�������UTF-8�������
// -1 -> ��⵽�Ƿ���UTF-8�������ֽ�
// -2 -> ��⵽�Ƿ���UTF-8�ֽڱ���ĺ����ֽ�.
int IsTextUTF8(const char* pszSrc); 