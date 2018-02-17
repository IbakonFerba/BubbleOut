#include "stdafx.h"
#include "PhysicsSystem.h"
#include "Rigidbody.h"

void PhysicsSystem::handleCollision(ObjectManager* ptrObjectManager, const float& rWindowWidth, const float& rWindowHeight)
{
	const ObjectCollection<Rigidbody> rigidbodys = ptrObjectManager->getObjectsOfType<Rigidbody>();

	for (unsigned i = 0; i < rigidbodys.object_list_starts.size(); ++i)
	{
		for (Rigidbody* ptrRigidbody1 = rigidbodys.object_list_starts.at(i); ptrRigidbody1 <= rigidbodys.object_list_ends.at(i); ++ptrRigidbody1)
		{
			if(!ptrRigidbody1->enabled)
			{
				continue;
			}

			const CircleCollider* ptrCircleCol1 = ptrRigidbody1->getCircleCollider();
			const RectCollider* ptrRectCol1 = ptrRigidbody1->getRectCollider();
			for (unsigned j = i; j < rigidbodys.object_list_starts.size(); ++j)
			{
				for (Rigidbody* ptrRigidbody2 = (j==i) ? ptrRigidbody1+1 : rigidbodys.object_list_starts.at(j); ptrRigidbody2 <= rigidbodys.object_list_ends.at(j); ++ptrRigidbody2)
				{
					if(!ptrRigidbody2->enabled)
					{
						continue;
					}

					const CircleCollider* ptrCircleCol2 = ptrRigidbody2->getCircleCollider();
					const RectCollider* ptrRectCol2 = ptrRigidbody2->getRectCollider();

					if(ptrCircleCol1 != nullptr)
					{
						if(ptrCircleCol2 != nullptr)
						{
							checkCircleCircle(ptrRigidbody1, ptrRigidbody2, ptrCircleCol1, ptrCircleCol2);
						} else
						{
							checkCircleRect(ptrRigidbody1, ptrRigidbody2, ptrCircleCol1, ptrRectCol2);
						}
					} else
					{
						if (ptrCircleCol2 != nullptr)
						{
							checkCircleRect(ptrRigidbody2, ptrRigidbody1, ptrCircleCol2, ptrRectCol1);
						}
						else
						{
							checkRectRect(ptrRigidbody1, ptrRigidbody2, ptrRectCol1, ptrRectCol2);
						}
					}
				}
			}
		}
	}
}

void PhysicsSystem::applyPhysics(ObjectManager* ptrObjectManager)
{
	const ObjectCollection<Rigidbody> rigidbodys = ptrObjectManager->getObjectsOfType<Rigidbody>();

	for (unsigned i = 0; i < rigidbodys.object_list_starts.size(); ++i)
	{
		for (Rigidbody* ptrRigidbody = rigidbodys.object_list_starts.at(i); ptrRigidbody <= rigidbodys.object_list_ends.at(i); ++ptrRigidbody)
		{
			ptrRigidbody->applyPhysics();
		}
	}
}


//--------------------------------------------------------------------------
//collision checks
void PhysicsSystem::checkCircleCircle(Rigidbody* ptrRb1, Rigidbody* ptrRb2, const CircleCollider* ptrC1, const CircleCollider* ptrC2)
{
	FloatVector2 force;

	FloatVector2 dist = ptrC1->getCenter() - ptrC2->getCenter();

	const float sumR = ptrC1->getRadius() + ptrC2->getRadius();
	const float distMag = dist.magnitude();
	if(distMag < sumR)
	{
		dist.normalize();
		dist *= sumR - distMag;
		force = dist;

		addToCollidingRbs(ptrRb1, ptrRb2);
		addToCollidingRbs(ptrRb2, ptrRb1);
	} else
	{
		removeFromCollidingRbs(ptrRb1, ptrRb2);
		removeFromCollidingRbs(ptrRb2, ptrRb1);
	}

	force *= 0.5f;
	ptrRb1->addForce(force);
	ptrRb2->addForce(-force);
}

void PhysicsSystem::checkCircleRect(Rigidbody* ptrRbC, Rigidbody* ptrRbR, const CircleCollider* ptrC, const RectCollider* ptrR)
{
	FloatVector2 force(0.0, 0.0);

	const FloatVector2 rectC = ptrR->getCenter();
	const FloatVector2 dim = ptrR->getDimensions();

	const FloatVector2 cC = ptrC->getCenter();
	const float rad = ptrC->getRadius();

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
		addToCollidingRbs(ptrRbC, ptrRbR);
		addToCollidingRbs(ptrRbR, ptrRbC);
	} else
	{
		removeFromCollidingRbs(ptrRbC, ptrRbR);
		removeFromCollidingRbs(ptrRbR, ptrRbC);
	}

	force *= 0.5f;
	ptrRbC->addForce(force);
	ptrRbR->addForce(-force);
}

void PhysicsSystem::checkRectRect(Rigidbody* ptrRb1, Rigidbody* ptrRb2, const RectCollider* ptrR1, const RectCollider* ptrR2)
{
	FloatVector2 force;

	const FloatVector2 center1 = ptrR1->getCenter();
	const FloatVector2 dim1 = ptrR1->getDimensions();

	const FloatVector2 center2 = ptrR2->getCenter();
	const FloatVector2 dim2 = ptrR2->getDimensions();

	FloatVector2 dir = center1 - center2;
	if(center1.x + dim1.x/2 > center2.x - dim2.x/2 
		&& center1.x - dim1.x/2 < center2.x + dim2.x/2 
		&& center1.y + dim1.y/2 > center2.y - dim2.y/2 
		&& center1.y - dim1.y/2 < center2.y + dim2.y/2)
	{
		addToCollidingRbs(ptrRb1, ptrRb2);
		addToCollidingRbs(ptrRb2, ptrRb1);
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
		removeFromCollidingRbs(ptrRb1, ptrRb2);
		removeFromCollidingRbs(ptrRb2, ptrRb1);
	}
	force *= 0.5f;
	ptrRb1->addForce(force);
	ptrRb2->addForce(-force);
}

void PhysicsSystem::addToCollidingRbs(Rigidbody* ptrRb, Rigidbody* ptrCollidingRb)
{
	bool foundRb = false;
	for (Rigidbody* ptrRigidbody : ptrRb->collidingRigidbodys)
	{
		if (ptrRigidbody == ptrCollidingRb)
		{
			foundRb = true;
			break;
		}
	}
	if (!foundRb)
	{
		ptrRb->collidingRigidbodys.push_back(ptrCollidingRb);
		ptrRb->collisionWith(ptrCollidingRb);
	}
}

void PhysicsSystem::removeFromCollidingRbs(Rigidbody* ptrRb, Rigidbody* ptrCollidingRb)
{
	for (unsigned i = 0; i < ptrRb->collidingRigidbodys.size(); ++i)
	{
		if (ptrRb->collidingRigidbodys.at(i) == ptrCollidingRb)
		{
			ptrRb->collidingRigidbodys.erase(ptrRb->collidingRigidbodys.begin() + i);
			ptrRb->collisionExitWith(ptrCollidingRb);
			break;
		}
	}
}
