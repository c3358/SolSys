#pragma once
#include "afxwin.h"


// CTexturesDlg 对话框

class CTexturesDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTexturesDlg)

public:
	CTexturesDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTexturesDlg();

// 对话框数据
	enum { IDD = IDD_TEXTURESDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox				m_CtrlComboPlanet;
	CEdit					m_CtrlEditShowTextures;
	CComboBox				m_CtrlComboAttributes;
	CStatic					m_CtrlStaticDlgTips;
	CButton					m_CtrlBnChooseImage;
	CString					m_sEditShowTextures;
	CString					m_sStaticDlgTips[8];
	int						m_nComboAttributes;  //属性
	int						m_nComboPlanet;      //星球
	float					m_fSize,             //行星大小
							m_fSections,         //绘图参数
							m_fPosX,             //位置X
							m_fPosY,             //位置Y
							m_fPosZ,             //位置Z
							m_fSolarAngle,       //公转角度
							m_fOwnAxisAngle;     //自转角度
	float					*m_pfArray[7];       //存放上述变量的地址

	afx_msg void OnCbnSelchangeComboPlanet();
	afx_msg void OnBnClickedBnChooseTextures();
	afx_msg void OnBnClickedBnDlgApply();
	afx_msg void OnCbnSelchangeComboAttributes();
	virtual BOOL OnInitDialog();
	void ChangeStaticDlgTips();
	void ChangeEditShowTextures();
};