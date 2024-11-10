#pragma once

#include <GL/glew.h>

//#include "../../GL/include/GL/glaux.H"
#include "../../GL/include/GL/glut.h"
//#include "../../GL/include/GL/GL.h"

//#include <GL/glut.h>

const double M_PI = 3.14;

class Sphere
{
public:
	/* �����������. ������� �������������������� ����� */
	Sphere(void);
	~Sphere(void);
	double x, y, z;  /* ���������� ������ ����� */
	double r;          /* ������ ����� */
	/* �����������. ������� ����� � ����������� �������� x, y, z, r */
	Sphere (double xc, double yc, double zc, double rc)
	{ x=xc; y=yc; z=zc; r=rc; }
	/* ������������ ����� ����� */
	double ob()   { return r*r*r*4*M_PI/3; }

	/* ������������ ������� ����������� ����� */
	double pov()   { return r*r*4*M_PI; }

	void CALLBACK resize(int width,int height);
	void CALLBACK display(void);
};

