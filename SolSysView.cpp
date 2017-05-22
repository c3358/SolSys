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

// SolSysView.cpp : CSolSysView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "SolSys.h"
#endif

#include "SolSysDoc.h"
#include "SolSysView.h"
#include "Particle.h"
#include <math.h>
#include "MainFrm.h"
#include "TexturesDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSolSysView

IMPLEMENT_DYNCREATE(CSolSysView, CView)

BEGIN_MESSAGE_MAP(CSolSysView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSolSysView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_RIBBON_PAUSE, &CSolSysView::OnRibbonPause)
	ON_UPDATE_COMMAND_UI(ID_RIBBON_PAUSE, &CSolSysView::OnUpdateRibbonPause)
	ON_COMMAND(ID_RIBBON_GLOBAL_ROTATE_X, &CSolSysView::OnRibbonGlobalRotateX)
	ON_UPDATE_COMMAND_UI(ID_RIBBON_GLOBAL_ROTATE_X, &CSolSysView::OnUpdateRibbonGlobalRotateX)
	ON_COMMAND(ID_RIBBON_GLOBAL_ROTATE_Y, &CSolSysView::OnRibbonGlobalRotateY)
	ON_UPDATE_COMMAND_UI(ID_RIBBON_GLOBAL_ROTATE_Y, &CSolSysView::OnUpdateRibbonGlobalRotateY)
	ON_COMMAND(ID_APP_EXIT, &CSolSysView::OnAppExit)
	ON_COMMAND(ID_RIBBON_AMBIENT0, &CSolSysView::OnRibbonAmbient0)
	ON_COMMAND(ID_POPUP_SCREEN_SHOT, &CSolSysView::OnPopupScreenShot)
	ON_COMMAND(ID_RIBBON_LOAD_MP3, &CSolSysView::OnRibbonLoadMp3)
	ON_COMMAND(ID_RIBBON_LOAD_OTHERS, &CSolSysView::OnRibbonLoadOthers)
	ON_COMMAND(ID_HOTKEY_SCREEN_SHOT, &CSolSysView::OnHotkeyScreenShot)
	ON_UPDATE_COMMAND_UI(ID_RIBBON_LOAD_MP3, &CSolSysView::OnUpdateRibbonLoadMp3)
	ON_COMMAND(ID_SHOW_PLANET, &CSolSysView::OnShowPlanet)
	ON_COMMAND(ID_SHOW_ORBITS, &CSolSysView::OnShowOrbits)
	ON_UPDATE_COMMAND_UI(ID_SHOW_ORBITS, &CSolSysView::OnUpdateShowOrbits)
	ON_COMMAND(ID_ADVANCED_ANTI_ALIASING, &CSolSysView::OnAdvancedAntiAliasing)
	ON_UPDATE_COMMAND_UI(ID_ADVANCED_ANTI_ALIASING, &CSolSysView::OnUpdateAdvancedAntiAliasing)
	ON_COMMAND(ID_ADVANCED_LIGHT0, &CSolSysView::OnAdvancedLight0)
	ON_UPDATE_COMMAND_UI(ID_ADVANCED_LIGHT0, &CSolSysView::OnUpdateAdvancedLight0)
	ON_COMMAND(ID_ADVANCED_LIGHT1, &CSolSysView::OnAdvancedLight1)
	ON_UPDATE_COMMAND_UI(ID_ADVANCED_LIGHT1, &CSolSysView::OnUpdateAdvancedLight1)
	ON_COMMAND(ID_RIBBON_ROTATE_SPEED, &CSolSysView::OnRibbonRotateSpeed)
	ON_COMMAND(ID_HOTKEY_APP_EXIT, &CSolSysView::OnHotkeyAppExit)
	ON_COMMAND(ID_RIBBON_CHANGE_LIGHT0_POS, &CSolSysView::OnRibbonChangeLight0Pos)
	ON_UPDATE_COMMAND_UI(ID_RIBBON_CHANGE_LIGHT0_POS, &CSolSysView::OnUpdateRibbonChangeLight0Pos)
	ON_COMMAND(ID_RIBBON_CHANGE_LIGHT1_POS, &CSolSysView::OnRibbonChangeLight1Pos)
	ON_UPDATE_COMMAND_UI(ID_RIBBON_CHANGE_LIGHT1_POS, &CSolSysView::OnUpdateRibbonChangeLight1Pos)
	ON_COMMAND(ID_ADVANCED_METEORIC_SHOWER, &CSolSysView::OnAdvancedMeteoricShower)
	ON_UPDATE_COMMAND_UI(ID_ADVANCED_METEORIC_SHOWER, &CSolSysView::OnUpdateAdvancedMeteoricShower)
	ON_COMMAND(ID_POPUP_RECORDING, &CSolSysView::OnPopupRecording)
	ON_UPDATE_COMMAND_UI(ID_POPUP_RECORDING, &CSolSysView::OnUpdatePopupRecording)
	ON_COMMAND(ID_HOTKEY_PAUSE, &CSolSysView::OnHotkeyPause)
	ON_COMMAND(ID_HOTKEY_SCREEN_RECORD, &CSolSysView::OnHotkeyScreenRecord)
	ON_COMMAND(ID_ADVANCED_SHOW_RECORDING, &CSolSysView::OnAdvancedShowRecording)
	ON_UPDATE_COMMAND_UI(ID_ADVANCED_SHOW_RECORDING, &CSolSysView::OnUpdateAdvancedShowRecording)
	ON_COMMAND(ID_RIBBON_AMBIENT1, &CSolSysView::OnRibbonAmbient1)
	ON_COMMAND(ID_ADVANCED_TEXTURES, &CSolSysView::OnAdvancedTextures)
	ON_COMMAND(ID_POPUP_MOVE, &CSolSysView::OnPopupMove)
	ON_COMMAND(ID_HOTKEY_MOVE, &CSolSysView::OnHotkeyMove)
	ON_COMMAND(ID_HOTKEY_GLOBAL_ROTATE_X, &CSolSysView::OnHotkeyGlobalRotateX)
	ON_COMMAND(ID_HOTKEY_GLOBAL_ROTATE_Y, &CSolSysView::OnHotkeyGlobalRotateY)
	ON_COMMAND(ID_HOTKEY_ZOOM_IN, &CSolSysView::OnHotkeyZoomIn)
	ON_COMMAND(ID_HOTKEY_ZOOM_OUT, &CSolSysView::OnHotkeyZoomOut)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
END_MESSAGE_MAP()

// CSolSysView ����/����

// ��Դ0
GLfloat LightAmbient0[4] = { 1.0f, 0.0f, 1.0f, 0.0f };      // ���廷�������ɫ
GLfloat LightDiffuse0[4] = { 1.0f, 0.0f, 0.0f, 0.0f };      // ��������������ɫ
GLfloat LightPosition0[4] = { 0.0f, 0.0f, 0.0f, 0.5f };     // �����Դ��λ��

// ��Դ1
GLfloat LightAmbient1[4]  = {0.0f, 1.0f, 0.0f, 0.0f};
GLfloat LightDiffuse1[4]  = {1.0f, 1.0f, 1.0f, 0.0f};
GLfloat LightPosition1[4] = {0.0f, 0.0f, 3.0f, 0.5f};

