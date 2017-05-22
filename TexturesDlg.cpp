// TexturesDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SolSys.h"
#include "TexturesDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "SolSysView.h"


// CTexturesDlg 对话框

IMPLEMENT_DYNAMIC(CTexturesDlg, CDialogEx)

CTexturesDlg::CTexturesDlg(CWnd* pParent /*=NULL*/) : CDialogEx(CTexturesDlg::IDD, pParent)
{
	m_nComboPlanet = 0;
	m_nComboAttributes = 0;
	m_sEditShowTextures = _T("");
	m_sStaticDlgTips[0] = _T("打开图像以绑定新的纹理。");
	m_sStaticDlgTips[1] = _T("设置星球的大小。");
	m_sStaticDlgTips[2] = _T("设置星球的x坐标(偏离轨道)。");
	m_sStaticDlgTips[3] = _T("设置星球的y坐标(出太阳系)。");
	m_sStaticDlgTips[4] = _T("设置星球的z坐标(增大轨道)。");
	m_sStaticDlgTips[5] = _T("设置星球的公转初值。");
	m_sStaticDlgTips[6] = _T("设置星球的自转初值。");
	m_sStaticDlgTips[7] = _T("设置绘制星球的逼真尺度。");
	m_pfArray[0] = &m_fSize;
	m_pfArray[1] = &m_fSections;
	m_pfArray[2] = &m_fPosX;
	m_pfArray[3] = &m_fPosY;
	m_pfArray[4] = &m_fPosZ;
	m_pfArray[5] = &m_fSolarAngle;
	m_pfArray[6] = &m_fOwnAxisAngle;
}

CTexturesDlg::~CTexturesDlg()
{
}

void CTexturesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_COMBO_PLANET, m_CtrlComboPlanet);
	DDX_Control(pDX, ID_EDIT_SHOW_TEXTURES, m_CtrlEditShowTextures);
	DDX_CBIndex(pDX, ID_COMBO_PLANET, m_nComboPlanet);
	DDV_MinMaxInt(pDX, m_nComboPlanet, 0, 12);
	DDX_Text(pDX, ID_EDIT_SHOW_TEXTURES, m_sEditShowTextures);
	DDX_Control(pDX, IDC_COMBO_ATTRIBUTES, m_CtrlComboAttributes);
	DDX_CBIndex(pDX, IDC_COMBO_ATTRIBUTES, m_nComboAttributes);
	DDV_MinMaxInt(pDX, m_nComboAttributes, 0, 7);
	DDX_Control(pDX, ID_DLG_TIPS, m_CtrlStaticDlgTips);
	DDX_Control(pDX, ID_BN_CHOOSE_TEXTURES, m_CtrlBnChooseImage);
}


BEGIN_MESSAGE_MAP(CTexturesDlg, CDialogEx)
	ON_CBN_SELCHANGE(ID_COMBO_PLANET, &CTexturesDlg::OnCbnSelchangeComboPlanet)
	ON_BN_CLICKED(ID_BN_CHOOSE_TEXTURES, &CTexturesDlg::OnBnClickedBnChooseTextures)
	ON_BN_CLICKED(ID_BN_DLG_APPLY, &CTexturesDlg::OnBnClickedBnDlgApply)
	ON_CBN_SELCHANGE(IDC_COMBO_ATTRIBUTES, &CTexturesDlg::OnCbnSelchangeComboAttributes)
END_MESSAGE_MAP()


// CTexturesDlg 消息处理程序


