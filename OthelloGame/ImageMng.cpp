#include <DxLib.h>
#include "ImageMng.h"

/* 静的なメンバ変数の定義 */
ImageMng	  *ImageMng::s_Instance;
std::once_flag ImageMng::initFlag;

ImageMng::ImageMng()
{
}

ImageMng::~ImageMng()
{
}

void ImageMng::Create()
{
	s_Instance = new ImageMng();
}

void ImageMng::Destroy()
{
	if (s_Instance)
	{
		delete s_Instance;
		s_Instance = nullptr;
	}
}

const VEC_INT ImageMng::ImgGetID(std::string fileName)
{
	/* 画像IDのハンドルが見つからなかった時、画像読み込みを行う(分割なし) */
	if (imgMap.find(fileName) == imgMap.end())
	{
		imgMap[fileName].resize(1);
		imgMap[fileName][0] = DxLib::LoadGraph(fileName.c_str(), true);
	}

	return imgMap[fileName];
}

const VEC_INT ImageMng::ImgGetID(std::string fileName, Vector2 divCnt, Vector2 divSize, Vector2 chipOffset)
{
	/* 画像IDのハンドルが見つからなかった時、画像読み込みを行う(分割あり) */
	if (imgMap.find(fileName) == imgMap.end())
	{
		imgMap[fileName].resize(divCnt.x * divCnt.y);
		DxLib::LoadDivGraph(fileName.c_str(), (divCnt.x * divCnt.y), divCnt.x, divCnt.y, divSize.x, divSize.y, &imgMap[fileName][0], true);
	}
	return imgMap[fileName];
}


