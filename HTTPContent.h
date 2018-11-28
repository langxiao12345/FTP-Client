#pragma once

#include "HTTPDef.h"

class CHTTPContent
{
public:
	CHTTPContent(void);
	virtual ~CHTTPContent(void);

protected:
	std::string m_strContentType;
	std::string m_strFileName;

	FILE* m_pFile;
	struct _stat32i64 m_FileInf;
	__int64 m_lFrom;
	__int64 m_lTo;

	int m_nBufferSize;
	char* m_pData;
	int m_nReadPos;
	int m_nWritePos;
	int m_nOpenType;

	std::string getContentTypeFromFileName(const char* pszFileName);

public:
	BOOL OpenFile(const char* pszFileName, __int64 &lFrom, __int64 &lTo);
	BOOL OpenFile(const char* pszFileName);
	BOOL OpenDir(const std::string &strUrl, const std::string &strFilePath);
	BOOL OpenText(const char* pszTxt, int nSize);
	BOOL OpenHtml(const char* pszHtmlTxt, int nSize);
	BOOL OpenData(const char* pData, int nSize);
	void Close();

	std::string GetContentType();
	__int64 GetContentLength();
	std::string GetLastModified();
	std::string GetETag();
	std::string GetContentRange();
	
	BOOL IsOpen();
	BOOL IsEOF();
	int WriteString(const char* pszString);
	int Read(void* pData, int nSize);
	int Write(void* pData, int nSize); // 为将来支持 PUT, POST 方法做准备.
	int Seek(int nOffset);
};
