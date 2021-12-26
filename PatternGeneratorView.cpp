// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface
// (the "Fluent UI") and is provided only as referential material to supplement the
// Microsoft Foundation Classes Reference and related electronic documentation
// included with the MFC C++ library software.
// License terms to copy, use or distribute the Fluent UI are available separately.
// To learn more about our Fluent UI licensing program, please visit
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// PatternGeneratorView.cpp : implementation of the CPatternGeneratorView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PatternGenerator.h"
#endif

#include "PatternGeneratorDoc.h"
#include "PatternGeneratorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPatternGeneratorView

IMPLEMENT_DYNCREATE(CPatternGeneratorView, CView)

BEGIN_MESSAGE_MAP(CPatternGeneratorView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPatternGeneratorView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	
	ON_COMMAND(ID_BUTTON3, &CPatternGeneratorView::OnButtonPatternStart)
	ON_COMMAND(ID_BUTTON4, &CPatternGeneratorView::OnButtonPatternStop)
	ON_COMMAND(ID_BUTTON5, &CPatternGeneratorView::OnButtonPatternResume)
END_MESSAGE_MAP()

// CPatternGeneratorView construction/destruction

CPatternGeneratorView::CPatternGeneratorView() noexcept
{
	// TODO: add construction code here
	m_pCurrentThread = NULL;
	//m_iCounter = 0;
	x1 = 580;
	y1 = 240;

	x2 = 440+190*cos(5);
	y2 = 240+190*sin(5);

}

CPatternGeneratorView::~CPatternGeneratorView()
{
}

BOOL CPatternGeneratorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPatternGeneratorView drawing

void CPatternGeneratorView::OnDraw(CDC* pDC)
{
	CPatternGeneratorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	CPen redPen,orangePen,bluePen,greenPen;
	CBrush orangeBrush(RGB(255, 165, 0));
	CBrush blueBrush(RGB(0,0,255));
	CBrush greenBrush(RGB(0,255,0));

	redPen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	orangePen.CreatePen(PS_SOLID,2,RGB(255, 165, 0));
	bluePen.CreatePen(PS_SOLID, 2, RGB(0,0,255));
	greenPen.CreatePen(PS_SOLID, 2, RGB(0,255,0));

	CPen* pOldPen = pDC->SelectObject(&redPen);


	/*CString strCounter;
	strCounter.Format(L"The Counter is %d", m_iCounter);*/
	pDC->Ellipse(250, 50, 630, 430);
	pDC->Ellipse(300, 100, 580, 380);
	CBrush* pOldBrush = pDC->SelectObject(&orangeBrush);
	pDC->Ellipse(400, 200, 480, 280); 
	pDC->SelectObject(pOldBrush);

	pOldBrush = pDC->SelectObject(&blueBrush);
	pDC->Ellipse(x1 + 10, y1 + 10, x1 - 10, y1 - 10);
	pDC->SelectObject(&greenBrush);
	pDC->Ellipse(x2 + 10, y2 + 10, x2 - 10, y2 - 10);
	pDC->SelectObject(pOldBrush);
	
	
	


	/*
	for (int i = 0; i < m_PointArray.GetSize() - 2; i++) {
		//pDC->MoveTo(m_PointArray[i].x, m_PointArray[i].y);
		pDC->LineTo(m_PointArray[i + 1].x, m_PointArray[i + 1].y);
	}*/

	

	pDC->SelectObject(pOldPen);
	
}


// CPatternGeneratorView printing


void CPatternGeneratorView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPatternGeneratorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPatternGeneratorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPatternGeneratorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CPatternGeneratorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPatternGeneratorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPatternGeneratorView diagnostics

#ifdef _DEBUG
void CPatternGeneratorView::AssertValid() const
{
	CView::AssertValid();
}

void CPatternGeneratorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPatternGeneratorDoc* CPatternGeneratorView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPatternGeneratorDoc)));
	return (CPatternGeneratorDoc*)m_pDocument;
}
#endif //_DEBUG


// CPatternGeneratorView message handlers



void CPatternGeneratorView::OnButtonPatternStart()
{
	// TODO: Add your command handler code here
	//AfxMessageBox(_T("Start"));
	m_pCurrentThread = AfxBeginThread(CPatternGeneratorView::StartThread, this);
}


void CPatternGeneratorView::OnButtonPatternStop()
{
	// TODO: Add your command handler code here
	m_pCurrentThread->SuspendThread();
}


void CPatternGeneratorView::OnButtonPatternResume()
{
	// TODO: Add your command handler code here
	m_pCurrentThread->ResumeThread();
}


UINT CPatternGeneratorView::StartThread(LPVOID param)
{
	// TODO: Add your implementation code here.
	CPatternGeneratorView* pView = (CPatternGeneratorView*)param;
	int j = 0;
	while (true) {

		//MyPoint.y = 200 + 50 * sin(pView->m_iCounter);
		//MyPoint.x = 100 + pView->m_iCounter;

		j = j + 6;

		pView->x1 = 440 + 140 * cos(j);
		pView->y1 = 240 + 140 * sin(j);

		pView->x2 = 440 + 190 * cos(j+5);
		pView->y2 = 240 + 190 * sin(j+5);
		
		pView->Invalidate();
		Sleep(300);
	}

	return 0;
}
