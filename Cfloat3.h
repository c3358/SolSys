#pragma once

//
// ÈýÎ¬×ø±ê
//

class Cfloat3
{
private:
	GLfloat x, y, z;

public:
	Cfloat3(void);
	Cfloat3(GLfloat x, GLfloat y, GLfloat z);
	~Cfloat3(void);

	GLfloat& operator[](UINT xyz);
	GLfloat GetX();
	GLfloat GetY();
	GLfloat GetZ();
	friend Cfloat3 make_float3(GLfloat x = 0, GLfloat y = 0, GLfloat z = 0);
};
