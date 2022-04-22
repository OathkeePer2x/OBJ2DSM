#pragma once
#include <string>
#include <vector>
#include "ObjLoader.h"

struct AABBBox
{
	double xMin;
	double yMin;
	double zMin;
	double xMax;
	double yMax;
	double zMax;
	AABBBox(std::vector<Point> objPoint)
	{
		xMin = DBL_MAX;
		yMin = DBL_MAX;
		zMin = DBL_MAX;
		xMax = -DBL_MAX;
		yMax = -DBL_MAX;
		zMax = -DBL_MAX;
		for (auto it = objPoint.begin(); it != objPoint.end(); it++)
		{
			if (xMin > it->x) xMin = it->x;
			if (xMax < it->x) xMax = it->x;
			if (yMin > it->y) yMin = it->y;
			if (yMax < it->y) yMax = it->y;
			if (zMin > it->z) zMin = it->z;
			if (zMax < it->z) zMax = it->z;
		}
	}
};

struct UnitZone
{
	Point center;
	int xNo;
	int yNo;
	int zNo;
	int triangleAboveCenter;

	UnitZone(Point center, int _xNo, int _yNo, int _zNo) :center(center), xNo(_xNo), yNo(_yNo), zNo(_zNo), triangleAboveCenter(0) {}
};


void UnitZoneSplit(AABBBox box, std::vector<UnitZone>& Zonelist, double size);