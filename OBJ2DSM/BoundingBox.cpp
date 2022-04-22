#include <string>
#include <math.h>
#include "ObjLoader.h"
#include "BoundingBox.h"



void UnitZoneSplit(AABBBox box, std::vector<UnitZone>& Zonelist, double size)
{
	int xNum = ceil((box.xMax - box.xMin) / size);
	int yNum = ceil((box.yMax - box.yMin) / size);
	int zNum = ceil((box.zMax - box.zMin) / size);


	for (int i = 0; i < xNum; i++)
	{
		for (int j = 0; j < yNum; j++)
		{
			for (int k = 0; k < zNum; k++)
			{
				Point center = Point(box.xMin + ((i + 0.5) * size), box.yMin + ((j + 0.5) * size), box.zMin + ((k + 0.5) * size));
				Zonelist.push_back(UnitZone(center, i, j, k));
			}
		}
	}
}