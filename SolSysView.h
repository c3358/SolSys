// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://go.microsoft.com/fwlink/?LinkId=238214��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// SolSysView.h : CSolSysView ��Ľӿ�
//

#pragma once

#include "Cfloat3.h"
#include "Planet.h"
#include "Texture.h"

class CMainFrame;
class CTexturesDlg;

//���ڲ���wav��ʽ����
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#include "Particle.h"
#include "SolSysDoc.h"

#define MAXTEXTURE              16              //���������
#define PARTICLE_NUMBER         1000
#define PI						3.141592654     //Բ����
#define DEG2RAD(angle)			angle*(PI/180)	//���Ƕ�ת��Ϊ����
#define texture_id_star         0               //�ǿ�
#define texture_id_halo         1               //����
#define texture_id_sun          2               //̫��
#define texture_id_moon         3               //����
#define texture_id_mercury      4               //ˮ��
#define texture_id_venus        5               //����
#define texture_id_earth        6               //����
#define texture_id_mars         7               //����
#define texture_id_jupiter      8               //ľ��
#define texture_id_saturn       9               //����
#define texture_id_uranus       10              //������
#define texture_id_neptune      11              //������
#define texture_id_pluto        12              //ڤ����

struct GlobalPosition                           //ȫ������
{
	float fPosX, fPosY;
	float iDegreesX, iDegreesY;
	bool bRotationOn;
};

class CSolSysView : public CView
{
protected: // �������л�����
	CSolSysView();
	DECLARE_DYNCREATE(CSolSysView)

// ����
public:
	CSolSysDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CSolSysView();
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

public:// ������Ա�뺯��
	int                              m_GLPixelIndex;
	HGLRC                              m_hGLContext;
	int                   m_nCometAngle, m_nCometPos; // ���ǽǶȡ�λ��
	CPlanet                    mercury, venus, earth, // ˮ�ǣ� ���ǣ� ����
		                       mars, jupiter, saturn, // ���ǣ� ľ�ǣ� ����
		                      uranus, neptune, pluto; // ������,������,ڤ����
	CPlanet*              m_PlanetArray[MAXTEXTURE]; // ���ǵ�ָ������
	CString           m_sTextureResource[MAXTEXTURE]; // ������Դ����
	CString              m_sPlanetNames[MAXTEXTURE];  //������������
	GLuint                  m_nTextures[MAXTEXTURE];  // ��������
	int                    m_nTextureIDs[MAXTEXTURE];  // ID����
	GLUquadricObj                       *m_pQuadric;  // �����������
	int                                m_nMouseOldX;  // ����λ��X
	int                                m_nMouseOldY;  // ����λ��Y
	Cfloat3                               m_fRotate;  // ��ת����
	Cfloat3                            m_fTranslate;  // λ������
	GLsizei                                 m_nWidth;  // �ӿڿ��
	GLsizei                                m_nHeight;  // �ӿڸ߶�
	GLfloat                                 m_Aspect;  // �ӿڿ�߱�
	GLfloat                              m_SceneSize;  // ������С
	GlobalPosition                  m_globalPosition; // ȫ�ֿ��Ʊ���
	GLfloat                         m_fRotationSpeed; // ������ת�ٶ�
	GLfloat								m_fStarAngle; // �ǿ���ת�Ƕ�
	Cfloat3                            m_f3globalPos; // ȫ��λ��

	//��������
	bool                            m_bGlobalRotateX; // ȫ����X��ת
	bool						    m_bGlobalRotateY; // ȫ����Y��ת
	bool                          m_bChangeLight0Pos; // �ı��Դ0λ��
	bool                          m_bChangeLight1Pos; // �ı��Դ1λ��
	bool                               m_bShowOrbits; // �Ƿ���ʾ���
	int                                m_nShowPlanet; // ��ʾĳ������
	BOOL                              m_bInitialized;  // �Ƿ��ѳ�ʼ��
	BOOL                           m_bLeftButtonDown;  // ���������
	BOOL                           m_bRotationPaused;  // ��ͣ����
	bool                             m_bAntiAliasing;  // �Ƿ����ÿ����
	bool                             m_bEnableLight0;  // �Ƿ����ù�Դ0
	bool                             m_bEnableLight1;  // �Ƿ����ù�Դ1

	//����
	bool                              m_bMusicPaused;  // ������ͣ
	MCI_OPEN_PARMS                       m_OpenMusic;  // ������
	MCI_PLAY_PARMS                       m_PlayMusic;  // ��������
	CString                            m_sOtherMusic;  // ����������

