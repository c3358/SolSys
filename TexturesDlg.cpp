// TexturesDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SolSys.h"
#include "TexturesDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "SolSysView.h"


// CTexturesDlg �Ի���

IMPLEMENT_DYNAMIC(CTexturesDlg, CDialogEx)

CTexturesDlg::CTexturesDlg(CWnd* pParent /*=NULL*/) : CDialogEx(CTexturesDlg::IDD, pParent)
{
	m_nComboPlanet = 0;
	m_nComboAttributes = 0;
	m_sEditShowTextures = _T("");
	m_sStaticDlgTips[0] = _T("��ͼ���԰��µ�����");
	m_sStaticDlgTips[1] = _T("��������Ĵ�С��");
	m_sStaticDlgTips[2] = _T("���������x����(ƫ����)��");
	m_sStaticDlgTips[3] = _T("���������y����(��̫��ϵ)��");
	m_sStaticDlgTips[4] = _T("���������z����(������)��");
	m_sStaticDlgTips[5] = _T("��������Ĺ�ת��ֵ��");
	m_sStaticDlgTips[6] = _T("�����������ת��ֵ��");
	m_sStaticDlgTips[7] = _T("���û�������ı���߶ȡ�");
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


// CTexturesDlg ��Ϣ�������


BOOL CTexturesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ������Ͽ�
	m_CtrlComboPlanet.InsertString(0, L"ˮ��");
	m_CtrlComboPlanet.InsertString(1, L"����");
	m_CtrlComboPlanet.InsertString(2, L"����");
	m_CtrlComboPlanet.InsertString(3, L"����");
	m_CtrlComboPlanet.InsertString(4, L"ľ��");
	m_CtrlComboPlanet.InsertString(5, L"����");
	m_CtrlComboPlanet.InsertString(6, L"������");
	m_CtrlComboPlanet.InsertString(7, L"������");
	m_CtrlComboPlanet.InsertString(8, L"ڤ����");
	m_CtrlComboPlanet.InsertString(9, L"̫��");
	m_CtrlComboPlanet.InsertString(10, L"̫������");
	m_CtrlComboPlanet.InsertString(11, L"�ǿ�");
	m_CtrlComboPlanet.InsertString(12, L"����");
	m_CtrlComboPlanet.SetCurSel(0);

	// ������Ͽ�
	m_CtrlComboAttributes.InsertString(0, L"����");
	m_CtrlComboAttributes.InsertString(1, L"��С");
	m_CtrlComboAttributes.InsertString(2, L"PosX");
	m_CtrlComboAttributes.InsertString(3, L"PosY");
	m_CtrlComboAttributes.InsertString(4, L"PosZ");
	m_CtrlComboAttributes.InsertString(5, L"��ת");
	m_CtrlComboAttributes.InsertString(6, L"��ת");
	m_CtrlComboAttributes.InsertString(7, L"����");
	m_CtrlComboAttributes.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
}

// ѡ������
void CTexturesDlg::OnBnClickedBnChooseTextures()
{
	CFileDialog hFileDlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_READONLY, TEXT("�����ļ�(*.*)|*.* | ͼ���ļ�(*.jpg;*.gif;*.png;*.tif;*.bmp)|*.jpg;*.gif;*.png;*.tif;*.bmp||"), NULL);
	hFileDlg.m_ofn.nFilterIndex = 2;
	hFileDlg.m_ofn.hwndOwner = m_hWnd;
	hFileDlg.m_ofn.lStructSize = sizeof(OPENFILENAME);
	hFileDlg.m_ofn.lpstrTitle = TEXT("ѡ��ͼ��...\0");
	hFileDlg.m_ofn.nMaxFile = MAX_PATH;

	if(hFileDlg.DoModal() != IDOK) return;
	m_sEditShowTextures = hFileDlg.GetPathName();
	ChangeEditShowTextures();
}

// ѡ������
void CTexturesDlg::OnCbnSelchangeComboPlanet()
{
	m_nComboPlanet = m_CtrlComboPlanet.GetCurSel();
	CMainFrame* pMain = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	CSolSysView* pView = (CSolSysView*) pMain->GetActiveView();
	if (m_nComboPlanet>8)//ѡ���˷ǾŴ�����
	{
		// �޸�����Ϊ0
		m_nComboAttributes = 0;
		// ��ֹ������Ͽ�
		m_CtrlComboAttributes.EnableWindow(FALSE);
		// ����Cedit��ʾ
		m_sEditShowTextures = pView->m_sTextureResource[m_nComboPlanet];
		// ̫��ϵ����
		pView->m_sShowText = "solar system";
		// ��ʾȫ��
		pView->m_nShowPlanet = 0;
		ChangeEditShowTextures();
		ChangeStaticDlgTips();
	}
	else
	{
		if (m_nComboAttributes == 0)
			m_sEditShowTextures = pView->m_sTextureResource[m_nComboPlanet];
		// ��������
		pView->m_sShowText = pView->m_sPlanetNames[m_nComboPlanet];
		// ������ʾ
		pView->m_nShowPlanet = m_nComboPlanet+1;
		m_CtrlComboAttributes.EnableWindow(TRUE);
		OnCbnSelchangeComboAttributes();
	}
	m_CtrlBnChooseImage.EnableWindow(TRUE);
}

// ѡ������
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

// ��ʾ��Ϣ
void CTexturesDlg::ChangeEditShowTextures()
{
	m_CtrlEditShowTextures.SetWindowTextW(m_sEditShowTextures);
}

// ������ʾ��Ϣ
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

// Ӧ��
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
				BuildTexture(Temp, pView->m_nTextures[pView->m_nTextureIDs[m_nComboPlanet]], TRUE);//�����ʧ�ܣ��ָ�ԭ״
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