CSolSysView::CSolSysView()
{
	m_GLPixelIndex = 0;
	m_fRotate = make_float3(30, 30, 0);
	m_fTranslate = make_float3(0, 0, -5);
	m_bLeftButtonDown = FALSE;
	m_bInitialized = FALSE;
	m_bRotationPaused = FALSE;
	m_SceneSize = 1.0;
	m_bGlobalRotateX = false;
	m_bGlobalRotateY = false;
	m_bChangeLight0Pos = false;
	m_bChangeLight1Pos = false;
	m_bShowOrbits = true;

	// ���ǵ�ָ�����顢�������顢ID�����
	m_nShowPlanet = 0;
	m_PlanetArray[0] = &mercury;
	m_PlanetArray[1] = &venus;
	m_PlanetArray[2] = &earth;
	m_PlanetArray[3] = &mars;
	m_PlanetArray[4] = &jupiter;
	m_PlanetArray[5] = &saturn;
	m_PlanetArray[6] = &uranus;
	m_PlanetArray[7] = &neptune;
	m_PlanetArray[8] = &pluto;
	m_sPlanetNames[0] = L"mercury";
	m_sPlanetNames[1] = L"venus";
	m_sPlanetNames[2] = L"earth";
	m_sPlanetNames[3] = L"mars";
	m_sPlanetNames[4] = L"jupiter";
	m_sPlanetNames[5] = L"saturn";
	m_sPlanetNames[6] = L"uranus";
	m_sPlanetNames[7] = L"neptune";
	m_sPlanetNames[8] = L"pluto";
	//��������·��
	LPTSTR  szPath = new TCHAR[MAX_PATH+1];
	GetCurrentDirectory(MAX_PATH, szPath);
	CString csFullPath(szPath);
	delete [] szPath;
	for (int i = 0; i<13; i++)
	{
		m_sTextureResource[i] += csFullPath + L"\\";
	}
	m_sTextureResource[0] += "Data\\mercury.jpg";
	m_sTextureResource[1] += "Data\\venus.jpg";
	m_sTextureResource[2] += "Data\\earth.bmp";
	m_sTextureResource[3] += "Data\\mars.jpg";
	m_sTextureResource[4] += "Data\\jupiter.jpg";
	m_sTextureResource[5] += "Data\\saturn.jpg";
	m_sTextureResource[6] += "Data\\uranus.jpg";
	m_sTextureResource[7] += "Data\\neptune.jpg";
	m_sTextureResource[8] += "Data\\pluto.bmp";
	m_sTextureResource[9] += "Data\\sun.bmp";
	m_sTextureResource[10] += "Data\\halo.bmp";
	m_sTextureResource[11] += "Data\\star.bmp";
	m_sTextureResource[12] += "Data\\moon.jpg";
	m_nTextureIDs[0] = texture_id_mercury;
	m_nTextureIDs[1] = texture_id_venus;
	m_nTextureIDs[2] = texture_id_earth;
	m_nTextureIDs[3] = texture_id_mars;
	m_nTextureIDs[4] = texture_id_jupiter;
	m_nTextureIDs[5] = texture_id_saturn;
	m_nTextureIDs[6] = texture_id_uranus;
	m_nTextureIDs[7] = texture_id_neptune;
	m_nTextureIDs[8] = texture_id_pluto;
	m_nTextureIDs[9] = texture_id_sun;
	m_nTextureIDs[10] = texture_id_halo;
	m_nTextureIDs[11] = texture_id_star;
	m_nTextureIDs[12] = texture_id_moon;

	// ����
	m_bMusicPaused = false;
	m_sOtherMusic = L"Music/Star wars - Star Wars Theme.mp3";
	m_OpenMusic.dwCallback = NULL;
	m_OpenMusic.lpstrAlias = NULL;
	m_OpenMusic.lpstrElementName = m_sOtherMusic;
	m_OpenMusic.lpstrDeviceType = L"mpegvideo";
	m_OpenMusic.wDeviceID = NULL; //�豸��

	// ��Ƶ
	m_bRecording = false;
	m_bShowRecWnd = false;

	// ��ݼ�
	m_MyHotkey = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	m_bUseHotkeyShotScreen = false;
	m_bUseHotkeyRecordScreen = false;

	// Model����
	m_nCometAngle = 0;
	m_nCometPos = 0;
	m_fRotationSpeed = 5;
	m_fStarAngle = 0;
	m_globalPosition.fPosX = 0;
	m_globalPosition.fPosY = 0;
	m_globalPosition.iDegreesX = 30;
	m_globalPosition.iDegreesY = 30;
	m_globalPosition.bRotationOn = true;
	m_f3globalPos = make_float3();

	// OpenGL����
	m_bAntiAliasing = false;
	m_bEnableLight0 = true;
	m_bEnableLight1 = true;

	//����
	m_bMeteoricShower = false;

	//��ģ̬�Ի���
	m_pTexturesDlg = NULL;

	//��ʾ������
	m_sShowText = L"solar system";
}

CSolSysView::~CSolSysView()
{
	if (m_pTexturesDlg != NULL)
	{
		delete m_pTexturesDlg;
	}
}

BOOL CSolSysView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	cs.style|=(WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
	return CView::PreCreateWindow(cs);
}

// CSolSysView ����

void CSolSysView::OnDraw(CDC* /*pDC*/)
{
	CSolSysDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CSolSysView ��ӡ


void CSolSysView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSolSysView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CSolSysView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CSolSysView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CSolSysView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSolSysView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSolSysView ���

#ifdef _DEBUG
void CSolSysView::AssertValid() const
{
	CView::AssertValid();
}

void CSolSysView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSolSysDoc* CSolSysView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSolSysDoc)));
	return (CSolSysDoc*)m_pDocument;
}
#endif //_DEBUG


// CSolSysView ��Ϣ�������

// *** ���� ***
int CSolSysView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	HWND hWnd = GetSafeHwnd();
	HDC hDC = ::GetDC(hWnd);
	if(SetWindowPixelFormat(hDC) == FALSE)
		return 0;
	if(CreateViewGLContext(hDC) == FALSE)
		return 0;
	//���ñ���ɫ
	COLORREF color = ::GetSysColor(COLOR_3DFACE);
	glClearColor((float)GetRValue(color)/255.0f, (float)GetGValue(color)/255.0f, (float)GetBValue(color)/255.0f, 1.0);
	glPolygonMode(GL_FRONT, GL_FILL);//�������ʾ��ʽ
	glPolygonMode(GL_BACK, GL_FILL);//�������ʾ��ʽ
	glShadeModel(GL_SMOOTH);//��ɫģʽ

	m_pTexturesDlg = new CTexturesDlg;
	m_pTexturesDlg->Create(IDD_TEXTURESDLG);
	m_pTexturesDlg->m_nComboPlanet = m_nTextureIDs[0];
	m_pTexturesDlg->m_sEditShowTextures = m_sTextureResource[0];

	return 0;
}

// *** ������ ***
bool CSolSysView::CreateViewGLContext(HDC hDC)
{
	m_hGLContext = wglCreateContext(hDC);

	if(m_hGLContext == NULL) return FALSE;

	if(wglMakeCurrent(hDC,m_hGLContext) == FALSE) return FALSE;

	return TRUE;
}

