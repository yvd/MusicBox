#ifndef LIGHTS
#define LIGHTS
#include <iostream>
#include "GL/glut.h"
#include <GL/gl.h>
#include <stdlib.h>
#include <stdio.h>
#include "global.h"
#include "drawbox.cpp"
#include "textureloader.cpp"

void lights()
{
	GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat quad_c[]           =  {20.0};
	char t1[] = "./textures/light.bmp";
	texture1 = textureloader(t1);
	light_1 = glGenLists(1);
	glNewList(light_1,GL_COMPILE);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_EMISSION, bulb);
	glLightfv(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, quad_c);
	//glTranslatef(0.0,1.0,1.0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	drawBox(0.1,GL_QUADS);
	glEndList();

	GLfloat light_ambient1[] = { 0.4, 0.4, 0, 1.0 };
	GLfloat light_diffuse1[] = { 1.0, 1.0, 0, 1.0 };
	GLfloat light_specular1[] = { 1.0, 1.0, 0, 1.0 };
	GLfloat light_position1[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat quad_c1[]           =  {2.0};
	light_2 = glGenLists(1);
	glNewList(light_2,GL_COMPILE);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular1);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT1, GL_EMISSION, bulb);
	//glLightf(GL_LIGHT1,  GL_SPOT_CUTOFF, 60.0);
	glLightfv(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, quad_c1);
	drawBox(0.1,GL_QUADS);
	glEndList();

	GLfloat light_ambient2[] = { 0.01, 0.01, 0.01, 1.0 };
	GLfloat light_diffuse2[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular2[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position2[] = { -1.0, 0.0, 0.0, 0 };
	GLfloat quad_c2[]           =  {0.000005};

	sun = glGenLists(1);
	glNewList(sun, GL_COMPILE);
	glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular2);
	glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
	//glLightfv(GL_LIGHT2, GL_EMISSION, bulb);
	//glLightfv(GL_LIGHT2, GL_LINEAR_ATTENUATION, quad_c2);
	glEndList();

}


#endif