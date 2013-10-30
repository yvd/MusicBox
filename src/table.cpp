#ifndef TABLE
#define TABLE
#include <iostream>
#include "GL/glut.h"
#include <GL/gl.h>
#include <stdlib.h>
#include <stdio.h>
#include "global.h"
#include "drawbox.cpp"
#include "textureloader.cpp"

void table()
{
	char t1[] = "./textures/table2.bmp";
	texture1 = textureloader(t1);
	char t2[] = "./textures/tableleg.bmp";
	texture2 = textureloader(t2);
	char t4[] = "./textures/bside.bmp";
	texture4 = textureloader(t4);
	b_front = textureloader(a2);
	r1 = textureloader(c1);
	r2 = textureloader(c2);
	r3 = textureloader(c3);
	r4 = textureloader(c4);
	r5 = textureloader(c5);
	furn_1 = glGenLists(1);
	glNewList(furn_1,GL_COMPILE);
	glBindTexture(GL_TEXTURE_2D, texture1);

	drawBox(0.5, GL_QUADS);
	glEndList();

	stool = glGenLists(1);
	glNewList(stool, GL_COMPILE);

	glBindTexture(GL_TEXTURE_2D, texture1);
	drawBox(0.2, GL_QUADS);
	glEndList();

	t_leg = glGenLists(1);
	glNewList(t_leg,GL_COMPILE);
	glBindTexture(GL_TEXTURE_2D, texture2);
	drawBox(0.2, GL_QUADS);
	glBindTexture(GL_TEXTURE_2D, 0);
	glEndList();

	r_cube = glGenLists(1);
	glNewList(r_cube,GL_COMPILE);
	glBindTexture(GL_TEXTURE_2D, r1);
	//side 1 - face
	glBegin(GL_POLYGON);
	glNormal3d(0,0,-1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(1.0,1.0,-1.0);
	glTexCoord2f(1.0,0.0);
	glVertex3f(1.0,-1.0,-1.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, r2);
	//side 2 - right side
	glBegin(GL_POLYGON);
	glNormal3d(1,0,0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(1.0,1.0,1.0);
	glTexCoord2f(1.0,0.0);
	glVertex3f(1.0,-1.0,1.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(1.0, -1.0, -1.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(1.0, 1.0, -1.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, r3);
	//side 3 - left side
	glBegin(GL_POLYGON);
	glNormal3d(-1,0,0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-1.0,1.0,-1.0);
	glTexCoord2f(1.0,0.0);
	glVertex3f(-1.0,-1.0,-1.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, r4);
	//side 4 - top side
	glBegin(GL_POLYGON);
	glNormal3d(0,1,0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(1.0,1.0,1.0);
	glTexCoord2f(1.0,0.0);
	glVertex3f(1.0,1.0,-1.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, r5);
	//side 5 - back face
	glBegin(GL_POLYGON);
	glNormal3d(0,0,1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-1.0,1.0,1.0);
	glTexCoord2f(1.0,0.0);
	glVertex3f(-1.0,-1.0,1.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(1.0, -1.0, 1.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glEnd();
	glEndList();

	book = glGenLists(1);
	glNewList(book,GL_COMPILE);
	//front side
	glBindTexture(GL_TEXTURE_2D, texture4);
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
	// rightside
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
	 
	//back side
	glBindTexture(GL_TEXTURE_2D, b_front);
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

	 
	//book cover
	glBegin(GL_POLYGON);
	glNormal3d(0,1,0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f( 0.4, 0.2,  0.2 );
	glTexCoord2f(1.0, 0.0);
	glVertex3f( 0.4, 0.2, -0.2 );
	glTexCoord2f(0.0, 0.0);
	glVertex3f(  -0.4, 0.2, -0.2 );
	glTexCoord2f(0.0, 1.0);
	glVertex3f( -0.4, 0.2, 0.2 );
	glEnd();

	// bottom 
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

	glEndList();

}
#endif