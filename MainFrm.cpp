// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://go.microsoft.com/fwlink/?LinkId=238214。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "SolSys.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_COMMAND(ID_VIEW_CAPTION_BAR, &CMainFrame::OnViewCaptionBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CAPTION_BAR, &CMainFrame::OnUpdateViewCaptionBar)
	ON_COMMAND(ID_TOOLS_OPTIONS, &CMainFrame::OnOptions)
	ON_COMMAND(ID_FILE_PRINT, &CMainFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CMainFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMainFrame::OnFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, &CMainFrame::OnUpdateFilePrintPreview)
	ON_WM_TIMER()
	ON_COMMAND(ID_SHOW_FULL_SCREEN, &CMainFrame::OnShowFullScreen)
	ON_UPDATE_COMMAND_UI(ID_SHOW_FULL_SCREEN, &CMainFrame::OnUpdateShowFullScreen)
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
	theApp.m_nAppLook = theApp.GetInt(L"ApplicationLook", ID_VIEW_APPLOOK_OFF_2007_BLACK);
	CTime CurTime = CTime::GetCurrentTime();
	m_sCurrentTime = CurTime.Format("时间：%H:%M:%S");
	m_sLightPos = L"光源0：( 0.0 , 0.0 , 0.0 )，光源1：( 0.0 , 0.0 , 3.0 )";
	m_sZoomRatio = L"缩放：1.0";
	GetModuleFileName(NULL, m_sScreenShotMsg.GetBufferSetLength(MAX_PATH+1), MAX_PATH);
	m_sScreenShotMsg.ReleaseBuffer();
	//m_sScreenShotMsg = m_sScreenShotMsg.Left(m_sScreenShotMsg.ReverseFind('\\'));
	m_bFullScreen = FALSE;
	m_OldWndPlacement.flags = 0;
	m_OldWndPlacement.length = 44;
	m_OldWndPlacement.showCmd = SW_SHOWDEFAULT;
	m_OldWndPlacement.ptMinPosition = CPoint(-1, -1);
	m_OldWndPlacement.ptMaxPosition = CPoint(0, 2);
	m_OldWndPlacement.rcNormalPosition = CRect(0, 0, 800, 600);
}

CMainFrame::~CMainFrame()
{
	//不能在这里delete m_pRibbonStatusBarPane
	//否则出现一堆内存泄露。不清楚这是为什么。
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	
	CString strTitlePane1;
	CString strTitlePane2;
	//ASSERT(strTitlePane1.LoadString(IDS_STATUS_PANE1));
	//ASSERT(strTitlePane2.LoadString(IDS_STATUS_PANE2));
	strTitlePane1 = L"就绪";
	strTitlePane2 = L"©袁沅祥, 2014";
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);

	// 时间
	m_wndStatusBar.AddSeparator();
	m_pBarCurrentTime = new CMFCRibbonStatusBarPane(ID_STATUSBAR_CURRENT_TIME, m_sCurrentTime, TRUE);
	m_wndStatusBar.AddDynamicElement(m_pBarCurrentTime);

	// 光源位置
	m_wndStatusBar.AddSeparator();
	m_pBarLightPos = new CMFCRibbonStatusBarPane(ID_STATUSBAR_LIGHT_POSITION, m_sLightPos, TRUE);
	m_wndStatusBar.AddDynamicElement(m_pBarLightPos);

	// 缩放比例
	m_wndStatusBar.AddSeparator();
	m_pBarZoomRatio = new CMFCRibbonStatusBarPane(ID_STATUSBAR_ZOOM_RATIO, m_sZoomRatio, TRUE);
	m_wndStatusBar.AddDynamicElement(m_pBarZoomRatio);

	// 保存截图
	m_wndStatusBar.AddSeparator();
	m_pBarScreenShotMsg = new CMFCRibbonStatusBarPane(ID_STATUSBAR_SCREENSHOT_MSG, m_sScreenShotMsg, TRUE);
	m_wndStatusBar.AddDynamicElement(m_pBarScreenShotMsg);
	
	// 定时器
	SetTimer(1, 300, NULL);
	
	// 启用 Visual Studio 2005 样式停靠窗口行为
	CDockingManager::SetDockingMode(DT_SMART);
	// 启用 Visual Studio 2005 样式停靠窗口自动隐藏行为
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// 导航窗格将创建在左侧，因此将暂时禁用左侧的停靠:
	EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM | CBRS_ALIGN_RIGHT);

	// 创建并设置“Outlook”导航栏:
	if (!CreateOutlookBar(m_wndNavigationBar, ID_VIEW_NAVIGATION, m_wndTree, m_wndCalendar, 250))
	{
		TRACE0("未能创建导航窗格\n");
		return -1;      // 未能创建
	}

	// 创建标题栏:
	if (!CreateCaptionBar())
	{
		TRACE0("未能创建标题栏\n");
		return -1;      // 未能创建
	}

	// 已创建 Outlook 栏，应允许在左侧停靠。
	EnableDocking(CBRS_ALIGN_LEFT);
	EnableAutoHidePanes(CBRS_ALIGN_RIGHT);
	// 基于持久值设置视觉管理器和样式
	OnApplicationLook(theApp.m_nAppLook);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

