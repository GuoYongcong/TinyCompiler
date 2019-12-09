
// TinyCompilerDoc.cpp : CTinyCompilerDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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


// CTinyCompilerDoc ����/����

CTinyCompilerDoc::CTinyCompilerDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CTinyCompilerDoc::~CTinyCompilerDoc()
{
}

BOOL CTinyCompilerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)
	
	return TRUE;
}




// CTinyCompilerDoc ���л�

void CTinyCompilerDoc::Serialize(CArchive& ar)
{
	// CEditView ����һ�������������л��ı༭�ؼ�
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

// ����ͼ��֧��
void CTinyCompilerDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
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

// ������������֧��
void CTinyCompilerDoc::InitializeSearchContent()
{
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ʹ�������ı��ļ���Ϊ�������ݡ�
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

// CTinyCompilerDoc ���

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
	//GetPathName��ȡ�ļ�·��
	USES_CONVERSION;
	char output[] = "syntaxTree.txt";
	cmain(W2A(GetPathName()), output);
	CString cstr(_T("syntaxTree.txt"));
	//CString strline;//����һ���������ڽ��ն�ȡ��һ������
	//CStdioFile file;//����һ��CStdioFile��Ķ��� file
	//CString doc = _T("");
	//BOOL flag = file.Open(cstr, CFile::modeRead);//open������Ҫ������������ǰһ�����ļ�·������һ�����ļ��Ĵ�ģʽ
	//if (flag == FALSE)
	//{
	//	AfxMessageBox(_T("�ļ���ʧ�ܣ�"));
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


// CTinyCompilerDoc ����
