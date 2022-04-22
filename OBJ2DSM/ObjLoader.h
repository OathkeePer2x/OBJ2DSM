#pragma once
#include <vector>
#include <string>

struct Point
{
	double x;
	double y;
	double z;

	Point(double _x, double _y, double _z) :x(_x), y(_y), z(_z) {}
};

struct Normal
{
	double nx;
	double ny;
	double nz;

	Normal() :nx(0.0f), ny(0.0f), nz(0.0f) {}
	Normal(double _x, double _y, double _z) :nx(_x), ny(_y), nz(_z) {}
};

struct Face
{
	Point p1;
	Point p2;
	Point p3;
	Normal normal;
	int direction;

	Face(Point _p1, Point _p2, Point _p3) :p1(_p1), p2(_p2), p3(_p3)
	{
		std::vector<double> v1 = { p2.x - p1.x, p2.y - p1.y, p2.z - p1.z };
		std::vector<double> v2 = { p3.x - p1.x, p3.y - p1.y, p3.z - p1.z };
		normal = Normal(
			v1[1] * v2[2] - v2[1] * v1[2],
			v1[0] * v2[2] - v2[0] * v1[2],
			v1[0] * v2[1] - v2[0] * v1[1]
		);

		direction = normal.nz > 0 ? 1 : 0;  //direction = 1,法向量与ENU坐标系z轴所指方向一致；
											//direction = 0,法向量与ENU坐标系z轴所指方向相反；

	}
};

class ObjLoader
{
public:
	ObjLoader();
	int Load(std::string filepath, int loadtype); // 1: x/x/x , 0: x/x
	std::vector<Point> V;
	std::vector<Face> F;
};

double product(Point p1, Point p2, Point p3);

bool isInTriangle(Point p1, Point p2, Point p3, Point center);

bool isBelowTriangle(Face triangle, Point center);