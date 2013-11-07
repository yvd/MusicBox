#ifndef GLOBAL
#define GLOBAL
#include <iostream>
#include "GL/glut.h"
#include <GL/gl.h>
#include <stdlib.h>
#include <stdio.h>
//#include <SFML/Audio.hpp>
#include "textureloader.cpp"
#include "pnt.h"
#include "bezier.h"

bezier b;
int win_width = 1024;
int win_height = 768;
int cur_axis = 1;
int side = 1;
int limb = 1;
int torso = 1;
int en_l1 = 1, en_l2 = 1, en_l3 = 0;
//sf::SoundBuffer buffer;
//buffer.loadFromFile("sounds/door.mp3");
//sf::Sound door_snd;
//door_snd.setBuffer(snd_bf);
GLdouble posX, posY, posZ; 
//variables for movements of the human model
double rotate_y=0, rotate_x=0, rotate_lid =0, rotate_door=0, theta=-4.7, phi=-0.8, rotate_flr=0;
double shldr_x_l = 60,shldr_y_l = 70,shldr_z_l = 0,shldr_x_r = 75,shldr_y_r = 0,shldr_z_r = 80;
double elb_x_l   = 100,elb_x_r   = 0;
double wrst_x_l  = 0,wrst_y_l  = 0,wrst_z_l  = 0,wrst_x_r  = 0,wrst_y_r  = 0,wrst_z_r  = 0;
double hip_x_l   = -20,hip_y_l   = 0,hip_z_l   = 0,hip_x_r   = 15,hip_y_r   = 0,hip_z_r   = 0;
double knee_x_l  = -15,knee_x_r  = -10;
double ankle_x_l = -30,ankle_y_l = 0,ankle_z_l = 0,ankle_x_r = 0,ankle_y_r = 0,ankle_z_r = 0;
double t1_x      = -35,t1_y      = 0,t1_z      = 0,t3_x      = -5,t3_y      = 0,t3_z      = 0;
double neck_x    = -20,neck_y    = 0,neck_z    = 0;
// 
double shldr_x_l1 = 80,shldr_y_l1 = 0,shldr_z_l1 = 75,shldr_x_r1 = 45,shldr_y_r1 = -40,shldr_z_r1 = 45;
double elb_x_l1   = 0,elb_x_r1   = 120;
double wrst_x_l1  = 0,wrst_y_l1  = 0,wrst_z_l1  = 0,wrst_x_r1  = -10,wrst_y_r1  = 0,wrst_z_r1  = 0;
double hip_x_l1   = -35,hip_y_l1   = 0,hip_z_l1   = 0,hip_x_r1   = 15,hip_y_r1   = 0,hip_z_r1   = 0;
double knee_x_l1  = 0,knee_x_r1  = -15;
double ankle_x_l1 = -30,ankle_y_l1 = 0,ankle_z_l1 = 0,ankle_x_r1 = -20,ankle_y_r1 = 0,ankle_z_r1 = 0;
double t1_x1      = 20,t1_y1      = 0,t1_z1      = 0,t3_x1      = 10,t3_y1      = 0,t3_z1      = 0;
double neck_x1    = 5,neck_y1    = 0,neck_z1    = 0;
//variables for glnewlists
int comp,l,base, rot_floor;// for box
int wall,door,pic,pic2,furn_1,t_leg,wallclock,book,r_cube,mat,stool,light_1,light_2,sun;
GLUquadric *q;
int head,neck,torso1,torso2,torso3,hip,thigh,knee,leg,ankle,foot,shoulder,uarm,elbow,larm,wrist,hand;
//Textures used.
GLuint texture1,texture2,texture3,texture4,texture5,texture6,texture7,texture8,texture9,b_front,r1,r2,r3,r4,r5,f_w1,f_w2,f_w3,pt;
GLdouble ex=0.05,ey=1.38,ez=-1.39,ux=0,uy=1,uz=0;
char a1[] = "./textures/bfront.bmp";
char a2[] = "./textures/bfront2.bmp";	
char c1[] = "./textures/r_cube/r1.bmp";
char c2[] = "./textures/r_cube/r2.bmp";
char c3[] = "./textures/r_cube/r3.bmp";
char c4[] = "./textures/r_cube/r4.bmp";
char c5[] = "./textures/r_cube/r5.bmp";
GLfloat cyan[] = {0, 0.8, 0.8, 1}, bulb[] = {1, 1, 1, 1}, white[] = {0.8f, 0.8f, 0.8f, 1.0f};
GLfloat shininess[] = {50};

#endif