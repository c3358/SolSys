#pragma once

#define MAXSATELLITE  8

//
//星球类
//

class CStar
{
public:
	float                  m_fSize,  //行星大小
		               m_fSections,  //绘图参数
		                   m_fPosX,  //位置X
		                   m_fPosY,  //位置Y
		                   m_fPosZ,  //位置Z
		             m_fSolarAngle,  //公转角度
		           m_fOwnAxisAngle;  //自转角度
	int               m_nTextureID;  //纹理ID

	CStar(void);
	~CStar(void);

	void Create(float Size, float Sections, float PosX, float PosY, float PosZ, float OwnAxisAngle, float SolarAngle, float TextureID);
};

class CPlanet : public CStar
{
public:
	CStar           m_Satellite[MAXSATELLITE];  //卫星数组
	int                  m_nNumberOfSatellite;  //卫星数量

	CPlanet(void);
	~CPlanet(void);
	CPlanet(int NumberOfSatellite);
	BOOL AddSatellite(int NumberOfSatellite = 1);
	void SetSatellite(int SatelliteIndex, float Size, float Sections, float PosX, float PosY, float PosZ, float OwnAxisAngle, float SolarAngle, float TextureID);
};