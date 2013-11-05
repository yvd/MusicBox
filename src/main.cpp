#include <iostream>
#include "GL/glut.h"
#include <GL/gl.h>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <fstream>
//#include <SFML/Audio.hpp>
#include "global.h"
#include "drawbox.cpp"
#include "box.cpp"
#include "textureloader.cpp"
#include "room.cpp"
#include "dancer.cpp"
#include "table.cpp"
#include "lights.cpp"
#include "pnt.cpp"
#include "bezier.cpp"
float angle = 0.0;
int flag_draw = 0;
int flag_pnt = 0;
int anim_cam = 0;
static void init()
{
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_DEPTH_TEST);

    lights();
	box();
	glBindTexture(GL_TEXTURE_2D, 0);
	room();
	table();
	glBindTexture(GL_TEXTURE_2D, 0);
	dancer();
	glCallList(sun);
}

void saveframe() 
{
    std::string f; 
    // std::cout<<"Enter File Name to be saved to:\n";
    // std::cin>>f;
    f = "keyframes.txt";
    std::ofstream output_file;
    output_file.open(f.c_str(),std::fstream::app|std::fstream::out);
    //WallLight LampLight boxlid door  rotate_flr  ex ey ez theta phi
    output_file<<"K "<<en_l1<<" "<<en_l2<<" "<<rotate_lid<<" "<<rotate_door<<" "<<rotate_flr<<ex<<" "<<ey<<" "<<ez<<" "<<theta<<" "<<phi;
    // output_file<<C.getr()<<" "<<C.getg()<<" "<<C.getb()<<" "<<ln.getsize()<<" "<<ln.getp1().getx()<<" "<<ln.getp1().gety()<<" "<<ln.getp2().getx()<<" "<<ln.getp2().gety()<<" \n";
    // output_file<<C.getr()<<" "<<C.getg()<<" "<<C.getb();
     
    output_file<<"\n";
	output_file.close();
 }

void animate(int value)
{	
	double t = value/100.0;
	if(value > 100)
	{
		return;	
	}
	else
	{
		ex = b.value(t).x;
		ey = b.value(t).y;
		ez = b.value(t).z;
		glutPostRedisplay();
		glutTimerFunc(10,animate,value+1);

	}
}
void mouseclick(int x, int y)
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY;
 
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );
 
    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    gluUnProject( winX, winY, 0, modelview, projection, viewport, &posX, &posY, &posZ);
    std::cout<<posX<<" "<<posY<<" "<<posZ<<"\n";

    
 	b.addCP(posX,posY,posZ);
 	flag_pnt = 1;
    //return CVector3(posX, posY, posZ);
}

