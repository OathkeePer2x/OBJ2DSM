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
	// ���ļ���
	std::ifstream fin(filepath);
	std::string line;
	if (!fin.is_open())
	{
		std::cout << "file " << filepath << " cannot open!" << std::endl;
		exit(-1);
	}

	while (std::getline(fin, line))
	{
		std::istringstream sin(line);   // ��һ�е�������Ϊ string stream �������Ҷ�ȡ
		std::string type;
		double x, y, z;
		int v0, vt0, vn0;   // ��������� 1 ������ġ�λ�ã��������꣬���ߡ�����
		int v1, vt1, vn1;   // 2
		int v2, vt2, vn2;   // 3
		char slash;

		// ��ȡobj�ļ�
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
	//���ȸ����������p1p2��p1p3��������Ȼ���ټ�����
	//p1p2 ������ʾΪ (p2.x-p1.x,p2.y-p1.y)
	//p1p3 ������ʾΪ (p3.x-p1.x,p3.y-p1.y)
	return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

bool isInTriangle(Point p1, Point p2, Point p3, Point center) {
	//��֤p1��p2��p3����ʱ��˳��
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