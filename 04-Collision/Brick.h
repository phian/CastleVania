#pragma once
#include "GameObject.h"
#include "TextureManager.h"
#include "Camera.h"

#define BRICK_BBOX_WIDTH  32
#define BRICK_BBOX_HEIGHT 32

#define BRICK_MODEL_1			1 // Gạch của màn 1, 32 px
#define BRICK_MODEL_2			2 // Gạch của màn 2, 32 px
#define BRICK_MODEL_3			3 // Gạch loại 3, ổ nhỏ 16px
#define BRICK_MODEL_TRANSPARENT 4 // Gạch trong suốt
#define BRICK_MODEL_3_3_32		5 // Gạch loại 3, 3 ô nhỏ - 32px
#define BRICK_MODEL_3_4_32		6 // Gạch loại 3, 4 ô nhỏ - 32px


class Brick : public GameObject
{
protected:
	int _width;
	int _height;
	int _model;

public:
	Brick(float X, float Y, int width, int height, int model);
	~Brick();
	virtual void Render(Camera* camera);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	int GetBrickModel();
};