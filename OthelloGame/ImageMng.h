#pragma once

#include <vector>
#include <map>
#include "Vector2.h"

#define LpImageMng ImageMng::GetInstance()

typedef std::vector<int> VEC_INT;

class ImageMng
{
public:
	static ImageMng & GetInstance()
	{
		Create();
		return *s_Instance;
	}
	static void Create();
	static void Destroy();
	const VEC_INT ImgGetID(std::string fileName);
	const VEC_INT ImgGetID(std::string fileName, Vector2 divCnt, Vector2 divSize, Vector2 chipOffset);
	~ImageMng();
private:
	ImageMng();
	static ImageMng *s_Instance;
	std::map<std::string, VEC_INT> imgMap;
};

