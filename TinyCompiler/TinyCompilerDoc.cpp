
// TinyCompilerDoc.cpp : CTinyCompilerDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "TinyCompiler.h"
#endif

#include "TinyCompilerDoc.h"

#include <propkey.h>
#include "CMAIN.H"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CTinyCompilerDoc

IMPLEMENT_DYNCREATE(CTinyCompilerDoc, CDocument)

BEGIN_MESSAGE_MAP(CTinyCompilerDoc, CDocument)
	ON_COMMAND(ID_BUILD_SYNTAX_TREE, &CTinyCompilerDoc::OnBuildSyntaxTree)

END_MESSAGE_MAP()


// CTinyCompilerDoc 构造/析构

CTinyCompilerDoc::CTinyCompilerDoc()
{
	// TODO: 在此添加一次性构造代码

}

CTinyCompilerDoc::~CTinyCompilerDoc()
{
}

BOOL CTinyCompilerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)
	
	return TRUE;
}




// CTinyCompilerDoc 序列化

void CTinyCompilerDoc::Serialize(CArchive& ar)
{
	// CEditView 包含一个处理所有序列化的编辑控件
	if (!m_viewList.IsEmpty())
	{
		reinterpret_cast<CEditView*>(m_viewList.GetHead())->SerializeRaw(ar);
	}
#ifdef SHARED_HANDLERS

	if (m_viewList.IsEmpty() && ar.IsLoading())
	{
		CFile* pFile = ar.GetFile();
		pFile->Seek(0, FILE_BEGIN);
		ULONGLONG nFileSizeBytes = pFile->GetLength();
		ULONGLONG nFileSizeChars = nFileSizeBytes/sizeof(TCHAR);
		LPTSTR lpszText = (LPTSTR)malloc(((size_t)nFileSizeChars + 1) * sizeof(TCHAR));
		if (lpszText != NULL)
		{
			ar.Read(lpszText, (UINT)nFileSizeBytes);
			lpszText[nFileSizeChars] = '\0';
			m_strThumbnailContent = lpszText;
			m_strSearchContent = lpszText;
		}
	}
#endif
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CTinyCompilerDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(m_strThumbnailContent, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CTinyCompilerDoc::InitializeSearchContent()
{
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 使用整个文本文件作为搜索内容。
	SetSearchContent(m_strSearchContent);
}

void CTinyCompilerDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CTinyCompilerDoc 诊断

#ifdef _DEBUG
void CTinyCompilerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTinyCompilerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
void CTinyCompilerDoc::OnBuildSyntaxTree()
{
	//GetPathName获取文件路径
	USES_CONVERSION;
	char output[] = "syntaxTree.txt";
	cmain(W2A(GetPathName()), output);
	CString cstr(_T("syntaxTree.txt"));
	//CString strline;//定义一个变量用于接收读取的一行内容
	//CStdioFile file;//定义一个CStdioFile类的对象 file
	//CString doc = _T("");
	//BOOL flag = file.Open(cstr, CFile::modeRead);//open函数需要传两个参数，前一个是文件路径，后一个是文件的打开模式
	//if (flag == FALSE)
	//{
	//	AfxMessageBox(_T("文件打开失败！"));
	//}
	//DWORD m_dwPos = 0;
	//file.Seek(m_dwPos, CFile::begin);
	//while (file.ReadString(strline) != FALSE)
	//{
	//	doc.Append(strline);
	//	doc.Append(_T("\n"));
	//}
	//file.Close();
	//AfxMessageBox(doc);
	GetDocTemplate()->OpenDocumentFile(cstr);
;}
#endif //_DEBUG


// CTinyCompilerDoc 命令
