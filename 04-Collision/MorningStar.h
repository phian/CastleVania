#ifndef __MORNINGSTAR_H__
#define __MORNINGSTAR_H__

#define MORNING_START_ANI_WAIT_TIME	120 // Thời gian cho một frame của morning star

#define MORNING_ANI_LEVEL0_START 0 // animation level 1 của morning star
#define MORNING_ANI_LEVEL0_END	 3

#define MORNING_ANI_LEVEL1_START 4 // animation level 2 của morning star
#define MORNING_ANI_LEVEL1_END	 7

#define MORNING_STAR_ANI_LEVEL2_START 8
#define MORNING_STAR_ANI_LEVEL2_END	  11


#include "Weapon.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "Sound.h"

class MorningStar : public Weapon
{
protected:
	int level; // Level của morning star (có dc nâng cấp hay chưa)

public:
	MorningStar();
	~MorningStar();

	void Update(DWORD dt, vector<LPGAMEOBJECT>* objectList = NULL);
	void Render(Camera* camera);

	void WeaponAttack(float X, float Y, int direction);

	void UpdatePositionFitSimon();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void RenderIcon(float X, float Y); // Vẽ icon của weapon khi rơi ra

	void UpgradeMorningStarLevel();

	int GetMorningStarLevel();
	bool IsCollision(GameObject* object);
};

#endif