BOOL CMainFrame::CreateOutlookBar(CMFCOutlookBar& bar, UINT uiID, CMFCShellTreeCtrl& tree, CCalendarBar& calendar, int nInitialWidth)
{
	bar.SetMode2003();

	BOOL bNameValid;
	CString strTemp;
	bNameValid = strTemp.LoadString(IDS_SHORTCUTS);
	ASSERT(bNameValid);
	if (!bar.Create(strTemp, this, CRect(0, 0, nInitialWidth, 32000), uiID, WS_CHILD | WS_VISIBLE | CBRS_LEFT))
	{
		return FALSE; // 未能创建
	}

	CMFCOutlookBarTabCtrl* pOutlookBar = (CMFCOutlookBarTabCtrl*)bar.GetUnderlyingWindow();

	if (pOutlookBar == NULL)
	{
		ASSERT(FALSE);
		return FALSE;
	}

	pOutlookBar->EnableInPlaceEdit(TRUE);

	static UINT uiPageID = 1;

	// 可浮动，可自动隐藏，可调整大小，但不能关闭
	DWORD dwStyle = AFX_CBRS_FLOAT | AFX_CBRS_AUTOHIDE | AFX_CBRS_RESIZE;

	CRect rectDummy(0, 0, 0, 0);
	const DWORD dwTreeStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	tree.Create(dwTreeStyle, rectDummy, &bar, 1200);
	bNameValid = strTemp.LoadString(IDS_FOLDERS);
	ASSERT(bNameValid);
	pOutlookBar->AddControl(&tree, strTemp, 2, TRUE, dwStyle);

	calendar.Create(rectDummy, &bar, 1201);
	bNameValid = strTemp.LoadString(IDS_CALENDAR);
	ASSERT(bNameValid);
	pOutlookBar->AddControl(&calendar, strTemp, 3, TRUE, dwStyle);

	bar.SetPaneStyle(bar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	pOutlookBar->SetImageList(theApp.m_bHiColorIcons ? IDB_PAGES_HC : IDB_PAGES, 24);
	pOutlookBar->SetToolbarImageList(theApp.m_bHiColorIcons ? IDB_PAGES_SMALL_HC : IDB_PAGES_SMALL, 16);
	pOutlookBar->RecalcLayout();

	BOOL bAnimation = theApp.GetInt(L"OutlookAnimation", TRUE);
	CMFCOutlookBarTabCtrl::EnableAnimation(bAnimation);

	bar.SetButtonsFont(&afxGlobalData.fontBold);

	return TRUE;
}

BOOL CMainFrame::CreateCaptionBar()
{
	if (!m_wndCaptionBar.Create(WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, this, ID_VIEW_CAPTION_BAR, -1, TRUE))
	{
		TRACE0("未能创建标题栏\n");
		return FALSE;
	}

	BOOL bNameValid;

	CString strTemp, strTemp2;
	bNameValid = strTemp.LoadString(IDS_CAPTION_BUTTON);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetButton(strTemp, ID_TOOLS_OPTIONS, CMFCCaptionBar::ALIGN_LEFT, FALSE);
	bNameValid = strTemp.LoadString(IDS_CAPTION_BUTTON_TIP);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetButtonToolTip(strTemp);

	bNameValid = strTemp.LoadString(IDS_CAPTION_TEXT);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetText(strTemp, CMFCCaptionBar::ALIGN_LEFT);

	m_wndCaptionBar.SetBitmap(IDB_INFO, RGB(255, 255, 255), FALSE, CMFCCaptionBar::ALIGN_LEFT);
	bNameValid = strTemp.LoadString(IDS_CAPTION_IMAGE_TIP);
	ASSERT(bNameValid);
	bNameValid = strTemp2.LoadString(IDS_CAPTION_IMAGE_TEXT);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetImageToolTip(strTemp, strTemp2);

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(TRUE);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(L"ApplicationLook", theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

void CMainFrame::OnViewCaptionBar()
{
	m_wndCaptionBar.ShowWindow(m_wndCaptionBar.IsVisible() ? SW_HIDE : SW_SHOW);
	RecalcLayout(FALSE);
}

void CMainFrame::OnUpdateViewCaptionBar(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndCaptionBar.IsVisible());
}

void CMainFrame::OnOptions()
{
	CMFCRibbonCustomizeDialog *pOptionsDlg = new CMFCRibbonCustomizeDialog(this, &m_wndRibbonBar);
	ASSERT(pOptionsDlg != NULL);

	pOptionsDlg->DoModal();
	delete pOptionsDlg;
}


void CMainFrame::OnFilePrint()
{
	if (IsPrintPreview())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_PRINT);
	}
}

