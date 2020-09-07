#include "Helicopter.h"

Helicopter::Helicopter(float X, float Y)
{
	ObjectType = oType::HELICOPTER;
	gameTexture = TextureManager::GetInstance()->GetTexture(ObjectType);
	objectSprite = new GSprite(gameTexture, 70);

	x = X;
	y = Y;
	_direction = -1;
	objectHealth = 1;

	vy = -HELICOPTER_SPEED_Y;
	vx = HELICOPTER_SPEED_X * _direction;
}

Helicopter::~Helicopter() {}

void Helicopter::Update(DWORD dt, vector<LPGAMEOBJECT>* objectList)
{
	GameObject::Update(dt); // Update dt, dx, dy

	y += dy;
	x += dx;
}

void Helicopter::Render(Camera* camera)
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
