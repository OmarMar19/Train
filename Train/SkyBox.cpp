#include <windows.h>
#include <gl\gl.h>
#include "point.h"
#include "SkyBox.h"
#include <stdio.h>  



void SkyBox::skyBox(Point left,Point upperLeft, Point upperRight,Point right)
{
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);   glVertex3f(left.x, left.y, left.z);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(upperLeft.x, upperLeft.y, upperLeft.z);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(upperRight.x, upperRight.y, upperRight.z);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(right.x, right.y, right.z);
	glEnd();
	
}