/*
*		This Code Was Created By Jeff Molofee 2000
*		A HUGE Thanks To Fredric Echols For Cleaning Up
*		And Optimizing This Code, Making It More Flexible!
*		If You've Found This Code Useful, Please Let Me Know.
*		Visit My Site At nehe.gamedev.net
*/

#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <GL\glut.h>
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <glaux.h>		// Header File For The Glaux Library
#include <math.h>
#include <stdio.h>                         // Header File For Standard Input/Output ( NEW )
#include "SOIL.h"
#include "Train.h"
#include "point.h"


#pragma comment(lib,"SOIL.lib")



HDC			hDC = NULL;		// Private GDI Device Context
HGLRC		hRC = NULL;		// Permanent Rendering Context
HWND		hWnd = NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

const float piover180 = 0.0174532925f;
float heading;
float xpos;				  
float zpos;

GLfloat	yrot;				// Y Rotation
GLfloat walkbias = 0;
GLfloat walkbiasangle = 0;
GLfloat lookupdown = 0.0f;
GLfloat	z=0.0f;				// Depth Into The Screen






bool	keys[256];			// Array Used For The Keyboard Routine
bool	active = TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen = TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default


GLuint      texture[100];                         // Storage For One Texture ( NEW )


LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

int LoadGLTextures()                                    // Load Bitmaps And Convert To Textures
{
	/* load an image file directly as a new OpenGL texture */
	texture[0] = SOIL_load_OGL_texture
		(
		"Textures/Wood.bmp",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);

	texture[1] = SOIL_load_OGL_texture
		(
		"Textures/nature1.bmp",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);

	texture[2] = SOIL_load_OGL_texture
		(
		"Textures/nature2.bmp",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y

		);
	if (texture[0] == 0 || texture[1] == 0 || texture[2] == 0) return false;


	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	return TRUE;                                        // Return Success
}



GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}



int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	if (!LoadGLTextures())                          // Jump To Texture Loading Routine ( NEW )
	{
		return FALSE;                           // If Texture Didn't Load Return FALSE ( NEW )
	}

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glEnable(GL_TEXTURE_2D);							 // Enable Texture Mapping 
	return TRUE;										// Initialization Went OK
}

