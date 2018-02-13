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
			const CircleCollider* circleCol1 = rigidbody1->getCircleCollider();
			const RectCollider* rectCol1 = rigidbody1->getRectCollider();
			for (unsigned j = i; j < rigidbodys.object_list_starts.size(); ++j)
			{
				for (Rigidbody* rigidbody2 = (j==i) ? rigidbody1+1 : rigidbodys.object_list_starts.at(j); rigidbody2 <= rigidbodys.object_list_ends.at(j); ++rigidbody2)
				{
					const CircleCollider* circleCol2 = rigidbody2->getCircleCollider();
					const RectCollider* rectCol2 = rigidbody2->getRectCollider();

					FloatVector2 f;
					if(circleCol1 != nullptr)
					{
						if(circleCol2 != nullptr)
						{
							f = checkCircleCircle(rigidbody1, rigidbody2, circleCol1, circleCol2);
						} else
						{
							f = checkCircleRect(rigidbody1, rigidbody2, circleCol1, rectCol2);
						}
					} else
					{
						if (circleCol2 != nullptr)
						{
							f = checkCircleRect(rigidbody1, rigidbody2, circleCol2, rectCol1);
						}
						else
						{
							f = checkRectRect(rigidbody1, rigidbody2, rectCol1, rectCol2);
						}
					}

					f.x *= 0.5;
					f.y *= 0.5;
					rigidbody1->addForce(f);
					rigidbody2->addForce(-f);
				}
			}

			FloatVector2 f;
			if(circleCol1 != nullptr)
			{
				f = checkEdges(circleCol1, windowWidth, windowHeight);
			} else
			{
				f = checkEdges(rectCol1, windowWidth, windowHeight);
			}

			rigidbody1->addForce(f);
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
FloatVector2 PhysicsSystem::checkCircleCircle(Rigidbody* rb1, Rigidbody* rb2, const CircleCollider* c1, const CircleCollider* c2)
{
	FloatVector2 force;

	FloatVector2 dist = c1->getCenter() - c2->getCenter();

	float sumR = c1->getRadius() + c2->getRadius();
	float distMag = dist.magnitude();
	if(distMag < sumR)
	{
		dist.normalize();
		dist *= sumR - distMag;
		force = dist;

		rb1->collisionWith(rb2);
		rb2->collisionWith(rb1);
	}

	return force;
}

FloatVector2 PhysicsSystem::checkCircleRect(Rigidbody* rb1, Rigidbody* rb2, const CircleCollider* c, const RectCollider* r)
{
	FloatVector2 force(0.0, 0.0);

	FloatVector2 rectC = r->getCenter();
	FloatVector2 dim = r->getDimensions();

	FloatVector2 cC = c->getCenter();
	float rad = c->getRadius();

	FloatVector2 dist(cC.x - std::max(rectC.x - dim.x / 2, std::min(cC.x, rectC.x + dim.x / 2)), cC.y - std::max(rectC.y - dim.y / 2, std::min(cC.y, rectC.y + dim.y / 2)));

	if(dist.magnitude() < rad)
	{
		force = dist.getNormalized() * (rad - dist.magnitude());
		rb1->collisionWith(rb2);
		rb2->collisionWith(rb1);
	}

	return force;
}

FloatVector2 PhysicsSystem::checkRectRect(Rigidbody* rb1, Rigidbody* rb2, const RectCollider* r1, const RectCollider* r2)
{
	FloatVector2 force;

	const FloatVector2 center1 = r1->getCenter();
	sf::Vector2f dim1 = r1->getDimensions();

	const FloatVector2 center2 = r2->getCenter();
	sf::Vector2f dim2 = r2->getDimensions();

	FloatVector2 dir = center1 - center2;
	if(center1.x + dim1.x/2 > center2.x - dim2.x/2 
		&& center1.x - dim1.x/2 < center2.x + dim2.x/2 
		&& center1.y + dim1.y/2 > center2.y - dim2.y/2 
		&& center1.y - dim1.y/2 < center2.y + dim2.y/2)
	{
		rb1->collisionWith(rb2);
		rb2->collisionWith(rb1);
		float angle = abs(dir.headingAngle());
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
	}
	return force;
}



FloatVector2 PhysicsSystem::checkEdges(const CircleCollider* c, const float windowWidth, const float windowHeight)
{
	FloatVector2 force;

	const FloatVector2 center = c->getCenter();
	float r = c->getRadius();
	if(center.x - r < 0)
	{
		force.x = 0 - (center.x - r);
	} else if(center.x + r > windowWidth)
	{
		force.x = windowWidth - (center.x + r);
	} 
	
	if(center.y - r < 0)
	{
		force.y = 0 - (center.y - r);
	}
	else if (center.y + r > windowHeight)
	{
		force.y = windowHeight - (center.y + r);
	}

	return force;
}

FloatVector2 PhysicsSystem::checkEdges(const RectCollider* r, const float windowWidth, const float windowHeight)
{
	FloatVector2 force;

	const FloatVector2 center = r->getCenter();
	sf::Vector2f dim = r->getDimensions();

	if(center.x - dim.x/2 < 0)
	{
		force.x = 0 - (center.x - dim.x / 2);
	} else if(center.x + dim.x/2 > windowWidth)
	{
		force.x = windowWidth - (center.x + dim.x / 2);
	}

	if (center.y - dim.y / 2 < 0)
	{
		force.y = 0 - (center.y - dim.y / 2);
	}
	else if (center.y + dim.y / 2 > windowHeight)
	{
		force.y = windowHeight - (center.y + dim.y / 2);
	}

	return force;
}