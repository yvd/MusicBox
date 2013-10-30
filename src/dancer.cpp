#ifndef DANCER
#define DANCER 
#include <iostream>
#include "GL/glut.h"
#include <GL/gl.h>
#include <stdlib.h>
#include <stdio.h>
#include "global.h"
#include "textureloader.cpp"

void dancer()
{
	q = gluNewQuadric();	
	gluQuadricDrawStyle(q, GLU_FILL);
  	gluQuadricTexture(q, GLU_TRUE);
  	gluQuadricNormals(q, GLU_SMOOTH);
	char t3[] = "./textures/skin.bmp";
	texture3 = textureloader(t3);
	
	head = glGenLists(1);
	glNewList(head,GL_COMPILE);
	glScalef(0.9,1.5,0.6);
	glBindTexture(GL_TEXTURE_2D, texture3);
	gluSphere(q,0.1,20,20);
	//glBindTexture(GL_TEXTURE_2D, texture3);
	glEndList();
	
	neck = glGenLists(1);
	glNewList(neck,GL_COMPILE);
	
	glScalef(0.2,0.1,0.1);
	gluCylinder(q,0.1,0.1,0.6,20,20);
	glEndList();
	
	torso1 = glGenLists(1);
	glNewList(torso1,GL_COMPILE);
	glBindTexture(GL_TEXTURE_2D, texture3);
	glScalef(0.6,0.7,0.5);
	//front side
	glNormal3d(0,0,-1);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0, 1.0);
	glVertex3f( 0.3, 0,  -0.1 );
	glTexCoord2f(1.0, 0.0);
	glVertex3f( 0.2, -0.5, -0.09 );
	glTexCoord2f(0.0, 0.0);
	glVertex3f(  -0.2, -0.5, -0.09 );
	glTexCoord2f(0.0, 1.0);
	glVertex3f( -0.3, 0, -0.1 );
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3d(0,0,1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f( 0.3, 0,  0.1 );
	glTexCoord2f(1.0, 0.0);
	glVertex3f( 0.2, -0.5, 0.09 );
	glTexCoord2f(0.0, 0.0);
	glVertex3f(  -0.2, -0.5, 0.09 );
	glTexCoord2f(0.0, 1.0);
	glVertex3f( -0.3, 0, 0.1 );
	glEnd();

	//right side
	glBegin(GL_POLYGON);
	glNormal3d(1,0,0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f( 0.3, 0,  0.1 );
	glTexCoord2f(1.0, 0.0);
	glVertex3f( 0.2, -0.5, 0.09 );
	glTexCoord2f(0.0, 0.0);
	glVertex3f(  0.2, -0.5, -0.09 );
	glTexCoord2f(0.0, 1.0);
	glVertex3f( 0.3, 0, -0.1 );
	glEnd();

	//left side
	glBegin(GL_POLYGON);
	glNormal3d(-1,0,0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f( -0.3, 0,  -0.1 );
	glTexCoord2f(1.0, 0.0);
	glVertex3f( -0.2, -0.5, -0.09 );
	glTexCoord2f(0.0, 0.0);
	glVertex3f(  -0.2, -0.5, 0.09 );
	glTexCoord2f(0.0, 1.0);
	glVertex3f( -0.3, 0, 0.1 );
	glEnd();

	//top side
	glBegin(GL_POLYGON);
	glNormal3d(0,1,0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f( 0.3, 0,  0.1 );
	glTexCoord2f(1.0, 0.0);
	glVertex3f( 0.3, 0, -0.1 );
	glTexCoord2f(0.0, 0.0);
	glVertex3f(  -0.3, 0, -0.1 );
	glTexCoord2f(0.0, 1.0);
	glVertex3f( -0.3, 0, 0.1 );
	glEnd();

	//down side
	glBegin(GL_POLYGON);
	glNormal3d(0,-1,0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f( 0.2, -0.5,  0.09 );
	glTexCoord2f(0.0, 1.0);
	glVertex3f( 0.2, -0.5, -0.09 );
	glTexCoord2f(0.0, 0.0);
	glVertex3f(  -0.2, -0.5, -0.09 );
	glTexCoord2f(0.0, 1.0);
	glVertex3f( -0.2, -0.5, 0.09 );
	glEnd();	
	glEndList();

	torso2 = glGenLists(1);
	glNewList(torso2,GL_COMPILE);
	glBindTexture(GL_TEXTURE_2D, texture3);
	gluSphere(q,0.1,20,20);
	glEndList();

	torso3 = glGenLists(1);
	glNewList(torso3,GL_COMPILE);
	glBindTexture(GL_TEXTURE_2D, texture3);
	glScalef(1,0.5,0.25);
	drawBox(0.2, GL_QUADS);
	//glutSolidCube(0.2);
	glEndList();

	hip = glGenLists(1);
	glNewList(hip,GL_COMPILE);
	gluSphere(q,0.1,20,20);
	glEndList();
	
	thigh = glGenLists(1);
	glNewList(thigh,GL_COMPILE);
	glScalef(0.25,0.25,0.5);
	gluCylinder(q,0.15,0.1,0.6,20,20);
	glEndList();
	
	knee = glGenLists(1);
	glNewList(knee,GL_COMPILE);
	gluSphere(q,0.1,20,20);
	glEndList();
	
	leg = glGenLists(1);
	glNewList(leg,GL_COMPILE);
	glScalef(0.15,0.15,0.4);
	gluCylinder(q,0.15,0.1,0.6,20,20);
	glEndList();
	
	ankle = glGenLists(1);
	glNewList(ankle,GL_COMPILE);
	gluSphere(q,0.1,20,20);
	glEndList();
	
	foot = glGenLists(1);
	glNewList(foot,GL_COMPILE);
	glScalef(0.6,0.4,1.5);
	drawBox(0.1, GL_QUADS);
	//glutSolidCube(0.1);
	glEndList();

	shoulder = glGenLists(1);
	glNewList(shoulder,GL_COMPILE);
	
	gluSphere(q,0.1,20,20);
	glEndList();

	uarm = glGenLists(1);
	glNewList(uarm,GL_COMPILE);
	glScalef(0.15,0.15,0.4);
	gluCylinder(q,0.15,0.1,0.6,20,20);
	glEndList();

	elbow = glGenLists(1);
	glNewList(elbow,GL_COMPILE);
	gluSphere(q,0.1,20,20);
	glEndList();

	larm = glGenLists(1);
	glNewList(larm,GL_COMPILE);
	glScalef(0.15,0.15,0.4);
	gluCylinder(q,0.15,0.1,0.6,20,20);
	glEndList();

	wrist = glGenLists(1);
	glNewList(wrist,GL_COMPILE);
	gluSphere(q,0.1,20,20);
	glEndList();

	hand = glGenLists(1);
	glNewList(hand,GL_COMPILE);
	glScalef(0.2,0.7,0.6);
	//glutSolidCube(0.1);
	drawBox(0.1, GL_QUADS);
	glEndList();
}



#endif