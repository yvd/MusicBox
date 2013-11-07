#include <iostream>
#include "GL/glut.h"
#include <GL/gl.h>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <fstream>
#include "vector"
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
int frm = 1;
int lfrm = 1;
int cur_kfrm = 1,cur_ifrm=1;
int a_1,a_2;
int record = 0;
double a_3,a_4,a_5,a_6;
unsigned char *pRGB;
unsigned int framenum=0;
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

void capture_frame(unsigned int framenum)
{
  //global pointer float *pRGB
  pRGB = new unsigned char [3 * (win_width+1) * (win_height + 1) ];


  // set the framebuffer to read
  //default for double buffered
  glReadBuffer(GL_BACK);

  glPixelStoref(GL_PACK_ALIGNMENT,1);//for word allignment
  
  glReadPixels(0, 0, win_width, win_height, GL_RGB, GL_UNSIGNED_BYTE, pRGB);
  char filename[200];
  sprintf(filename,"images/frame_%04d.ppm",framenum);
  std::ofstream out(filename, std::ios::out);
  out<<"P6"<<std::endl;
  out<<win_width<<" "<<win_height<<" 255"<<std::endl;
  out.write(reinterpret_cast<char const *>(pRGB), (3 * (win_width+1) * (win_height + 1)) * sizeof(int));
  out.close();

  //function to store pRGB in a file named count
  delete pRGB;
}

void loadkeyframe(int n)
{
	std::string f;
	f = "keyframes.txt";
	std::ifstream input_file;
//	std::cout<<"here\n";
	input_file.open(f.c_str());
	while(input_file.good())
	{
		//std::cout<<"here1\n";
		std::string str, par;
		int fnum,psn,i;
		std::vector<std::string> parse;
		getline(input_file,str);
		
		if(str.length() < 2)
		{
			break;
		}
		while((psn = str.find(" ")) != std::string::npos)
		{
			par = str.substr(0,psn);
			parse.push_back(par);
			str = str.substr(psn+1);
		//	std::cout<<"here3\n";
		}
		//std::cout<<"here4\n";
		if(n == atoi(parse[0].c_str()))
		{
			a_1 = atoi(parse[1].c_str());
			//std::cout<<"en_l1\n";
			a_2 = atoi(parse[2].c_str());
			//std::cout<<"en_l2\n";
			a_3 = atof(parse[3].c_str());
			//std::cout<<"rotate_lid\n";
			a_4 = atof(parse[4].c_str());
			a_5 = atof(parse[5].c_str());
			a_6 = atof(parse[6].c_str());
			//std::cout<<"rotate_flr\n";
			break;
		}
	}
	input_file.close();
}

void loadframe(int a,int b,double c,double d,double e,double f)
{
	en_l1 = a;
	en_l2 = b;
	rotate_lid = c;
	rotate_flr = d;
	neck_x = e;
	neck_x1 = f;
}
void saveframe() 
{
    std::string f; 
    // std::cout<<"Enter File Name to be saved to:\n";
    // std::cin>>f;
    f = "keyframes.txt";
    std::ofstream output_file;
    output_file.open(f.c_str(),std::fstream::app|std::fstream::out);
    //WallLight LampLight boxlid rotate_flr neckpos1 neckpos2
    output_file<<frm<<" "<<en_l1<<" "<<en_l2<<" "<<rotate_lid<<" "<<rotate_flr;
    output_file<<" "<<neck_x<<" "<<neck_x1;
    // output_file<<C.getr()<<" "<<C.getg()<<" "<<C.getb()<<" "<<ln.getsize()<<" "<<ln.getp1().getx()<<" "<<ln.getp1().gety()<<" "<<ln.getp2().getx()<<" "<<ln.getp2().gety()<<" \n";
    // output_file<<C.getr()<<" "<<C.getg()<<" "<<C.getb();
    frm++; 
    output_file<<" E\n";
	output_file.close();
 }

