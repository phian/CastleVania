#include"TextureManager.h"

TextureManager* TextureManager::__Instance = NULL;

TextureManager* TextureManager::GetInstance()
{
	if (__Instance == NULL)
		__Instance = new TextureManager();
	return __Instance;
}

void TextureManager::AddTexture(oType objectType, GTexture* texture)
{
	_ArrTextures[objectType] = texture;
}

GTexture* TextureManager::GetTexture(oType type)
{
	return _ArrTextures[type];
}

void TextureManager::LoadResource()
{
	// Map
	AddTexture(oType::MAP1, new GTexture("Resources/map/tileset_map1.png", 8, 4, 32));

	// Game object
	AddTexture(oType::TEX_BRICK_MODEL_1, new GTexture("Resources/ground/2.png")); // Gạch cho phần trc khi vào lâu đài
	AddTexture(oType::RENDERBBOX, new GTexture("Resources/bbox.png"));
	AddTexture(oType::TORCH, new GTexture("Resources/ground/0.png", 2, 1, 2)); // Ngọn đuốc
	AddTexture(oType::TEX_BRICK_TRANSPARENT, new GTexture("Resources/brick_transparent.png")); // Bouding box cho gạch

	// Game items
	AddTexture(oType::DAGGER, new GTexture("Resources/item/4.png")); // Dao
	AddTexture(oType::LARGEHEART, new GTexture("Resources/item/1.png")); // Trái tim lớn rơi ra khi đánh đuốc
	AddTexture(oType::UPGRADEMORNINGSTAR, new GTexture("Resources/item/3.png")); // Item để upgrade roi

	// Weapon
	AddTexture(oType::DAGGER, new GTexture("Resources/weapon/1.png")); // Dao
	AddTexture(oType::MORNINGSTAR, new GTexture("Resources/weapon/morningstar.png", 4, 3, 12)); // Roi

	// Player
	AddTexture(oType::SIMON, new GTexture("Resources/simon.png", 8, 3, 24)); // Simon
	AddTexture(oType::SIMON_TRANS, new GTexture("Resources/simon_trans.png", 8, 3, 24)); // Hiệu ứng khi Simon nhặt đồ

	// Effect
	AddTexture(oType::HIT, new GTexture("Resources/other/0.png"));
	AddTexture(oType::FIRE, new GTexture("Resources/other/1.png"));
}

TextureManager::TextureManager()
{
	LoadResource();
}


TextureManager::~TextureManager()
{
	SAFE_DELETE(__Instance);
}
