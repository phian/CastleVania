#ifndef __HELICOPTER_H__
#define __HELICOPTER_H__

#include "GameObject.h"

#define HELICOPTER_SPEED_X 0.02f
#define HELICOPTER_SPEED_Y 0.08f

class Helicopter : public GameObject
{
public:
	Helicopter(float X, float Y);
	virtual ~Helicopter();

	void Update(DWORD dt, vector<LPGAMEOBJECT>* objectList = NULL);
	void Render(Camera* camera);
};

#endif