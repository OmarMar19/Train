
#include "Train.h"
#include "point.h"
#include <windows.h>
#include <gl\gl.h>


GLfloat tra7=3,open7=6 , roll7;
void Train7::DrawTrain(Point leftPoint, Point leftUpPoint ,Point rightUpPoint,Point rightPoint)
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

void Train7::DrawDoor(Point leftPoint, Point upperLeftPoint,Point upperRightPoint, Point rightPoint)
{

	glPushMatrix();

	glTranslatef(tra7,0,0);
	glBegin(GL_POLYGON);

	glTexCoord2f(0.0f, 0.0f);	glVertex3f(leftPoint.x, leftPoint.y, leftPoint.z);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(upperLeftPoint.x, upperLeftPoint.y, upperLeftPoint.z);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(upperRightPoint.x, upperRightPoint.y, upperRightPoint.z);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(rightPoint.x, rightPoint.y, rightPoint.z);
	glEnd();
	//glTranslatef(3,0,0);
	glPopMatrix();
	
		if(tra7<=open7)
		{
			tra7+=0.01;
			if(tra7>open7)
				open7=0;
		}
		else if (tra7 >0)
		{
			tra7-=0.01;
			if(tra7<=0)
				open7=6;
		}

	
}
void Train7::DrawWalls(Point leftPoint, Point upperLeftPoint,Point upperRightPoint, Point rightPoint)
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
void Train7::Window(Point leftPoint, Point upperLeftPoint,Point upperRightPoint, Point rightPoint)
{


	glPushMatrix();
	glBegin(GL_POLYGON);
	glTexCoord2f(+roll7 + 0.0f, 0.0f);	glVertex3f(leftPoint.x, leftPoint.y, leftPoint.z);
	glTexCoord2f(+roll7 +0.0f, 1.0f);	glVertex3f(upperLeftPoint.x, upperLeftPoint.y, upperLeftPoint.z);
	glTexCoord2f(+roll7 +1.0f, 1.0f);	glVertex3f(upperRightPoint.x, upperRightPoint.y, upperRightPoint.z);
	glTexCoord2f(+roll7 +1.0f, 0.0f);	glVertex3f(rightPoint.x, rightPoint.y, rightPoint.z);
	glEnd();
	glPopMatrix();
	roll7 += 0.002f;                               // Increase Our Texture Roll Variable
	

}