void Train1()
{
	glBindTexture(GL_TEXTURE_2D, texture[0]);               // Select Our Texture
	Train1::DrawTrain(Point(-10,0,0),Point(-10,10,0),Point(10,10,0),Point(10,0,0)); //front

	Train1::DrawTrain(Point(-10,0,-30),Point(-10,10,-30),Point(-3,10,-30),Point(-3,0,-30)); //back left
	Train1::DrawTrain(Point(-3,7,-30),Point(-3,10,-30),Point(3,10,-30),Point(3,7,-30)); //back center
	Train1::DrawTrain(Point(3,0,-30),Point(3,10,-30),Point(10,10,-30),Point(10,0,-30)); //back right


	Train1::DrawWalls(Point(-10,0,-30),Point(-10,10,-30),Point(-10,10,0),Point(-10,0,0)); //left
	Train1::DrawWalls(Point(10,0,0),Point(10,10,0),Point(10,10,-30),Point(10,0,-30));	//right
	Train1::DrawWalls(Point(-10,10,-30),Point(10,10,-30),Point(10,10,0),Point(-10,10,0));	 //roof
	Train1::DrawWalls(Point(-10,0,-30),Point(10,0,-30),Point(10,0,0),Point(-10,0,0));	//floor

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	Train1::Window(Point(-10,3,-10),Point(-10,8,-10),Point(-10,8,-20),Point(-10,3,-20));
	Train1::Window(Point(10,3,-10),Point(10,8,-10),Point(10,8,-20),Point(10,3,-20));
}
void Train2()
{
	glTranslatef(0,0,-30);
	glBindTexture(GL_TEXTURE_2D, texture[0]);               // Select Our Texture
	Train2::DrawTrain(Point(-10,0,0),Point(-10,10,0),Point(-3,10,0),Point(-3,0,0)); //front left
	Train2::DrawTrain(Point(-3,7,0),Point(-3,10,0),Point(3,10,0),Point(3,7,0)); //front center
	Train2::DrawTrain(Point(3,0,0),Point(3,10,0),Point(10,10,0),Point(10,0,0)); //front right
	Train2::DrawTrain(Point(-10,0,-30),Point(-10,10,-30),Point(-3,10,-30),Point(-3,0,-30)); //back left
	Train2::DrawTrain(Point(-3,7,-30),Point(-3,10,-30),Point(3,10,-30),Point(3,7,-30)); //back center
	Train2::DrawTrain(Point(3,0,-30),Point(3,10,-30),Point(10,10,-30),Point(10,0,-30)); //back right

	glBindTexture(GL_TEXTURE_2D, texture[0]); 
	Train2::DrawDoor(Point(3,0,0),Point(3,7,0),Point(-3,7,0),Point(-3,0,0));

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	Train2::DrawWalls(Point(-10,0,-30),Point(-10,10,-30),Point(-10,10,0),Point(-10,0,0)); //left
	Train2::DrawWalls(Point(10,0,0),Point(10,10,0),Point(10,10,-30),Point(10,0,-30));	//right
	Train2::DrawWalls(Point(-10,10,-30),Point(10,10,-30),Point(10,10,0),Point(-10,10,0));	 //roof
	Train2::DrawWalls(Point(-10,0,-30),Point(10,0,-30),Point(10,0,0),Point(-10,0,0));	//floor

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	Train2::Window(Point(-10,3,-10),Point(-10,8,-10),Point(-10,8,-20),Point(-10,3,-20));
	Train2::Window(Point(10,3,-10),Point(10,8,-10),Point(10,8,-20),Point(10,3,-20));
}
void Train3()
{
	glTranslatef(0,0,-30);
	glBindTexture(GL_TEXTURE_2D, texture[0]);               // Select Our Texture
	Train3::DrawTrain(Point(-10,0,0),Point(-10,10,0),Point(-3,10,0),Point(-3,0,0)); //front left
	Train3::DrawTrain(Point(-3,7,0),Point(-3,10,0),Point(3,10,0),Point(3,7,0)); //front center
	Train3::DrawTrain(Point(3,0,0),Point(3,10,0),Point(10,10,0),Point(10,0,0)); //front right
	Train3::DrawTrain(Point(-10,0,-30),Point(-10,10,-30),Point(-3,10,-30),Point(-3,0,-30)); //back left
	Train3::DrawTrain(Point(-3,7,-30),Point(-3,10,-30),Point(3,10,-30),Point(3,7,-30)); //back center
	Train3::DrawTrain(Point(3,0,-30),Point(3,10,-30),Point(10,10,-30),Point(10,0,-30)); //back right

	glBindTexture(GL_TEXTURE_2D, texture[0]); 
	Train3::DrawDoor(Point(3,0,0),Point(3,7,0),Point(-3,7,0),Point(-3,0,0));

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	Train3::DrawWalls(Point(-10,0,-30),Point(-10,10,-30),Point(-10,10,0),Point(-10,0,0)); //left
	Train3::DrawWalls(Point(10,0,0),Point(10,10,0),Point(10,10,-30),Point(10,0,-30));	//right
	Train3::DrawWalls(Point(-10,10,-30),Point(10,10,-30),Point(10,10,0),Point(-10,10,0));	 //roof
	Train3::DrawWalls(Point(-10,0,-30),Point(10,0,-30),Point(10,0,0),Point(-10,0,0));	//floor

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	Train3::Window(Point(-10,3,-10),Point(-10,8,-10),Point(-10,8,-20),Point(-10,3,-20));
	Train3::Window(Point(10,3,-10),Point(10,8,-10),Point(10,8,-20),Point(10,3,-20));
}
void Train4()
{
	glTranslatef(0,0,-30);
	glBindTexture(GL_TEXTURE_2D, texture[0]);               // Select Our Texture
	Train4::DrawTrain(Point(-10,0,0),Point(-10,10,0),Point(-3,10,0),Point(-3,0,0)); //front left
	Train4::DrawTrain(Point(-3,7,0),Point(-3,10,0),Point(3,10,0),Point(3,7,0)); //front center
	Train4::DrawTrain(Point(3,0,0),Point(3,10,0),Point(10,10,0),Point(10,0,0)); //front right
	Train4::DrawTrain(Point(-10,0,-30),Point(-10,10,-30),Point(-3,10,-30),Point(-3,0,-30)); //back left
	Train4::DrawTrain(Point(-3,7,-30),Point(-3,10,-30),Point(3,10,-30),Point(3,7,-30)); //back center
	Train4::DrawTrain(Point(3,0,-30),Point(3,10,-30),Point(10,10,-30),Point(10,0,-30)); //back right

	glBindTexture(GL_TEXTURE_2D, texture[0]); 
	Train4::DrawDoor(Point(3,0,0),Point(3,7,0),Point(-3,7,0),Point(-3,0,0));

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	Train4::DrawWalls(Point(-10,0,-30),Point(-10,10,-30),Point(-10,10,0),Point(-10,0,0)); //left
	Train4::DrawWalls(Point(10,0,0),Point(10,10,0),Point(10,10,-30),Point(10,0,-30));	//right
	Train4::DrawWalls(Point(-10,10,-30),Point(10,10,-30),Point(10,10,0),Point(-10,10,0));	 //roof
	Train4::DrawWalls(Point(-10,0,-30),Point(10,0,-30),Point(10,0,0),Point(-10,0,0));	//floor

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	Train4::Window(Point(-10,3,-10),Point(-10,8,-10),Point(-10,8,-20),Point(-10,3,-20));
	Train4::Window(Point(10,3,-10),Point(10,8,-10),Point(10,8,-20),Point(10,3,-20));
}
void Train5()
{
	glTranslatef(0,0,-30);
	glBindTexture(GL_TEXTURE_2D, texture[0]);               // Select Our Texture
	Train5::DrawTrain(Point(-10,0,0),Point(-10,10,0),Point(-3,10,0),Point(-3,0,0)); //front left
	Train5::DrawTrain(Point(-3,7,0),Point(-3,10,0),Point(3,10,0),Point(3,7,0)); //front center
	Train5::DrawTrain(Point(3,0,0),Point(3,10,0),Point(10,10,0),Point(10,0,0)); //front right
	Train5::DrawTrain(Point(-10,0,-30),Point(-10,10,-30),Point(-3,10,-30),Point(-3,0,-30)); //back left
	Train5::DrawTrain(Point(-3,7,-30),Point(-3,10,-30),Point(3,10,-30),Point(3,7,-30)); //back center
	Train5::DrawTrain(Point(3,0,-30),Point(3,10,-30),Point(10,10,-30),Point(10,0,-30)); //back right

	glBindTexture(GL_TEXTURE_2D, texture[0]); 
	Train5::DrawDoor(Point(3,0,0),Point(3,7,0),Point(-3,7,0),Point(-3,0,0));

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	Train5::DrawWalls(Point(-10,0,-30),Point(-10,10,-30),Point(-10,10,0),Point(-10,0,0)); //left
	Train5::DrawWalls(Point(10,0,0),Point(10,10,0),Point(10,10,-30),Point(10,0,-30));	//right
	Train5::DrawWalls(Point(-10,10,-30),Point(10,10,-30),Point(10,10,0),Point(-10,10,0));	 //roof
	Train5::DrawWalls(Point(-10,0,-30),Point(10,0,-30),Point(10,0,0),Point(-10,0,0));	//floor

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	Train5::Window(Point(-10,3,-10),Point(-10,8,-10),Point(-10,8,-20),Point(-10,3,-20));
	Train5::Window(Point(10,3,-10),Point(10,8,-10),Point(10,8,-20),Point(10,3,-20));
}
void Train6()
{
	glTranslatef(0,0,-30);
	glBindTexture(GL_TEXTURE_2D, texture[0]);               // Select Our Texture
	Train6::DrawTrain(Point(-10,0,0),Point(-10,10,0),Point(-3,10,0),Point(-3,0,0)); //front left
	Train6::DrawTrain(Point(-3,7,0),Point(-3,10,0),Point(3,10,0),Point(3,7,0)); //front center
	Train6::DrawTrain(Point(3,0,0),Point(3,10,0),Point(10,10,0),Point(10,0,0)); //front right
	Train6::DrawTrain(Point(-10,0,-30),Point(-10,10,-30),Point(-3,10,-30),Point(-3,0,-30)); //back left
	Train6::DrawTrain(Point(-3,7,-30),Point(-3,10,-30),Point(3,10,-30),Point(3,7,-30)); //back center
	Train6::DrawTrain(Point(3,0,-30),Point(3,10,-30),Point(10,10,-30),Point(10,0,-30)); //back right

	glBindTexture(GL_TEXTURE_2D, texture[0]); 
	Train6::DrawDoor(Point(3,0,0),Point(3,7,0),Point(-3,7,0),Point(-3,0,0));

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	Train6::DrawWalls(Point(-10,0,-30),Point(-10,10,-30),Point(-10,10,0),Point(-10,0,0)); //left
	Train6::DrawWalls(Point(10,0,0),Point(10,10,0),Point(10,10,-30),Point(10,0,-30));	//right
	Train6::DrawWalls(Point(-10,10,-30),Point(10,10,-30),Point(10,10,0),Point(-10,10,0));	 //roof
	Train6::DrawWalls(Point(-10,0,-30),Point(10,0,-30),Point(10,0,0),Point(-10,0,0));	//floor

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	Train6::Window(Point(-10,3,-10),Point(-10,8,-10),Point(-10,8,-20),Point(-10,3,-20));
	Train6::Window(Point(10,3,-10),Point(10,8,-10),Point(10,8,-20),Point(10,3,-20));
}
void Train7()
{
	glTranslatef(0,0,-30);
	glBindTexture(GL_TEXTURE_2D, texture[0]);               // Select Our Texture
	Train7::DrawTrain(Point(-10,0,0),Point(-10,10,0),Point(-3,10,0),Point(-3,0,0)); //front left
	Train7::DrawTrain(Point(-3,7,0),Point(-3,10,0),Point(3,10,0),Point(3,7,0)); //front center
	Train7::DrawTrain(Point(3,0,0),Point(3,10,0),Point(10,10,0),Point(10,0,0)); //front right
	Train7::DrawTrain(Point(-10,0,-30),Point(-10,10,-30),Point(-3,10,-30),Point(-3,0,-30)); //back left
	Train7::DrawTrain(Point(-3,7,-30),Point(-3,10,-30),Point(3,10,-30),Point(3,7,-30)); //back center
	Train7::DrawTrain(Point(3,0,-30),Point(3,10,-30),Point(10,10,-30),Point(10,0,-30)); //back right

	glBindTexture(GL_TEXTURE_2D, texture[0]); 
	Train7::DrawDoor(Point(3,0,0),Point(3,7,0),Point(-3,7,0),Point(-3,0,0));

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	Train7::DrawWalls(Point(-10,0,-30),Point(-10,10,-30),Point(-10,10,0),Point(-10,0,0)); //left
	Train7::DrawWalls(Point(10,0,0),Point(10,10,0),Point(10,10,-30),Point(10,0,-30));	//right
	Train7::DrawWalls(Point(-10,10,-30),Point(10,10,-30),Point(10,10,0),Point(-10,10,0));	 //roof
	Train7::DrawWalls(Point(-10,0,-30),Point(10,0,-30),Point(10,0,0),Point(-10,0,0));	//floor

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	Train7::Window(Point(-10,3,-10),Point(-10,8,-10),Point(-10,8,-20),Point(-10,3,-20));
	Train7::Window(Point(10,3,-10),Point(10,8,-10),Point(10,8,-20),Point(10,3,-20));
}
void Train8()
{
	glTranslatef(0,0,-30);
	glBindTexture(GL_TEXTURE_2D, texture[0]);               // Select Our Texture
	Train8::DrawTrain(Point(-10,0,0),Point(-10,10,0),Point(-3,10,0),Point(-3,0,0)); //front left
	Train8::DrawTrain(Point(-3,7,0),Point(-3,10,0),Point(3,10,0),Point(3,7,0)); //front center
	Train8::DrawTrain(Point(3,0,0),Point(3,10,0),Point(10,10,0),Point(10,0,0)); //front right
	Train8::DrawTrain(Point(-10,0,-30),Point(-10,10,-30),Point(-3,10,-30),Point(-3,0,-30)); //back left
	Train8::DrawTrain(Point(-3,7,-30),Point(-3,10,-30),Point(3,10,-30),Point(3,7,-30)); //back center
	Train8::DrawTrain(Point(3,0,-30),Point(3,10,-30),Point(10,10,-30),Point(10,0,-30)); //back right

	glBindTexture(GL_TEXTURE_2D, texture[0]); 
	Train8::DrawDoor(Point(3,0,0),Point(3,7,0),Point(-3,7,0),Point(-3,0,0));

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	Train8::DrawWalls(Point(-10,0,-30),Point(-10,10,-30),Point(-10,10,0),Point(-10,0,0)); //left
	Train8::DrawWalls(Point(10,0,0),Point(10,10,0),Point(10,10,-30),Point(10,0,-30));	//right
	Train8::DrawWalls(Point(-10,10,-30),Point(10,10,-30),Point(10,10,0),Point(-10,10,0));	 //roof
	Train8::DrawWalls(Point(-10,0,-30),Point(10,0,-30),Point(10,0,0),Point(-10,0,0));	//floor

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	Train8::Window(Point(-10,3,-10),Point(-10,8,-10),Point(-10,8,-20),Point(-10,3,-20));
	Train8::Window(Point(10,3,-10),Point(10,8,-10),Point(10,8,-20),Point(10,3,-20));
}
void Train9()
{
	glTranslatef(0,0,-30);
	glBindTexture(GL_TEXTURE_2D, texture[0]);               // Select Our Texture
	Train9::DrawTrain(Point(-10,0,0),Point(-10,10,0),Point(-3,10,0),Point(-3,0,0)); //front left
	Train9::DrawTrain(Point(-3,7,0),Point(-3,10,0),Point(3,10,0),Point(3,7,0)); //front center
	Train9::DrawTrain(Point(3,0,0),Point(3,10,0),Point(10,10,0),Point(10,0,0)); //front right
	Train9::DrawTrain(Point(-10,0,-30),Point(-10,10,-30),Point(-3,10,-30),Point(-3,0,-30)); //back left
	Train9::DrawTrain(Point(-3,7,-30),Point(-3,10,-30),Point(3,10,-30),Point(3,7,-30)); //back center
	Train9::DrawTrain(Point(3,0,-30),Point(3,10,-30),Point(10,10,-30),Point(10,0,-30)); //back right

	glBindTexture(GL_TEXTURE_2D, texture[0]); 
	Train9::DrawDoor(Point(3,0,0),Point(3,7,0),Point(-3,7,0),Point(-3,0,0));

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	Train9::DrawWalls(Point(-10,0,-30),Point(-10,10,-30),Point(-10,10,0),Point(-10,0,0)); //left
	Train9::DrawWalls(Point(10,0,0),Point(10,10,0),Point(10,10,-30),Point(10,0,-30));	//right
	Train9::DrawWalls(Point(-10,10,-30),Point(10,10,-30),Point(10,10,0),Point(-10,10,0));	 //roof
	Train9::DrawWalls(Point(-10,0,-30),Point(10,0,-30),Point(10,0,0),Point(-10,0,0));	//floor

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	Train9::Window(Point(-10,3,-10),Point(-10,8,-10),Point(-10,8,-20),Point(-10,3,-20));
	Train9::Window(Point(10,3,-10),Point(10,8,-10),Point(10,8,-20),Point(10,3,-20));
}
void Train10()
{
	glTranslatef(0,0,-30);
	glBindTexture(GL_TEXTURE_2D, texture[0]);               // Select Our Texture
	Train10::DrawTrain(Point(-10,0,0),Point(-10,10,0),Point(-3,10,0),Point(-3,0,0)); //front left
	Train10::DrawTrain(Point(-3,7,0),Point(-3,10,0),Point(3,10,0),Point(3,7,0)); //front center
	Train10::DrawTrain(Point(3,0,0),Point(3,10,0),Point(10,10,0),Point(10,0,0)); //front right
	Train10::DrawTrain(Point(-10,0,-30),Point(-10,10,-30),Point(-3,10,-30),Point(-3,0,-30)); //back left
	Train10::DrawTrain(Point(-3,7,-30),Point(-3,10,-30),Point(3,10,-30),Point(3,7,-30)); //back center
	Train10::DrawTrain(Point(3,0,-30),Point(3,10,-30),Point(10,10,-30),Point(10,0,-30)); //back right

	glBindTexture(GL_TEXTURE_2D, texture[0]); 
	Train10::DrawDoor(Point(3,0,0),Point(3,7,0),Point(-3,7,0),Point(-3,0,0));

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	Train10::DrawWalls(Point(-10,0,-30),Point(-10,10,-30),Point(-10,10,0),Point(-10,0,0)); //left
	Train10::DrawWalls(Point(10,0,0),Point(10,10,0),Point(10,10,-30),Point(10,0,-30));	//right
	Train10::DrawWalls(Point(-10,10,-30),Point(10,10,-30),Point(10,10,0),Point(-10,10,0));	 //roof
	Train10::DrawWalls(Point(-10,0,-30),Point(10,0,-30),Point(10,0,0),Point(-10,0,0));	//floor

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	Train10::Window(Point(-10,3,-10),Point(-10,8,-10),Point(-10,8,-20),Point(-10,3,-20));
	Train10::Window(Point(10,3,-10),Point(10,8,-10),Point(10,8,-20),Point(10,3,-20));
}
void Camera(){
	GLfloat xtrans = -xpos;
	GLfloat ztrans = -zpos;
	GLfloat ytrans = -walkbias-0.25f;
	GLfloat sceneroty = 360.0f - yrot;

	glRotatef(lookupdown,1.0f,0,0);
	glRotatef(sceneroty,0,1.0f,0);

	glTranslatef(xtrans, ytrans-2.5, ztrans);

}
int DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();	// Reset The Current Modelview Matrix

	Camera();
	Train1();
	Train2();
	Train3();
	Train4();
	Train5();
	Train6();
	Train7();
	Train8();	 
	Train9();
	Train10();






	//DO NOT REMOVE THIS

	return TRUE;
}

GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL, 0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL, NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd, hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL", hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
*	title			- Title To Appear At The Top Of The Window				*
*	width			- Width Of The GL Window Or Fullscreen Mode				*
*	height			- Height Of The GL Window Or Fullscreen Mode			*
*	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
*	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/

BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;			// Set Left Value To 0
	WindowRect.right = (long)width;		// Set Right Value To Requested Width
	WindowRect.top = (long)0;				// Set Top Value To 0
	WindowRect.bottom = (long)height;		// Set Bottom Value To Requested Height

	fullscreen = fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance = GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = (WNDPROC)WndProc;					// WndProc Handles Messages
	wc.cbClsExtra = 0;									// No Extra Window Data
	wc.cbWndExtra = 0;									// No Extra Window Data
	wc.hInstance = hInstance;							// Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground = NULL;									// No Background Required For GL
	wc.lpszMenuName = NULL;									// We Don't Want A Menu
	wc.lpszClassName = "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth = width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight = height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel = bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", "NeHe GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle = WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle = WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle = WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd = CreateWindowEx(dwExStyle,							// Extended Style For The Window
		"OpenGL",							// Class Name
		title,								// Window Title
		dwStyle |							// Defined Window Style
		WS_CLIPSIBLINGS |					// Required Window Style
		WS_CLIPCHILDREN,					// Required Window Style
		0, 0,								// Window Position
		WindowRect.right - WindowRect.left,	// Calculate Window Width
		WindowRect.bottom - WindowRect.top,	// Calculate Window Height
		NULL,								// No Parent Window
		NULL,								// No Menu
		hInstance,							// Instance
		NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(hDC = GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC = wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!wglMakeCurrent(hDC, hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd, SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}

LRESULT CALLBACK WndProc(HWND	hWnd,			// Handle For This Window
						 UINT	uMsg,			// Message For This Window
						 WPARAM	wParam,			// Additional Message Information
						 LPARAM	lParam)			// Additional Message Information
{
	static PAINTSTRUCT ps;

	switch (uMsg)									// Check For Windows Messages
	{
	case WM_PAINT:
		DrawGLScene();
		BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		return 0;

	case WM_TIMER:
		DrawGLScene();
		return 0;

	case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))					// Check Minimization State
			{
				active = TRUE;						// Program Is Active
			}
			else
			{
				active = FALSE;						// Program Is No Longer Active
			}

			return 0;								// Return To The Message Loop
		}

	case WM_SYSCOMMAND:							// Intercept System Commands
		{
			switch (wParam)							// Check System Calls
			{
			case SC_SCREENSAVE:					// Screensaver Trying To Start?
			case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				return 0;							// Prevent From Happening
			}
			break;									// Exit
		}

	case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}

	case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
			keys[wParam] = TRUE;					// If So, Mark It As TRUE
			return 0;								// Jump Back
		}

	case WM_KEYUP:								// Has A Key Been Released?
		{
			keys[wParam] = FALSE;					// If So, Mark It As FALSE
			return 0;								// Jump Back
		}

	case WM_SIZE:								// Resize The OpenGL Window
		{
			ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;								// Jump Back
		}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE	hInstance,			// Instance
				   HINSTANCE	hPrevInstance,		// Previous Instance
				   LPSTR		lpCmdLine,			// Command Line Parameters
				   int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	done = FALSE;								// Bool Variable To Exit Loop

	// Ask The User Which Screen Mode They Prefer
	//if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	//{
	//	fullscreen = FALSE;							// Windowed Mode
	//}

	// Create Our OpenGL Window
	char c[] = "";
	if (!CreateGLWindow(c, 1920, 1080, 16, fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}

	while(!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
			{
				done=TRUE;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if ((active && !DrawGLScene()) || keys[VK_ESCAPE])	// Active?  Was There A Quit Received?
			{
				done=TRUE;							// ESC or DrawGLScene Signalled A Quit
			}
			else									// Not Time To Quit, Update Screen
			{
				SwapBuffers(hDC);					// Swap Buffers (Double Buffering)


				if (keys['W'])
				{

					xpos -= (float)sin(heading*piover180) * 0.05f;
					zpos -= (float)cos(heading*piover180) * 0.05f;
					if (walkbiasangle >= 359.0f)
					{
						walkbiasangle = 0.0f;
					}
					else
					{
						walkbiasangle+= 10;
					}
					walkbias = (float)sin(walkbiasangle * piover180)/20.0f;
				}

				if (keys['S'])
				{
					xpos += (float)sin(heading*piover180) * 0.05f;
					zpos += (float)cos(heading*piover180) * 0.05f;
					if (walkbiasangle <= 1.0f)
					{
						walkbiasangle = 359.0f;
					}
					else
					{
						walkbiasangle-= 10;
					}
					walkbias = (float)sin(walkbiasangle * piover180)/20.0f;
				}

				if (keys['D'])
				{
					heading -= 1.0f;
					yrot = heading;
				}

				if (keys['A'])
				{
					heading += 1.0f;	
					yrot = heading;
				}

				if (keys[VK_PRIOR])
				{
					lookupdown-= 1.0f;
				}

				if (keys[VK_NEXT])
				{
					lookupdown+= 1.0f;
				}

				if (keys[VK_F1])						// Is F1 Being Pressed?
				{
					keys[VK_F1]=FALSE;					// If So Make Key FALSE
					KillGLWindow();						// Kill Our Current Window
					fullscreen=!fullscreen;				// Toggle Fullscreen / Windowed Mode
					// Recreate Our OpenGL Window
					if (!CreateGLWindow("Lionel Brits & NeHe's 3D World Tutorial",1920, 1080, 16,fullscreen))
					{
						return 0;						// Quit If Window Was Not Created
					}
				}
			}
		}
	}

	//Set drawing timer to 20 frame per second
	UINT timer = SetTimer(hWnd, 0, 0, (TIMERPROC)NULL);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;

}
