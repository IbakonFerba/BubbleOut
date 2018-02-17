#pragma once

#ifndef SOUND_SYSTEM_H
#define SOUND_SYSTEM_H

#include "stdafx.h"
#include "Observer.h"

/*
 * System for handeling music and sound
 */
class SoundSystem : public Observer
{
public:
	SoundSystem() {}
	~SoundSystem(){}

	void loadSounds();

	void startMusic();
	void stopMusic();

	//update observer
	void update(const Message& rMessage) override;
private:
	static const int VOICES = 20;
	sf::Sound m_voices[VOICES];
	std::map<MessageType, sf::SoundBuffer> m_sounds;

	sf::SoundBuffer m_musicBuffer;
	sf::Sound m_music;

	void playSound(const sf::SoundBuffer& rSound);
};

#endif