void display( void )
{
	glClearColor(1,1,120,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	float k[] = {-1, 0, 0, 0, 0,1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

	//glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMultMatrixf(k);
	if(anim_cam == 0)
	gluLookAt(ex,ey,ez,ex + cos(theta)*cos(phi),ey + sin(phi),ez + sin(theta)*cos(phi),0,1,0);
	else
	{
		gluLookAt(ex,ey,ez,-0.199218,0.0718179,0.372866,0,1,0);
	}
	if(flag_draw == 1)
	{
		b.draw(1000);
	}
	b.drawcp();
 	glColor3f(   0.41,  0.41,  0.41 );

//////////////////////////ROOM////////////////////////////////
	glPushMatrix();
		glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
		glMaterialfv(GL_FRONT, GL_AMBIENT, white);
		glMaterialfv(GL_FRONT, GL_SPECULAR, white);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
		glPushMatrix();
			glScalef(0.5,0.47,0.5);
			glCallList(pic);
			glPushMatrix();
				glTranslatef(-0.9,0.2,0.5);
				glScalef(0.5,0.6,0.5);
				glCallList(pic2);
			glPopMatrix();
			glPushMatrix();
				glScalef(1,1,0.5);
				glCallList(wallclock);
			glPopMatrix();
			glCallList(wall);
			glPushMatrix();
				glTranslatef(0.4,-1,-0.8);
				glScalef(7,0.1,4);
				glRotatef(90,0,1,0);
				glCallList(mat);
			glPopMatrix();
			glTranslatef(0,0,-1.05);
			glRotatef(rotate_door,0,1, 0);
			glCallList(door);
			glPointSize(100);
			glVertex3f(0,0,0);
		glPopMatrix();
		glTranslatef(-0.25,-0.02,0.3);

	////////////////////////////////////////////////////////
		glPushMatrix();
			glTranslatef(0.3,0,0);
			glScalef(0.2,0.2,0.2);
		    glTranslatef(-1,0,0);
		    glCallList(comp);
		    glPushMatrix();
		    	glTranslatef(0.0,0.2,0.2);
		  		glRotatef(rotate_lid,1,0,0);
		    	glCallList(l);
			glPopMatrix();
		    glPushMatrix();
		    	glTranslatef(0,rotate_lid/250,0);
		    	glCallList(base);
		    	glPushMatrix();
		    		glTranslatef(0,-0.18,0);
		    		glRotatef(rotate_flr,0,1,0);
		    		glScalef(1,0.1,1);
		    		glCallList(rot_floor);
		    	glPopMatrix();
		    	glBindTexture(GL_TEXTURE_2D, 0);
		    glPopMatrix();
		glPopMatrix();
	//////////////////////////////////////////////////////////////
	////////////////////////////Dancer 1/////////////////////////////////	
		glPushMatrix();
			glTranslatef(0.1,(rotate_lid + 3)/1250,0);
			glRotatef(-90,0,1,0);
			glRotatef(rotate_flr,0,1,0);
			glScalef(0.04,0.04,0.04);
			glPushMatrix();
				glTranslatef(0,-0.17,0);
				glRotatef(t3_x,1,0,0);
				glRotatef(t3_z,0,0,1);
				glRotatef(t3_y,0,1,0);
				glPushMatrix();
					glCallList(torso3);
				glPopMatrix();

	/////////////////////left leg///////////////////////

				glPushMatrix();
				glTranslatef(0.065,-0.07,0);
				glRotatef(hip_x_l,1,0,0);
				glRotatef(hip_z_l,0,0,1);
				glRotatef(hip_y_l,0,1,0);

				glPushMatrix();
					glScalef(0.35,0.35,0.35);
					glCallList(hip);
				glPopMatrix();
				
				glPushMatrix();
					glTranslatef(0.002,-0.03,0);
					glRotatef(90,1,0,0);
					glCallList(thigh);
				glPopMatrix();

				glPushMatrix();
					glTranslatef(0.002,-0.34,0);
					glRotatef(knee_x_l,1,0,0);

				 	glPushMatrix();
						glScalef(0.2,0.2,0.2);
						glCallList(knee);
					glPopMatrix();	

					glPushMatrix();
					 	glTranslatef(0,-0.01,0);
					 	glRotatef(90,1,0,0);
					 	glCallList(leg);
					glPopMatrix();

					glPushMatrix();
						glTranslatef(0,-0.26,0);
						glRotatef(ankle_x_l,1,0,0);
						glRotatef(ankle_z_l,0,0,1);
						glRotatef(ankle_y_l,0,1,0);
						
						glPushMatrix();
							glScalef(0.15,0.15,0.15);
							glCallList(ankle);
						glPopMatrix();

						glPushMatrix();
							glTranslatef(0,-0.03,-0.05);
							glCallList(foot);
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();

				glPopMatrix();
	//////////////////////////right leg///////////////////
				glPushMatrix();
				glTranslatef(-0.065,-0.07,0);
				glRotatef(hip_x_r,1,0,0);
				glRotatef(-hip_z_r,0,0,1);
				glRotatef(hip_y_r,0,1,0);
				
				glPushMatrix();
					glScalef(0.35,0.35,0.35);
					glCallList(hip);
				glPopMatrix();
				
				glPushMatrix();
					glTranslatef(-0.002,-0.03,0);
					glRotatef(90,1,0,0);
					glCallList(thigh);
				glPopMatrix();

				glPushMatrix();
					glTranslatef(-0.002,-0.34,0);
				 	glRotatef(knee_x_r,1,0,0);

				 	glPushMatrix();
						glScalef(0.2,0.2,0.2);
						glCallList(knee);
					glPopMatrix();	

					glPushMatrix();
					 	glTranslatef(0,-0.01,0);
					 	glRotatef(90,1,0,0);
					 	glCallList(leg);
					glPopMatrix();

					glPushMatrix();
						glTranslatef(0,-0.26,0);
						glRotatef(ankle_x_r,1,0,0);
						glRotatef(ankle_z_r,0,0,1);
						glRotatef(ankle_y_r,0,1,0);

						glPushMatrix();
							glScalef(0.15,0.15,0.15);
							glCallList(ankle);
						glPopMatrix();

						glPushMatrix();
							glTranslatef(0,-0.03,-0.05);
							glCallList(foot);
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();

				glPopMatrix();
			glPopMatrix();
////////////////////////Torso1////////////////////////////////	
		glPushMatrix();
			glTranslatef(0,-0.08,0);
			glRotatef(t1_x,1,0,0);
			glRotatef(t1_z,0,0,1);
			glRotatef(t1_y,0,1,0);
			
			glPushMatrix();	
				glScalef(1.2,0.6,0.25);
				glCallList(torso2);	
			glPopMatrix();	
	
			glPushMatrix();
				glTranslatef(0,0.38,0);
				glCallList(torso1);
			glPopMatrix();

////////////////////////head///////////////////////////////////
			glPushMatrix();
				glTranslatef(0,0.435,0);
				glRotatef(neck_x,1,0,0);
				glRotatef(neck_z,1,0,1);
				glRotatef(neck_y,0,1,0);

					glPushMatrix();	
						glRotatef(90,1,0,0);
						glCallList(neck);
					glPopMatrix();

					glPushMatrix();
						glTranslatef(0.0, 0.145, 0.0);
						glCallList(head);
					glPopMatrix();
			glPopMatrix();		
	///////////////////////////////////////////////////////////
	/////////////////left hand///////////////////////	

				glPushMatrix();
					glTranslatef(0.19,0.34,0);
					glRotatef(shldr_x_l,1,0,0);
					glRotatef(shldr_z_l,0,0,1);
					glRotatef(shldr_y_l,0,1,0);
					glPushMatrix();
						glScalef(0.4,0.4,0.5);
						glCallList(shoulder);
					glPopMatrix();
				
					glPushMatrix();
						glTranslatef(0,-0.03,0);
						glRotatef(90,1,0,0);
						glCallList(uarm);
					glPopMatrix();
					
					glPushMatrix();
						glTranslatef(0,-0.285,0);
						glRotatef(elb_x_l,1,0,0);
						glPushMatrix();
							glScalef(0.18,0.18,0.18);
							glCallList(elbow);
						glPopMatrix();

						glPushMatrix();
							glTranslatef(0,-0.015,0);
							glRotatef(90,1,0,0);
							glCallList(larm);
						glPopMatrix();

						glPushMatrix();
							glTranslatef(0,-0.265,0);
							glRotatef(wrst_x_l,1,0,0);
							glRotatef(wrst_z_l,0,0,1);
							glRotatef(wrst_y_l,0,1,0);

							glPushMatrix();
								glScalef(0.16,0.16,0.16);
								glCallList(wrist);
							glPopMatrix();

							glPushMatrix();
								glTranslatef(0,-0.05,0);
								glCallList(hand);
							glPopMatrix();
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
	//////////////////right hand///////////////////
				glPushMatrix();
					glTranslatef(-0.19,0.34,0);
					glRotatef(shldr_x_r,1,0,0);
					glRotatef(-shldr_z_r,0,0,1);
					glRotatef(shldr_y_r,0,1,0);
					glPushMatrix();
						glScalef(0.4,0.4,0.5);
						glCallList(shoulder);
					glPopMatrix();
				
					glPushMatrix();
						glTranslatef(0,-0.03,0);
						glRotatef(90,1,0,0);
						glCallList(uarm);
					glPopMatrix();
					
					glPushMatrix();
						glTranslatef(0,-0.285,0);
						glRotatef(elb_x_r,1,0,0);
						glPushMatrix();
							glScalef(0.18,0.18,0.18);
							glCallList(elbow);
						glPopMatrix();

						glPushMatrix();
							glTranslatef(0,-0.015,0);
							glRotatef(90,1,0,0);
							glCallList(larm);
						glPopMatrix();

						glPushMatrix();
							glTranslatef(0,-0.265,0);
							glRotatef(wrst_x_r,1,0,0);
							glRotatef(wrst_z_r,0,0,1);
							glRotatef(wrst_y_r,0,1,0);

							glPushMatrix();
								glScalef(0.16,0.16,0.16);
								glCallList(wrist);
							glPopMatrix();

							glPushMatrix();
								glTranslatef(0,-0.05,0);
								glCallList(hand);
							glPopMatrix();
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();	
		glPopMatrix();
	glPopMatrix();
////////////////////////////////////////////////////
////////////////////////////Dancer 2/////////////////////////////////	
	glPushMatrix();
		glTranslatef(0.107,(rotate_lid + 5)/1250 - 0.005,0);
		glRotatef(90,0,1,0);
		glRotatef(rotate_flr,0,1,0);
		glRotatef(15,1,0,0);
		glScalef(0.04,0.035,0.04);	
		glPushMatrix();
			glTranslatef(0,-0.17,0);
			glRotatef(t3_x1,1,0,0);
			glRotatef(t3_z1,0,0,1);
			glRotatef(t3_y1,0,1,0);
			glPushMatrix();
				glCallList(torso3);
			glPopMatrix();

	/////////////////////left leg///////////////////////

			glPushMatrix();
				glTranslatef(0.065,-0.07,0);
				glRotatef(hip_x_l1,1,0,0);
				glRotatef(hip_z_l1,0,0,1);
				glRotatef(hip_y_l1,0,1,0);

				glPushMatrix();
					glScalef(0.35,0.35,0.35);
					glCallList(hip);
				glPopMatrix();
				
				glPushMatrix();
					glTranslatef(0.002,-0.03,0);
					glRotatef(90,1,0,0);
					glCallList(thigh);
				glPopMatrix();

				glPushMatrix();
					glTranslatef(0.002,-0.34,0);
					glRotatef(knee_x_l1,1,0,0);

				 	glPushMatrix();
						glScalef(0.2,0.2,0.2);
						glCallList(knee);
					glPopMatrix();	

					glPushMatrix();
					 	glTranslatef(0,-0.01,0);
					 	glRotatef(90,1,0,0);
					 	glCallList(leg);
					glPopMatrix();

					glPushMatrix();
						glTranslatef(0,-0.26,0);
						glRotatef(ankle_x_l1,1,0,0);
						glRotatef(ankle_z_l1,0,0,1);
						glRotatef(ankle_y_l1,0,1,0);
						
						glPushMatrix();
							glScalef(0.15,0.15,0.15);
							glCallList(ankle);
						glPopMatrix();

						glPushMatrix();
							glTranslatef(0,-0.03,-0.05);
							glCallList(foot);
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();

			glPopMatrix();
//////////////////////////right leg///////////////////
		glPushMatrix();
			glTranslatef(-0.065,-0.07,0);
			glRotatef(hip_x_r1,1,0,0);
			glRotatef(-hip_z_r1,0,0,1);
			glRotatef(hip_y_r1,0,1,0);
			
			glPushMatrix();
				glScalef(0.35,0.35,0.35);
				glCallList(hip);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(-0.002,-0.03,0);
				glRotatef(90,1,0,0);
				glCallList(thigh);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-0.002,-0.34,0);
			 	glRotatef(knee_x_r1,1,0,0);

			 	glPushMatrix();
					glScalef(0.2,0.2,0.2);
					glCallList(knee);
				glPopMatrix();	

				glPushMatrix();
				 	glTranslatef(0,-0.01,0);
				 	glRotatef(90,1,0,0);
				 	glCallList(leg);
				glPopMatrix();

				glPushMatrix();
					glTranslatef(0,-0.26,0);
					glRotatef(ankle_x_r1,1,0,0);
					glRotatef(ankle_z_r1,0,0,1);
					glRotatef(ankle_y_r1,0,1,0);

					glPushMatrix();
						glScalef(0.15,0.15,0.15);
						glCallList(ankle);
					glPopMatrix();

					glPushMatrix();
						glTranslatef(0,-0.03,-0.05);
						glCallList(foot);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();

		glPopMatrix();
	glPopMatrix();
////////////////////////Torso1////////////////////////////////	
		glPushMatrix();
			glTranslatef(0,-0.08,0);
			glRotatef(t1_x1,1,0,0);
			glRotatef(t1_z1,0,0,1);
			glRotatef(t1_y1,0,1,0);
			
			glPushMatrix();	
				glScalef(1.2,0.6,0.25);
				glCallList(torso2);	
			glPopMatrix();	
	
			glPushMatrix();
				glTranslatef(0,0.38,0);
				glCallList(torso1);
			glPopMatrix();

////////////////////////head///////////////////////////////////
			glPushMatrix();
				glTranslatef(0,0.435,0);
				glRotatef(neck_x1,1,0,0);
				glRotatef(neck_z1,1,0,1);
				glRotatef(neck_y1,0,1,0);

					glPushMatrix();	
						glRotatef(90,1,0,0);
						glCallList(neck);
					glPopMatrix();

					glPushMatrix();
						glTranslatef(0.0, 0.145, 0.0);
						glCallList(head);
					glPopMatrix();
			glPopMatrix();		
	///////////////////////////////////////////////////////////
	/////////////////left hand///////////////////////	

			glPushMatrix();
					glTranslatef(0.19,0.34,0);
					glRotatef(shldr_x_l1,1,0,0);
					glRotatef(shldr_z_l1,0,0,1);
					glRotatef(shldr_y_l1,0,1,0);
					glPushMatrix();
						glScalef(0.4,0.4,0.5);
						glCallList(shoulder);
					glPopMatrix();
				
					glPushMatrix();
						glTranslatef(0,-0.03,0);
						glRotatef(90,1,0,0);
						glCallList(uarm);
					glPopMatrix();
					
					glPushMatrix();
						glTranslatef(0,-0.285,0);
						glRotatef(elb_x_l1,1,0,0);
						glPushMatrix();
							glScalef(0.18,0.18,0.18);
							glCallList(elbow);
						glPopMatrix();

						glPushMatrix();
							glTranslatef(0,-0.015,0);
							glRotatef(90,1,0,0);
							glCallList(larm);
						glPopMatrix();

						glPushMatrix();
							glTranslatef(0,-0.265,0);
							glRotatef(wrst_x_l1,1,0,0);
							glRotatef(wrst_z_l1,0,0,1);
							glRotatef(wrst_y_l1,0,1,0);

							glPushMatrix();
								glScalef(0.16,0.16,0.16);
								glCallList(wrist);
							glPopMatrix();

							glPushMatrix();
								glTranslatef(0,-0.05,0);
								glCallList(hand);
							glPopMatrix();
						glPopMatrix();
					glPopMatrix();
			glPopMatrix();
	//////////////////right hand///////////////////
			glPushMatrix();
					glTranslatef(-0.19,0.34,0);
					glRotatef(shldr_x_r1,1,0,0);
					glRotatef(-shldr_z_r1,0,0,1);
					glRotatef(shldr_y_r1,0,1,0);
					glPushMatrix();
						glScalef(0.4,0.4,0.5);
						glCallList(shoulder);
					glPopMatrix();
				
					glPushMatrix();
						glTranslatef(0,-0.03,0);
						glRotatef(90,1,0,0);
						glCallList(uarm);
					glPopMatrix();
					
					glPushMatrix();
						glTranslatef(0,-0.285,0);
						glRotatef(elb_x_r1,1,0,0);
						glPushMatrix();
							glScalef(0.18,0.18,0.18);
							glCallList(elbow);
						glPopMatrix();

						glPushMatrix();
							glTranslatef(0,-0.015,0);
							glRotatef(90,1,0,0);
							glCallList(larm);
						glPopMatrix();

						glPushMatrix();
							glTranslatef(0,-0.265,0);
							glRotatef(wrst_x_r1,1,0,0);
							glRotatef(wrst_z_r1,0,0,1);
							glRotatef(wrst_y_r1,0,1,0);

							glPushMatrix();
								glScalef(0.16,0.16,0.16);
								glCallList(wrist);
							glPopMatrix();

							glPushMatrix();
								glTranslatef(0,-0.05,0);
								glCallList(hand);
							glPopMatrix();
						glPopMatrix();
					glPopMatrix();
			glPopMatrix();	
		glPopMatrix();
		glPopMatrix();
////////////////////////////////////////////////////		
	/////////////////////////LIGHTS//////////////////////////////

		glPushMatrix();
			glTranslatef(-0.25,0.45,-0.3);
			glScalef(0.2,0.8,0.3);
			glCallList(light_1);

		glPopMatrix();

		glPushMatrix();
			glTranslatef(-0.15,0.1,0.13);
			glScalef(0.3,0.4,1.3);
			glCallList(light_2);

		glPopMatrix();
		glPushMatrix();
			glTranslatef(-0.15,0,0.18);
			glScalef(0.1,0.9,0.1);
			glCallList(t_leg);
		glPopMatrix();


	////////////////////////////////////////////	
	/////////////////////////Furniture/////////////////////////////

		b_front = textureloader(a1);
		glPushMatrix();
			glScalef(0.15,0.1,0.13);
			glTranslatef(-1,-0.2,0);
			glRotatef(270,0,1,0);
			glCallList(book);
		glPopMatrix();
		b_front = textureloader(a2);
		glPushMatrix();
			glScalef(0.15,0.1,0.13);
			glTranslatef(-0.5,-0.2,0);
			glRotatef(270,0,1,0);
			glCallList(book);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.16,-0.02,-0.16);
			glScalef(0.02,0.02,0.02);
			glCallList(r_cube);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0,-0.066,0);
			glScalef(0.8,0.1,0.8);
			glCallList(furn_1);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0,-0.1,-0.3);
			glScalef(0.7,0.2,0.7);
			glCallList(stool);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0,-0.285,-0.3);
			glScalef(0.2,2,0.2);
			glCallList(t_leg);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0,-0.445,-0.3);
			glScalef(0.4,0.4,0.4);
			glCallList(stool);
		glPopMatrix();	

		glPushMatrix();
			glTranslatef(0.3,-0.1,0);
			glScalef(0.7,0.2,0.7);
			glCallList(stool);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.3,-0.285,0);
			glScalef(0.2,2,0.2);
			glCallList(t_leg);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.3,-0.445,0);
			glScalef(0.4,0.4,0.4);
			glCallList(stool);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.18,-0.285,-0.18);
			glScalef(0.2,2,0.2);
			glCallList(t_leg);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.18, -0.41, 0);
			glScalef(0.2,0.2,1.7);
			glCallList(t_leg);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.18,-0.285,0.18);
			glScalef(0.2,2,0.2);
			glCallList(t_leg);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-0.18, -0.41, 0);
			glScalef(0.2,0.2,1.7);
			glCallList(t_leg);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-0.18,-0.285,0.18);
			glScalef(0.2,2,0.2);
			glCallList(t_leg);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-0.18,-0.285,-0.18);
			glScalef(0.2,2,0.2);
			glCallList(t_leg);
		glPopMatrix();		
		glPushMatrix();
			glTranslatef(0, -0.41, 0);
			glScalef(1.7,0.2,0.2);
			glCallList(t_leg);
		glPopMatrix();
	glPopMatrix();		