	//��Ƶ
	bool                                m_bRecording;  //�Ƿ�¼��
	bool                               m_bShowRecWnd;  //��ʾ����
	double                                     m_FPS;  //֡����
	CvSize                                  m_CvSize;  //��Ļ��С
	CvVideoWriter*                     m_MovieWriter;  //д��Ƶ�豸
	IplImage*                             m_CurFrame;  //��ǰ֡

	//��ݼ�
	HACCEL                                m_MyHotkey;  //��ݼ�
	bool                      m_bUseHotkeyShotScreen;  //ʹ�ÿ�ݼ���ͼ
	bool                    m_bUseHotkeyRecordScreen;  //ʹ�ÿ�ݼ�¼��

	//����
	bool                            m_bMeteoricShower; //�Ƿ�������Ч
	GLuint                    m_nTextures_Particle[8]; //����ϵͳ
	CParticle          m_MyParticles[PARTICLE_NUMBER]; //��������
	void InitParticle();
	void DrawParticle();

	//�Ի���
	CTexturesDlg*                       m_pTexturesDlg;

	//��ʾ������
	CString                                m_sShowText;

	//ģ��
	void InitGL(void);
	bool CreateViewGLContext(HDC hDC);
	bool SetWindowPixelFormat(HDC hDC);
	void DrawStar();                       // �����ǿ�
	void DrawSun();                        // ��̫��
	void DrawAllOrbits();                  // �����й��
	void DrawOrbit(CPlanet planet);        // ���������
	void DrawAllPlanets();                 // ����������
	void DrawPlanet(CPlanet planet);       // ����������
	void DrawComet();                      // ������
	void InitPlanets();                    // �������ʼ��
	void Rotate();                         // ��ת
	BOOL Display();                        // ��ʾ

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnAppExit();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnRibbonPause();
	afx_msg void OnUpdateRibbonPause(CCmdUI *pCmdUI);
	afx_msg void OnRibbonGlobalRotateX();
	afx_msg void OnUpdateRibbonGlobalRotateX(CCmdUI *pCmdUI);
	afx_msg void OnRibbonGlobalRotateY();
	afx_msg void OnUpdateRibbonGlobalRotateY(CCmdUI *pCmdUI);
	afx_msg void OnRibbonAmbient0();
	afx_msg void OnPopupScreenShot();
	afx_msg void OnRibbonLoadMp3();
	afx_msg void OnUpdateRibbonLoadMp3(CCmdUI *pCmdUI);
	afx_msg void OnRibbonLoadOthers();
	afx_msg void OnShowPlanet();
	afx_msg void OnShowOrbits();
	afx_msg void OnUpdateShowOrbits(CCmdUI *pCmdUI);
	afx_msg void OnAdvancedAntiAliasing();
	afx_msg void OnUpdateAdvancedAntiAliasing(CCmdUI *pCmdUI);
	afx_msg void OnAdvancedLight0();
	afx_msg void OnUpdateAdvancedLight0(CCmdUI *pCmdUI);
	afx_msg void OnAdvancedLight1();
	afx_msg void OnUpdateAdvancedLight1(CCmdUI *pCmdUI);
	afx_msg void OnRibbonRotateSpeed();
	afx_msg void OnRibbonChangeLight0Pos();
	afx_msg void OnUpdateRibbonChangeLight0Pos(CCmdUI *pCmdUI);
	afx_msg void OnRibbonChangeLight1Pos();
	afx_msg void OnUpdateRibbonChangeLight1Pos(CCmdUI *pCmdUI);
	afx_msg void OnAdvancedMeteoricShower();
	afx_msg void OnUpdateAdvancedMeteoricShower(CCmdUI *pCmdUI);
	afx_msg void OnPopupRecording();
	afx_msg void OnUpdatePopupRecording(CCmdUI *pCmdUI);
	//��ݼ�
	afx_msg void OnHotkeyAppExit();
	afx_msg void OnHotkeyScreenShot();
	afx_msg void OnHotkeyPause();
	afx_msg void OnHotkeyScreenRecord();
	afx_msg void OnAdvancedShowRecording();
	afx_msg void OnUpdateAdvancedShowRecording(CCmdUI *pCmdUI);
	afx_msg void OnRibbonAmbient1();
	afx_msg void OnAdvancedTextures();
	afx_msg void OnPopupMove();
	afx_msg void OnHotkeyMove();
	afx_msg void OnHotkeyGlobalRotateX();
	afx_msg void OnHotkeyGlobalRotateY();
	afx_msg void OnHotkeyZoomIn();
	afx_msg void OnHotkeyZoomOut();
};

// ��ʾ����
void DrawCNString(const char* str);
void DrawCNString(CString str);

#ifndef _DEBUG  // SolSysView.cpp �еĵ��԰汾
inline CSolSysDoc* CSolSysView::GetDocument() const
   { return reinterpret_cast<CSolSysDoc*>(m_pDocument); }
#endif