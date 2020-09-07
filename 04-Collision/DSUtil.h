#ifndef _DSUTIL_H_
#define _DSUTIL_H_

#include <Windows.h>
#include <mmsystem.h>
#include <mmreg.h>
#include <dsound.h>
#include <xstring>
#include "define.h"

using namespace std;

#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] p; (p) = NULL; } }
#define SAFE_RELEASE_SOUND(p) { if (p) { (p)->Release(); (p) = NULL; } }

//-----------------------------------------------------------------------------
// Typing macros 
//-----------------------------------------------------------------------------
#define WAVEFILE_READ 1
#define WAVEFILE_WRITE 2

#define DSUtil_StopSound(sound) { if(sound) sound->Stop(); }
#define DSUtil_PlaySound(sound) { if(sound) sound->Play(0, 0); }
#define DSUtil_PlaySoundLooping(sound) { if(sound) sound->Play(0, DSBPLAY_LOOPING); }



//-----------------------------------------------------------------------------
// Name: class CSoundManager
// Desc: 
//-----------------------------------------------------------------------------
class GSoundManager
{
protected:
	LPDIRECTSOUND8 _gameSound;

public:
	GSoundManager();
	~GSoundManager();

	HRESULT InitializeWindow(HWND hwnd, DWORD CoopLevel);
	inline LPDIRECTSOUND8 getDirectSound() { return _gameSound; }
	HRESULT SetPrimaryBufferFormat(DWORD PrimaryChannels, DWORD PrimaryFreq, DWORD PrimaryBitRate);
	HRESULT Get3DListenerInterface(LPDIRECTSOUND3DLISTENER* DSListener);

	HRESULT Create(GSound** ppSound, LPTSTR strWaveFileName, DWORD dwCreationFlags = 0, GUID guid3DAlgorithm = GUID_NULL, DWORD dwNumBuffers = 1);
	HRESULT CreateSoundFromMemory(GSound** Sound, BYTE* data, ULONG dataSize, LPWAVEFORMATEX formatEx, DWORD createFlags = 0, GUID guid3DAlgorihtm = GUID_NULL, DWORD numBuffers = 1);
	HRESULT CreateStreaming( GStreamingSound** StreamingSound, LPTSTR waveFileName, DWORD createFlags, GUID guid3DAlgorithm, DWORD notifyCount, DWORD notifySize, HANDLE notifyEvent );
};

//-----------------------------------------------------------------------------
// Name: class CSound
// Desc: Encapsulates functionality of a DirectSound buffer.
//-----------------------------------------------------------------------------
class GSound
{
	LPDIRECTSOUNDBUFFER DSBuffer;
	DWORD DSBufferSize;
	GWaveFile* waveFile;
	DWORD numBuffers;
	DWORD createFlags;

	HRESULT RestoreBuffer(LPDIRECTSOUNDBUFFER DSBuffer, BOOL* wasRestored);

public:
	GSound(LPDIRECTSOUNDBUFFER* DSBuffer, DWORD DSBufferSize, DWORD numBuffers, GWaveFile* waveFile, DWORD createFlags);
	virtual ~GSound();

	HRESULT Get3DBufferInterface(DWORD index, LPDIRECTSOUND3DBUFFER* DS3DBuffer);
	HRESULT FillBufferWithSound(LPDIRECTSOUNDBUFFER DSBuffer, BOOL RepeatWaveIfBufferLarger);
	LPDIRECTSOUNDBUFFER GetFreeBuffer();
	LPDIRECTSOUNDBUFFER GetBuffer(DWORD index);

	HRESULT PlaySound(DWORD priority = 0, DWORD flags = 0, LONG volume = 0, LONG frequency = -1, LONG pan = 0);
	HRESULT PlaySound3D(LPDS3DBUFFER DS3DBuffer, DWORD priority = 0, DWORD flags = 0, LONG frequency = 0);
	HRESULT StopSound();
	HRESULT ResetSound();
	BOOL GetIsSoundPlaying();
};

//-----------------------------------------------------------------------------
// Name: class CStreamingSound
// Desc: Encapsulates functionality to play a wave file with DirectSound.  
//       The Attack() method loads a chunk of wave file into the buffer, 
//       and as sound plays more is written to the buffer by calling 
//       HandleWaveStreamNotification() whenever hNotifyEvent is signaled.
//-----------------------------------------------------------------------------
class GStreamingSound : public GSound
{
protected:
	DWORD lastPlayPosition;
	DWORD playProgress;
	DWORD notifySize;
	DWORD nextWriteOffset;
	BOOL fillNextNotificationWithSilence;

public:
	GStreamingSound(LPDIRECTSOUNDBUFFER DSBuffer, DWORD DSBufferSize, GWaveFile* waveFile, DWORD notifySize);
	~GStreamingSound();

	HRESULT HandleWaveStreamNotification(BOOL loopedPlay);
	HRESULT ResetStream();
};

//-----------------------------------------------------------------------------
// Name: class CWaveFile
// Desc: Encapsulates reading or writing sound data to or from a wave file
//-----------------------------------------------------------------------------
class GWaveFile
{
public:
	WAVEFORMATEX* pWaveFormatEx; // Con trỏ đến kiến trúc của WAVEFORMATEX
	HMMIO hmmioHandle; // MM I/O handle cho wave
	MMCKINFO multimediaInfo; // Multimedia RIFF chunk
	MMCKINFO openWaveFile; // Dùng cho việc mở wave file
	DWORD waveFileSize; // Kích thước của wave file
	MMIOINFO ioOutInfo;
	DWORD flags;
	BOOL IsReadingFromMemory;
	BYTE* data;
	BYTE* curData;
	ULONG dataSize;
	CHAR* resourceBuffer;

protected:
	HRESULT ReadMMIO();
	HRESULT WriteMMIO(WAVEFORMATEX* destination);

public:
	GWaveFile();
	~GWaveFile();

	HRESULT OpenWaveFile(LPTSTR fileName, WAVEFORMATEX* formatEx, DWORD flags);
	HRESULT OpenWaveFileFromMemory(BYTE* data, ULONG dataSize, WAVEFORMATEX formatEx, DWORD flags);
	HRESULT CloseWaveFile();

	HRESULT ReadWaveFile(BYTE* buffer, DWORD sizeToRead, DWORD sizeRead);
	HRESULT WriteWaveFile(UINT sizeToWrite, BYTE* data, UINT* sizeWrote);

	DWORD GetWaveFiletSize();
	HRESULT ResetWaveFileSize();
	WAVEFORMATEX* GetWaveFileFormat() { return pWaveFormatEx; }
};

#endif