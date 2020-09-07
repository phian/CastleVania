#include "MorningStar.h"

MorningStar::MorningStar()
{
	ObjectType = oType::MORNINGSTAR;
	gameTexture = TextureManager::GetInstance()->GetTexture(ObjectType);
	objectSprite = new GSprite(gameTexture, MORNING_START_ANI_WAIT_TIME);
	level = 0;
}

MorningStar::~MorningStar() {}

void MorningStar::Update(DWORD dt, vector<LPGAMEOBJECT>* object)
{
	GameObject::Update(dt);

	// Update để check collision
	_isFinishedAttack = (objectSprite->GetCurrentFrame() == 3 && level == 0) + (objectSprite->GetCurrentFrame() == 7 && level == 1) + (objectSprite->GetCurrentFrame() == 11 && level == 2);
	
	int StartFrame = MORNING_ANI_LEVEL0_START + 4 * level; // ánh xạ chỉ số frame bằng level thay vì dùng if else
	int EndFrame = MORNING_ANI_LEVEL0_END + 4 * level;

	if (StartFrame <= objectSprite->GetCurrentFrame() && objectSprite->GetCurrentFrame() < EndFrame)
		objectSprite->Update(dt);
	else
		objectSprite->SelectFrame(StartFrame);
}

void MorningStar::Render(Camera* camera)
{
	D3DXVECTOR2 position = camera->Transform(x, y);
	if (_direction == -1)
		objectSprite->Draw(position.x, position.y);
	else
		objectSprite->DrawFlipX(position.x, position.y);

	if (IS_DEBUG_RENDER_BBOX)
	{
		if (level == 0 && objectSprite->GetCurrentFrame() == MORNING_ANI_LEVEL0_START || objectSprite->GetCurrentFrame() == MORNING_ANI_LEVEL0_START + 1)
			return; // frame đầu và frame chuẩn bị đánh thì về BBOX

		if (level == 1 && objectSprite->GetCurrentFrame() == MORNING_ANI_LEVEL1_START || objectSprite->GetCurrentFrame() == MORNING_ANI_LEVEL1_START + 1)
			return;

		if (level == 2 && objectSprite->GetCurrentFrame() == MORNING_STAR_ANI_LEVEL2_START || objectSprite->GetCurrentFrame() == MORNING_STAR_ANI_LEVEL2_START + 1)
			return;

		RenderBoundingBox(camera);
	}
}

void MorningStar::WeaponAttack(float X, float Y, int direction)
{
	Weapon::WeaponAttack(X, Y, direction);

	UpdatePositionFitSimon();

	switch (level)
	{
	case 0:
		objectSprite->SelectFrame(MORNING_ANI_LEVEL0_START);
		objectSprite->ResetTime();
		break;
	case 1:
		objectSprite->SelectFrame(MORNING_ANI_LEVEL1_START);
		objectSprite->ResetTime();
		break;
	case 2:
		objectSprite->SelectFrame(MORNING_STAR_ANI_LEVEL2_START);
		objectSprite->ResetTime();
		break;
	}
}

void MorningStar::UpdatePositionFitSimon()
{
	if (_direction == 1)
	{
		this->x -= 75;
		this->y -= 2;
	}
	else
	{
		this->x -= 25;
		this->y -= 2;
	}
}

void MorningStar::RenderIcon(float X, float Y) {}

void MorningStar::UpgradeMorningStarLevel()
{
	if (level >= 2)
		return;

	level++;
	if (_isFinishedAttack == false) // Nếu Simon đang attack thì phải update lại frame để sau khi Freezed xong thì sẽ chạy tiếp
		objectSprite->SelectFrame(objectSprite->GetCurrentFrame() + 4);
}

int	MorningStar::GetMorningStarLevel()
{
	return level;
}

bool MorningStar::IsCollision(GameObject* object)
{
	if (level == 0 && objectSprite->GetCurrentFrame() == MORNING_ANI_LEVEL0_START || objectSprite->GetCurrentFrame() == MORNING_ANI_LEVEL0_START + 1)
		return false;

	if (level == 1 && objectSprite->GetCurrentFrame() == MORNING_ANI_LEVEL1_START || objectSprite->GetCurrentFrame() == MORNING_ANI_LEVEL1_START + 1)
		return false;

	if (level == 2 && objectSprite->GetCurrentFrame() == MORNING_STAR_ANI_LEVEL2_START || objectSprite->GetCurrentFrame() == MORNING_STAR_ANI_LEVEL2_START + 1)
		return false;

	return Weapon::IsCollision(object);
}

void MorningStar::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	switch (level)
	{
	case 0:
		if (_direction == -1)
		{

		}
	}
}

