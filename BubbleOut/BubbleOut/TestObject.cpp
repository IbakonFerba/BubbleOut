#include "TestObject.h"
#include "SpriteRenderer.h"

//----------------------------------------------------------------------
//destructor
TestObject::~TestObject()
{
	m_ptr_objManager->destroyObject(m_ptr_trans);
	m_ptr_objManager->destroyObject(m_ptr_rend);
}

//----------------------------------------------------------------------
//init
void TestObject::init(ObjectManager* ptrObjectManager, const FloatVector2& pos, const FloatVector2& initialForce, float mass, bool circleCollider)
{
	setObjectManager(ptrObjectManager);

	m_ptr_trans = m_ptr_objManager->getNewObject<Transform>();
	m_ptr_rend = m_ptr_objManager->getNewObject<ShapeRenderer>();
	if(circleCollider)
	{
		m_ptr_circleCollider = m_ptr_objManager->getNewObject<CircleCollider>();
	} else
	{
		m_ptr_collider = m_ptr_objManager->getNewObject<RectCollider>();
	}
	m_ptr_rigidbody = m_ptr_objManager->getNewObject<Rigidbody>();

	if(circleCollider)
	{
		sf::CircleShape* ptrShape = new sf::CircleShape();
		ptrShape->setFillColor(sf::Color::Red);
		ptrShape->setRadius(30);
		m_ptr_rend->init(m_ptr_trans, ptrShape, Origin::CENTER);
	} else
	{
		sf::RectangleShape* ptrShape = new sf::RectangleShape();
		ptrShape->setFillColor(sf::Color::Red);
		ptrShape->setSize(sf::Vector2f(60, 60));
		m_ptr_rend->init(m_ptr_trans, ptrShape, Origin::CENTER);
	}

	m_ptr_trans->position.x = pos.x;
	m_ptr_trans->position.y = pos.y;

	if(circleCollider)
	{
		m_ptr_circleCollider->init(m_ptr_trans, 30);
		m_ptr_rigidbody->init(this, m_ptr_circleCollider, m_ptr_trans, 0, mass);
	} else
	{
		m_ptr_collider->init(m_ptr_trans, 60, 60);
		m_ptr_rigidbody->init(this, m_ptr_collider, m_ptr_trans, 0, mass);
	}

	m_ptr_rigidbody->addForce(initialForce);
	m_ptr_rigidbody->addObserver(this);
}


void TestObject::update(const Message& message)
{
	std::cout << (int)tag << std::endl;
	std::cout << "other";
	std::cout << (int)message.tag << std::endl;
}


