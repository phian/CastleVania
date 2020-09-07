#include "DSUtil.h"

//-----------------------------------------------------------------------------
// File: DSUtil.cpp
//
// Desc: DirectSound framework classes for reading and writing wav files and
//       playing them in DirectSound buffers. Feel free to use this class 
//       as a starting point for adding extra functionality.
//
// Copyright (c) Microsoft Corp. All rights reserved.
//-----------------------------------------------------------------------------
#define STRICT
#include "DSUtil.h"

#if MEMORY_LEAK_DEBUG == 1
#include <vld.h>
#endif

//-----------------------------------------------------------------------------
// Name: CSoundManager::CSoundManager()
// Desc: Constructs the class
//-----------------------------------------------------------------------------
GSoundManager::GSoundManager()
{
	_gameSound = NULL;
}

//-----------------------------------------------------------------------------
// Name: CSoundManager::~CSoundManager()
// Desc: Destroys the class
//-----------------------------------------------------------------------------
GSoundManager::~GSoundManager()
{
	SAFE_RELEASE_SOUND(_gameSound);
}

//-----------------------------------------------------------------------------
// Name: CSoundManager::Initialize()
// Desc: Initializes the IDirectSound object and also sets the primary buffer
//       format.  This function must be called before any others.
//-----------------------------------------------------------------------------
HRESULT GSoundManager::InitializeWindow(HWND hwnd, DWORD CoopLevel)
{
	HRESULT result;
	SAFE_RELEASE_SOUND(_gameSound);

	// Attack IDirectSound using the primary sound device
	if (FAILED(result = DirectSoundCreate8(NULL, &_gameSound, NULL)))
		return 0; //( TEXT("DirectSoundCreate8"), hr );

	// Set DirectSound coop level 
	if (FAILED(result = _gameSound->SetCooperativeLevel(hwnd, CoopLevel)))
		return 0;

	return S_OK;
}

