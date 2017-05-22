#include "stdafx.h"
#include "Planet.h"


CStar::CStar(void)
{
	m_fSize				= 0;
	m_fSections			= 0;
	m_fPosX				= 0;
	m_fPosY				= 0;
	m_fPosZ				= 0;
	m_fOwnAxisAngle		= 0;
	m_fSolarAngle		= 0;
	m_nTextureID		= 0;
}


CStar::~CStar(void)
{
}

// Ϊ�������ò���
void CStar::Create(float Size, float Sections, float PosX, float PosY, float PosZ, float OwnAxisAngle, float SolarAngle, float TextureID)
{
	m_fSize				= Size;
	m_fSections			= Sections;
	m_fPosX				= PosX;
	m_fPosY				= PosY;
	m_fPosZ				= PosZ;
	m_fOwnAxisAngle		= OwnAxisAngle;
	m_fSolarAngle		= SolarAngle;
	m_nTextureID		= TextureID;
}


/************************************************************************/


CPlanet::CPlanet(void)
{
	m_nNumberOfSatellite = 0;
}

CPlanet::~CPlanet(void)
{
}

// ����һ������һЩ���ǵ�����
CPlanet::CPlanet(int NumberOfSatellite)
{
	m_nNumberOfSatellite = NumberOfSatellite;
}

// Ϊû�й������ǵ������������
BOOL CPlanet::AddSatellite(int NumberOfSatellite)
{
	int Number = m_nNumberOfSatellite+NumberOfSatellite;
	if (Number>=MAXSATELLITE) return FALSE;
	m_nNumberOfSatellite = Number;
	return TRUE;
}

// �������ǲ���
void CPlanet::SetSatellite(int SatelliteIndex, float Size, float Sections, float PosX, float PosY, float PosZ, float OwnAxisAngle, float SolarAngle, float TextureID)
{
	if (SatelliteIndex>=MAXSATELLITE) return;
	m_Satellite[SatelliteIndex].Create(Size, Sections, PosX, PosY, PosZ, OwnAxisAngle, SolarAngle, TextureID);
}