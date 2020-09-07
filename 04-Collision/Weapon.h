#ifndef __WEAPON_H__
#define	__WEAPON_H__

#include "define.h"
#include "Camera.h"
#include "GTexture.h"
#include "GSprite.h"
#include "GameObject.h"

class Weapon : public GameObject
{
protected:
	bool _isFinishedAttack; // Check xem vũ khí đã hoàn thành animation attack hay chưa
	DWORD lastAttackTime; // Thời điểm tấn công trc đó để delay attack, tránh việc attack liên tục

public:
	Weapon();
	~Weapon();

	int GetObjectDirection(); // Lấy hướng của object để render weapon theo hướng tương ứng
	void SetDirection(int direction);

	virtual void WeaponAttack(float X, float Y, int attackDirection); // Hàm xử lý phần tấn công cho các vũ khí

	virtual void Render(Camera* camera);
	virtual void UpdatePositionFitSimon(); // Căn chỉnh tạo độ của vũ khí theo vị trí của Simon
	virtual bool IsCollision(GameObject* object); // Check xem vũ khí có va chạm với object trong game hay chưa
	virtual void RenderIcon(float X, float Y) = 0; // Hàm để vẽ icon của vũ khí khi nó rơi ra
	bool GetFinish(); // Check xem vũ khí đã hoàn thành xử dụng hay chưa
	void SetFinish(bool isFinish);

	DWORD GetLastAttackTime(); // Lấy thời điểm tấn công trc đó để tính toán và cho phép tấn công lại
};

#endif