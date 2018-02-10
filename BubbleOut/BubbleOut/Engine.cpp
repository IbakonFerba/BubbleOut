#include "stdafx.h"
#include "Engine.h"

#include "ObjectManager.h"
#include "GameObject.h"

//----------------------------------------------------------------------
//main loop of the engine
void Engine::run()
{
	//======================================
	//TESTING AREA
	ObjectManager* OBJECT_MANAGER = new ObjectManager();
	OBJECT_MANAGER->getNewObject<A>();
	OBJECT_MANAGER->getNewObject<A>()->i = 30;
	OBJECT_MANAGER->getNewObject<B>()->setObjectManager(OBJECT_MANAGER);
	OBJECT_MANAGER->getNewObject<C>();

	ObjectCollection<B> collection = OBJECT_MANAGER->getObjectsOfType<B>();
	for(unsigned i = 0; i < collection.object_list_starts.size(); ++i)
	{
		for(B* j = collection.object_list_starts.at(i); j <= collection.object_list_ends.at(i); ++j)
		{
			std::cout << j->f << std::endl;
		}
	}
	/*int* i = manager->getNewObject<int>();
	*i = 10;
	std::cout << *i << std::endl;

	int* i2 = manager->getNewObject<int>();
	*i2 = 1;
	std::cout << *i << std::endl;
	std::cout << *i2 << std::endl;

	for(int x = 0; x < 200; ++x)
	{
		manager->getNewObject<int>();
	}

	float* f = manager->getNewObject<float>();
	*f = 3.141;
	std::cout << *f << std::endl;*/
	/*std::vector<ObjectPoolTypes> pools;
	ObjectPool<int> p;
	ObjectPool<float> p2;
	pools.emplace_back(&p);
	pools.emplace_back(&p2);
	ObjectPool<int>* pool = std::get<ObjectPool<int>*>(pools[0]);
	std::cout << pool->isFull() << std::endl;
	std::cout << pool->getTypeInfo().name() << std::endl;
	std::cout << pool->getDummy() << std::endl;

	for(int i = 0; i < 127; ++i)
	{
		*(pool->getNewObject()) = 10;
		std::cout << *(pool->getLastObject()) << std::endl;
	}

	std::cout << pool->isFull() << std::endl;

	int* start = pool->getObjects();
	*start = 21;
	std::cout << *start << std::endl;
	std::cout << pool->getLastObject() << std::endl;

	pool->deleteObject(start);
	std::cout << pool->getLastObject() << std::endl;

	start = pool->getObjects();
	std::cout << *start << std::endl;
	std::cout << pool->getLastObject() << std::endl;

	ObjectPool<float>* pool2 = std::get<ObjectPool<float>*>(pools[1]);
	std::cout << pool2->isFull() << std::endl;
	std::cout << pool2->getTypeInfo().name() << std::endl;
	std::cout << pool2->getDummy() << std::endl;
*/

	//======================================

	sf::Clock clock;
	double lag = 0.0;
	while (m_window.isOpen())
	{
		lag += clock.getElapsedTime().asMicroseconds() * 0.001;
		clock.restart();

		processInput();

		while (lag >= MS_PER_UPDATE)
		{
			update();
			//TODO: DELETE SCHEDULED OBJECTS
			lag -= MS_PER_UPDATE;
		}
		
		render();
	}
}

//----------------------------------------------------------------------
//engine functions
void Engine::processInput()
{
	//dispatch events
	while (m_window.pollEvent(m_event))
	{
		if (m_event.type == sf::Event::Closed)
		{
			m_window.close();
		}
	}
}

void Engine::update()
{
	
}

void Engine::render()
{
	//clear window
	m_window.clear();

	//draw objects

	//display image
	m_window.display();
}