void move_cam(double a,double b,double c,double d,double e)
{
	ex = a;
	ey = b;
	ez = c;
	theta = d;
	phi = e;
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

void box_animate(int k)
{	
	if(cur_ifrm <= 30)
	{
		
		int c1,c2;
		double c3,c4,c5,c6;
		loadkeyframe(cur_kfrm + 1);
		c1 = a_1;
		c2 = a_2;
		c3 = a_3;
		c4 = a_4;
		c5 = a_5;
		c6 = a_6;
		loadkeyframe(cur_kfrm);
		//c1 = (c1 - a_1)/30;
		//c2 = (c2 - a_2)/30;
		c3 = (c3 - a_3)/30;
		c4 = (c4 - a_4)/30;
		c5 = (c5 - a_5)/30;
		c6 = (c6 - a_6)/30;
		loadframe(a_1,a_2,a_3 + cur_ifrm*c3,a_4 + cur_ifrm*c4,a_5 + cur_ifrm*c5,a_6 + cur_ifrm*c6);
		glutPostRedisplay();
		cur_ifrm++;
		glutTimerFunc(20,box_animate,cur_ifrm);
		//std::cout<<"cur_kfrm is: "<<cur_kfrm<<" and k is: "<<cur_ifrm<<" \n";
	}
	else if(cur_kfrm < 16)
	{
		//std::cout<<"cur_kfrm is: "<<cur_kfrm<<"\n";
		cur_kfrm++;
		cur_ifrm = 0;
		glutTimerFunc(20,box_animate,cur_ifrm);
	}
	else
	{
		return;
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
	if(record)
	{
		capture_frame(framenum++);
	}
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
  case '-':
  	lfrm--;
  	std::cout<<"lfrm is: "<<lfrm<<"\n";
  	break;
  case '+':
  	lfrm++;
  	std::cout<<"lfrm is: "<<lfrm<<"\n";
  	break;	
  case 'x':
  	saveframe();  
  	break;
  case 'z':
  	box_animate(cur_ifrm);
  	break;
  case 'c':
  	cur_ifrm = 1;
  	cur_kfrm = 1;
  	break;
  case '1':
  	b.del_lastCP();
  	break;
  case '2':
  	if(flag_draw == 0)
  		flag_draw = 1;
  	else
  		flag_draw = 0;
  	break;
  case 'A':
  	b.addCP(-0.144,0.077,-0.058);
  	theta = -4.8;
  	phi = -0.1;
	break;
  case 'C':
  	if(record == 0)
  		record = 1;
  	else
  		record = 0;
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
  		if(neck_x < 40)
  		{
  			neck_x += 5;
  		}
  	}
  	else if(cur_axis ==2)
  	{
  		if(neck_y < 110)
  		{
  			neck_y += 5;
  		}
  	}
  	else
  	{
  		if(neck_z < 40)
  		{
  			neck_z += 5;
  		}
  	}
  	std::cout<<"d1: x: "<<neck_x<<" y: "<<neck_y<<" z: "<<neck_z<<"\n"; 
  	break;
  case 'y':
  	if(cur_axis ==1)
  	{
  		if(neck_x > -40)
  		{
  			neck_x -=5;
  		}
  	}
  	else if(cur_axis ==2)
  	{
  		if(neck_y > -100)
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
  	std::cout<<"d1: x: "<<neck_x<<" y: "<<neck_y<<" z: "<<neck_z<<"\n";
  	break;  	
  case 'u':
  	if(cur_axis ==1)
  	{
  		if(neck_x1 < 40)
  		{
  			neck_x1 += 5;
  		}
  	}
  	else if(cur_axis ==2)
  	{
  		if(neck_y1 < 110)
  		{
  			neck_y1 += 5;
  		}
  	}
  	else
  	{
  		if(neck_z1 < 40)
  		{
  			neck_z1 += 5;
  		}
  	}
  	std::cout<<"d2: x: "<<neck_x1<<" y: "<<neck_y1<<" z: "<<neck_z1<<"\n";
  	break;
  case 'i':
  	if(cur_axis ==1)
  	{
  		if(neck_x1 > -40)
  		{
  			neck_x1 -=5;
  		}
  	}
  	else if(cur_axis ==2)
  	{
  		if(neck_y1 > -100)
  		{
  			neck_y1 -= 5;
  		}
  	}
  	else
  	{
  		if(neck_z1 > -40)
  		{
  			neck_z1 -= 5;
  		}
  	}
  	std::cout<<"d2: x: "<<neck_x1<<" y: "<<neck_y1<<" z: "<<neck_z1<<"\n";
  	break;
  case 'M':
  	move_cam(-0.144,0.077,-0.058,-4.8,-0.1);
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
