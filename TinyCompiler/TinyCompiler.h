
// TinyCompiler.h : TinyCompiler Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CTinyCompilerApp:
// �йش����ʵ�֣������ TinyCompiler.cpp
//

class CTinyCompilerApp : public CWinAppEx
{
public:
	CTinyCompilerApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	afx_msg void PrintSyntaxTree();
	DECLARE_MESSAGE_MAP()
};

extern CTinyCompilerApp theApp;
