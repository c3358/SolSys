#pragma once

#define MAXSATELLITE  8

//
//������
//

class CStar
{
public:
	float                  m_fSize,  //���Ǵ�С
		               m_fSections,  //��ͼ����
		                   m_fPosX,  //λ��X
		                   m_fPosY,  //λ��Y
		                   m_fPosZ,  //λ��Z
		             m_fSolarAngle,  //��ת�Ƕ�
		           m_fOwnAxisAngle;  //��ת�Ƕ�
	int               m_nTextureID;  //����ID

	CStar(void);
	~CStar(void);

	void Create(float Size, float Sections, float PosX, float PosY, float PosZ, float OwnAxisAngle, float SolarAngle, float TextureID);
};

class CPlanet : public CStar
{
public:
	CStar           m_Satellite[MAXSATELLITE];  //��������
	int                  m_nNumberOfSatellite;  //��������

	CPlanet(void);
	~CPlanet(void);
	CPlanet(int NumberOfSatellite);
	BOOL AddSatellite(int NumberOfSatellite = 1);
	void SetSatellite(int SatelliteIndex, float Size, float Sections, float PosX, float PosY, float PosZ, float OwnAxisAngle, float SolarAngle, float TextureID);
};