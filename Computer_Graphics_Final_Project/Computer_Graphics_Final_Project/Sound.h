#pragma once
#include <iostream>
#include <dshow.h>
#include <Windows.h>
#pragma comment (lib, "strmiids.lib")
#define GET_SOUND SOUND::Instance()

class SOUND
{

private:
	
public:
	void PlayerEffect();
	void PlayerVictory();
	void PlayerDeath();
	

public:
	static SOUND* Instance() {
		static SOUND* SoundInstance = nullptr;
		if (SoundInstance == nullptr)
			SoundInstance = new SOUND;

		return SoundInstance;
	}
};
