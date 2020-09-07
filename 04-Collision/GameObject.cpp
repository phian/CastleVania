#include <d3dx9.h>
#include <algorithm>


#include "debug.h"
#include "Textures.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"

GameObject::GameObject()
{
	x = y = 0;
	vx = vy = 0;
	nx = 1;	
	_direction = 1; // Ban đầu mặc định là đi qua phải
}

void GameObject::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	this->dt = dt;
	dx = vx*dt;
	dy = vy*dt;
}

void GameObject::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + gameTexture->GetFrameWidth();
	bottom = top + gameTexture->GetFrameHeight();
}

void GameObject::SetDirection(int direction)
{
	_direction = direction;
}

int GameObject::GetDirection()
{
	return _direction;
}

void GameObject::SetPosition(float X, float Y)
{
	x = Y;
	y = Y;
}

void GameObject::GetPosition(float& X, float& Y)
{
	X = this->x;
	Y = this->y;
}

void GameObject::SetSpeed(float VX, float VY)
{
	this->vx = VX;
	this->vy = VY;
}

float GameObject::GetX()
{
	return x;
}

float GameObject::GetY()
{
	return y;
}

float GameObject::GetVx()
{
	return vx;
}

float GameObject::GetVy()
{
	return vy;
}

// Toạ độ của object
void GameObject::SetX(float X)
{
	x = X;
}

// Toạ độ của object
void GameObject::SetY(float Y)
{
	y = Y;
}

void GameObject::SetVx(float VX)
{
	vx = VX;
}

void GameObject::SetVy(float VY)
{
	vy = VY;
}

int GameObject::GetFrameHeight()
{
	return gameTexture->GetFrameHeight();
}

int GameObject::GetFrameWidth()
{
	return gameTexture->GetFrameWidth();
}

oType GameObject::GetType()
{
	return ObjectType;
}

/*
	Extension of original SweptAABB to deal with two moving objects
*/
LPCOLLISIONEVENT GameObject::SweptAABBEx(LPGAMEOBJECT coO)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	coO->GetBoundingBox(sl, st, sr, sb);

	// deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;
	coO->GetSpeed(svx, svy);

	float sdx = svx*dt;
	float sdy = svy*dt;

	float dx = this->dx - sdx;
	float dy = this->dy - sdy;

	GetBoundingBox(ml, mt, mr, mb);

	Game::SweptAABB(
		ml, mt, mr, mb,
		dx, dy,
		sl, st, sr, sb,
		t, nx, ny
	);

	CollisionEvent * e = new CollisionEvent(t, nx, ny, coO);
	return e;
}

/*
	Calculate potential collisions with the list of colliable objects 
	
	coObjects: the list of colliable objects
	coEvents: list of potential collisions
*/
void GameObject::CalcPotentialCollisions(
	vector<LPGAMEOBJECT> *coObjects, 
	vector<LPCOLLISIONEVENT> &coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else
			delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CollisionEvent::compare);
}

void GameObject::FilterCollision(
	vector<LPCOLLISIONEVENT> &coEvents,
	vector<LPCOLLISIONEVENT> &coEventsResult,
	float &min_tx, float &min_ty, 
	float &nx, float &ny)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; 
			nx = c->nx; 
			min_ix = i;
		}

		if (c->t < min_ty  && c->ny != 0) {
			min_ty = c->t; 
			ny = c->ny;
			min_iy = i;
		}
	}

	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}

// Hàm để kiểm tra va chạm bằng AABB và Sweept AABB
bool GameObject::IsObjectCollisionWithObject(GameObject* object)
{
	// Kiểm tra bằng Sweept AABB trước tiên
	if (CheckAABB(object))
		return true;

	LPCOLLISIONEVENT collisionEvent = SweptAABBEx(object); // Kiểm tra xem 2 object có đang va chạm bằng Swept AABB
	bool result = collisionEvent->t > 0 && collisionEvent->t <= 1.0f; // Điều kiện để các object va chạm
	SAFE_DELETE(collisionEvent);
	return result;
}

bool GameObject::CheckAABB(GameObject* object)
{
	float left, top, right, bottom;
	float left1, top1, right1, bottom1;

	this->GetBoundingBox(left, top, right, bottom);
	object->GetBoundingBox(left1, top1, right1, bottom1);

	if (Game::GetInstance()->CheckAABB(left, top, right, bottom, left1, top1, right1, bottom1))
		return true;
	return false;
}

void GameObject::SetTexture(GTexture* texture)
{
	this->gameTexture = texture;
	objectSprite->texture = texture;
}

GSprite* GameObject::GetSprite()
{
	return objectSprite;
}

void GameObject::RenderBoundingBox(Camera* camera)
{
	float l, t, r, b;
	GetBoundingBox(l, t, r, b);
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = (LONG)r - (LONG)l;
	rect.bottom = (LONG)b - (LONG)t;

	D3DXVECTOR2 position = camera->Transform(l, t);

	Game::GetInstance()->Draw(x, y, TextureManager::GetInstance()->GetTexture(oType::RENDERBBOX)->Texture, rect.left, rect.top, rect.right, rect.bottom, 90);
}

void GameObject::AddAnimation(int aniId)
{
	LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);
	animations.push_back(ani);
}


GameObject::~GameObject()
{
	// Ko thể xoá texture vì Texture là dùng chung và dc quản lý bởi TextureManager
	SAFE_DELETE(objectSprite);
}