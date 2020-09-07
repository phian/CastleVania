#include "Weapon.h"

Weapon::Weapon()
{
	_isFinishedAttack = 1;
}

Weapon::~Weapon() {}

int Weapon::GetObjectDirection()
{
	return _direction;
}

void Weapon::SetDirection(int weaponDirection)
{
	_direction = weaponDirection;
}

void Weapon::WeaponAttack(float X, float Y, int attackDirection)
{
	x = X;
	y = Y;
	_direction = attackDirection;
	_isFinishedAttack = false;

	lastAttackTime = GetTickCount(); // Lưu lại thời điểm vừa tấn công để tránh việc object tấn công liên tục, có health > 1
}

void Weapon::Render(Camera* camera)
{
	if (_isFinishedAttack)
		return;

	D3DXVECTOR2 position = camera->Transform(x, y);
	if (_direction == -1)
		objectSprite->Draw(position.x, position.y);
	else
		objectSprite->DrawFlipX(position.x, position.y);

	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
}

void Weapon::UpdatePositionFitSimon() {}

bool Weapon::IsCollision(GameObject* object)
{
	if (_isFinishedAttack)
		return false;

	// dt, dx, dy đã update
	
}

bool Weapon::GetFinish()
{
	return _isFinishedAttack;
}

void Weapon::SetFinish(bool isFinished)
{
	_isFinishedAttack = isFinished;
}

DWORD Weapon::GetLastAttackTime()
{
	return lastAttackTime;
}