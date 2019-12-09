
// TinyCompilerView.cpp : CTinyCompilerView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "TinyCompiler.h"
#endif

#include "TinyCompilerDoc.h"
#include "TinyCompilerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTinyCompilerView

IMPLEMENT_DYNCREATE(CTinyCompilerView, CEditView)

BEGIN_MESSAGE_MAP(CTinyCompilerView, CEditView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CTinyCompilerView ����/����

CTinyCompilerView::CTinyCompilerView()
{
	// TODO: �ڴ˴���ӹ������


}

CTinyCompilerView::~CTinyCompilerView()
{
}

BOOL CTinyCompilerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// ���û���
	return bPreCreated;
}

void CTinyCompilerView::OnFilePrintPreview()
{
}

void CTinyCompilerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTinyCompilerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}




// CTinyCompilerView ���

#ifdef _DEBUG
void CTinyCompilerView::AssertValid() const
{
	CEditView::AssertValid();
}

void CTinyCompilerView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CTinyCompilerDoc* CTinyCompilerView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTinyCompilerDoc)));
	return (CTinyCompilerDoc*)m_pDocument;
}
#endif //_DEBUG


// CTinyCompilerView ��Ϣ�������
