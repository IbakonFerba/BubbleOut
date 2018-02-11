#include "TestObject.h"
#include "SpriteRenderer.h"

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
	setObjectManager(ptrObjectManager);

	m_ptr_trans = m_ptr_objManager->getNewObject<Transform>();
	m_ptr_rend = m_ptr_objManager->getNewObject<SpriteRenderer>();

	//sf::RectangleShape* ptrShape = new sf::RectangleShape;
	//ptrShape->setFillColor(sf::Color::Red);
	//ptrShape->setSize(sf::Vector2f(30, 30));

	//ptrShape->setPosition(m_ptr_trans->position);


	m_ptr_rend->init(m_ptr_trans, "graphics/player.png", Origin::CENTER);
}


