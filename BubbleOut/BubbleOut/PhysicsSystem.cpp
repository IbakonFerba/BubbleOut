#include "stdafx.h"
#include "PhysicsSystem.h"
#include "Rigidbody.h"

void PhysicsSystem::handleCollision(ObjectManager* ptrObjectManager, const float windowWidth, const float windowHeight)
{
	ObjectCollection<Rigidbody> rigidbodys = ptrObjectManager->getObjectsOfType<Rigidbody>();

	for (unsigned i = 0; i < rigidbodys.object_list_starts.size(); ++i)
	{
		for (Rigidbody* rigidbody1 = rigidbodys.object_list_starts.at(i); rigidbody1 <= rigidbodys.object_list_ends.at(i); ++rigidbody1)
		{
			if(!rigidbody1->enabled)
			{
				continue;
			}
			const CircleCollider* circleCol1 = rigidbody1->getCircleCollider();
			const RectCollider* rectCol1 = rigidbody1->getRectCollider();
			for (unsigned j = i; j < rigidbodys.object_list_starts.size(); ++j)
			{
				for (Rigidbody* rigidbody2 = (j==i) ? rigidbody1+1 : rigidbodys.object_list_starts.at(j); rigidbody2 <= rigidbodys.object_list_ends.at(j); ++rigidbody2)
				{
					if(!rigidbody2->enabled)
					{
						continue;
					}
					const CircleCollider* circleCol2 = rigidbody2->getCircleCollider();
					const RectCollider* rectCol2 = rigidbody2->getRectCollider();

					FloatVector2 f;
					if(circleCol1 != nullptr)
					{
						if(circleCol2 != nullptr)
						{
							checkCircleCircle(rigidbody1, rigidbody2, circleCol1, circleCol2);
						} else
						{
							checkCircleRect(rigidbody1, rigidbody2, circleCol1, rectCol2);
						}
					} else
					{
						if (circleCol2 != nullptr)
						{
							checkCircleRect(rigidbody2, rigidbody1, circleCol2, rectCol1);
						}
						else
						{
							checkRectRect(rigidbody1, rigidbody2, rectCol1, rectCol2);
						}
					}
				}
			}
		}
	}
}

void PhysicsSystem::applyPhysics(ObjectManager* ptrObjectManager)
{
	ObjectCollection<Rigidbody> rigidbodys = ptrObjectManager->getObjectsOfType<Rigidbody>();

	for (unsigned i = 0; i < rigidbodys.object_list_starts.size(); ++i)
	{
		for (Rigidbody* rigidbody = rigidbodys.object_list_starts.at(i); rigidbody <= rigidbodys.object_list_ends.at(i); ++rigidbody)
		{
			rigidbody->applyPhysics();
		}
	}
}


//--------------------------------------------------------------------------
//collision checks
void PhysicsSystem::checkCircleCircle(Rigidbody* rb1, Rigidbody* rb2, const CircleCollider* c1, const CircleCollider* c2)
{
	FloatVector2 force;

	FloatVector2 dist = c1->getCenter() - c2->getCenter();

	const float sumR = c1->getRadius() + c2->getRadius();
	const float distMag = dist.magnitude();
	if(distMag < sumR)
	{
		dist.normalize();
		dist *= sumR - distMag;
		force = dist;

		addToCollidingRbs(rb1, rb2);
		addToCollidingRbs(rb2, rb1);
	} else
	{
		removeFromCollidingRbs(rb1, rb2);
		removeFromCollidingRbs(rb2, rb1);
	}

	force *= 0.5f;
	rb1->addForce(force);
	rb2->addForce(-force);
}

