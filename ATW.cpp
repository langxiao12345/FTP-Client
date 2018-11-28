#include "stdafx.h"
#include "ATW.h"

//UTF8 תANSI
std::string UTF8toANSI(const char* pszText)  
{  
	//��ȡת��Ϊ���ֽں���Ҫ�Ļ�������С���������ֽڻ�����  
	std::string strRet("");
	UINT nLen = MultiByteToWideChar(CP_UTF8,NULL,pszText,-1,NULL,NULL);  
	WCHAR *wszBuffer = new WCHAR[nLen+1];  
	nLen = MultiByteToWideChar(CP_UTF8,NULL,pszText,-1,wszBuffer,nLen);  
	wszBuffer[nLen] = 0;  

	nLen = WideCharToMultiByte(936,NULL,wszBuffer,-1,NULL,NULL,NULL,NULL);  
	CHAR *szBuffer = new CHAR[nLen+1];  
	nLen = WideCharToMultiByte(936,NULL,wszBuffer,-1,szBuffer,nLen,NULL,NULL);  
	szBuffer[nLen] = 0;  

	strRet = szBuffer;  
	//�����ڴ�  
	delete []szBuffer;  
	delete []wszBuffer;  
	return strRet;
}  
	//ANSIתUTF8  
void ANSItoUTF8(CString &strAnsi)  
{  
	//��ȡת��Ϊ���ֽں���Ҫ�Ļ�������С���������ֽڻ�������936Ϊ��������GB2312����ҳ  
	UINT nLen = MultiByteToWideChar(936,NULL,strAnsi,-1,NULL,NULL);  
	WCHAR *wszBuffer = new WCHAR[nLen+1];  
	nLen = MultiByteToWideChar(936,NULL,strAnsi,-1,wszBuffer,nLen);  
	wszBuffer[nLen] = 0;  
	//��ȡתΪUTF8���ֽں���Ҫ�Ļ�������С���������ֽڻ�����  
	nLen = WideCharToMultiByte(CP_UTF8,NULL,wszBuffer,-1,NULL,NULL,NULL,NULL);  
	CHAR *szBuffer = new CHAR[nLen+1];  
	nLen = WideCharToMultiByte(CP_UTF8,NULL,wszBuffer,-1,szBuffer,nLen,NULL,NULL);  
	szBuffer[nLen] = 0;  

	strAnsi = szBuffer;  
	//�ڴ�����  
	delete []wszBuffer;  
	delete []szBuffer;  
}  

std::string __do_w_to_a_utf8(const wchar_t *pwszText, UINT uCodePage)
{
	ASSERT(pwszText);

	// ��ָ������
	if(pwszText == NULL) return "";

	// �޷�������Ҫ�ĳ���.
	int nNeedSize = WideCharToMultiByte(uCodePage, 0, pwszText, -1, NULL, 0, NULL, NULL);
	if( 0 == nNeedSize ) return "";

	// ����ռ�,ת��.
	char *pRet = new char[nNeedSize + 1]; // ��Ȼ����WideCharToMultiByte�ĳ����ǰ��� null �ַ��ĳ���, ���Ƕ�+һ���ַ�.
	memset(pRet, 0, nNeedSize + 1);

	std::string strRet("");
	if ( 0 == WideCharToMultiByte(uCodePage, 0, pwszText, -1, pRet, nNeedSize, NULL, NULL) )
	{
	}
	else
	{
		strRet = pRet;
	}

	delete []pRet;
	return strRet;
}

std::string __do_a_utf8_to_w(const char* pszText, UINT uCodePage)
{
	// ��ָ��
	ASSERT(pszText);
	if( pszText == NULL ) return "";

	// ���㳤��
	int nNeedSize = MultiByteToWideChar(uCodePage, 0, pszText, -1, NULL, 0);
	if( 0 == nNeedSize ) return "";

	// ����ռ�,ת��
	std::string strRet("");
	char *pRet = new char[nNeedSize + 1];
	memset(pRet, 0, (nNeedSize + 1) * sizeof(char));
	if( 0 == MultiByteToWideChar(uCodePage, 0, pszText, -1, (WCHAR*)pRet, nNeedSize) )
	{
	}
	else
	{
		strRet = pRet;
	}
	//delete []pRet;
	return strRet;
}

std::string WtoA(const std::wstring &strText)
{
	return __do_w_to_a_utf8(strText.c_str(), CP_ACP);
}

