#ifndef BOX
#define BOX
#include <iostream>
#include "GL/glut.h"
#include <GL/gl.h>
#include <stdlib.h>
#include <stdio.h>
#include "global.h"
#include "textureloader.cpp"
void box()
{
	comp = glGenLists(1);
	glNewList(comp,GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glMaterialfv(GL_FRONT, GL_AMBIENT, white);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	char t1[] = "./textures/w3.bmp";
	char t2[] = "./textures/w2.bmp";
	texture1 = textureloader(t1);
	texture2 = textureloader(t2);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texture1);
	
	//front side
	glBegin(GL_POLYGON);
	glNormal3d(0,0,-1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(  0.4, 0.2, -0.2 );
	glTexCoord2f(1.0, 0.0);
	glVertex3f(  0.4,  -0.2, -0.2 );
	glTexCoord2f(0.0, 0.0);
	glVertex3f( -0.4,  -0.2, -0.2 );
	glTexCoord2f(0.0, 1.0);
	glVertex3f( -0.4, 0.2, -0.2 );
	glEnd();
	 
	//right side
	glBegin(GL_POLYGON);
	glNormal3d(1,0,0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f( 0.4, 0.2,  0.2 );
	glTexCoord2f(1.0, 0.0);
	glVertex3f( 0.4, -0.2, 0.2 );
	glTexCoord2f(0.0, 0.0);
	glVertex3f( 0.4,  -0.2, -0.2 );
	glTexCoord2f(0.0, 1.0);
	glVertex3f( 0.4,  0.2,  -0.2 );
	glEnd();
	 
	// left side
	glBegin(GL_POLYGON);
	glNormal3d(-1,0,0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f( -0.4, 0.2, -0.2 );
	glTexCoord2f(1.0, 0.0);
	glVertex3f( -0.4, -0.2,  -0.2 );
	glTexCoord2f(0.0, 0.0);
	glVertex3f( -0.4,  -0.2,  0.2 );
	glTexCoord2f(0.0, 1.0);
	glVertex3f( -0.4,  0.2, 0.2 );
	
	glEnd();
	 
	// backside
	glBegin(GL_POLYGON);
	glNormal3d(0,0,1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(  -0.4, 0.2,  0.2 );
	glTexCoord2f(1.0, 0.0);
	glVertex3f( -0.4, -0.2,  0.2 );
	glTexCoord2f(0.0, 0.0);
	glVertex3f( 0.4, -0.2, 0.2 );
	glTexCoord2f(0.0, 1.0);
	glVertex3f(  0.4, 0.2, 0.2 );
	glEnd();
	glEndList();
	// bottom 
	base = glGenLists(1);
	glNewList(base,GL_COMPILE);
	glBegin(GL_POLYGON);
	glNormal3d(0,-1,0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f( 0.4, -0.2,  -0.2 );
	glTexCoord2f(1.0, 0.0);
	glVertex3f( 0.4, -0.2, 0.2 );
	glTexCoord2f(0.0, 0.0);
	glVertex3f(  -0.4, -0.2, 0.2 );
	glTexCoord2f(0.0, 1.0);
	glVertex3f( -0.4, -0.2, -0.2 );
	glEnd();
	glEndList();

	rot_floor = glGenLists(1);
	glNewList(rot_floor, GL_COMPILE);
	drawBox(0.2,GL_QUADS);
	glEndList();
	// Lid 
	l = glGenLists(1);
	glNewList(l,GL_COMPILE);
	glBegin(GL_POLYGON);
	glNormal3d(0,1,0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f( 0.4, 0,  0 );
	glTexCoord2f(1.0, 0.0);
	glVertex3f( 0.4, 0, -0.4 );
	glTexCoord2f(0.0, 0.0);
	glVertex3f(  -0.4, 0, -0.4 );
	glTexCoord2f(0.0, 1.0);
	glVertex3f( -0.4, 0, 0 );
	glEnd();
	glEndList();
}
#endif