#include "stdafx.h"
#include "Bubble.h"

//-------------------------------------------------------
//init
void Bubble::init(ObjectManager* ptrObjectManager, const float& rPosX, const float& rPosY)
{
	//get components
	m_ptr_trans = ptrObjectManager->getNewObject<Transform>();
	m_ptr_rend = ptrObjectManager->getNewObject<SpriteRenderer>();
	m_ptr_col = ptrObjectManager->getNewObject<CircleCollider>();
	m_ptr_rigidbody = ptrObjectManager->getNewObject<Rigidbody>();

	//set values
	m_startPos.x = rPosX;
	m_startPos.y = rPosY;

	m_startMass = 2;
	m_startDrag = 2;
	tag = Tag::BUBBLE;

	//setup components
	m_ptr_rend->init(m_ptr_trans, "Assets/graphics/Bubble.png", Origin::CENTER);
	m_ptr_rend->tag = RenderTag::INGAME;

	const sf::FloatRect bounds = m_ptr_rend->getBounds();
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
void Bubble::update(const Message& rMessage)
{
	if (rMessage.type == MessageType::COLLISION_EXIT)
	{
		m_observerMessage.type = MessageType::BUBBLE_IMPACT;
		notifyObservers();

		if (rMessage.tag == Tag::BUBBLE)
		{
			if (rMessage.ptr_circle_collider->getScale().x < m_ptr_trans->scale.x)
			{
				if (m_ptr_trans->scale.x < MAX_SCALE)
				{
					m_ptr_trans->scale += SCALE_STEP;
					m_ptr_rigidbody->drag += DRAG_STEP;
					m_ptr_rigidbody->mass += MASS_STEP;
				}
			}
			else if (rMessage.ptr_circle_collider->getScale().x > m_ptr_trans->scale.x && rMessage.ptr_circle_collider->getScale().x < MAX_SCALE)
			{
				if (m_ptr_trans->scale.x > MIN_SCALE)
				{
					m_ptr_trans->scale -= SCALE_STEP;
				}
			}
		}
		else if (rMessage.tag == Tag::PLAYER)
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
