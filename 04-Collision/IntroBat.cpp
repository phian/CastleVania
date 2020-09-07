#include "IntroBat.h"

IntroBat::IntroBat(float X, float Y, float VX, float VY)
{
	ObjectType = oType::INTRO_BAT;
	gameTexture = TextureManager::GetInstance()->GetTexture(ObjectType);
	objectSprite = new GSprite(gameTexture, 70);

	x = X;
	y = Y;
	_direction = -1;
	objectHealth = 1;

	vx = VX;
	vy = VY;
}

IntroBat::~IntroBat() {}

void IntroBat::Update(DWORD dt, vector<LPGAMEOBJECT>* objectList)
{
	GameObject::Update(dt); // Update dt, dx, dy
	x += dx;
	y += dy;

	objectSprite->Update(dt);
}

void IntroBat::Render(Camera* camera)
{
	if (objectHealth <= 0)
		return;

	D3DXVECTOR2 position = camera->Transform(x, y);
	if (_direction == -1)
		objectSprite->Draw(position.x, position.y);
	else
		objectSprite->DrawFlipX(position.x, position.y);

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
}