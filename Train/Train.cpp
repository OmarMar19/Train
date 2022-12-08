
#include "Train.h"
#include "point.h"
#include <windows.h>
#include <gl\gl.h>


void Train::DrawTrain(Point leftPoint, Point leftUpPoint ,Point rightUpPoint,Point rightPoint)
{

	glPushMatrix();																																
	glColor3f(1,0,0);
	glBegin(GL_POLYGON);	
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(leftPoint.x, leftPoint.y, leftPoint.z);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(leftUpPoint.x, leftUpPoint.y, leftUpPoint.z);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(rightUpPoint.x, rightUpPoint.y, rightUpPoint.z);
glTexCoord2f(1.0f, 0.0f);	glVertex3f(rightPoint.x, rightPoint.y, rightPoint.z);
	

	glEnd();
	glColor3f(1,1,1);
	glPopMatrix();
}

void Train::DrawDoor(Point leftPoint, Point upperLeftPoint,Point upperRightPoint, Point rightPoint)
{
	glPushMatrix();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(leftPoint.x, leftPoint.y, leftPoint.z);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(upperLeftPoint.x, upperLeftPoint.y, upperLeftPoint.z);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(upperRightPoint.x, upperRightPoint.y, upperRightPoint.z);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(rightPoint.x, rightPoint.y, rightPoint.z);
	glEnd();

	glPopMatrix();
}
void Train::DrawWalls(Point leftPoint, Point upperLeftPoint,Point upperRightPoint, Point rightPoint)
{
	glPushMatrix();


	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(leftPoint.x, leftPoint.y, leftPoint.z);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(upperLeftPoint.x, upperLeftPoint.y, upperLeftPoint.z);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(upperRightPoint.x, upperRightPoint.y, upperRightPoint.z);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(rightPoint.x, rightPoint.y, rightPoint.z);
	glEnd();

	glPopMatrix();
}





