#pragma once
//
//������
//
class CParticle
{
public:
	GLfloat m_fPosx;     //����x
	GLfloat m_fPosy;     //����y
	GLfloat m_fPosz;     //����z
	GLfloat m_fRadius;   //�뾶
	GLfloat m_fLife;     //����
	GLfloat m_fVy, m_fVx;//
	GLfloat m_fAy, m_fAx;//

public:
	CParticle(void);
	~CParticle(void);

	void Create();  //����һ������
};