// *** ���ظ�ʽ ***
bool CSolSysView::SetWindowPixelFormat(HDC hDC)
{
	PIXELFORMATDESCRIPTOR pixelDesc;

	pixelDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelDesc.nVersion = 1;
	pixelDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_STEREO_DONTCARE;
	pixelDesc.iPixelType = PFD_TYPE_RGBA;
	pixelDesc.cColorBits = 32;
	pixelDesc.cRedBits = 8;
	pixelDesc.cRedShift = 16;
	pixelDesc.cGreenBits = 8;
	pixelDesc.cGreenShift = 8;
	pixelDesc.cBlueBits = 8;
	pixelDesc.cBlueShift = 0;
	pixelDesc.cAlphaBits = 0;
	pixelDesc.cAlphaShift = 0;
	pixelDesc.cAccumBits = 64;
	pixelDesc.cAccumRedBits = 16;
	pixelDesc.cAccumGreenBits = 16;
	pixelDesc.cAccumBlueBits = 16;
	pixelDesc.cAccumAlphaBits = 0;
	pixelDesc.cDepthBits = 32;
	pixelDesc.cStencilBits = 8;
	pixelDesc.cAuxBuffers = 0;
	pixelDesc.iLayerType = PFD_MAIN_PLANE;
	pixelDesc.bReserved = 0;
	pixelDesc.dwLayerMask = 0;
	pixelDesc.dwVisibleMask = 0;
	pixelDesc.dwDamageMask = 0;

	m_GLPixelIndex = ChoosePixelFormat(hDC,&pixelDesc);
	if(m_GLPixelIndex == 0) // Choose default
	{
		m_GLPixelIndex = 1;
		if(DescribePixelFormat(hDC,m_GLPixelIndex, sizeof(PIXELFORMATDESCRIPTOR),&pixelDesc) == 0) return FALSE;
	}
	if(SetPixelFormat(hDC,m_GLPixelIndex,&pixelDesc) == FALSE) return FALSE;
	return TRUE;
}

// *** ��ʼ������ ***
void CSolSysView::InitGL(void)
{
	//���Ϊ�ѳ�ʼ��
	m_bInitialized = TRUE;

	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(2.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_CULL_FACE);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// ��������
	for (int i = 0; i<13; i++)
	{
		BuildTexture(m_sTextureResource[i], m_nTextures[m_nTextureIDs[i]], TRUE);
	}

	glEnable(GL_TEXTURE_2D);                             // ����2D����ӳ��

	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient0);     // ���û�����
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse0);     // �����������
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient1);     // ���û�����
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse1);     // �����������

	m_pQuadric = gluNewQuadric();                        // ����һ���������ָ��
	gluQuadricTexture(m_pQuadric, GLU_TRUE);             // ������������
	gluQuadricDrawStyle(m_pQuadric, GLU_FILL);           // �������
	glEnable(GL_LIGHTING);                               // �򿪹���
	glEnable(GL_LIGHT0);                                 // �򿪹�Դ0
	glEnable(GL_LIGHT1);                                 // �򿪹�Դ1

	glRotatef(m_globalPosition.iDegreesX, 0.0, 1.0, 0.0);
	glRotatef(m_globalPosition.iDegreesY, 1.0, 0.0, 0.0);

	//��ʼ���������ö�ʱ��
	InitPlanets();
	SetTimer(1, 50, NULL);                               // ��ʱ��1

	//���뱳������
	if (mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT | MCI_WAIT, (DWORD)(LPVOID)&m_OpenMusic) == 0)
	{
		m_PlayMusic.dwFrom = 0;
		m_PlayMusic.dwCallback = NULL;
		mciSendCommand(m_OpenMusic.wDeviceID, MCI_PLAY, 0, (DWORD)&m_PlayMusic);
	}

	//��ʼ������
	InitParticle();
}

// *** �����ػ� ***
void CSolSysView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	
	m_nWidth = cx;
	m_nHeight = cy;
	m_Aspect = 1.0f*cx/cy;

	//��Ӵ�������ʱ��ͼ�α任����
	glViewport(0, 0, m_nWidth, m_nHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	
	if (m_nHeight == 0) m_nHeight = 1;	
	gluPerspective(45, m_Aspect, 1.0, 50.0) ;
	glTranslatef(0.0, 0.0, -5.0);
	glScalef(m_SceneSize, m_SceneSize, m_SceneSize);
	glMatrixMode(GL_MODELVIEW);
}

// *** ��ʱ������ ***
void CSolSysView::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		if (!m_bRotationPaused) Rotate();
		// X++, Y++
		if (m_bGlobalRotateX)
		{
			m_globalPosition.iDegreesX += 0.1f * m_fRotationSpeed;
			if (m_globalPosition.iDegreesX >= 360){m_globalPosition.iDegreesX -= 360;}
		}
		if (m_bGlobalRotateY)
		{
			m_globalPosition.iDegreesY += 0.1f * m_fRotationSpeed;
			if (m_globalPosition.iDegreesY >= 360){m_globalPosition.iDegreesY -= 360;}
		}
		Invalidate(FALSE);
	}
	if (nIDEvent == 2)
	{
		m_CurFrame = cvCreateImage(m_CvSize, IPL_DEPTH_8U, 3);
		glReadPixels(0, 0, m_CvSize.width, m_CvSize.height, GL_RGB, GL_UNSIGNED_BYTE, m_CurFrame->imageData);
		if (!m_CurFrame) return;
		cvFlip(m_CurFrame, NULL, 0);
		if (m_bShowRecWnd)
		{
			cvNamedWindow("����¼��...", CV_WINDOW_KEEPRATIO);
			cvShowImage("����¼��...", m_CurFrame);
		}
		cvWriteFrame(m_MovieWriter, m_CurFrame);
		cvReleaseImage(&m_CurFrame);
	}
	CView::OnTimer(nIDEvent);
}

// *** ���� ***
void CSolSysView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	if (!m_bInitialized) InitGL();
	Display();
	SwapBuffers(dc.m_ps.hdc);
	CView::OnPaint();
}

// ���ǿ�
void CSolSysView::DrawStar()
{
	glPushMatrix ();
	glEnable(GL_TEXTURE_2D);
	glTranslatef(-10.0f, 3.0f, 0.0f);
	glRotatef (m_fStarAngle, 0.0f, 0.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, m_nTextures[texture_id_star]);       // ���ǿ�����
	glBegin(GL_QUADS); 
	glNormal3f( 0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-30.0f, -30.0f, -5.0f);
	glTexCoord2f(6.0f, 0.0f); glVertex3f( 30.0f, -30.0f, -5.0f);
	glTexCoord2f(6.0f, 6.0f); glVertex3f( 30.0f,  30.0f, -5.0f);
	glTexCoord2f(0.0f, 6.0f); glVertex3f(-30.0f,  30.0f, -5.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix ();
}

// ��̫��
void CSolSysView::DrawSun()
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_nTextures[texture_id_halo]);
	glEnable(GL_BLEND);// �������
	glDisable(GL_DEPTH_TEST);
	//����̫������
	glDisable(GL_LIGHTING);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);// ����Դ����alphaͨ��ֵ�İ�͸����Ϻ���
	glColor4f(1.0f, 1.0f, 1.0f, 0.4f);// ����RGBAֵ
	glBegin(GL_QUADS);
	glNormal3f( 0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,-1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, m_nTextures[texture_id_sun]);
	gluQuadricDrawStyle(m_pQuadric, GLU_FILL);
	gluQuadricNormals (m_pQuadric, GLU_SMOOTH);
	gluQuadricTexture (m_pQuadric, GL_TRUE);
	gluSphere(m_pQuadric, 0.05, 32, 32);

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition0);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition1);
	glPopMatrix();
}

// �����й��
void CSolSysView::DrawAllOrbits()
{
	if (m_nShowPlanet == 0)//��������
	{
		for (int i = 0; i<9; i++)
			DrawOrbit(*m_PlanetArray[i]);
	}
	else if (m_nShowPlanet != 10)
		DrawOrbit(*m_PlanetArray[m_nShowPlanet-1]);
}

// �����
void CSolSysView::DrawOrbit(CPlanet planet)
{
	glDisable(GL_LIGHTING);
	glColor3f (0.7, 0.7, 0.7);

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++)
	{
		glVertex3f(cos(DEG2RAD(i))*planet.m_fPosZ, planet.m_fPosY, sin(DEG2RAD(i))*planet.m_fPosZ);
	}
	glEnd();

	glEnable(GL_LIGHTING);
}

// ����������
void CSolSysView::DrawAllPlanets()
{
	glEnable(GL_TEXTURE_2D);

	if (m_nShowPlanet == 0)//��������
	{
		for (int i = 0; i<9; i++)
			DrawPlanet(*m_PlanetArray[i]);
	}
	else if (m_nShowPlanet != 10)
		DrawPlanet(*m_PlanetArray[m_nShowPlanet-1]);

	glDisable(GL_TEXTURE_2D);
}

// ����������
void CSolSysView::DrawPlanet(CPlanet planet)
{
	glPushMatrix();

	glRotatef(planet.m_fSolarAngle, 0, -1, 0);
	glTranslatef(planet.m_fPosX, planet.m_fPosY, planet.m_fPosZ);
	glRotatef(planet.m_fOwnAxisAngle, 0, -1, 0);
	glRotatef(90.0, 1.0, 0.0, 0.0); 
	glBindTexture(GL_TEXTURE_2D, m_nTextures[planet.m_nTextureID]);
	gluQuadricDrawStyle(m_pQuadric, GLU_FILL);
	gluQuadricNormals (m_pQuadric, GLU_SMOOTH);
	gluQuadricTexture (m_pQuadric, GL_TRUE);
	gluSphere(m_pQuadric, planet.m_fSize, planet.m_fSections, planet.m_fSections);

	//��������
	if (planet.m_nNumberOfSatellite)
	{
		for (int i = 0; i<planet.m_nNumberOfSatellite; i++)
		{
			glPushMatrix();

			glRotatef(planet.m_Satellite[i].m_fSolarAngle, 0, -1, 0);
			glTranslatef(planet.m_Satellite[i].m_fPosX, planet.m_Satellite[i].m_fPosY, planet.m_Satellite[i].m_fPosZ);
			glRotatef(planet.m_Satellite[i].m_fOwnAxisAngle, 0, -1, 0);
			glRotatef(90.0, 0.0, 0.0, 1.0); 
			glBindTexture(GL_TEXTURE_2D, m_nTextures[planet.m_Satellite[i].m_nTextureID]);
			gluQuadricDrawStyle(m_pQuadric, GLU_FILL);
			gluQuadricNormals (m_pQuadric, GLU_SMOOTH);
			gluQuadricTexture (m_pQuadric, GL_TRUE);
			gluSphere(m_pQuadric, 0.02, 32, 32);

			glPopMatrix();
		}
	}

	glPopMatrix();
}

// ������
void CSolSysView::DrawComet()
{
	glPushMatrix();

	glRotatef(m_nCometAngle, 0, 0, 1);
	glTranslatef(1, 0, 0);
	glutSolidSphere(0.02, 20, 20);

	glPopMatrix();
}

// ��ʼ������
void CSolSysView::InitPlanets()
{
	mercury.m_fSize				= 0.04;
	mercury.m_fSections			= 32;
	mercury.m_fPosX				= 0;
	mercury.m_fPosY				= 0;
	mercury.m_fPosZ				= 0.1;
	mercury.m_fOwnAxisAngle		= 0;
	mercury.m_fSolarAngle		= 0;
	mercury.m_nTextureID		= texture_id_mercury;

	venus.m_fSize				= 0.09;
	venus.m_fSections			= 32;
	venus.m_fPosX				= 0;
	venus.m_fPosY				= 0;
	venus.m_fPosZ				= 0.3;
	venus.m_fOwnAxisAngle		= 0;
	venus.m_fSolarAngle			= 225;
	venus.m_nTextureID			= texture_id_venus;

	earth.m_fSize				= 0.09;
	earth.m_fSections			= 32;
	earth.m_fPosX				= 0;
	earth.m_fPosY				= 0;
	earth.m_fPosZ				= 0.5;
	earth.m_fOwnAxisAngle		= 0;
	earth.m_fSolarAngle			= 45;
	earth.m_nTextureID			= texture_id_earth;

	mars.m_fSize				= 0.07;
	mars.m_fSections			= 32;
	mars.m_fPosX				= 0;
	mars.m_fPosY				= 0;
	mars.m_fPosZ				= 0.8;
	mars.m_fOwnAxisAngle		= 0;
	mars.m_fSolarAngle			= 270;
	mars.m_nTextureID			= texture_id_mars;

	jupiter.m_fSize				= 0.26;
	jupiter.m_fSections			= 32;
	jupiter.m_fPosX				= 0;
	jupiter.m_fPosY				= 0;
	jupiter.m_fPosZ				= 1.3;
	jupiter.m_fOwnAxisAngle		= 0;
	jupiter.m_fSolarAngle		= 90;
	jupiter.m_nTextureID		= texture_id_jupiter;

	saturn.m_fSize				= 0.22;
	saturn.m_fSections			= 32;
	saturn.m_fPosX				= 0;
	saturn.m_fPosY				= 0;
	saturn.m_fPosZ				= 1.9;
	saturn.m_fOwnAxisAngle		= 0;
	saturn.m_fSolarAngle		= 315;
	saturn.m_nTextureID		    = texture_id_saturn;

	uranus.m_fSize				= 0.18;
	uranus.m_fSections			= 32;
	uranus.m_fPosX				= 0;
	uranus.m_fPosY				= 0;
	uranus.m_fPosZ				= 2.5;
	uranus.m_fOwnAxisAngle		= 0;
	uranus.m_fSolarAngle		= 135;
	uranus.m_nTextureID		    = texture_id_uranus;

	neptune.m_fSize			    = 0.2;
	neptune.m_fSections		    = 32;
	neptune.m_fPosX			    = 0;
	neptune.m_fPosY			    = 0;
	neptune.m_fPosZ		    	= 3.3;
	neptune.m_fOwnAxisAngle  	= 0;
	neptune.m_fSolarAngle		= 0;
	neptune.m_nTextureID		= texture_id_neptune;

	pluto.m_fSize				= 0.05;
	pluto.m_fSections			= 32;
	pluto.m_fPosX				= 0;
	pluto.m_fPosY				= 0;
	pluto.m_fPosZ				= 3.9;
	pluto.m_fOwnAxisAngle		= 0;
	pluto.m_fSolarAngle		    = 180;
	pluto.m_nTextureID			= texture_id_pluto;

	//Ϊ�������һ������,���趨����
	earth.AddSatellite();
	earth.SetSatellite(0, 0.01, 16, 0.1, 0, 0, 45, 90, texture_id_moon);
}

// ��ת
void CSolSysView::Rotate()
{
	if (m_globalPosition.bRotationOn)
	{
		// comet
		m_nCometAngle += 2;
		if (m_nCometAngle >= 360)
		{
			m_nCometAngle -= 360;
		}

		// star rotation
		m_fStarAngle += 0.01f;

		// solar rotation
		mercury.m_fSolarAngle += 1.6 * m_fRotationSpeed;
		if (mercury.m_fSolarAngle >= 360){mercury.m_fSolarAngle -= 360;}

		venus.m_fSolarAngle += 1.2 * m_fRotationSpeed;
		if (venus.m_fSolarAngle >= 360){venus.m_fSolarAngle -= 360;}

		earth.m_fSolarAngle += 1.1 * m_fRotationSpeed;
		if (earth.m_fSolarAngle >= 360){earth.m_fSolarAngle -= 360;}

		mars.m_fSolarAngle += 0.9 * m_fRotationSpeed;
		if (mars.m_fSolarAngle >= 360){mars.m_fSolarAngle -= 360;}

		jupiter.m_fSolarAngle += 0.1 * m_fRotationSpeed;
		if (jupiter.m_fSolarAngle >= 360){jupiter.m_fSolarAngle -= 360;}

		saturn.m_fSolarAngle += 0.3 * m_fRotationSpeed;
		if (saturn.m_fSolarAngle >= 360){saturn.m_fSolarAngle -= 360;}

		uranus.m_fSolarAngle += 0.06 * m_fRotationSpeed;
		if (uranus.m_fSolarAngle >= 360){uranus.m_fSolarAngle -= 360;}

		neptune.m_fSolarAngle += 0.03 * m_fRotationSpeed;
		if (neptune.m_fSolarAngle >= 360){neptune.m_fSolarAngle -= 360;}

		pluto.m_fSolarAngle += 0.01 * m_fRotationSpeed;
		if (pluto.m_fSolarAngle >= 360){pluto.m_fSolarAngle -= 360;}

		// axis rotation
		mercury.m_fOwnAxisAngle += 0.1;
		if (mercury.m_fOwnAxisAngle >= 360){mercury.m_fOwnAxisAngle -= 360;}

		venus.m_fOwnAxisAngle += 0.2;
		if (venus.m_fOwnAxisAngle >= 360){venus.m_fOwnAxisAngle -= 360;}

		earth.m_fOwnAxisAngle += 0.6;
		if (earth.m_fOwnAxisAngle >= 360){earth.m_fOwnAxisAngle -= 360;}

		mars.m_fOwnAxisAngle += 0.5;
		if (mars.m_fOwnAxisAngle >= 360){mars.m_fOwnAxisAngle -= 360;}

		jupiter.m_fOwnAxisAngle += 2.6;
		if (jupiter.m_fOwnAxisAngle >= 360){jupiter.m_fOwnAxisAngle -= 360;}

		saturn.m_fOwnAxisAngle += 2.5;
		if (saturn.m_fOwnAxisAngle >= 360){saturn.m_fOwnAxisAngle -= 360;}

		uranus.m_fOwnAxisAngle += 1.5;
		if (uranus.m_fOwnAxisAngle >= 360){uranus.m_fOwnAxisAngle -= 360;}

		neptune.m_fOwnAxisAngle += 1.7;
		if (neptune.m_fOwnAxisAngle >= 360){neptune.m_fOwnAxisAngle -= 360;}

		pluto.m_fOwnAxisAngle += 3;
		if (pluto.m_fOwnAxisAngle >= 360){pluto.m_fOwnAxisAngle -= 360;}

		// moon rotation
		earth.m_Satellite[0].m_fSolarAngle += 7.0 * m_fRotationSpeed;
		if (earth.m_Satellite[0].m_fSolarAngle >= 360){earth.m_Satellite[0].m_fSolarAngle -= 360;}

		earth.m_Satellite[0].m_fOwnAxisAngle += 14.0 * m_fRotationSpeed;
		if (earth.m_Satellite[0].m_fOwnAxisAngle >= 360){earth.m_Satellite[0].m_fOwnAxisAngle -= 360;}
	}
}

// ��ʾ
BOOL CSolSysView::Display() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glColor3f(1.0f, 1.0f, 1.0f);  // ��ɫ
	glRasterPos2f(0.0f, -1.0f);   // λ��
	DrawCNString(m_sShowText);    // ����

	DrawStar();        // �����ǿ�
	glTranslatef(m_f3globalPos[1], m_f3globalPos[2], m_f3globalPos[3]);//ȫ��λ��
	if (m_bMeteoricShower)
		DrawParticle();// ������
	DrawSun();         // ����̫��
	glRotatef(m_globalPosition.iDegreesX, 0.0, 1.0, 0.0);
	glRotatef(m_globalPosition.iDegreesY, 1.0, 0.0, 0.0);
	
	glPushMatrix();
	glRotatef(m_fRotate[1], 1.0, 0.0, 0.0);
	glRotatef(m_fRotate[2], 0.0, 1.0, 0.0);
	DrawAllPlanets();                       // ������������
	if (m_bShowOrbits)
		DrawAllOrbits();                    // �������й��
	if (m_nShowPlanet == 0 || m_nShowPlanet == 10)
		DrawComet();                        // ��������
	glPopMatrix();

	return TRUE;
}

//
// *** ��Ϣ��Ӧ ***
//


void CSolSysView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bLeftButtonDown = TRUE;
	CView::OnLButtonDown(nFlags, point);
}


void CSolSysView::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bLeftButtonDown = FALSE;
	CView::OnLButtonUp(nFlags, point);
}


void CSolSysView::OnMouseMove(UINT nFlags, CPoint point)
{
	float dx = (float)(point.x - m_nMouseOldX);
	float dy = (float)(point.y - m_nMouseOldY);
	if (m_bLeftButtonDown)
	{
		if (m_bChangeLight0Pos == 0 && m_bChangeLight1Pos == 0)
		{
			m_fRotate[1] += dy * 0.2f;
			m_fRotate[2] += dx * 0.2f;
		}
		if (m_bChangeLight0Pos)
		{
			LightPosition0[0] += dx * 0.01f;
			LightPosition0[1] += -dy * 0.01f;
			if (LightPosition0[0]<-24) LightPosition0[0] = -24;
			if (LightPosition0[1]<-24) LightPosition0[1] = -24;
			if (LightPosition0[0]>24) LightPosition0[0] = 24;
			if (LightPosition0[1]>24) LightPosition0[1] = 24;
			// �޸�״̬����Դλ����Ϣ
			CMainFrame *pMainFrame = (CMainFrame *)AfxGetMainWnd();
			pMainFrame->m_sLightPos.Format(L"��Դ0��(%.1f, %.1f, %.1f)����Դ1��(%.1f, %.1f, %.1f)", LightPosition0[0], LightPosition0[1], LightPosition0[2], LightPosition1[0], LightPosition1[1], LightPosition1[2]);
		}
		if (m_bChangeLight1Pos)
		{
			LightPosition1[0] += dx * 0.01f;
			LightPosition1[1] += -dy * 0.01f;
			if (LightPosition1[0]<-24) LightPosition1[0] = -24;
			if (LightPosition1[1]<-24) LightPosition1[1] = -24;
			if (LightPosition1[0]>24) LightPosition1[0] = 24;
			if (LightPosition1[1]>24) LightPosition1[1] = 24;
			CMainFrame *pMainFrame = (CMainFrame *)AfxGetMainWnd();
			pMainFrame->m_sLightPos.Format(L"��Դ0��(%.1f, %.1f, %.1f)����Դ1��(%.1f, %.1f, %.1f)", LightPosition0[0], LightPosition0[1], LightPosition0[2], LightPosition1[0], LightPosition1[1], LightPosition1[2]);
		}
	}
	m_nMouseOldX = point.x;
	m_nMouseOldY = point.y;
	CView::OnMouseMove(nFlags, point);
}

BOOL CSolSysView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (zDelta > 0)
	{
		m_SceneSize += 0.1f;
		m_SceneSize = std::min(10.0f, m_SceneSize);
	}
	else if (zDelta < 0)
	{
		m_SceneSize -= 0.1f;
		m_SceneSize = std::max(0.3f, m_SceneSize);
	}
	// �޸�״̬�����ű���
	CMainFrame *pMainFrame = (CMainFrame *)AfxGetMainWnd();
	pMainFrame->m_sZoomRatio.Format(L"���ţ�%1.1f", m_SceneSize);
	
	glViewport(0, 0, m_nWidth, m_nHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, m_Aspect, 1.0, 50.0) ;
	glTranslatef(0.0, 0.0, -5.0);
	glScalef(m_SceneSize, m_SceneSize, m_SceneSize);
	glMatrixMode(GL_MODELVIEW);
	InvalidateRect(FALSE);
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CSolSysView::OnRibbonPause()
{
	m_bRotationPaused = !m_bRotationPaused;
}

