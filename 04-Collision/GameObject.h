#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include "define.h"

#include "Sprites.h"
#include "GTexture.h"
#include "GSprite.h"
#include "Camera.h"
#include "TextureManager.h"


using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box

class GameObject; 
typedef GameObject * LPGAMEOBJECT;

struct CollisionEvent;
typedef CollisionEvent * LPCOLLISIONEVENT;
struct CollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny; // Thời điểm va chạm  và hướng va chạm
	CollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};



class GameObject
{
public:
	// Toạ độ của object
	float x; 
	float y;

	// Quãng đường mà object đi và nhảy
	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	// Vận tốc khi đi và nhảy của Object
	float vx;
	float vy;

	int objectHealth;
	int id;

	int nx;	 

	int _direction; // hướng trái = -1, hướng phải = 1;
	oType ObjectType; // Loại Object

	int state;

	DWORD dt; 

	// Texture và Sprite cho animation
	GTexture* gameTexture;
	GSprite* objectSprite;

	vector<LPANIMATION> animations;

public: 
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }

	float GetX();
	float GetY();
	float GetVx();
	float GetVy();
	void SetX(float X);
	void SetY(float Y);
	void SetVx(float VX);
	void SetVy(float VY);
	int GetFrameWidth();
	int GetFrameHeight();
	oType GetType();

	void SetDirection(int direction);
	int GetDirection();

	int GetState() { return this->state; }

	void RenderBoundingBox(Camera* camera);

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents, 
		vector<LPCOLLISIONEVENT> &coEventsResult, 
		float &min_tx, 
		float &min_ty, 
		float &nx, 
		float &ny);

	// Hàm để check xem 2 object có va chạm với nhau ko (Kiểm tra AABB bằng Swept AABB)
	bool IsObjectCollisionWithObject(GameObject* object);
	bool CheckAABB(GameObject* object); // Hàm để check va chạm

	void SetTexture(GTexture* text);
	GSprite* GetSprite();

	void AddAnimation(int aniId);

	GameObject();

	~GameObject();
};