//////////////////////////////////////////////////////////////	
	glFlush();
	glutSwapBuffers();
}

void reshape( int w, int h )
{
  glViewport( 0, 0, w, h );

  win_width = w;
  win_height = h;
  if  ( h == 0 ) h = 1;
  float ratio = 1.0f* w /h ;
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective(70, ratio, 0.1, 100);
}

void keyboard( unsigned char key, int x, int y ) {
  switch(key) {
  case 27: 
    exit(0);
    break;
  case 'x':
  	saveframe();  
  case '1':
  	b.del_lastCP();
  	break;
  case '2':
  	if(flag_draw == 0)
  		flag_draw = 1;
  	else
  		flag_draw = 0;
  	break;
  case '3':
  	if(rotate_door < 135)
  		rotate_door += 5;
  		//door_snd.play();
  	break;
  case '4':
	if(rotate_door > 0)
		rotate_door -= 5;
	break;  	
  case '5':
  	if(anim_cam == 0)
  		anim_cam = 1;
  	else
  		anim_cam = 0;
  	break;	 
  case 'n':
	if(rotate_flr < 25)
	  	rotate_flr += 5;
  	break;
  case 'm':
	if(rotate_flr > -25)
	  	rotate_flr -= 5;
  	break;	
  case 'q':
  	animate(0);
  	break;
  case 'W':	
  	ex+= 0.1*cos(theta)*cos(phi);
	ey+= 0.1*sin(phi);
	ez+= 0.1*sin(theta)*cos(phi);
	std::cout<<"ex: "<<ex<<" ey: "<<ey<<" ez: "<<ez<<"\n";
	break;
  case 'S':  	
	ex-= 0.1*cos(theta)*cos(phi);
	ey-= 0.1*sin(phi);
	ez-= 0.1*sin(theta)*cos(phi);
	std::cout<<"ex: "<<ex<<" ey: "<<ey<<" ez: "<<ez<<"\n";
	break;

  case 'd':
   	theta -= 0.1;
   	std::cout<<"theta is :"<<theta<<"\n";
    break;
  case 'w':
  	phi += 0.1;
  	std::cout<<"phi is :"<<phi<<"\n";
    break;
  case 'a':
  	theta += 0.1;
  	std::cout<<"theta is :"<<theta<<"\n";
    break;
  case 's':
  	phi -= 0.1;
  	std::cout<<"phi is :"<<phi<<"\n";
  	break;	
  case '[':
  	if(rotate_lid < 90)
  		rotate_lid += 5;
  	break;
  case ']':
	if(rotate_lid > 0)
		rotate_lid -= 5;
	break;
  case 'e':
  	if(en_l1 == 0)
	{
		en_l1 = 1;
		glEnable(GL_LIGHT0);
	}
	else
	{
		en_l1 = 0;
		glDisable(GL_LIGHT0);
	}
	break;
  case 'r':
  	if(en_l2 == 0)
	{
		en_l2 = 1;
		glEnable(GL_LIGHT1);
	}
	else
	{
		en_l2 = 0;
		glDisable(GL_LIGHT1);
	}
	break;		
  case 'R':
  	if(en_l3 == 0)
	{
		en_l3 = 1;
		glEnable(GL_LIGHT2);
	}
	else
	{
		en_l3 = 0;
		glDisable(GL_LIGHT2);
	}
	break;	
  case '6':
  	cur_axis = 1;//x axis
  	break;
  case '7':
  	cur_axis = 2;// y axis
  	break;
  case '8':
  	cur_axis = 3;//z axis
  	break;
  case 't':
  	if(cur_axis ==1)
  	{
  		if(neck_x < 20)
  		{
  			neck_x += 5;
  		}
  	}
  	else if(cur_axis ==2)
  	{
  		if(neck_y < 90)
  		{
  			neck_y += 5;
  		}
  	}
  	else
  	{
  		if(neck_z < 20)
  		{
  			neck_z += 5;
  		}
  	}
  	break;
  case 'y':
  	if(cur_axis ==1)
  	{
  		if(neck_x > -20)
  		{
  			neck_x -=5;
  		}
  	}
  	else if(cur_axis ==2)
  	{
  		if(neck_y > -90)
  		{
  			neck_y -= 5;
  		}
  	}
  	else
  	{
  		if(neck_z > -20)
  		{
  			neck_z -= 5;
  		}
  	}
  	break;  	
  case 'u':
  	if(cur_axis ==1)
  	{
  		if(neck_x1 < 20)
  		{
  			neck_x1 += 5;
  		}
  	}
  	else if(cur_axis ==2)
  	{
  		if(neck_y1 < 90)
  		{
  			neck_y1 += 5;
  		}
  	}
  	else
  	{
  		if(neck_z1 < 20)
  		{
  			neck_z1 += 5;
  		}
  	}
  	break;
  case 'i':
  	if(cur_axis ==1)
  	{
  		if(neck_x1 > -20)
  		{
  			neck_x1 -=5;
  		}
  	}
  	else if(cur_axis ==2)
  	{
  		if(neck_y1 > -90)
  		{
  			neck_y1 -= 5;
  		}
  	}
  	else
  	{
  		if(neck_z1 > -20)
  		{
  			neck_z1 -= 5;
  		}
  	}
  	break;
  	
  default:
    break;
  }
  glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) 
{
   if (state == GLUT_DOWN) 
   {
   		if (button == GLUT_LEFT_BUTTON) 
	    {
	 		mouseclick(x,y);
	 	}
   }
   glutPostRedisplay();
}       


int main (int argc, char *argv[]) 
{
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize( win_width, win_height );

	glutCreateWindow( "Music Box" );
	init();
	glutDisplayFunc( display );
	glutReshapeFunc( reshape );
	glutKeyboardFunc( keyboard );
	//glutSpecialFunc(arrowkeys);
	glutMouseFunc( mouse );
	glutMainLoop();
	return 0;
}
