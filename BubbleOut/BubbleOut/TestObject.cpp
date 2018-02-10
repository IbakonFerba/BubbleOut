#include "TestObject.h"

//----------------------------------------------------------------------
//destructor
TestObject::~TestObject()
{
	delete m_ptr_rend;
	delete m_ptr_trans;
}

//----------------------------------------------------------------------
//init
void TestObject::init(ObjectManager* ptrObjectManager)
{
	m_ptr_objManager = ptrObjectManager;

	m_ptr_trans = m_ptr_objManager->getNewObject<Transform>();
	m_ptr_rend = m_ptr_objManager->getNewObject<CircleRenderer>();

	sf::CircleShape* circle = new sf::CircleShape;
	circle->setFillColor(sf::Color::Red);
	circle->setRadius(20);

	circle->setPosition(m_ptr_trans->Position);

	m_ptr_trans->Position.x = 100;

	m_ptr_rend->init(m_ptr_trans, circle);
}

