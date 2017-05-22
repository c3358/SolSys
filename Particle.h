#pragma once
//
//粒子类
//
class CParticle
{
public:
	GLfloat m_fPosx;     //坐标x
	GLfloat m_fPosy;     //坐标y
	GLfloat m_fPosz;     //坐标z
	GLfloat m_fRadius;   //半径
	GLfloat m_fLife;     //生命
	GLfloat m_fVy, m_fVx;//
	GLfloat m_fAy, m_fAx;//

public:
	CParticle(void);
	~CParticle(void);

	void Create();  //创建一颗粒子
};