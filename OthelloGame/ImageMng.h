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
		return *s_Instance;
	}
	const VEC_INT ImgGetID(std::string fileName);
	const VEC_INT ImgGetID(std::string fileName, Vector2 divCnt, Vector2 divSize, Vector2 chipOffset);
private:
	struct ImageMngDeleter
	{
		void operator()(ImageMng * imageMng) const
		{
			delete imageMng;
		}
	};
	ImageMng();
	~ImageMng();
	static std::unique_ptr<ImageMng, ImageMngDeleter> s_Instance;
	std::map<std::string, VEC_INT> imgMap;		// �摜ID�̃n���h���Ɖ摜�̕�������ۑ�����ϐ�
};

