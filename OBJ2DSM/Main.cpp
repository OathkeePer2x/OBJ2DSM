#include <iostream>
#include <filesystem>

#include "ObjLoader.h"
#include "BoundingBox.h"

namespace fs = std::filesystem;

int main()
{
	//================================================================================================
	////function test
	//ObjLoader objtest;
	//objtest.Load("F:\\3DTILES\\Data\\nnu\\Obj\\Tile_-034_-003\\Tile_-034_-003_L21_0000031000.obj", 0);
	//for (auto it = objtest.F.begin(); it != objtest.F.end(); it++)
	//{
	//	std::cout << it->normal.nx << " " << it->normal.ny << " " << it->normal.nz << " " << it->direction << std::endl;
	//}
	//AABBBox boxtest(objtest.V);
	//std::vector<UnitZone> Zonelisttest;
	//UnitZoneSplit(boxtest, Zonelisttest, 3);
	//for (auto it = Zonelisttest.begin(); it != Zonelisttest.end(); it++)
	//{
	//	for (auto f = objtest.F.begin(); f != objtest.F.end(); f++)
	//	{
	//		if (isInTriangle(f->p1, f->p2, f->p3, it->center))
	//		{
	//			if (isBelowTriangle(*f, it->center))
	//			{
	//				it->triangleAboveCenter++;
	//			}
	//		}
	//	}
	//}

	//int space = 0;
	//int entity = 0;

	//for (auto it = Zonelisttest.begin(); it != Zonelisttest.end(); it++)
	//{
	//	std::cout << "xNo: " << it->xNo << std::endl;
	//	std::cout << "yNo: " << it->yNo << std::endl;
	//	std::cout << "zNo: " << it->zNo << std::endl;
	//	std::cout << "center: " << it->center.x << " " << it->center.y << " " << it->center.z << std::endl;
	//	std::cout << "triangleAboveCenter: " << it->triangleAboveCenter << std::endl;
	//	if (it->triangleAboveCenter == 1)
	//		entity++;
	//	else
	//		space++;
	//	std::cout << "space number: " << space << std::endl;
	//	std::cout << "entity number: " << entity << std::endl;
	//}



	//================================================================================================
	//遍历所有obj数据，将顶点和面数据读出来
	ObjLoader nnuObj;

	std::string path = "F:\\3DTILES\\Data\\nnu\\NorthObj";

	std::cout << "loading obj data......" << std::endl;
	for (const auto& objFile : fs::recursive_directory_iterator(path))
	{
		if (fs::path(objFile).extension() == ".obj")
		{
			std::cout << objFile << std::endl;
			std::string objFileString = fs::path(objFile).string();
			nnuObj.Load(objFileString, 0);
		}
	}

	std::cout << "computing boundingbox......" << std::endl;
	AABBBox nnuBoundingBox(nnuObj.V);

	std::cout << "computing unitzone......" << std::endl;
	std::vector<UnitZone> nnuUnitZoneList;
	UnitZoneSplit(nnuBoundingBox, nnuUnitZoneList, 3);

	std::cout << "computing air/entity attribute......" << std::endl;
	for (auto it = nnuUnitZoneList.begin(); it != nnuUnitZoneList.end(); it++)
	{
		for (auto f = nnuObj.F.begin(); f != nnuObj.F.end(); f++)
		{
			if (isInTriangle(f->p1, f->p2, f->p3, it->center))
			{
				if (isBelowTriangle(*f, it->center))
				{
					if (f->direction == 1)
						it->triangleAboveCenter++;
					else
						it->triangleAboveCenter--;
				}
			}
		}
	}

	int space = 0;
	int entity = 0;

	std::cout << "computing space/entity rate......" << std::endl;
	for (auto it = nnuUnitZoneList.begin(); it != nnuUnitZoneList.end(); it++)
	{
		std::cout << "xNo: " << it->xNo << std::endl;
		std::cout << "yNo: " << it->yNo << std::endl;
		std::cout << "zNo: " << it->zNo << std::endl;
		std::cout << "center: " << it->center.x << " " << it->center.y << " " << it->center.z << std::endl;
		std::cout << "triangleAboveCenter: " << it->triangleAboveCenter << std::endl;
		if (it->triangleAboveCenter == 0)
			space++;
		else
			entity++;
	}
	std::cout << "space number: " << space << std::endl;
	std::cout << "entity number: " << entity << std::endl;


	//================================================================================================
	//先计算包围盒，但按原瓦片分开处理各Tile中的obj
}