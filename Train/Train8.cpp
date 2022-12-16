
#include "Train.h"
#include "point.h"
#include <windows.h>
#include <gl\gl.h>


GLfloat tra8=3,open8=6 , roll8;
void Train8::DrawTrain(Point leftPoint, Point leftUpPoint ,Point rightUpPoint,Point rightPoint)
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

void Train8::DrawDoor(Point leftPoint, Point upperLeftPoint,Point upperRightPoint, Point rightPoint)
{

	glPushMatrix();

	glTranslatef(tra8,0,0);
	glBegin(GL_POLYGON);

	glTexCoord2f(0.0f, 0.0f);	glVertex3f(leftPoint.x, leftPoint.y, leftPoint.z);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(upperLeftPoint.x, upperLeftPoint.y, upperLeftPoint.z);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(upperRightPoint.x, upperRightPoint.y, upperRightPoint.z);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(rightPoint.x, rightPoint.y, rightPoint.z);
	glEnd();
	//glTranslatef(3,0,0);
	glPopMatrix();
	
		if(tra8<=open8)
		{
			tra8+=0.01;
			if(tra8>open8)
				open8=0;
		}
		else if (tra8 >0)
		{
			tra8-=0.01;
			if(tra8<=0)
				open8=6;
		}

	
}
void Train8::DrawWalls(Point leftPoint, Point upperLeftPoint,Point upperRightPoint, Point rightPoint)
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
void Train8::Window(Point leftPoint, Point upperLeftPoint,Point upperRightPoint, Point rightPoint)
{


	glPushMatrix();
	glBegin(GL_POLYGON);
	glTexCoord2f(+roll8 + 0.0f, 0.0f);	glVertex3f(leftPoint.x, leftPoint.y, leftPoint.z);
	glTexCoord2f(+roll8 +0.0f, 1.0f);	glVertex3f(upperLeftPoint.x, upperLeftPoint.y, upperLeftPoint.z);
	glTexCoord2f(+roll8 +1.0f, 1.0f);	glVertex3f(upperRightPoint.x, upperRightPoint.y, upperRightPoint.z);
	glTexCoord2f(+roll8 +1.0f, 0.0f);	glVertex3f(rightPoint.x, rightPoint.y, rightPoint.z);
	glEnd();
	glPopMatrix();
	roll8 += 0.002f;                               // Increase Our Texture Roll Variable
	

}





