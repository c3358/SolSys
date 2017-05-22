#include "stdafx.h"
#include "Particle.h"


CParticle::CParticle(void)
{
}


CParticle::~CParticle(void)
{
}

void CParticle::Create()
{
	m_fLife   = rand()%100;
	m_fRadius = 0.0003*(rand() % 100);
	m_fPosx   = 0.01*(rand() % 100)-0.5;
	m_fPosy   = 0.01*(rand() % 100)-0.5;
	m_fPosz   = 0.01*(rand() % 100)-0.5;
	m_fVy     = (rand()%10-4.0)/30;
	m_fVx     = (rand()%10-4.0)/60;
	m_fAy     = -4.9/40000;
	m_fAx     = -1.0/10000;
}