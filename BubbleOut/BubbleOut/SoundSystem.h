#pragma once

#ifndef SOUND_SYSTEM_H
#define SOUND_SYSTEM_H

#include "stdafx.h"
#include "Observer.h"

class SoundSystem : public Observer
{
public:
	SoundSystem();
	~SoundSystem(){}

	void update(const Message& message) override;
private:
	static const int VOICES = 20;
	sf::Sound m_voices[VOICES];
	std::map<MessageType, sf::SoundBuffer> m_sounds;

	void playSound(const sf::SoundBuffer& sound);
};

#endif