void CSolSysView::OnUpdateRibbonPause(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(m_bRotationPaused);
}

BOOL CSolSysView::OnEraseBkgnd(CDC* pDC)
{
	//ʹ�䲻Ҫ�ػ汳��
	return TRUE;
}

void CSolSysView::OnRibbonGlobalRotateX()
{
	m_bGlobalRotateX = !m_bGlobalRotateX;
}

void CSolSysView::OnUpdateRibbonGlobalRotateX(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(m_bGlobalRotateX);
}

void CSolSysView::OnRibbonGlobalRotateY()
{
	m_bGlobalRotateY = !m_bGlobalRotateY;
}

void CSolSysView::OnUpdateRibbonGlobalRotateY(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(m_bGlobalRotateY);
}

// �˳�����
void CSolSysView::OnAppExit()
{
	if(MessageBox(L"�˳�Ӧ�ó���?", L"��Ϣ", MB_YESNO | MB_ICONQUESTION) == IDYES)
		GetParent()->SendMessage(WM_CLOSE, 0, 0);
}

// ��ϢԤ����
BOOL CSolSysView::PreTranslateMessage(MSG* pMsg)
{
	if( pMsg->message == WM_KEYDOWN )
	{
		switch( pMsg->wParam )
		{
		case VK_ESCAPE://ESC
			{
				CMainFrame *pMainFrame = (CMainFrame *)AfxGetMainWnd();
				pMainFrame->EndFullScreen();
				return TRUE;
			}
		case VK_UP    : m_f3globalPos[2] += 0.01; InvalidateRect(FALSE); break;
		case VK_DOWN  : m_f3globalPos[2] -= 0.01; InvalidateRect(FALSE); break;
		case VK_LEFT  : m_f3globalPos[1] -= 0.01; InvalidateRect(FALSE); break;
		case VK_RIGHT : m_f3globalPos[1] += 0.01; InvalidateRect(FALSE); break;
		default:                                  break;
		}
	}
	if (m_MyHotkey && ::TranslateAccelerator(m_hWnd, m_MyHotkey, pMsg)) 
		return TRUE;

	return CView::PreTranslateMessage(pMsg);
}

// ���û�����0
void CSolSysView::OnRibbonAmbient0()
{
	CColorDialog dlg;
	COLORREF Temp;
	GLfloat R, G, B;
	R = LightAmbient0[0]*255;
	G = LightAmbient0[1]*255;
	B = LightAmbient0[2]*255;
	dlg.m_cc.Flags |= CC_RGBINIT | CC_FULLOPEN;
	dlg.m_cc.rgbResult = RGB(R, G, B);
	if(IDOK == dlg.DoModal())
	{
		Temp = dlg.m_cc.rgbResult;
		R = GetRValue(Temp);
		G = GetGValue(Temp);
		B = GetBValue(Temp);
		LightAmbient0[0] = R/255;
		LightAmbient0[1] = G/255;
		LightAmbient0[2] = B/255;
		glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient0);
	}
}

// ���û�����1
void CSolSysView::OnRibbonAmbient1()
{
	CColorDialog dlg;
	COLORREF Temp;
	GLfloat R, G, B;
	R = LightAmbient1[0]*255;
	G = LightAmbient1[1]*255;
	B = LightAmbient1[2]*255;
	dlg.m_cc.Flags |= CC_RGBINIT | CC_FULLOPEN;
	dlg.m_cc.rgbResult = RGB(R, G, B);
	if(IDOK == dlg.DoModal())
	{
		Temp = dlg.m_cc.rgbResult;
		R = GetRValue(Temp);
		G = GetGValue(Temp);
		B = GetBValue(Temp);
		LightAmbient1[0] = R/255;
		LightAmbient1[1] = G/255;
		LightAmbient1[2] = B/255;
		glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient1);
	}
}

// ��ȡ��ǰ��Ļ������
void CSolSysView::OnPopupScreenShot()
{
	CRect rect;
	GetClientRect(&rect);
	int w = rect.Width(), h = rect.Height();
	if ((w % 4) != 0)
	{
		//��ȱ�����4��������
		int dw = 4 - w % 4;
		w = w + dw;
	}
	DWORD Length = w * h * 3;//RGBͼ��
	GLbyte* dataDes = new GLbyte[w*h*3];
	glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, dataDes); 
	// ��������ͼ��
	CImage* pImage = new CImage;
	pImage->Create(w, h, 24, Length);
	GLbyte *pBits = (GLbyte *)pImage->GetBits()+(pImage->GetPitch()*(pImage->GetHeight()-1));
	memcpy(pBits, dataDes, Length);
	delete [] dataDes;

	// �������ͼ��
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	CString CurTime;
	CurTime.Format(L"%04d%02d%02d%02d%02d%02d", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond);
	CString strFileName = L"";
	CString strExtension = L"";
	if (m_bUseHotkeyShotScreen)
	{
		if(!PathIsDirectory(L"ScreenShot"))
		{         
			if(!CreateDirectory(L"ScreenShot", NULL))
			{
				MessageBox(L"Failed!");
				delete pImage;
				return;
			}
		}
		strFileName = L"ScreenShot/" + CurTime + L".bmp";
		// ״̬��������ʾ��Ϣ
		CMainFrame *pMainFrame = (CMainFrame *)AfxGetMainWnd();
		pMainFrame->m_sScreenShotMsg = L"��ͼ��" + strFileName;
		m_bUseHotkeyShotScreen = false;
	}
	else
	{
		CFileDialog dlg(FALSE, NULL, CurTime, NULL, TEXT("BMP λͼ�ļ�(*.bmp)|*.bmp|JPEG ͼ���ļ�(*.jpg)|*.jpg|PNG ͼ���ļ�(*.png)|*.png|TIF �ļ���ʽ(*.tif)|*.tif|GIF ͼ���ļ�(*.gif)|*.gif||"), NULL);
		dlg.m_ofn.hwndOwner = m_hWnd;
		dlg.m_ofn.lStructSize = sizeof(OPENFILENAME);
		dlg.m_ofn.lpstrTitle = TEXT("����ͼ���ļ�...\0");
		dlg.m_ofn.nMaxFile = MAX_PATH;

		if ( dlg.DoModal() != IDOK)
		{
			delete pImage;
			return;
		}

		strFileName += dlg.GetPathName();

		switch (dlg.m_ofn.nFilterIndex)
		{
		case 1 : strExtension = L"bmp"; break;
		case 2 : strExtension = L"jpg"; break;
		case 3 : strExtension = L"png"; break;
		case 4 : strExtension = L"tif"; break;
		case 5 : strExtension = L"gif"; break;
		default:                        break;
		}
		if (strFileName.Right(4) != L".bmp" && strFileName.Right(4) != L".jpg" && strFileName.Right(4) != L".png" && strFileName.Right(4) != L".tif" && strFileName.Right(4) != L".gif")
		{
			strFileName = strFileName + '.' + strExtension;
		}
	}

	if (pImage->Save(strFileName) != S_OK) MessageBox(L"����ͼƬʧ�ܣ�");
	delete pImage;
}

// Mp3
void CSolSysView::OnRibbonLoadMp3()
{
	m_bMusicPaused = !m_bMusicPaused;
	sndPlaySound(NULL, SND_ASYNC);
	if (m_bMusicPaused) //��ͣ
		mciSendCommand(m_OpenMusic.wDeviceID, MCI_PAUSE, 0, (DWORD)&m_PlayMusic);
	else
		mciSendCommand(m_OpenMusic.wDeviceID, MCI_PLAY, 0, (DWORD)&m_PlayMusic);
}

