#include "SceneManager.h"

SceneManager* SceneManager::__Instance = NULL;

SceneManager* SceneManager::GetIntance()
{
	if (__Instance == NULL)
		__Instance = new SceneManager();
	return __Instance;
}

SceneManager::SceneManager() {}
SceneManager::~SceneManager() {}

void SceneManager::SetScene(Scene* scene)
{
	Scene* sceneTemp = _scene; // trỏ scene cũ đến một nơi khác
	_scene = scene; // Cập nhật scene nới
	SAFE_DELETE(sceneTemp); // Xoá scene cũ
}

void SceneManager::KeyState(BYTE* state)
{
	_scene->KeyState(state);
}

void SceneManager::OnKeyDown(int KeyCode)
{
	_scene->OnKeyDown(KeyCode);
}

void SceneManager::OnKeyUp(int KeyCode)
{
	_scene->OnKeyUp(KeyCode);
}

void SceneManager::LoadResources()
{
	_scene->LoadResources();
}

void SceneManager::Update(DWORD dt)
{
	_scene->Update(dt);
}

void SceneManager::Render()
{
	_scene->Render();
}

Scene* SceneManager::GetScene()
{
	return _scene;
}