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

	buffer.loadFromFile("Assets/sound/GameOver.wav");
	m_sounds[MessageType::GAME_OVER] = buffer;

	buffer.loadFromFile("Assets/sound/StartGame.wav");
	m_sounds[MessageType::START_GAME] = buffer;

	buffer.loadFromFile("Assets/sound/Win.wav");
	m_sounds[MessageType::WIN_GAME] = buffer;

	buffer.loadFromFile("Assets/sound/BallDestroyed.wav");
	m_sounds[MessageType::PLAYER_BALL_HIT_BOTTOM] = buffer;

	buffer.loadFromFile("Assets/sound/BubbleDestroyed.wav");
	m_sounds[MessageType::BUBBLE_DESTROYED] = buffer;
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
	if(m_sounds.find(message.type) != m_sounds.end())
	{
		playSound((m_sounds[message.type]));
	}
	/*if(message.type == MessageType::BUBBLE_IMPACT)
	{
		playSound(m_sounds[MessageType::BUBBLE_IMPACT]);
	}

	if(message.type == MessageType::PLAYER_BALL_IMPACT)
	{
		playSound(m_sounds[MessageType::PLAYER_BALL_IMPACT]);
	}*/
}