BOOL CTexturesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 星球组合框
	m_CtrlComboPlanet.InsertString(0, L"水星");
	m_CtrlComboPlanet.InsertString(1, L"金星");
	m_CtrlComboPlanet.InsertString(2, L"地球");
	m_CtrlComboPlanet.InsertString(3, L"火星");
	m_CtrlComboPlanet.InsertString(4, L"木星");
	m_CtrlComboPlanet.InsertString(5, L"土星");
	m_CtrlComboPlanet.InsertString(6, L"天王星");
	m_CtrlComboPlanet.InsertString(7, L"海王星");
	m_CtrlComboPlanet.InsertString(8, L"冥王星");
	m_CtrlComboPlanet.InsertString(9, L"太阳");
	m_CtrlComboPlanet.InsertString(10, L"太阳光晕");
	m_CtrlComboPlanet.InsertString(11, L"星空");
	m_CtrlComboPlanet.InsertString(12, L"月亮");
	m_CtrlComboPlanet.SetCurSel(0);

	// 属性组合框
	m_CtrlComboAttributes.InsertString(0, L"纹理");
	m_CtrlComboAttributes.InsertString(1, L"大小");
	m_CtrlComboAttributes.InsertString(2, L"PosX");
	m_CtrlComboAttributes.InsertString(3, L"PosY");
	m_CtrlComboAttributes.InsertString(4, L"PosZ");
	m_CtrlComboAttributes.InsertString(5, L"公转");
	m_CtrlComboAttributes.InsertString(6, L"自转");
	m_CtrlComboAttributes.InsertString(7, L"绘制");
	m_CtrlComboAttributes.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
}

// 选择纹理
void CTexturesDlg::OnBnClickedBnChooseTextures()
{
	CFileDialog hFileDlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_READONLY, TEXT("所有文件(*.*)|*.* | 图像文件(*.jpg;*.gif;*.png;*.tif;*.bmp)|*.jpg;*.gif;*.png;*.tif;*.bmp||"), NULL);
	hFileDlg.m_ofn.nFilterIndex = 2;
	hFileDlg.m_ofn.hwndOwner = m_hWnd;
	hFileDlg.m_ofn.lStructSize = sizeof(OPENFILENAME);
	hFileDlg.m_ofn.lpstrTitle = TEXT("选择图像...\0");
	hFileDlg.m_ofn.nMaxFile = MAX_PATH;

	if(hFileDlg.DoModal() != IDOK) return;
	m_sEditShowTextures = hFileDlg.GetPathName();
	ChangeEditShowTextures();
}

// 选择星球
void CTexturesDlg::OnCbnSelchangeComboPlanet()
{
	m_nComboPlanet = m_CtrlComboPlanet.GetCurSel();
	CMainFrame* pMain = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	CSolSysView* pView = (CSolSysView*) pMain->GetActiveView();
	if (m_nComboPlanet>8)//选中了非九大行星
	{
		// 修改属性为0
		m_nComboAttributes = 0;
		// 禁止属性组合框
		m_CtrlComboAttributes.EnableWindow(FALSE);
		// 更新Cedit显示
		m_sEditShowTextures = pView->m_sTextureResource[m_nComboPlanet];
		// 太阳系名字
		pView->m_sShowText = "solar system";
		// 显示全部
		pView->m_nShowPlanet = 0;
		ChangeEditShowTextures();
		ChangeStaticDlgTips();
	}
	else
	{
		if (m_nComboAttributes == 0)
			m_sEditShowTextures = pView->m_sTextureResource[m_nComboPlanet];
		// 行星名字
		pView->m_sShowText = pView->m_sPlanetNames[m_nComboPlanet];
		// 单独显示
		pView->m_nShowPlanet = m_nComboPlanet+1;
		m_CtrlComboAttributes.EnableWindow(TRUE);
		OnCbnSelchangeComboAttributes();
	}
	m_CtrlBnChooseImage.EnableWindow(TRUE);
}

