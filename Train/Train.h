#pragma once
#include "point.h"

class Train
{
public:
	static	void DrawTrain(Point leftPoint, Point leftUpPoint ,Point rightUpPoint,Point rightPoint);
	static  void DrawWalls(Point leftPoint, Point upperLeftPoint,Point upperRightPoint, Point rightPoint);
	static  void DrawDoor(Point leftPoint, Point upperLeftPoint,Point upperRightPoint, Point rightPoint); 

};



