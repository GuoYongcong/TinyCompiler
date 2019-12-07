
// TinyCompilerView.h : CTinyCompilerView ��Ľӿ�
//

#pragma once


class CTinyCompilerView : public CEditView
{
protected: // �������л�����
	CTinyCompilerView();
	DECLARE_DYNCREATE(CTinyCompilerView)

// ����
public:
	CTinyCompilerDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CTinyCompilerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // TinyCompilerView.cpp �еĵ��԰汾
inline CTinyCompilerDoc* CTinyCompilerView::GetDocument() const
   { return reinterpret_cast<CTinyCompilerDoc*>(m_pDocument); }
#endif

