#ifndef BEZIER
#define BEZIER
#include <vector>
#include "pnt.h"
#include "GL/glut.h"
#include <GL/gl.h>
#include <cmath>
#include "drawbox.cpp"
#include "global.h"
class bezier
{
private:
	std::vector<pnt> c_pnts;
	int l;
	int choose[100][100];
public:
	bezier();
	void addCP(double ,double, double);
	void del_lastCP();
	pnt value(double );
	void draw(int );
	int nCi(int ,int);
	void drawcp();
	//~bezier();

	/* data */
};
#endif