void CSolSysView::OnUpdateRibbonLoadMp3(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(!m_bMusicPaused);
}

// ������...
void CSolSysView::OnRibbonLoadOthers()
{
	CFileDialog hFileDlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_READONLY, TEXT("�����ļ�(*.*)|*.* | ͼ���ļ�(*.mp3;*.wma;*.wav;*.wmv;*.mid)|*.mp3;*.wma;*.wav;*.wmv;*.mid||"), NULL);
	hFileDlg.m_ofn.nFilterIndex = 2;
	hFileDlg.m_ofn.hwndOwner = m_hWnd;
	hFileDlg.m_ofn.lStructSize = sizeof(OPENFILENAME);
	hFileDlg.m_ofn.lpstrTitle = TEXT("�������ļ�...\0");
	hFileDlg.m_ofn.nMaxFile = MAX_PATH;

	if(hFileDlg.DoModal() != IDOK) return;
	m_sOtherMusic = hFileDlg.GetPathName();
	m_OpenMusic.lpstrElementName = m_sOtherMusic;
	mciSendCommand(m_OpenMusic.wDeviceID, MCI_CLOSE, MCI_WAIT, (DWORD)&m_PlayMusic);
	//���뱳������
	if (mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT | MCI_WAIT, (DWORD)(LPVOID)&m_OpenMusic) == 0)
	{
		m_PlayMusic.dwFrom = 0;
		m_PlayMusic.dwCallback = NULL;
		mciSendCommand(m_OpenMusic.wDeviceID, MCI_PLAY, 0, (DWORD)&m_PlayMusic);
		m_bMusicPaused = false;
	}
}

// ��ͼ��ݼ��� Ctrl + G
void CSolSysView::OnHotkeyScreenShot()
{
	m_bUseHotkeyShotScreen = true;
	OnPopupScreenShot();
}

// ������ʾĳ������
void CSolSysView::OnShowPlanet()
{
	// ��ȡ�ؼ�ָ��
	CMainFrame *pMainFrame = (CMainFrame *)AfxGetMainWnd();
	CMFCRibbonComboBox* pRibbonComboBox = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, pMainFrame->GetRibbonBar()->FindByID(ID_SHOW_PLANET));
	m_nShowPlanet = pRibbonComboBox->GetCurSel();
	if (m_nShowPlanet == 0)
	{
		m_sShowText = L"solar system";
	}
	else if (m_nShowPlanet == 10)
	{
		m_sShowText = "comet";
	}
	else
	{
		m_sShowText = m_sPlanetNames[m_nShowPlanet-1];
	}
}

// �Ƿ���ʾ���
void CSolSysView::OnShowOrbits()
{
	m_bShowOrbits = !m_bShowOrbits;
}

void CSolSysView::OnUpdateShowOrbits(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(m_bShowOrbits);
}

// �Ƿ񿹾��
void CSolSysView::OnAdvancedAntiAliasing()
{
	m_bAntiAliasing = !m_bAntiAliasing;
	if (m_bAntiAliasing)
	{
		glEnable(GL_LINE_SMOOTH);//�����
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	}
	else
		glDisable(GL_LINE_SMOOTH);
}

void CSolSysView::OnUpdateAdvancedAntiAliasing(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(m_bAntiAliasing);
}

// �Ƿ�򿪹�Դ0
void CSolSysView::OnAdvancedLight0()
{
	m_bEnableLight0 = !m_bEnableLight0;
	if (m_bEnableLight0)
		glEnable(GL_LIGHT0);
	else
		glDisable(GL_LIGHT0);
}

void CSolSysView::OnUpdateAdvancedLight0(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(m_bEnableLight0);
}

// �Ƿ�򿪹�Դ1
void CSolSysView::OnAdvancedLight1()
{
	m_bEnableLight1 = !m_bEnableLight1;
	if (m_bEnableLight1)
		glEnable(GL_LIGHT1);
	else
		glDisable(GL_LIGHT1);
}

void CSolSysView::OnUpdateAdvancedLight1(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(m_bEnableLight1);
}

// �������ǵ������ٶ�
void CSolSysView::OnRibbonRotateSpeed()
{
	CMainFrame *pMainFrame = (CMainFrame *)AfxGetMainWnd();
	CMFCRibbonEdit* pRibbonEdit = dynamic_cast<CMFCRibbonEdit*>(pMainFrame->GetRibbonBar()->FindByID(ID_RIBBON_ROTATE_SPEED));
	ASSERT_VALID(pRibbonEdit);
	CString sValue = pRibbonEdit->GetEditText();
	int nValue = _ttoi(sValue);
	m_fRotationSpeed = nValue;
}

// ��ݼ���Ctrl + Q, �˳�����
void CSolSysView::OnHotkeyAppExit()
{
	OnAppExit();
}

// �Ƿ��ƶ���Դ0�ı��
void CSolSysView::OnRibbonChangeLight0Pos()
{
	m_bChangeLight0Pos = !m_bChangeLight0Pos;
	if (m_bChangeLight0Pos) m_bChangeLight1Pos = false;
}

void CSolSysView::OnUpdateRibbonChangeLight0Pos(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(m_bChangeLight0Pos);
	pCmdUI->Enable(m_bEnableLight0);//ֻ�п�����Դ0�����ƶ���λ��
}

// �Ƿ��ƶ���Դ1�ı��
void CSolSysView::OnRibbonChangeLight1Pos()
{
	m_bChangeLight1Pos = !m_bChangeLight1Pos;
	if (m_bChangeLight1Pos) m_bChangeLight0Pos = false;
}

void CSolSysView::OnUpdateRibbonChangeLight1Pos(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(m_bChangeLight1Pos);
	pCmdUI->Enable(m_bEnableLight1);//ֻ�п�����Դ1�����ƶ���λ��
}

// ��ʼ������
void CSolSysView::InitParticle()
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	for (int i = 0; i<PARTICLE_NUMBER; i++)
	{		
		m_MyParticles[i].Create();
	}

	BuildTexture(L"Particle/fig1.bmp", m_nTextures_Particle[0]);
	BuildTexture(L"Particle/fig2.bmp", m_nTextures_Particle[1]);
	BuildTexture(L"Particle/fig3.bmp", m_nTextures_Particle[2]);
	BuildTexture(L"Particle/fig4.bmp", m_nTextures_Particle[3]);
	BuildTexture(L"Particle/fig5.bmp", m_nTextures_Particle[4]);
	BuildTexture(L"Particle/fig6.bmp", m_nTextures_Particle[5]);
	BuildTexture(L"Particle/fig7.bmp", m_nTextures_Particle[6]);
	BuildTexture(L"Particle/fig8.bmp", m_nTextures_Particle[7]);

	glNewList(8, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-1, -1, 0.0);
	glTexCoord2f(1, 0); glVertex3f(1, -1, 0.0);
	glTexCoord2f(1, 1); glVertex3f(1, 1, 0.0);
	glTexCoord2f(0, 1); glVertex3f(-1, 1, 0.0);
	glEnd();
	glEndList();

	for (int i = 0; i<8; i++)
	{
		glNewList(i,GL_COMPILE);
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBindTexture(GL_TEXTURE_2D, m_nTextures_Particle[i]);
		glCallList(8);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glEndList();
	}
}

