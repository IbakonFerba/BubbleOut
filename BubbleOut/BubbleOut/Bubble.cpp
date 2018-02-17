#include "stdafx.h"
#include "Bubble.h"

//-------------------------------------------------------
//init
void Bubble::init(ObjectManager* ptrObjectManager, const float posX, const float posY)
{
	setObjectManager(ptrObjectManager);

	//get components
	m_ptr_trans = m_ptr_objManager->getNewObject<Transform>();
	m_ptr_rend = m_ptr_objManager->getNewObject<ShapeRenderer>();
	m_ptr_col = m_ptr_objManager->getNewObject<CircleCollider>();
	m_ptr_rigidbody = m_ptr_objManager->getNewObject<Rigidbody>();

	//set values
	m_startPos.x = posX;
	m_startPos.y = posY;

	m_startMass = 2;
	m_startDrag = 2;
	tag = Tag::BUBBLE;

	//setup components
	sf::CircleShape* shape = new sf::CircleShape(50);
	shape->setFillColor(sf::Color::White);
	m_ptr_rend->init(m_ptr_trans, shape, Origin::CENTER);
	m_ptr_rend->tag = RenderTag::INGAME;

	sf::FloatRect bounds = m_ptr_rend->getBounds();
	m_ptr_col->init(m_ptr_trans, bounds.width / 2);
	
	m_ptr_rigidbody->init(this, m_ptr_col, m_ptr_trans, m_startDrag, m_startMass);
	m_ptr_rigidbody->addObserver(this);

	reset();
}

void Bubble::reset()
{
	m_ptr_trans->position = m_startPos;
	m_ptr_trans->scale.x = 1.0f;
	m_ptr_trans->scale.y = 1.0f;

	m_ptr_rigidbody->setVelocity(FloatVector2(0, 0));
	m_ptr_rigidbody->drag = m_startDrag;
	m_ptr_rigidbody->mass = m_startMass;

	m_ptr_rend->enabled = true;
	m_ptr_rigidbody->enabled = true;
	enabled = true;
}

void Bubble::disable()
{
	enabled = false;
	m_ptr_rend->enabled = false;
	m_ptr_rigidbody->enabled = false;

	m_observerMessage.type = MessageType::BUBBLE_DESTROYED;
	notifyObservers();
}



//-------------------------------------------------------
//ovbserver
void Bubble::update(const Message& message)
{
	if(message.type == MessageType::COLLISION_EXIT)
	{
		m_observerMessage.type = MessageType::BUBBLE_IMPACT;
		notifyObservers();
		if (message.tag == Tag::BUBBLE)
		{
			if(message.circle_collider != nullptr)
			{
				if(message.circle_collider->getScale().x < m_ptr_trans->scale.x)
				{
					if(m_ptr_trans->scale.x < MAX_SCALE)
					{
						m_ptr_trans->scale += SCALE_STEP;
						m_ptr_rigidbody->drag += DRAG_STEP;
						m_ptr_rigidbody->mass += MASS_STEP;
					}
				} else if(message.circle_collider->getScale().x > m_ptr_trans->scale.x && message.circle_collider->getScale().x < MAX_SCALE)
				{
					if (m_ptr_trans->scale.x > MIN_SCALE)
					{
						m_ptr_trans->scale -= SCALE_STEP;
					}
				}
			}
		}
		else if (message.tag == Tag::PLAYER)
		{
			if (m_ptr_trans->scale.x > MIN_SCALE)
			{
				m_ptr_trans->scale -= SCALE_STEP;
				m_ptr_rigidbody->drag -= DRAG_STEP;
				m_ptr_rigidbody->mass -= MASS_STEP;
			}
		}
	}
}

void Bubble::notifyObservers() const
{
	for (unsigned i = 0; i < m_observers.size(); ++i)
	{
		m_observers.at(i)->update(m_observerMessage);
	}
}


//-------------------------------------------------------
//getter
FloatVector2 Bubble::getScale() const
{
	return m_ptr_trans->scale;
}

FloatVector2 Bubble::getPosition() const
{
	return m_ptr_trans->position;
}
