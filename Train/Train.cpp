
#include "Train.h"
#include "point.h"
#include <windows.h>
#include <gl\gl.h>


void Train::DrawTrain(Point leftPoint, Point leftUpPoint ,Point rightUpPoint,Point rightPoint)
{

	glPushMatrix();
	glBegin(GL_POLYGON);	
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(leftPoint.x, leftPoint.y, leftPoint.z);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(leftUpPoint.x, leftUpPoint.y, leftUpPoint.z);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(rightUpPoint.x, rightUpPoint.y, rightUpPoint.z);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(rightPoint.x, rightPoint.y, rightPoint.z);
	glEnd();
	glPopMatrix();


}
float tra=3,open=6;
void Train::DrawDoor(Point leftPoint, Point upperLeftPoint,Point upperRightPoint, Point rightPoint)
{

	glPushMatrix();
	//glTranslatef(3,0,0);
	//glRotatef(rot,0,1,0);
	glTranslatef(tra,0,0);
	glBegin(GL_POLYGON);

	glTexCoord2f(0.0f, 0.0f);	glVertex3f(leftPoint.x, leftPoint.y, leftPoint.z);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(upperLeftPoint.x, upperLeftPoint.y, upperLeftPoint.z);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(upperRightPoint.x, upperRightPoint.y, upperRightPoint.z);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(rightPoint.x, rightPoint.y, rightPoint.z);
	glEnd();
	//glTranslatef(3,0,0);
	glPopMatrix();

	if(tra<=open)
	{
		tra+=0.001;
		if(tra>open)
			open=0;
	}
	else if (tra >0)
	{
	  tra-=0.001;
	  if(tra<=0)
		 open=6;
	}
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
GLfloat roll;                                  // Rolling Texture
void Train::Window(Point leftPoint, Point upperLeftPoint,Point upperRightPoint, Point rightPoint)
{


	glPushMatrix();
	glBegin(GL_POLYGON);
	glTexCoord2f(-roll + 0.0f, 0.0f);	glVertex3f(leftPoint.x, leftPoint.y, leftPoint.z);
	glTexCoord2f(-roll +0.0f, 1.0f);	glVertex3f(upperLeftPoint.x, upperLeftPoint.y, upperLeftPoint.z);
	glTexCoord2f(-roll +1.0f, 1.0f);	glVertex3f(upperRightPoint.x, upperRightPoint.y, upperRightPoint.z);
	glTexCoord2f(-roll +1.0f, 0.0f);	glVertex3f(rightPoint.x, rightPoint.y, rightPoint.z);
	glEnd();
	glPopMatrix();
	roll += 0.00005f;                               // Increase Our Texture Roll Variable
	if (roll>1)                               // Is Roll Greater Than One
	{
		roll -= 2;                         // Subtract 1 From Roll
	}

}





