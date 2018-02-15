#include "stdafx.h"
#include "SoundSystem.h"

//-----------------------------------------------
//constructor
SoundSystem::SoundSystem()
{
	sf::SoundBuffer buffer;
	buffer.loadFromFile("Assets/sound/BubbleImpact.wav");
	m_sounds[MessageType::BUBBLE_IMPACT] = buffer;

	buffer.loadFromFile("Assets/sound/BallImpact.wav");
	m_sounds[MessageType::PLAYER_BALL_IMPACT] = buffer;
}

//---------------------------------------------
//playsound
void SoundSystem::playSound(const sf::SoundBuffer& sound)
{
	for(int i = 0; i < VOICES; ++i)
	{
		if(m_voices[i].getStatus() != sf::SoundSource::Status::Playing)
		{
			m_voices[i].setBuffer(sound);
			m_voices[i].play();
			return;
		}
	}
}


//---------------------------------------------
//observer
void SoundSystem::update(const Message& message)
{
	if(message.type == MessageType::BUBBLE_IMPACT)
	{
		playSound(m_sounds[MessageType::BUBBLE_IMPACT]);
	}

	if(message.type == MessageType::PLAYER_BALL_IMPACT)
	{
		playSound(m_sounds[MessageType::PLAYER_BALL_IMPACT]);
	}
}
