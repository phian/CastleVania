#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "define.h"

class Camera
{
protected:
	// Toạ độ của Camera
	float _xCam;
	float _yCam;

	// Các biến lưu trữ lại toạ độ trc đói của Simon để khi dead thì restart từ chỗ này
	float _xCamBackup;
	float _yCamBackup;
	float _boundaryLeftBackup;
	float _boundaryRightBackup;

	// Kích thước hiển thị của Camera
	int _width, _height;
	float _boundaryLeft; // Biên giới hạn bên trái
	float _boundaryRight; // Biên giới hạn bên phải, không bao gồm đoạn Simon ko đi dc ở cuối - SCREEN_WIDTH

	float vx; // Speed của Camera
	DWORD dt; // Cập nhật time trong Update

	bool IsAutoGoX; // Biến check Simon có đang trong chế độ tự đi hay không
	float AutoGoX_Distance; // Khoảng cách Simon tự đi
	float AutoGoX_Backup_X; // Vị trí Camera trc khi vào chế độ tự đi

	bool IsFollowingSimon; // Biến check xem Camera có đăng follow Simon ko

public:
	Camera(int width, int height);
	~Camera();

	void Update(DWORD dt);

	D3DXVECTOR2 Transform(float, float); // Hàm để di chuyển Camera

	void SetCameraPosition(float x, float y);

	float GetXCam();
	float GetYCam();
	int GetWidth();
	int GetHeight();

	bool CheckIsObjectInCamera(float x, float y, int width, int height);

	bool GetIsFollowingSimon();
	void SetIsFollowingSimon(bool IsFollowing);

	void SetAutoGoX(float Distance, float Speed); // Hàm để set các thông số khi Simon tự đi
	void StopAutoGoX(); // Dừng chế độ tự đi
	bool GetIsAutoGoX();

	void SetCameraBoundary(float left, float right); // Set các biên giới hạn Camera
	float GetBoundaryLeft(); // Lấy các biên giới hạn của Camera
	float GetBoundaryRight();

	void SetPositionBackUp(float X, float Y); // Hàm để set vị trí theo vị trí đã backup trc đó
	void RestorePosition(); // Trả về vị trí cũ

	void SetBoundaryBackUp(float left, float right); // Set 2 biên theo giá trị đã lưu lại trc đó
	void RestoreBoundary();
};

#endif