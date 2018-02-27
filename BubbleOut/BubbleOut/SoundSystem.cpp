#include "stdafx.h"
#include "SoundSystem.h"

//-----------------------------------------------
//init

void SoundSystem::loadSounds()
{
	sf::SoundBuffer buffer;

	//music
	m_musicStartSeqBuffer.loadFromFile("Assets/sound/Music/GameCornerStart.wav"); //chiptune cover of the Game Corner Theme from Pokémon Diamond and Pearl arranged and produced by me 
	m_musicStartSeq.setBuffer(m_musicStartSeqBuffer);
	m_musicStartSeq.setVolume(50);
	m_musicWaitTime = m_musicStartSeqBuffer.getDuration().asMicroseconds();


	m_musicBuffer.loadFromFile("Assets/sound/Music/GameCornerLoop.wav"); //chiptune cover of the Game Corner Theme from Pokémon Diamond and Pearl arranged and produced by me 
	m_music.setBuffer(m_musicBuffer);
	m_music.setVolume(50);
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
	//find a free voice and play the sound
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
	m_musicStartSeq.play();
	m_musicTimer.restart();
}

void SoundSystem::updateMusic()
{
	if(m_musicTimer.getElapsedTime().asMicroseconds() >= m_musicWaitTime && m_music.getStatus() != sf::SoundStream::Status::Playing)
	{
		m_music.play();
	}
}


void SoundSystem::stopMusic()
{
	m_musicStartSeq.stop();
	m_music.stop();
}


//---------------------------------------------
//observer

void SoundSystem::update(const Message& rMessage)
{
	//if the event has a corresponding sound effect, play it
	if(m_sounds.find(rMessage.type) != m_sounds.end())
	{
		playSound((m_sounds[rMessage.type]));
	}
}