void PhysicsSystem::checkCircleRect(Rigidbody* rbC, Rigidbody* rbR, const CircleCollider* c, const RectCollider* r)
{
	FloatVector2 force(0.0, 0.0);

	const FloatVector2 rectC = r->getCenter();
	const FloatVector2 dim = r->getDimensions();

	const FloatVector2 cC = c->getCenter();
	const float rad = c->getRadius();

	const float distX = cC.x - std::max(rectC.x - dim.x / 2, std::min(cC.x, rectC.x + dim.x / 2));
	const float distY = cC.y - std::max(rectC.y - dim.y / 2, std::min(cC.y, rectC.y + dim.y / 2));

	FloatVector2 dist(distX, distY);

	if(dist.magnitude() < rad)
	{
		if(distX == 0 && distY == 0)
		{
			const float distToCenterX = cC.x - rectC.x;
			const float distToCenterY = cC.y - rectC.y;
			const float innerDistX = ((dim.x / 2 - abs(distToCenterX)) + rad) * distToCenterX / abs(distToCenterX);
			const float innerDistY = ((dim.y / 2 - abs(distToCenterY)) + rad) * distToCenterY / abs(distToCenterY);
			force.x = -innerDistX;
			force.y = -innerDistY;
		} else
		{
			force = dist.getNormalized() * (rad - dist.magnitude());
		}
		addToCollidingRbs(rbC, rbR);
		addToCollidingRbs(rbR, rbC);
	} else
	{
		removeFromCollidingRbs(rbC, rbR);
		removeFromCollidingRbs(rbR, rbC);
	}

	force *= 0.5f;
	rbC->addForce(force);
	rbR->addForce(-force);
}

void PhysicsSystem::checkRectRect(Rigidbody* rb1, Rigidbody* rb2, const RectCollider* r1, const RectCollider* r2)
{
	FloatVector2 force;

	const FloatVector2 center1 = r1->getCenter();
	const sf::Vector2f dim1 = r1->getDimensions();

	const FloatVector2 center2 = r2->getCenter();
	const sf::Vector2f dim2 = r2->getDimensions();

	FloatVector2 dir = center1 - center2;
	if(center1.x + dim1.x/2 > center2.x - dim2.x/2 
		&& center1.x - dim1.x/2 < center2.x + dim2.x/2 
		&& center1.y + dim1.y/2 > center2.y - dim2.y/2 
		&& center1.y - dim1.y/2 < center2.y + dim2.y/2)
	{
		addToCollidingRbs(rb1, rb2);
		addToCollidingRbs(rb2, rb1);
		const float angle = abs(dir.headingAngle());
		if(angle > 135.0 || angle < 45.0)
		{
			if(dir.x < 0)
			{
				force.x = (center2.x - dim2.x / 2) - (center1.x + dim1.x / 2);
			} else
			{
				force.x = (center2.x + dim2.x / 2) - (center1.x - dim1.x / 2);
			}
		} else
		{
			if(dir.y < 0)
			{
				force.y = (center2.y - dim2.y / 2) - (center1.y + dim1.y / 2);
			} else
			{
				force.y = (center2.y + dim2.y / 2) - (center1.y - dim1.y / 2);
			}
		}
	} else
	{
		removeFromCollidingRbs(rb1, rb2);
		removeFromCollidingRbs(rb2, rb1);
	}
	force *= 0.5f;
	rb1->addForce(force);
	rb2->addForce(-force);
}

void PhysicsSystem::addToCollidingRbs(Rigidbody* rb, Rigidbody* collidingRb)
{
	bool foundRb = false;
	for (Rigidbody* rigidbody : rb->collidingRigidbodys)
	{
		if (rigidbody == collidingRb)
		{
			foundRb = true;
			break;
		}
	}
	if (!foundRb)
	{
		rb->collidingRigidbodys.push_back(collidingRb);
		rb->collisionWith(collidingRb);
	}
}

void PhysicsSystem::removeFromCollidingRbs(Rigidbody* rb, Rigidbody* collidingRb)
{
	for (unsigned i = 0; i < rb->collidingRigidbodys.size(); ++i)
	{
		if (rb->collidingRigidbodys.at(i) == collidingRb)
		{
			rb->collidingRigidbodys.erase(rb->collidingRigidbodys.begin() + i);
			rb->collisionExitWith(collidingRb);
			break;
		}
	}
}