// 选择属性
void CTexturesDlg::OnCbnSelchangeComboAttributes()
{
	m_nComboAttributes = m_CtrlComboAttributes.GetCurSel();
	if (m_nComboAttributes == 0)
	{
		m_CtrlBnChooseImage.EnableWindow(TRUE);
	}
	else
	{
		m_CtrlBnChooseImage.EnableWindow(FALSE);
	}
	CMainFrame* pMain = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	CSolSysView* pView = (CSolSysView*) pMain->GetActiveView();
	switch (m_nComboAttributes)
	{
	case 0:
		m_sEditShowTextures = pView->m_sTextureResource[m_nComboPlanet];
		break;
	case 1:
		m_sEditShowTextures.Format(L"%.6f", pView->m_PlanetArray[m_nComboPlanet]->m_fSize);
		break;
	case 2:
		m_sEditShowTextures.Format(L"%.6f", pView->m_PlanetArray[m_nComboPlanet]->m_fPosX);
		break;
	case 3:
		m_sEditShowTextures.Format(L"%.6f", pView->m_PlanetArray[m_nComboPlanet]->m_fPosY);
		break;
	case 4:
		m_sEditShowTextures.Format(L"%.6f", pView->m_PlanetArray[m_nComboPlanet]->m_fPosZ);
		break;
	case 5:
		m_sEditShowTextures.Format(L"%.6f", pView->m_PlanetArray[m_nComboPlanet]->m_fSolarAngle);
		break;
	case 6:
		m_sEditShowTextures.Format(L"%.6f", pView->m_PlanetArray[m_nComboPlanet]->m_fOwnAxisAngle);
		break;
	case 7:
		m_sEditShowTextures.Format(L"%.6f", pView->m_PlanetArray[m_nComboPlanet]->m_fSections);
		break;
	}
	ChangeEditShowTextures();
	ChangeStaticDlgTips();
}

// 显示信息
void CTexturesDlg::ChangeEditShowTextures()
{
	m_CtrlEditShowTextures.SetWindowTextW(m_sEditShowTextures);
}

// 更改提示信息
void CTexturesDlg::ChangeStaticDlgTips()
{
	if (m_nComboPlanet<=8)
	{
		m_CtrlStaticDlgTips.SetWindowTextW(m_sStaticDlgTips[m_nComboAttributes]);
	}
	else
	{
		m_CtrlStaticDlgTips.SetWindowTextW(m_sStaticDlgTips[0]);
	}
}

// 应用
void CTexturesDlg::OnBnClickedBnDlgApply()
{
	CMainFrame* pMain = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	CSolSysView* pView = (CSolSysView*) pMain->GetActiveView();
	if (m_nComboAttributes != 0) UpdateData(TRUE);
	switch (m_nComboAttributes)
	{
	case 0:
		{
			CString Temp = pView->m_sTextureResource[m_nComboPlanet];
			pView->m_sTextureResource[m_nComboPlanet] = m_sEditShowTextures;
			if (BuildTexture(m_sEditShowTextures, pView->m_nTextures[pView->m_nTextureIDs[m_nComboPlanet]], TRUE) == FALSE)
				BuildTexture(Temp, pView->m_nTextures[pView->m_nTextureIDs[m_nComboPlanet]], TRUE);//如果绑定失败，恢复原状
		}
		break;
	case 1:
		pView->m_PlanetArray[m_nComboPlanet]->m_fSize = _tstof(m_sEditShowTextures);
		break;
	case 2:
		pView->m_PlanetArray[m_nComboPlanet]->m_fPosX = _tstof(m_sEditShowTextures);
		break;
	case 3:
		pView->m_PlanetArray[m_nComboPlanet]->m_fPosY = _tstof(m_sEditShowTextures);
		break;
	case 4:
		pView->m_PlanetArray[m_nComboPlanet]->m_fPosZ = _tstof(m_sEditShowTextures);
		break;
	case 5:
		pView->m_PlanetArray[m_nComboPlanet]->m_fSolarAngle = _tstof(m_sEditShowTextures);
		break;
	case 6:
		pView->m_PlanetArray[m_nComboPlanet]->m_fOwnAxisAngle = _tstof(m_sEditShowTextures);
		break;
	case 7:
		pView->m_PlanetArray[m_nComboPlanet]->m_fSections = _tstof(m_sEditShowTextures);
		break;
	}
}