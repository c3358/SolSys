#include "stdafx.h"
#include "Cfloat3.h"


Cfloat3::Cfloat3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}
Cfloat3::Cfloat3(GLfloat x, GLfloat y, GLfloat z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Cfloat3::~Cfloat3()
{

}

GLfloat& Cfloat3::operator[](UINT xyz)
{
	switch (xyz)
	{
	case 1 : return x;
	case 2 : return y;
	case 3 : return z;
	default : AfxMessageBox(L"Error."); return x;
	}
}

GLfloat Cfloat3::GetX()
{
	return x;
}

GLfloat Cfloat3::GetY()
{
	return y;
}

GLfloat Cfloat3::GetZ()
{
	return z;
}

Cfloat3 make_float3(GLfloat x, GLfloat y, GLfloat z)
{
	return Cfloat3(x, y, z);
}