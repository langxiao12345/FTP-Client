#pragma once
#include "HTTPDef.h"

class CHTTPContent;
class CHTTPResponse
{
public:
	CHTTPResponse(const char* pszIP, unsigned int nPort);
	virtual ~CHTTPResponse(void);

protected:
	HTTP_METHOD m_Method;
	std::string m_strIP;
	unsigned int m_nPort;
	SERVER_CODE m_nServerCode;

	char* m_pData; // 响应头缓冲
	int m_nReadPos; // 读取位置
	int m_nHeaderSize; // 响应头的长度
	
	CHTTPContent* m_pContent;

	std::string getFirstLine(SERVER_CODE nServerCode); // 根据制定的 Servercode 返回对应的 HTTP响应头的第一行,包括换行符.
	std::string getContentType(const char* pszFileName); 

public:
	SERVER_CODE SetServerCode(SERVER_CODE nNewCode); // 设置HTTP服务端响应码.
	HTTP_METHOD SetMethod(HTTP_METHOD mh);
	SERVER_CODE GetServerCode() { return m_nServerCode;}
	
	BOOL CookResponse(); // 生成响应
	int PopData(void* pData, int nSize); // 弹出数据
	BOOL IsEOF(); // 判断是否到结尾

	void AttachContent(CHTTPContent *pContent);
};
