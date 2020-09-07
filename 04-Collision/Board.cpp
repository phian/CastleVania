#include "Board.h"

string Board::FillNumber(string s, UINT MaxNumber)
{
	while (s.size() < MaxNumber)
		s = "0" + s; 
	return s;
}

Board::Board(float X, float  Y)
{
	_texture = TextureManager::GetInstance()->GetTexture(oType::BOARD);
	_sprite = new GSprite(_texture, 0);

	_spriteIconDoubleShot = new GSprite(TextureManager::GetInstance()->GetTexture(oType::ITEMDOUBLESHOT), 0);

	x = X;
	y = Y;

	_boardHealth = new BoardHealth(x + 110, y + 30);
}

void Board::Render(Simon* simon, int stage, int RemainingTime, GameObject* boss)
{
	_sprite->Draw(x, y);

	
}

Board::~Board()
{
	SAFE_DELETE(_sprite);
}

void Board::SetTexture(GTexture* texture)
{
	_texture = texture;
	_sprite->texture = texture;
}
