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

// SolSysView.h : CSolSysView 类的接口
//

#pragma once

#include "Cfloat3.h"
#include "Planet.h"
#include "Texture.h"

class CMainFrame;
class CTexturesDlg;

//用于播放wav格式音乐
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#include "Particle.h"
#include "SolSysDoc.h"

#define MAXTEXTURE              16              //最大纹理数
#define PARTICLE_NUMBER         1000
#define PI						3.141592654     //圆周率
#define DEG2RAD(angle)			angle*(PI/180)	//将角度转换为弧度
#define texture_id_star         0               //星空
#define texture_id_halo         1               //光晕
#define texture_id_sun          2               //太阳
#define texture_id_moon         3               //月亮
#define texture_id_mercury      4               //水星
#define texture_id_venus        5               //金星
#define texture_id_earth        6               //地球
#define texture_id_mars         7               //火星
#define texture_id_jupiter      8               //木星
#define texture_id_saturn       9               //土星
#define texture_id_uranus       10              //天王星
#define texture_id_neptune      11              //海王星
#define texture_id_pluto        12              //冥王星

struct GlobalPosition                           //全局坐标
{
	float fPosX, fPosY;
	float iDegreesX, iDegreesY;
	bool bRotationOn;
};

class CSolSysView : public CView
{
protected: // 仅从序列化创建
	CSolSysView();
	DECLARE_DYNCREATE(CSolSysView)

// 特性
public:
	CSolSysDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CSolSysView();
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

public:// 新增成员与函数
	int                              m_GLPixelIndex;
	HGLRC                              m_hGLContext;
	int                   m_nCometAngle, m_nCometPos; // 彗星角度、位置
	CPlanet                    mercury, venus, earth, // 水星， 金星， 地球
		                       mars, jupiter, saturn, // 火星， 木星， 土星
		                      uranus, neptune, pluto; // 天王星,海王星,冥王星
	CPlanet*              m_PlanetArray[MAXTEXTURE]; // 行星的指针数组
	CString           m_sTextureResource[MAXTEXTURE]; // 纹理资源数组
	CString              m_sPlanetNames[MAXTEXTURE];  //星球名字数组
	GLuint                  m_nTextures[MAXTEXTURE];  // 纹理数组
	int                    m_nTextureIDs[MAXTEXTURE];  // ID数组
	GLUquadricObj                       *m_pQuadric;  // 二次曲面对象
	int                                m_nMouseOldX;  // 鼠标旧位置X
	int                                m_nMouseOldY;  // 鼠标旧位置Y
	Cfloat3                               m_fRotate;  // 旋转向量
	Cfloat3                            m_fTranslate;  // 位移向量
	GLsizei                                 m_nWidth;  // 视口宽度
	GLsizei                                m_nHeight;  // 视口高度
	GLfloat                                 m_Aspect;  // 视口宽高比
	GLfloat                              m_SceneSize;  // 场景大小
	GlobalPosition                  m_globalPosition; // 全局控制变量
	GLfloat                         m_fRotationSpeed; // 场景旋转速度
	GLfloat								m_fStarAngle; // 星空旋转角度
	Cfloat3                            m_f3globalPos; // 全局位置

	//布尔变量
	bool                            m_bGlobalRotateX; // 全局绕X旋转
	bool						    m_bGlobalRotateY; // 全局绕Y旋转
	bool                          m_bChangeLight0Pos; // 改变光源0位置
	bool                          m_bChangeLight1Pos; // 改变光源1位置
	bool                               m_bShowOrbits; // 是否显示轨道
	int                                m_nShowPlanet; // 显示某个行星
	BOOL                              m_bInitialized;  // 是否已初始化
	BOOL                           m_bLeftButtonDown;  // 左键被按下
	BOOL                           m_bRotationPaused;  // 暂停运行
	bool                             m_bAntiAliasing;  // 是否启用抗锯齿
	bool                             m_bEnableLight0;  // 是否启用光源0
	bool                             m_bEnableLight1;  // 是否启用光源1

	//音乐
	bool                              m_bMusicPaused;  // 音乐暂停
	MCI_OPEN_PARMS                       m_OpenMusic;  // 打开音乐
	MCI_PLAY_PARMS                       m_PlayMusic;  // 播放音乐
	CString                            m_sOtherMusic;  // 载入别的音乐

	//视频
	bool                                m_bRecording;  //是否录制
	bool                               m_bShowRecWnd;  //显示窗口
	double                                     m_FPS;  //帧速率
	CvSize                                  m_CvSize;  //屏幕大小
	CvVideoWriter*                     m_MovieWriter;  //写视频设备
	IplImage*                             m_CurFrame;  //当前帧

	//快捷键
	HACCEL                                m_MyHotkey;  //快捷键
	bool                      m_bUseHotkeyShotScreen;  //使用快捷键截图
	bool                    m_bUseHotkeyRecordScreen;  //使用快捷键录制

	//粒子
	bool                            m_bMeteoricShower; //是否启用特效
	GLuint                    m_nTextures_Particle[8]; //粒子系统
	CParticle          m_MyParticles[PARTICLE_NUMBER]; //粒子纹理
	void InitParticle();
	void DrawParticle();

	//对话框
	CTexturesDlg*                       m_pTexturesDlg;

	//显示的文字
	CString                                m_sShowText;

	//模型
	void InitGL(void);
	bool CreateViewGLContext(HDC hDC);
	bool SetWindowPixelFormat(HDC hDC);
	void DrawStar();                       // 绘制星空
	void DrawSun();                        // 画太阳
	void DrawAllOrbits();                  // 画所有轨道
	void DrawOrbit(CPlanet planet);        // 画单个轨道
	void DrawAllPlanets();                 // 画所有星球
	void DrawPlanet(CPlanet planet);       // 画单个星球
	void DrawComet();                      // 画彗星
	void InitPlanets();                    // 对星球初始化
	void Rotate();                         // 旋转
	BOOL Display();                        // 显示

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
	//快捷键
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

// 显示汉字
void DrawCNString(const char* str);
void DrawCNString(CString str);

#ifndef _DEBUG  // SolSysView.cpp 中的调试版本
inline CSolSysDoc* CSolSysView::GetDocument() const
   { return reinterpret_cast<CSolSysDoc*>(m_pDocument); }
#endif