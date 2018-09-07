#pragma once

#include <vector>
#include <map>
#include <mutex>
#include "Vector2.h"

#define LpImageMng (ImageMng::GetInstance())

typedef std::vector<int> VEC_INT;

class ImageMng
{
public:
	static ImageMng & GetInstance()
	{
		std::call_once(initFlag, Create);
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
	static ImageMng		  *s_Instance;
	static std::once_flag initFlag;
	std::map<std::string, VEC_INT> imgMap;		// ‰æ‘œID‚Ìƒnƒ“ƒhƒ‹‚Æ‰æ‘œ‚Ì•ªŠ„”‚ğ•Û‘¶‚·‚é•Ï”
};

