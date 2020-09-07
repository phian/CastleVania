#ifndef __TEXTUREMANAGER_H__
#define __TEXTUREMANAGER_H__

#include <unordered_map>
#include "define.h"
#include "GTexture.h"
class TextureManager
{
	unordered_map<oType, GTexture*> _ArrTextures;

public:
	static TextureManager* __Instance;
	static TextureManager* GetInstance();

	void AddTexture(oType type, GTexture* texture);
	GTexture* GetTexture(oType type);

	void LoadResource();

	TextureManager();
	~TextureManager();
};

#endif