// ������
void CSolSysView::DrawParticle()
{
	glPushMatrix();
	for (int i = 0;i<PARTICLE_NUMBER;i++)
	{
		if(m_MyParticles[i].m_fLife>0)
		{
			int j = rand()%7+1;
			glPushMatrix();
			glTranslatef(m_MyParticles[i].m_fPosx,m_MyParticles[i].m_fPosy,m_MyParticles[i].m_fPosz);
			glScalef(m_MyParticles[i].m_fRadius,m_MyParticles[i].m_fRadius,1.0);
			glCallList(j);
			glPopMatrix();
			m_MyParticles[i].m_fLife -= (rand()%100)/120.0f+0.0003f;
			m_MyParticles[i].m_fVy   += m_MyParticles[i].m_fAy;
			m_MyParticles[i].m_fVx   += m_MyParticles[i].m_fAx;
			m_MyParticles[i].m_fPosy += m_MyParticles[i].m_fVy;
			m_MyParticles[i].m_fPosx += m_MyParticles[i].m_fVx;
		}
		if(m_MyParticles[i].m_fLife <= 0)
		{
			m_MyParticles[i].Create();
		}
	}
	glPopMatrix();
}

// �Ƿ�������Ч��
void CSolSysView::OnAdvancedMeteoricShower()
{
	m_bMeteoricShower = !m_bMeteoricShower;
}

void CSolSysView::OnUpdateAdvancedMeteoricShower(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bMeteoricShower);
}


//
// *** ��Ƶ ***
//


// ��ʼ¼��
void CSolSysView::OnPopupRecording()
{
	m_bRecording = !m_bRecording;
	if (m_bRecording)
	{
		CRect rect;
		GetClientRect(&rect);
		m_CvSize = cvSize(rect.Width(), rect.Height());
		m_FPS = 15;

		SYSTEMTIME sys;
		GetLocalTime(&sys);
		CString CurTime;
		CurTime.Format(L"%04d%02d%02d%02d%02d%02d", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond);
		CString strFileName = L"";

		if (m_bUseHotkeyRecordScreen)
		{
			if(!PathIsDirectory(L"ScreenRecord"))
			{         
				if(!CreateDirectory(L"ScreenRecord", NULL))
				{
					MessageBox(L"Failed!");
					m_bRecording = false;
					return;
				}
			}
			strFileName = L"ScreenRecord/" + CurTime + L".avi";
			m_bUseHotkeyRecordScreen = false;
		}
		else
		{
			CFileDialog dlg(FALSE, NULL, CurTime, NULL, TEXT("AVI ��Ƶ(*.avi)|*.avi||"), NULL);
			dlg.m_ofn.hwndOwner = m_hWnd;
			dlg.m_ofn.lStructSize = sizeof(OPENFILENAME);
			dlg.m_ofn.lpstrTitle = TEXT("������Ƶ�ļ�...\0");
			dlg.m_ofn.nMaxFile = MAX_PATH;
			if ( dlg.DoModal() != IDOK)
			{
				m_bRecording = false;
				return;
			}
			strFileName += dlg.GetPathName();
			if (strFileName.Right(4) != L".avi")
			{
				strFileName = strFileName + L".avi";
			}
		}
		USES_CONVERSION;
		char* filename = W2A(strFileName);
		m_MovieWriter = cvCreateVideoWriter(filename, CV_FOURCC('X', 'V', 'I', 'D'), m_FPS, m_CvSize);
		SetTimer(2, 60, NULL);
		// ״̬��������ʾ��Ϣ
		CMainFrame *pMainFrame = (CMainFrame *)AfxGetMainWnd();
		pMainFrame->m_sScreenShotMsg = L"��Ƶ��" + strFileName;
	}
	else
	{
		KillTimer(2);
		cvReleaseVideoWriter(&m_MovieWriter);
		cvDestroyAllWindows();
	}
}

void CSolSysView::OnUpdatePopupRecording(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bRecording);
}

// ��ͣ��Ctrl+P
void CSolSysView::OnHotkeyPause()
{
	OnRibbonPause();
}

// ¼�ƣ�Ctrl+R
void CSolSysView::OnHotkeyScreenRecord()
{
	m_bUseHotkeyRecordScreen = true;
	OnPopupRecording();
}

// ��ʾ¼����Ƶ�Ĵ���
void CSolSysView::OnAdvancedShowRecording()
{
	m_bShowRecWnd = !m_bShowRecWnd;
	if (m_bShowRecWnd == false)
		cvDestroyAllWindows();
}


void CSolSysView::OnUpdateAdvancedShowRecording(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bShowRecWnd);
	pCmdUI->Enable(m_bRecording);
}

// ��������Ի���
void CSolSysView::OnAdvancedTextures()
{
	m_pTexturesDlg->ShowWindow(SW_SHOW);
	m_pTexturesDlg->ChangeEditShowTextures();
	CRect rect;
	m_pTexturesDlg->GetClientRect(&rect);
	::SetWindowPos(m_pTexturesDlg->GetSafeHwnd(), HWND_TOPMOST, 0, 0, rect.Width(), rect.Height(), SWP_NOMOVE || SWP_NOSIZE);
}

// ʹ����ı��ӽ���Ч
void CSolSysView::OnPopupMove()
{
	m_bChangeLight0Pos = m_bChangeLight1Pos = false;
	m_bRotationPaused = FALSE;
}

// �ӽǣ�Ctrl+V
void CSolSysView::OnHotkeyMove()
{
	OnPopupMove();
}

// X++��Ctrl+X
void CSolSysView::OnHotkeyGlobalRotateX()
{
	OnRibbonGlobalRotateX();
}

// Y++��Ctrl+Y
void CSolSysView::OnHotkeyGlobalRotateY()
{
	OnRibbonGlobalRotateY();
}

// �Ŵ�+
void CSolSysView::OnHotkeyZoomIn()
{
	m_SceneSize += 0.01f;
	m_SceneSize = std::min(10.0f, m_SceneSize);
	glViewport(0, 0, m_nWidth, m_nHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, m_Aspect, 1.0, 50.0) ;
	glTranslatef(0.0, 0.0, -5.0);
	glScalef(m_SceneSize, m_SceneSize, m_SceneSize);
	glMatrixMode(GL_MODELVIEW);
	InvalidateRect(FALSE);
}

// ��С��-
void CSolSysView::OnHotkeyZoomOut()
{
	m_SceneSize -= 0.01f;
	m_SceneSize = std::max(0.3f, m_SceneSize);
	glViewport(0, 0, m_nWidth, m_nHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, m_Aspect, 1.0, 50.0) ;
	glTranslatef(0.0, 0.0, -5.0);
	glScalef(m_SceneSize, m_SceneSize, m_SceneSize);
	glMatrixMode(GL_MODELVIEW);
	InvalidateRect(FALSE);
}
//
//********** ��ʾ�ַ� **********
//
void DrawCNString(const char* str)
{
	int len, i;
	wchar_t* wstring;
	HDC hDC = wglGetCurrentDC(); //��ȡ��ʾ�豸
	GLuint list = glGenLists(1); //����1����ʾ�б�
	//�����ַ��ĸ���
	//�����˫�ֽ��ַ��ģ����������ַ����������ֽڲ���һ���ַ�
	//����һ���ֽ���һ���ַ�
	len = 0;
	for(i=0; str[i] != '\0'; ++i)
	{
		if( IsDBCSLeadByte(str[i]) )
			++i;
		++len;
	}
	// ������ַ�ת��Ϊ���ַ�
	wstring = (wchar_t*)malloc((len+1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len);
	wstring[len] = L'';// ֻ��ת���,�������������wchar_t
	// �������ַ�
	for(i=0; i<len; ++i)
	{
		wglUseFontBitmapsW(hDC, wstring[i], 1, list);
		glCallList(list);
	}
	// ����������ʱ��Դ
	free(wstring);
	glDeleteLists(list, 1);
}

// ����
void DrawCNString(CString str)
{
	USES_CONVERSION;
	char* target = W2A(str);
	DrawCNString(target);
}