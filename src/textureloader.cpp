#ifndef TEXTURELOADER
#define TEXTURELOADER
#include <iostream>
#include "GL/glut.h"
#include <GL/gl.h>
#include <stdlib.h>
#include <stdio.h>
#include "global.h"
#include "drawbox.cpp"

GLuint textureloader(char* imagepath)//Function to load bitmap images for texturing.
{							//REFERENCE:http://www.opengl-tutorial.org/beginners-tutorials/tutorial-5-a-textured-cube
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
  	unsigned int dataPos;     // Position in the file where the actual data begins
  	unsigned int width, height;
  	unsigned int imageSize;   // = width*height*3
  	// Actual RGB data
  	unsigned char * data;
  	GLuint textureID;
  	// Open the file
  	FILE* file = fopen(imagepath,"rb");
  	if (!file)                              
  	{
  		//printf("Image cannot be opened\n"); 
  		return 0;
   	}

  	if ( fread(header, 1, 54, file)!=54 ) // If not 54 bytes read : problem
  	{ 
    	//printf("Not a correct BMP file\n");
    	return 0;
	}
  
  	if ( header[0]!='B' || header[1]!='M' )
    {
    	//printf("Not a correct BMP file\n");
    	return 0;
	}
	dataPos    = *(int*)&(header[0x0A]);
	imageSize  = *(int*)&(header[0x22]);
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);
	// Some BMP files are mis-formatted, guess missing information
	if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos==0)      dataPos=54; // The BMP header is done that way
	// Create a buffer
	data = new unsigned char [imageSize];

	// Read the actual data from the file into the buffer
	fread(data,1,imageSize,file);
	//Everything is in memory now, the file can be closed
	fclose(file);
	// Create one OpenGL texture
	glGenTextures(1, &textureID);
	 
	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);
	 
	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	delete[] data;
	return textureID;
}
#endif