#include "Camera.h"

Camera::Camera(int width, int height)
{
	_width = width;
	_height = height;
	IsFollowingSimon = true;
	IsAutoGoX = false;

	// Biên mặc định ban đầu là kích thước của map
	_boundaryLeft = 0;
	_boundaryRight = 0;
	_xCamBackup = _yCamBackup = 0;
	SetBoundaryBackUp(_boundaryLeft, _boundaryRight); // Lưu trữ toạ độ mặc định ban đầu
	vx = 0;
}

Camera::~Camera() {}

void Camera::Update(DWORD dt)
{
	this->dt = dt;

	// Nếu Simon đang tự đi
	if (IsAutoGoX)
	{
		// Cập nhật đoạn đường và vị trí của Cam
		float dx = vx * dt;
		_xCam += dx;
		
		if (abs(_xCam - AutoGoX_Backup_X) >= AutoGoX_Distance)
		{
			_xCam -= (abs(_xCam - AutoGoX_Backup_X) - AutoGoX_Distance);
			IsAutoGoX = false;
		}
	}

	// Nếu đi tới 2 biên
	if (_xCam < _boundaryLeft)
		_xCam = _boundaryLeft;

	if (_xCam > _boundaryRight)
		_xCam = _boundaryRight;
}

D3DXVECTOR2 Camera::Transform(float xWorld, float yWorld)
{
	return D3DXVECTOR2(xWorld - _xCam, yWorld - _yCam);
}

void Camera::SetCameraPosition(float x, float y)
{
	_xCam = x;
	_yCam = y;
}

float Camera::GetXCam()
{
	return _xCam;
}

float Camera::GetYCam()
{
	return _yCam;
}

int Camera::GetWidth()
{
	return _width;
}

int Camera::GetHeight()
{
	return _height;
}

bool Camera::CheckIsObjectInCamera(float x, float y, int width, int height) // Toạ độ và kích thước của object
{
	// Nếu object nằm ngài theo chiều ngang
	if (x + width < _xCam || _xCam + _width < x)
		return false;
	// Nếu object nằm ngoài theo chiều dọc
	if (y + height < _yCam || _yCam + _height < y)
		return false;
	return true;
}

bool Camera::GetIsFollowingSimon()
{
	return IsFollowingSimon;
}

void Camera::SetIsFollowingSimon(bool IsFollowingSimon)
{
	this->IsFollowingSimon = IsFollowingSimon;
}

void Camera::SetAutoGoX(float Distance, float Speed)
{
	if (IsAutoGoX)
		return;
	vx = Speed;
	AutoGoX_Backup_X = _xCam;
	AutoGoX_Distance = Distance;
	IsAutoGoX = true;
	IsFollowingSimon = false;
}

void Camera::StopAutoGoX()
{
	IsAutoGoX = false;
}

bool Camera::GetIsAutoGoX()
{
	return IsAutoGoX;
}

void Camera::SetCameraBoundary(float boundaryLeft, float boundaryRight)
{
	_boundaryLeft = boundaryLeft;
	_boundaryRight = boundaryRight;
}

float Camera::GetBoundaryLeft()
{
	return _boundaryLeft;
}

float Camera::GetBoundaryRight()
{
	return _boundaryRight;
}

// Back up lại các giá trị vị trí của Camera
void Camera::SetPositionBackUp(float X, float Y)
{
	_xCamBackup = X;
	_yCamBackup = Y;
}

// Back up lại các giá trị biên
void Camera::SetBoundaryBackUp(float boundaryBackUpLeft, float boundaryBackUpRight)
{
	_boundaryLeftBackup = boundaryBackUpLeft;
	_boundaryRightBackup = boundaryBackUpRight;
}

// Reset lại các giá trị theo giá trị dc backup trc đó
void Camera::RestoreBoundary()
{
	_xCam = _xCamBackup;
	_yCam = _yCamBackup;

	_boundaryLeft = _boundaryLeftBackup;
	_boundaryRight = _boundaryRightBackup;
}

