
// TinyCompilerView.h : CTinyCompilerView 类的接口
//

#pragma once


class CTinyCompilerView : public CEditView
{
protected: // 仅从序列化创建
	CTinyCompilerView();
	DECLARE_DYNCREATE(CTinyCompilerView)

// 特性
public:
	CTinyCompilerDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CTinyCompilerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // TinyCompilerView.cpp 中的调试版本
inline CTinyCompilerDoc* CTinyCompilerView::GetDocument() const
   { return reinterpret_cast<CTinyCompilerDoc*>(m_pDocument); }
#endif

