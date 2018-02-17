#include "stdafx.h"
#include "SoundSystem.h"

//-----------------------------------------------
//init
void SoundSystem::loadSounds()
{
	sf::SoundBuffer buffer;

	//music
	m_musicBuffer.loadFromFile("Assets/sound/Music/Sinnoh_Game_Corner_Remix_V_II.wav");
	m_music.setBuffer(m_musicBuffer);
	m_music.setLoop(true);

	//sound effects
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
void SoundSystem::playSound(const sf::SoundBuffer& rSound)
{
	for(int i = 0; i < VOICES; ++i)
	{
		if(m_voices[i].getStatus() != sf::SoundSource::Status::Playing)
		{
			m_voices[i].setBuffer(rSound);
			m_voices[i].play();
			return;
		}
	}
}

void SoundSystem::startMusic()
{
	m_music.play();
}

void SoundSystem::stopMusic()
{
	m_music.stop();
}


//---------------------------------------------
//observer
void SoundSystem::update(const Message& rMessage)
{
	if(m_sounds.find(rMessage.type) != m_sounds.end())
	{
		playSound((m_sounds[rMessage.type]));
	}
}
