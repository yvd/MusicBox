#ifndef ROOM
#define ROOM
#include <iostream>
#include "GL/glut.h"
#include <GL/gl.h>
#include <stdlib.h>
#include <stdio.h>
#include "global.h"
#include "textureloader.cpp"
#include "drawbox.cpp"

void room()
{
	wall = glGenLists(1);
	glNewList(wall,GL_COMPILE);
	char t1[] = "./textures/wall-17.bmp";
	char t2[] = "./textures/wall-14.bmp";
	char t3[] = "./textures/door.bmp";	
	char t4[] = "./textures/pic.bmp";
	char t5[] = "./textures/fl1.bmp";
	char t6[] = "./textures/clock3.bmp";
	char t7[] = "./textures/mat2.bmp";
	char t8[] = "./textures/wall1-2.bmp";
	char w1[] = "./textures/wall-14-1.bmp";
	char w2[] = "./textures/wall-14-2.bmp";
	char w3[] = "./textures/wall-14-3.bmp";
	char p1[] = "./textures/pic2.bmp";
	pt = textureloader(p1);
	f_w1   = textureloader(w1);
	f_w2   = textureloader(w2);
	f_w3   = textureloader(w3);
	texture1 = textureloader(t1);
	texture2 = textureloader(t2);
	texture5 = textureloader(t3);
	texture6 = textureloader(t4);
	texture7 = textureloader(t5);
	texture8 = textureloader(t6);
	texture4 = textureloader(t7);
	texture9 = textureloader(t8);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glMaterialfv(GL_FRONT, GL_AMBIENT, white);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	//right wall - inside
	glBegin(GL_POLYGON);
	glNormal3d(-1,0,0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(  1, 1, 1 );
	glTexCoord2f(1.0, 0.0);
	glVertex3f(  1,  -1, 1 );
	glTexCoord2f(0.0, 0.0);
	glVertex3f( 1,  -1, -1 );
	glTexCoord2f(0.0, 1.0);
	glVertex3f( 1, 1, -1 );
	glEnd();

	//left wall - inside
	glBegin(GL_POLYGON);
	glNormal3d(1,0,0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(  -1, 1, 1 );
	glTexCoord2f(1.0, 0.0);
	glVertex3f(  -1,  -1, 1 );
	glTexCoord2f(0.0, 0.0);
	glVertex3f( -1,  -1, -1 );
	glTexCoord2f(0.0, 1.0);
	glVertex3f( -1, 1, -1 );
	glEnd();	
	//front side - inside
	glBegin(GL_POLYGON);
	glNormal3d(0,0,1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(  1, 1, -1 );
	glTexCoord2f(1.0, 0.0);
	glVertex3f(  1,  0.6, -1 );
	glTexCoord2f(0.0, 0.0);
	glVertex3f( -1,  0.6, -1 );
	glTexCoord2f(0.0, 1.0);
	glVertex3f( -1, 1, -1 );
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(  0, 0.6, -1 );
	glTexCoord2f(1.0, 0.0);
	glVertex3f(  0,  -1, -1 );
	glTexCoord2f(0.0, 0.0);
	glVertex3f( -1,  -1, -1 );
	glTexCoord2f(0.0, 1.0);
	glVertex3f( -1, 0.6, -1 );
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(  1, 0.6, -1 );
	glTexCoord2f(1.0, 0.0);
	glVertex3f(  1,  -1, -1 );
	glTexCoord2f(0.0, 0.0);
	glVertex3f( 0.8,  -1, -1 );
	glTexCoord2f(0.0, 1.0);
	glVertex3f( 0.8, 0.6, -1 );
	glEnd();
	///

	//back wall - inside
	glBegin(GL_POLYGON);
	glNormal3d(0,0,-1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(  1, 1, 1 );
	glTexCoord2f(1.0, 0.0);
	glVertex3f(  1,  -1, 1 );
	glTexCoord2f(0.0, 0.0);
	glVertex3f( -1,  -1, 1 );
	glTexCoord2f(0.0, 1.0);
	glVertex3f( -1, 1, 1 );
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture2);
	//right wall - outside
	glBegin(GL_POLYGON);
	glNormal3d(1,0,0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(  1.05, 1.05, 1.05 );
	glTexCoord2f(1.0, 0.0);
	glVertex3f(  1.05,  -1.05, 1.05 );
	glTexCoord2f(0.0, 0.0);
	glVertex3f( 1.05,  -1.05, -1.05 );
	glTexCoord2f(0.0, 1.0);
	glVertex3f( 1.05, 1.05, -1.05 );
	glEnd();

	//left wall - outside
	glBegin(GL_POLYGON);
	glNormal3d(-1,0,0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(  -1.05, 1.05, 1.05 );
	glTexCoord2f(1.0, 0.0);
	glVertex3f(  -1.05,  -1.05, 1.05 );
	glTexCoord2f(0.0, 0.0);
	glVertex3f( -1.05,  -1.05, -1.05 );
	glTexCoord2f(0.0, 1.0);
	glVertex3f( -1.05, 1.05, -1.05 );
	glEnd();

	//back wall - outside
	glBegin(GL_POLYGON);
	glNormal3d(0,0,1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(  1.05, 1.05, 1.05 );
	glTexCoord2f(1.0, 0.0);
	glVertex3f(  1.05,  -1.05, 1.05 );
	glTexCoord2f(0.0, 0.0);
	glVertex3f( -1.05,  -1.05, 1.05 );
	glTexCoord2f(0.0, 1.0);
	glVertex3f( -1.05, 1.05, 1.05 );
	glEnd();
	//front side - outside
	glBindTexture(GL_TEXTURE_2D, f_w2);
	glBegin(GL_POLYGON);
	glNormal3d(0,0,-1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(  1.05, 1.05, -1.05 );
	glTexCoord2f(1.0, 0.0);
	glVertex3f(  1.05,  0.6, -1.05 );
	glTexCoord2f(0.0, 0.0);
	glVertex3f( -1.05,  0.6, -1.05 );
	glTexCoord2f(0.0, 1.0);
	glVertex3f( -1.05, 1.05, -1.05 );
	glEnd();

	glBindTexture(GL_TEXTURE_2D, f_w1);
	glBegin(GL_POLYGON);
	glNormal3d(0,0,-1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(  0, 0.6, -1.05 );
	glTexCoord2f(1.0, 0.0);
	glVertex3f(  0,  -1.05, -1.05 );
	glTexCoord2f(0.0, 0.0);
	glVertex3f( -1.05,  -1.05, -1.05 );
	glTexCoord2f(0.0, 1.0);
	glVertex3f( -1.05, 0.6, -1.05 );
	glEnd();

	glBindTexture(GL_TEXTURE_2D, f_w3);
	glBegin(GL_POLYGON);	
	glNormal3d(0,0,-1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(  1.05, 0.6, -1.05 );
	glTexCoord2f(1.0, 0.0);
	glVertex3f(  1.05,  -1.05, -1.05 );
	glTexCoord2f(0.0, 0.0);
	glVertex3f( 0.8,  -1.05, -1.05 );
	glTexCoord2f(0.0, 1.0);
	glVertex3f( 0.8, 0.6, -1.05 );
	glEnd();

	//joining inner and outer walls
	//right
	glBegin(GL_POLYGON);
	glNormal3d(0,1,0);
	glTexCoord2f(1.0,1.0);
	glVertex3f(1.05,1.05,1.05);
	glTexCoord2f(1.0,0.0);
	glVertex3f(1.05,1.05,-1.05);
	glTexCoord2f(0.0,0.0);
	glVertex3f(1,1,-1);
	glTexCoord2f(0.0,1.0);
	glVertex3f(1,1,1);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3d(0,1,0);
	glTexCoord2f(1.0,1.0);
	glVertex3f(1.05,-1.05,1.05);
	glTexCoord2f(1.0,0.0);
	glVertex3f(1.05,-1.05,-1.05);
	glTexCoord2f(0.0,0.0);
	glVertex3f(1,-1,-1);
	glTexCoord2f(0.0,1.0);
	glVertex3f(1,-1,1);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3d(0,1,0);
	glTexCoord2f(1.0,1.0);
	glVertex3f(1.05,1.05,-1.05);
	glTexCoord2f(1.0,0.0);
	glVertex3f(1.05,-1.05,-1.05);
	glTexCoord2f(0.0,0.0);
	glVertex3f(1,-1,-1);
	glTexCoord2f(0.0,1.0);
	glVertex3f(1,1,-1);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3d(0,1,0);
	glTexCoord2f(1.0,1.0);
	glVertex3f(1.05,1.05,1.05);
	glTexCoord2f(1.0,0.0);
	glVertex3f(1.05,-1.05,1.05);
	glTexCoord2f(0.0,0.0);
	glVertex3f(1,-1,1);
	glTexCoord2f(0.0,1.0);
	glVertex3f(1,1,1);
	glEnd();

	//left side
	glBegin(GL_POLYGON);
	glNormal3d(0,1,0);
	glTexCoord2f(1.0,1.0);
	glVertex3f(-1.05,1.05,1.05);
	glTexCoord2f(1.0,0.0);
	glVertex3f(-1.05,1.05,-1.05);
	glTexCoord2f(0.0,0.0);
	glVertex3f(-1,1,-1);
	glTexCoord2f(0.0,1.0);
	glVertex3f(-1,1,1);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3d(0,1,0);
	glTexCoord2f(1.0,1.0);
	glVertex3f(-1.05,-1.05,1.05);
	glTexCoord2f(1.0,0.0);
	glVertex3f(-1.05,-1.05,-1.05);
	glTexCoord2f(0.0,0.0);
	glVertex3f(-1,-1,-1);
	glTexCoord2f(0.0,1.0);
	glVertex3f(-1,-1,1);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3d(0,1,0);
	glTexCoord2f(1.0,1.0);
	glVertex3f(-1.05,1.05,-1.05);
	glTexCoord2f(1.0,0.0);
	glVertex3f(-1.05,-1.05,-1.05);
	glTexCoord2f(0.0,0.0);
	glVertex3f(-1,-1,-1);
	glTexCoord2f(0.0,1.0);
	glVertex3f(-1,1,-1);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3d(0,1,0);
	glTexCoord2f(1.0,1.0);
	glVertex3f(-1.05,1.05,1.05);
	glTexCoord2f(1.0,0.0);
	glVertex3f(-1.05,-1.05,1.05);
	glTexCoord2f(0.0,0.0);
	glVertex3f(-1,-1,1);
	glTexCoord2f(0.0,1.0);
	glVertex3f(-1,1,1);
	glEnd();
	//front side
	glBegin(GL_POLYGON);
	glNormal3d(0,1,0);
	glTexCoord2f(1.0,1.0);
	glVertex3f(1,1,-1);
	glTexCoord2f(1.0,0.0);
	glVertex3f(1.05,1.05,-1.05);
	glTexCoord2f(0.0,0.0);
	glVertex3f(-1.05,1.05,-1.05);
	glTexCoord2f(0.0,1.0);
	glVertex3f(-1,1,-1);
	glEnd();

	//back side
	glBegin(GL_POLYGON);
	glNormal3d(0,1,0);
	glTexCoord2f(1.0,1.0);
	glVertex3f(1,1,1);
	glTexCoord2f(1.0,0.0);
	glVertex3f(1.05,1.05,1.05);
	glTexCoord2f(0.0,0.0);
	glVertex3f(-1.05,1.05,1.05);
	glTexCoord2f(0.0,1.0);
	glVertex3f(-1,1,1);
	glEnd();
	///floor
	glBindTexture(GL_TEXTURE_2D, texture7);
	glBegin(GL_POLYGON);
	glNormal3d(0,1,0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(  1.05, -1.05, -1.05 );
	glTexCoord2f(1.0, 0.0);
	glVertex3f(  1.05,  -1.05, 1.05 );
	glTexCoord2f(0.0, 0.0);
	glVertex3f( -1.05,  -1.05, 1.05 );
	glTexCoord2f(0.0, 1.0);
	glVertex3f( -1.05, -1.05, -1.05 );
	glEnd();
	glEndList();

	door = glGenLists(1);
	glNewList(door,GL_COMPILE);
	glBindTexture(GL_TEXTURE_2D, texture5);
	//front
	glBegin(GL_POLYGON);
	glNormal3d(0,0,-1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(  0.8, 0.6, 0 );
	glTexCoord2f(1.0, 0.0);
	glVertex3f(  0.8,  -1.05, 0 );
	glTexCoord2f(0.0, 0.0);
	glVertex3f( 0,  -1.05, 0 );
	glTexCoord2f(0.0, 1.0);
	glVertex3f( 0, 0.6, 0 );
	glEnd();
	//back
	glBegin(GL_POLYGON);
	glNormal3d(0,0,1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(  0.8, 0.6, 0.05 );
	glTexCoord2f(1.0, 0.0);
	glVertex3f(  0.8,  -1.05, 0.05 );
	glTexCoord2f(0.0, 0.0);
	glVertex3f( 0,  -1.05, 0.05 );
	glTexCoord2f(0.0, 1.0);
	glVertex3f( 0, 0.6, 0.05 );
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(  0.8, 0.6, 0.05 );
	glTexCoord2f(1.0, 0.0);
	glVertex3f(  0.8,  -1.05, 0.05 );
	glTexCoord2f(0.0, 0.0);
	glVertex3f( 0,  -1.05, 0 );
	glTexCoord2f(0.0, 1.0);
	glVertex3f( 0, 0.6, 0 );
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(  0, 0.6, 0 );
	glTexCoord2f(1.0, 0.0);
	glVertex3f(  0,  -1.05, 0 );
	glTexCoord2f(0.0, 0.0);
	glVertex3f( 0,  -1.05, 0.05 );
	glTexCoord2f(0.0, 1.0);
	glVertex3f( 0, 0.6, 0.05 );
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(  0.8, 0.6, 0.05 );
	glTexCoord2f(1.0, 0.0);
	glVertex3f(  0.8,  0.6, 0 );
	glTexCoord2f(0.0, 0.0);
	glVertex3f( 0,  0.6, 0 );
	glTexCoord2f(0.0, 1.0);
	glVertex3f( 0, 0.6, 0.05 );
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(  0.8, -1.05, 0.05 );
	glTexCoord2f(1.0, 0.0);
	glVertex3f(  0.8,  -1.05, 0 );
	glTexCoord2f(0.0, 0.0);
	glVertex3f( 0,  -1.05, 0 );
	glTexCoord2f(0.0, 1.0);
	glVertex3f( 0, -1.05, 0.05 );
	glEnd();	

	glEndList();

	pic = glGenLists(1);
	glNewList(pic,GL_COMPILE);
	glBindTexture(GL_TEXTURE_2D, texture6);

	glBegin(GL_POLYGON);
	glNormal3d(0,0,-1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(  0.7, 0.8, 0.995 );
	glTexCoord2f(1.0, 0.0);
	glVertex3f(  0.7,  0.3, 0.995 );
	glTexCoord2f(0.0, 0.0);
	glVertex3f( 0,  0.3, 0.995 );
	glTexCoord2f(0.0, 1.0);
	glVertex3f( 0, 0.8, 0.995 );
	glEnd();
	glEndList();

	pic2 = glGenLists(1);
	glNewList(pic2,GL_COMPILE);
	glBindTexture(GL_TEXTURE_2D, pt);

	glBegin(GL_POLYGON);
	glNormal3d(0,0,-1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(  0.7, 0.8, 0.995 );
	glTexCoord2f(1.0, 0.0);
	glVertex3f(  0.7,  0.3, 0.995 );
	glTexCoord2f(0.0, 0.0);
	glVertex3f( 0,  0.3, 0.995 );
	glTexCoord2f(0.0, 1.0);
	glVertex3f( 0, 0.8, 0.995 );
	glEnd();
	glEndList();

	wallclock = glGenLists(1);
	glNewList(wallclock,GL_COMPILE);
	glBindTexture(GL_TEXTURE_2D, texture8);

	glBegin(GL_POLYGON);
	glNormal3d(-1,0,0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(  0.995, 0.8, -0.7 );
	glTexCoord2f(1.0, 0.0);
	glVertex3f(  0.995,  0.3, -0.7 );
	glTexCoord2f(0.0, 0.0);
	glVertex3f( 0.995,  0.3, 0 );
	glTexCoord2f(0.0, 1.0);
	glVertex3f( 0.995, 0.8, 0 );
	glEnd();
	glEndList();	

	mat = glGenLists(1);
	glNewList(mat, GL_COMPILE);
	glBindTexture(GL_TEXTURE_2D, texture4);
	q = gluNewQuadric();	
	gluQuadricDrawStyle(q, GLU_FILL);
  	gluQuadricTexture(q, GLU_TRUE);
  	gluQuadricNormals(q, GLU_SMOOTH);
	
	drawBox(0.1, GL_QUADS);
	glEndList();	
}


#endif
