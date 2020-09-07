#ifndef __SOUND_H__
#define __SOUND_H__

#include "Game.h"
#include "DSUtil.h"
#include <unordered_map>

enum gSound
{
	soundWhip = 1,
	soundHit = 2,
	soundCollectItem = 3,
	soundCollectWeapon = 4,
	soundStopTimer = 5,
	soundDagger = 6,
	soundDisplayMoney = 7,
	soundHurting = 8,
	soundOpenDoor = 9,
	soundBrokenBrick = 10,
	soundHolyWater = 11,
	soundSplashWater = 12,
	soundFalingDownWater = 13,
	soundGetScoreTimer = 14,
	soundGetScoreHeart = 15,
	soundAxe = 16,
	soundStopWatch = 17,
	soundInvisibilityPotion_Begin = 18,
	soundInvisibilityPotion_End = 19,
	soundHolyCross = 20,
	soundBoomerang = 21,

	musicState1 = 51,
	musicLifeLost = 52,
	musicPhantomBat = 53,
	musicStateClear = 54,
	musicStartPrologue = 55
};

class Sound
{
private:
	
};

#endif