std::string WtoA(const wchar_t *pwszText)
{
	return __do_w_to_a_utf8(pwszText, CP_ACP);
}

std::string AtoW(const std::string &strText)
{
	return __do_a_utf8_to_w(strText.c_str(), CP_ACP);
}

std::string AtoW(const char* pszText)
{
	return  UTF8toANSI(pszText);
}

std::string WtoUTF8(const std::wstring &strText)
{
	return __do_w_to_a_utf8(strText.c_str(), CP_ACP);
}

std::string WtoUTF8(const wchar_t *pwszText)
{
	return __do_w_to_a_utf8(pwszText, CP_UTF8);
}

std::string UTF8toW(const std::string &strText)
{
	return UTF8toANSI(strText.c_str());
}

std::string UTF8toW(const char* pszText)
{
	return UTF8toANSI(pszText);
}

/*
UTF-8 ������������6���ֽ�

1�ֽ� 0xxxxxxx
2�ֽ� 110xxxxx 10xxxxxx
3�ֽ� 1110xxxx 10xxxxxx 10xxxxxx
4�ֽ� 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
5�ֽ� 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
6�ֽ� 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx

*/

// ����ֵ˵��: 
// 0 -> �����ַ�������UTF-8�������
// -1 -> ��⵽�Ƿ���UTF-8�������ֽ�
// -2 -> ��⵽�Ƿ���UTF-8�ֽڱ���ĺ����ֽ�.

int IsTextUTF8(const char* pszSrc)
{
	const unsigned char* puszSrc = (const unsigned char*)pszSrc; // һ��Ҫ�޷��ŵ�,�з��ŵıȽϾͲ���ȷ��.
	// ������û��BOM��ʾ EF BB BF
	if( puszSrc[0] != 0 && puszSrc[0] == 0xEF && 
		puszSrc[1] != 0 && puszSrc[1] == 0xBB &&
		puszSrc[2] != 0 && puszSrc[2] == 0xBF)
	{
		return 0;
	}

	// ���û�� BOM��ʶ
	BOOL bIsNextByte = FALSE;
	int nBytes = 0; // ��¼һ���ַ���UTF8�����Ѿ�ռ���˼����ֽ�.
	const unsigned char* pCur = (const unsigned char*)pszSrc; // ָ���α����޷����ַ���. ��Ϊ��λΪ1, ����� char ��, ���Ϊ����,�����ڱ��ʱ��ıȽϲ���.
	
	while( pCur[0] != 0 )
	{
		if(!bIsNextByte)
		{
			bIsNextByte = TRUE;
			if ( (pCur[0] >> 7) == 0) { bIsNextByte = FALSE; nBytes = 1; bIsNextByte = FALSE; } // ���λΪ0, ANSI ���ݵ�.
			else if ((pCur[0] >> 5) == 0x06) { nBytes = 2; } // ����5λ���� 110 -> 2�ֽڱ����UTF8�ַ������ֽ�
			else if ((pCur[0] >> 4) == 0x0E) { nBytes = 3; } // ����4λ���� 1110 -> 3�ֽڱ����UTF8�ַ������ֽ�
			else if ((pCur[0] >> 3) == 0x1E) { nBytes = 4; } // ����3λ���� 11110 -> 4�ֽڱ����UTF8�ַ������ֽ�
			else if ((pCur[0] >> 2) == 0x3E) { nBytes = 5; } // ����2λ���� 111110 -> 5�ֽڱ����UTF8�ַ������ֽ�
			else if ((pCur[0] >> 1) == 0x7E) { nBytes = 6; } // ����1λ���� 1111110 -> 6�ֽڱ����UTF8�ַ������ֽ�
			else
			{
				nBytes = -1; // �Ƿ���UTF8�ַ���������ֽ�
				break;
			}
		}
		else
		{
			if ((pCur[0] >> 6) == 0x02) // ����,�����ֽڱ����� 10xxx ��ͷ
			{
				nBytes--;
				if (nBytes == 1) bIsNextByte = FALSE; // �� nBytes = 1ʱ, ˵����һ���ֽ�Ӧ�������ֽ�.
			}
			else
			{
				nBytes = -2;
				break;
			}
		}

		// ����һ���ַ�
		pCur++;
	}

	if( nBytes == 1) return 0;
	else return nBytes;
}
