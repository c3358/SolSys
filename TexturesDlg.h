#pragma once
#include "afxwin.h"


// CTexturesDlg �Ի���

class CTexturesDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTexturesDlg)

public:
	CTexturesDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTexturesDlg();

// �Ի�������
	enum { IDD = IDD_TEXTURESDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox				m_CtrlComboPlanet;
	CEdit					m_CtrlEditShowTextures;
	CComboBox				m_CtrlComboAttributes;
	CStatic					m_CtrlStaticDlgTips;
	CButton					m_CtrlBnChooseImage;
	CString					m_sEditShowTextures;
	CString					m_sStaticDlgTips[8];
	int						m_nComboAttributes;  //����
	int						m_nComboPlanet;      //����
	float					m_fSize,             //���Ǵ�С
							m_fSections,         //��ͼ����
							m_fPosX,             //λ��X
							m_fPosY,             //λ��Y
							m_fPosZ,             //λ��Z
							m_fSolarAngle,       //��ת�Ƕ�
							m_fOwnAxisAngle;     //��ת�Ƕ�
	float					*m_pfArray[7];       //������������ĵ�ַ

	afx_msg void OnCbnSelchangeComboPlanet();
	afx_msg void OnBnClickedBnChooseTextures();
	afx_msg void OnBnClickedBnDlgApply();
	afx_msg void OnCbnSelchangeComboAttributes();
	virtual BOOL OnInitDialog();
	void ChangeStaticDlgTips();
	void ChangeEditShowTextures();
};