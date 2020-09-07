#ifndef __SCENE_INTRO_H__
#define __SCENE_INTRO_H__

#include "Scene.h"
#include "TextureManager.h"
#include "Sound.h"
#include "GSprite.h"
#include "Font.h"
#include "Simon.h"
#include "Board.h"
#include "Brick.h"
#include "Helicopter.h"
#include "IntroBat.h"
#include "SceneGame.h"

#define INTRO_STATUS_PROCESS_MENU 0 // Trạng thái khi đang ở phần press to start
#define INTRO_STATUS_PROCESS_GO_SCENE1 // Trạng thái khi Simon đang auto đi để qua scene 1
#define SIMON_INTRO_WALKING_SPEED 0.08f // Tốc độ của Simon khi tự đi

class SceneIntro : public Scene
{
private:
	GSprite* MainMenu;
	GSprite* IntroBat;
	
	// Các biến cho phần xử lý nhấn phím
	bool IsPressStart;
	DWORD TimeWaited;

	// Các biến cho phần xử lý nhấp nháy chữ khi ấn Start
	bool IsDrawTextPressStart;
	DWORD TimeWaitedToChangeDisplayStartText;

	int ProcessStatus; // Trạng thái xử lý
};

#endif