#include "ObjLoader.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

ObjLoader::ObjLoader()
{

}

int ObjLoader::Load(std::string filepath, int loadtype)
{
	// 打开文件流
	std::ifstream fin(filepath);
	std::string line;
	if (!fin.is_open())
	{
		std::cout << "file " << filepath << " cannot open!" << std::endl;
		exit(-1);
	}

	while (std::getline(fin, line))
	{
		std::istringstream sin(line);   // 以一行的数据作为 string stream 解析并且读取
		std::string type;
		double x, y, z;
		int v0, vt0, vn0;   // 三角网面第 1 个顶点的【位置，纹理坐标，法线】索引
		int v1, vt1, vn1;   // 2
		int v2, vt2, vn2;   // 3
		char slash;

		// 读取obj文件
		sin >> type;
		if (type == "v") {
			sin >> x >> y >> z;
			V.push_back(Point(x, y, z));
		}

		else if (type == "f") {
			if (loadtype == 0)
			{
				sin >> v0 >> slash >> vt0 >> slash;
				sin >> v1 >> slash >> vt1 >> slash;
				sin >> v2 >> slash >> vt2 >> slash;
				F.push_back(Face(V[v0 - 1], V[v1 - 1], V[v2 - 1]));
			}
			else
			{
				sin >> v0 >> slash >> vt0 >> slash >> vn0;
				sin >> v1 >> slash >> vt1 >> slash >> vn1;
				sin >> v2 >> slash >> vt2 >> slash >> vn2;
				F.push_back(Face(V[v0 - 1], V[v1 - 1], V[v2 - 1]));
			}

		}
	}
	return 0;
}

double product(Point p1, Point p2, Point p3) {
	//首先根据坐标计算p1p2和p1p3的向量，然后再计算叉乘
	//p1p2 向量表示为 (p2.x-p1.x,p2.y-p1.y)
	//p1p3 向量表示为 (p3.x-p1.x,p3.y-p1.y)
	return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

bool isInTriangle(Point p1, Point p2, Point p3, Point center) {
	//保证p1，p2，p3是逆时针顺序
	if (product(p1, p2, p3) < 0) return isInTriangle(p1, p3, p2, center);
	if (product(p1, p2, center) > 0 && product(p2, p3, center) > 0 && product(p3, p1, center) > 0)
		return true;
	return false;
}

bool isBelowTriangle(Face triangle, Point center)
{
	double k = triangle.normal.nx * triangle.p1.x +
		triangle.normal.ny * triangle.p1.y +
		triangle.normal.nz * triangle.p1.z;

	double zAtTriangle = (k - triangle.normal.nx * center.x - triangle.normal.ny * center.y) / triangle.normal.nz;

	if (center.z <= zAtTriangle)
		return true;
	return false;
}