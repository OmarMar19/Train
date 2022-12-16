														  
#include "Train.h"
#include "point.h"
#include <windows.h>
#include <gl\gl.h>


GLfloat tra5=3,open5=6 , roll5;
void Train5::DrawTrain(Point leftPoint, Point leftUpPoint ,Point rightUpPoint,Point rightPoint)
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

void Train5::DrawDoor(Point leftPoint, Point upperLeftPoint,Point upperRightPoint, Point rightPoint)
{

	glPushMatrix();

	glTranslatef(tra5,0,0);
	glBegin(GL_POLYGON);

	glTexCoord2f(0.0f, 0.0f);	glVertex3f(leftPoint.x, leftPoint.y, leftPoint.z);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(upperLeftPoint.x, upperLeftPoint.y, upperLeftPoint.z);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(upperRightPoint.x, upperRightPoint.y, upperRightPoint.z);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(rightPoint.x, rightPoint.y, rightPoint.z);
	glEnd();
	//glTranslatef(3,0,0);
	glPopMatrix();
	
		if(tra5<=open5)
		{
			tra5+=0.01;
			if(tra5>open5)
				open5=0;
		}
		else if (tra5 >0)
		{
			tra5-=0.01;
			if(tra5<=0)
				open5=6;
		}

	
}
void Train5::DrawWalls(Point leftPoint, Point upperLeftPoint,Point upperRightPoint, Point rightPoint)
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
// Rolling Texture
void Train5::Window(Point leftPoint, Point upperLeftPoint,Point upperRightPoint, Point rightPoint)
{


	glPushMatrix();
	glBegin(GL_POLYGON);
	glTexCoord2f(+roll5 + 0.0f, 0.0f);	glVertex3f(leftPoint.x, leftPoint.y, leftPoint.z);
	glTexCoord2f(+roll5 +0.0f, 1.0f);	glVertex3f(upperLeftPoint.x, upperLeftPoint.y, upperLeftPoint.z);
	glTexCoord2f(+roll5 +1.0f, 1.0f);	glVertex3f(upperRightPoint.x, upperRightPoint.y, upperRightPoint.z);
	glTexCoord2f(+roll5 +1.0f, 0.0f);	glVertex3f(rightPoint.x, rightPoint.y, rightPoint.z);
	glEnd();
	glPopMatrix();
	roll5 += 0.002f;                               // Increase Our Texture Roll Variable
	

}





