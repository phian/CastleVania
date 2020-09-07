#include "Sprites.h"
#include "Game.h"
#include "debug.h"
#include<vector>
#include "Textures.h"
#include"define.h"

CSprite::CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
}

CSprites * CSprites::__instance = NULL;

CSprites *CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

void CSprite::Draw(float x, float y, int alpha)
{
	Game * game = Game::GetInstance();
	game->Draw(x, y, texture, left, top, right, bottom, alpha);
}

void CSprites::AddRersources()
{
	CTextures* textures = CTextures::GetInstance();
	LPDIRECT3DTEXTURE9 texMario = textures->Get(ID_TEX_MARIO);
	// Mario
	// big
	Add(10001, 246, 154, 260, 181, texMario);		// idle right

	Add(10002, 275, 154, 290, 181, texMario);		// walk
	Add(10003, 304, 154, 321, 181, texMario);

	Add(10011, 186, 154, 200, 181, texMario);		// idle left
	Add(10012, 155, 154, 170, 181, texMario);		// walk
	Add(10013, 125, 154, 140, 181, texMario);

	Add(10099, 215, 120, 231, 135, texMario);		// die 

	// small
	Add(10021, 247, 0, 259, 15, texMario);			// idle small right
	Add(10022, 275, 0, 291, 15, texMario);			// walk 
	Add(10023, 306, 0, 320, 15, texMario);			// 

	Add(10031, 187, 0, 198, 15, texMario);			// idle small left

	Add(10032, 155, 0, 170, 15, texMario);			// walk
	Add(10033, 125, 0, 139, 15, texMario);			// 

	LPDIRECT3DTEXTURE9 texMisc = textures->Get(ID_TEX_MISC);
	// Gạch
	Add(20001, 0, 0, 32, 32, texMisc);

	LPDIRECT3DTEXTURE9 texEnemy = textures->Get(ID_TEX_ENEMY);
	// Enemy
	Add(30001, 5, 14, 21, 29, texEnemy);
	Add(30002, 25, 14, 41, 29, texEnemy);

	Add(30003, 45, 21, 61, 29, texEnemy);
}

void CSprites::InitSprites()
{

}

void CSprites::Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new CSprite(id, left, top, right, bottom, tex);
	sprites[id] = s;
}

LPSPRITE CSprites::Get(int id)
{
	return sprites[id];
}


void CAnimation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t=this->defaultTime;

	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);
	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

void CAnimation::Render(float x, float y, int alpha)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1) 
	{
		currentFrame = 0; 
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
		}
		
	}

	frames[currentFrame]->GetSprite()->Draw(x, y, alpha);
}

CAnimations * CAnimations::__instance = NULL;

CAnimations * CAnimations::GetInstance()
{
	if (__instance == NULL) __instance = new CAnimations();
	return __instance;
}

void CAnimations::Add(int id, LPANIMATION ani)
{
	animations[id] = ani;
}

void CAnimations::AddResources() 
{
	LPANIMATION ani;

	ani = new CAnimation(100);	// idle big right
	ani->Add(10001);
	Add(400, ani);

	ani = new CAnimation(100);	// idle big left
	ani->Add(10011);
	Add(401, ani);

	ani = new CAnimation(100);	// idle small right
	ani->Add(10021);
	Add(402, ani);

	ani = new CAnimation(100);	// idle small left
	ani->Add(10031);
	Add(403, ani);

	ani = new CAnimation(100);	// walk right big
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	Add(500, ani);

	ani = new CAnimation(100);	// // walk left big
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	Add(501, ani);

	ani = new CAnimation(100);	// walk right small
	ani->Add(10021);
	ani->Add(10022);
	ani->Add(10023);
	Add(502, ani);

	ani = new CAnimation(100);	// walk left small
	ani->Add(10031);
	ani->Add(10032);
	ani->Add(10033);
	Add(503, ani);


	ani = new CAnimation(100);		// Mario die
	ani->Add(10099);
	Add(599, ani);



	ani = new CAnimation(100);		// brick
	ani->Add(20001);
	Add(601, ani);

	ani = new CAnimation(300);		// Goomba walk
	ani->Add(30001);
	ani->Add(30002);
	Add(701, ani);

	ani = new CAnimation(1000);		// Goomba dead
	ani->Add(30003);
	Add(702, ani);
}

LPANIMATION CAnimations::Get(int id)
{
	return animations[id];
}