#ifndef __SIMON_H__
#define __SIMON_H__

#include "GameObject.h"
#include "Sound.h"
#include "MorningStar.h"
#include "Sound.h"
#include "Weapon.h"

// Simon animation
#define SIMON_ANI_IDLE			0
#define SIMON_ANI_HIDE_FACE		9
#define SIMON_ANI_WALKING_BEGIN 1
#define SIMON_ANI_WALKING		3

// Simon state
#define SIMON_STATE_IDLE	0
#define SIMON_STATE_WALKING 1

#define SIMON_DEFAULT_POSITION 50f, 300f
#define SIMON_BBOX_WIDTH  60
#define SIMON_BBOX_HEIGHT 63

#define SIMON_GRAVITY	0.005f
#define SIMON_WALKING_SPEED 0.12f

#define SIMON_DEFAULT_HEALTH		16
#define SIMON_DEFAULT_HEART_COLLECT 5
#define SIMON_DEFAULT_SCORE			0
#define SIMON_DEFAULT_LIVES			3

#define MAX_FREEZE_TIME 500

class Simon : public GameObject
{
private:
	GSprite* _Simon_Death_Sprite;
	int SimonLives; // Số mạng còn lại của Simon
	int SimonScore; // Điểm của Simon

	bool isFreezed; // Biến check xem Simon có đang trong trạng thái đứng yên đổi màu liên tục hay không
	DWORD freezeTime; // Thời gian đã đóng băng

	D3DXVECTOR2 SimonBackUpPosition; // Lưu trữ lại toạ độ trc đó của Simon

	bool isWalking_BackUp;
	bool isJumping_BackUp;
	bool isSitting_BackUp;
	bool isAttacking_BackUp;
	bool isOnStair_BackUp;
	int isProcessingOnStair_BackUp;
	int directionStair_BackUp;
	int directionY_BackUp;
	int directionAfterGo;

	float AutoGoXDistance; // Khoảng cách mà Simon tự đi
	float AutoGoXSpeed; // Tốc độ khi tự đi của Simon
	float AutoGoX_DirectionGo; // Hướng tự đi của Simon
	float AutoGoX_BackUp; // Lưu vị trí trc khi tự động đi

	bool isAutoGoX; // Biến check xem Simon có đang trong chế độ tự đi hay ko
	bool isDeath; // Biến check xem Simon đã chết chưa

	oType collectedWeaponType; // Loại vũ khí mà Simon đã nhặt dc

	Camera* camera;
	Sound* sound;
	bool isDoubleShot;

public:
	// Các biến check trạng thái của Simon
	bool isAttacking;
	bool isHurting;
	bool isWalking;
	bool isJumping;
	bool isSitting;

	bool isOnStair;
	int isProcessingOnStair; // Biến để lưu trữ giai đoạn xử lý khi Simon đi lên cầu thang (có 2 giai đoạn)
	int stairDiretion; // Hướng của cầu thang đang đi (-1 là qua trái và 1 là ngược lại)
	int directionY; // Hướng đi theo trục y của Simon

	float stairPassedHeight; // Độ cao đã đi dc

	bool untouchable; // Set Simon có ở vào trạng thái không thể va chạm hay không
	DWORD untouchable_start; // Thời điểm trạng thái được kích hoạt

	bool isCollisionAxisYWithBrick; // Biến check xem Simon có đang va chạm với gạch theo chiều dọc hay không

	DWORD TimeWaitedAfterDeath; // Thời gian delay để quay lại chơi sau khi chết

	Simon(Camera* camera);
	~Simon();
};

#endif