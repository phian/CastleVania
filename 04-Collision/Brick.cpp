#include "Brick.h"

Brick::Brick(float X, float Y, int width, int height, int model)
{
	_model = model;
	switch (_model)
	{
	case BRICK_MODEL_1:
		gameTexture = TextureManager::GetInstance()->GetTexture(oType::TEX_BRICK_MODEL_1); // Gạch của màn 1
		break;
	case BRICK_MODEL_2:
		gameTexture = TextureManager::GetInstance()->GetTexture(oType::TEX_BRICK_MODEL_2); // Gạch của màn 2
		break;
	case BRICK_MODEL_3:
		gameTexture = TextureManager::GetInstance()->GetTexture(oType::TEX_BRICK_MODEL_3); // Gạch loại nhỏ 16px
		break;
	case BRICK_MODEL_TRANSPARENT:
		gameTexture = TextureManager::GetInstance()->GetTexture(oType::TEX_BRICK_TRANSPARENT); // Gạch trong suốt
		break;
	case BRICK_MODEL_3_3_32:
		gameTexture = TextureManager::GetInstance()->GetTexture(oType::TEX_BRICK_MODEL_3_3_32); // Gạch loại 3 ô nhỏ - 32px
		break;
	case BRICK_MODEL_3_4_32:
		gameTexture = TextureManager::GetInstance()->GetTexture(oType::TEX_BRICK_MODEL_3_4_32); // Gạch loại đủ 4 ô nhỏ - 32px
		break;
	default:
		DebugOut(L"[BRICK] Không thể get texture! Không nhận được Model của gạch!");
		break;
	}

	ObjectType = oType::BRICK;
	objectSprite = new GSprite(gameTexture, 1000);
	x = X;
	y = Y;
	_width = width;
	_height = height;
}

void Brick::Render(Camera* camera)
{
	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);

	/*animations[0]->Render(x, y);
	RenderBoundingBox();*/

	if (_model == BRICK_MODEL_TRANSPARENT)
		return;

	D3DXVECTOR2 position = camera->Transform(x, y);

	// Lấy kích thước gạch chia cho kích thước của map rồi nhân cho kích thước viên gạch để render
	for (int i = 0; i < (int)ceil(_width / gameTexture->GetFrameWidth()); i++)
		for (int j = 0; j < (int)ceil(_height / gameTexture->GetFrameHeight()); j++)
			objectSprite->Draw(position.x + i * gameTexture->GetFrameWidth(), position.y + j * gameTexture->GetFrameHeight());
}

void Brick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + (float)ceil(_width / gameTexture->GetFrameWidth()) * gameTexture->GetFrameWidth();
	b = y + (float)ceil(_height / gameTexture->GetFrameHeight()) * gameTexture->GetFrameHeight();
}