void CMainFrame::OnFilePrintPreview()
{
	if (IsPrintPreview())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_CLOSE);  // 强制关闭“打印预览”模式
	}
}

void CMainFrame::OnUpdateFilePrintPreview(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(IsPrintPreview());
}

// 状态栏显示时间
void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		CTime CurTime = CTime::GetCurrentTime();
		m_sCurrentTime = CurTime.Format("时间：%H:%M:%S");
		m_pBarCurrentTime->SetText(m_sCurrentTime);
		m_wndStatusBar.InvalidateRect(m_pBarCurrentTime->GetRect());

		m_pBarLightPos->SetText(m_sLightPos);
		m_wndStatusBar.InvalidateRect(m_pBarLightPos->GetRect());

		m_pBarZoomRatio->SetText(m_sZoomRatio);
		m_wndStatusBar.InvalidateRect(m_pBarZoomRatio->GetRect());

		m_pBarScreenShotMsg->SetText(m_sScreenShotMsg);
		m_wndStatusBar.InvalidateRect(m_pBarScreenShotMsg->GetRect());
	}
	CFrameWndEx::OnTimer(nIDEvent);
}

// 屏幕最大化
void CMainFrame::OnShowFullScreen()
{
	m_bFullScreen = !m_bFullScreen;
	if (m_bFullScreen)
	{
		// 隐藏最大化，最小化，关闭按钮
		ModifyStyleEx(WS_SYSMENU, 0);
		// 隐藏标题栏
		ModifyStyleEx(WS_CAPTION, 0);

		//最大化，隐藏所有Bars
		ShowAllBars(SW_HIDE);
		GetWindowPlacement(&m_OldWndPlacement);
		CRect WindowRect;
		GetWindowRect(&WindowRect);
		CRect ClientRect;
		RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, reposQuery, &ClientRect);
		ClientToScreen(&ClientRect);
		//获取屏幕的分辨率
		int nFullWidth = GetSystemMetrics(SM_CXSCREEN);
		int nFullHeight = GetSystemMetrics(SM_CYSCREEN);
		//将除控制条外的客户区全屏显示到从(0, 0)到(nFullWidth, nFullHeight)区域
		//将(0, 0)和(nFullWidth, nFullHeight)两个点外扩充原窗口和除控制条之外的客
		//户区位置间的差值, 就得到全屏显示的窗口位置
		m_FullScreenRect.left = WindowRect.left - ClientRect.left;
		m_FullScreenRect.top = WindowRect.top - ClientRect.top;
		m_FullScreenRect.right = WindowRect.right - ClientRect.right + nFullWidth;
		m_FullScreenRect.bottom = WindowRect.bottom - ClientRect.bottom + nFullHeight;

		//进入全屏显示状态
		WINDOWPLACEMENT wndpl;
		wndpl.length = sizeof(WINDOWPLACEMENT);
		wndpl.flags = 0;
		wndpl.showCmd = SW_SHOWNORMAL;
		wndpl.rcNormalPosition = m_FullScreenRect;
		SetWindowPlacement(&wndpl);
	}
}

void CMainFrame::OnUpdateShowFullScreen(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bFullScreen);
}

// 最大最小化消息响应
void CMainFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	if (m_bFullScreen)
	{
		lpMMI->ptMaxSize.x = m_FullScreenRect.Width();
		lpMMI->ptMaxSize.y = m_FullScreenRect.Height();
		lpMMI->ptMaxPosition.x = m_FullScreenRect.Width();
		lpMMI->ptMaxPosition.y = m_FullScreenRect.Height();
		//最大的Track尺寸也要改变
		lpMMI->ptMaxTrackSize.x = m_FullScreenRect.Width();
		lpMMI->ptMaxTrackSize.y = m_FullScreenRect.Height();
	}

	CFrameWndEx::OnGetMinMaxInfo(lpMMI);
}

// 结束最大化
void CMainFrame::EndFullScreen()
{
	//退出全屏显示, 恢复原窗口显示
	ShowAllBars(SW_SHOW);
	if (m_bFullScreen)
	{
		m_bFullScreen = false;
		::SetWindowPos(GetSafeHwnd(), HWND_TOP, m_OldWndPlacement.rcNormalPosition.left, m_OldWndPlacement.rcNormalPosition.top,
			m_OldWndPlacement.rcNormalPosition.right, m_OldWndPlacement.rcNormalPosition.bottom, SWP_NOMOVE || SWP_NOSIZE);
		CenterWindow();
	}
}

// 显示所有Bars
void CMainFrame::ShowAllBars(BOOL bShow)
{
	m_wndCalendar.ShowWindow(bShow);
	m_wndCaptionBar.ShowWindow(bShow);
	m_wndNavigationBar.ShowWindow(bShow);
	m_wndRibbonBar.ShowWindow(bShow);
	m_wndStatusBar.ShowWindow(bShow);
	m_wndTree.ShowWindow(bShow);
	this->UpdateWindow();
}