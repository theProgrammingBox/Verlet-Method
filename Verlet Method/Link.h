#pragma once
#include "Header.h"
#include "Ball.h"

struct Link
{
	Ball* ball1;
	Ball* ball2;
	float length;

	Link(Ball* b1, Ball* b2, float l = -1)
	{
		ball1 = b1;
		ball2 = b2;
		if (l == -1)
		{
			length = ball1->radius + ball2->radius;
		}
		else
		{
			length = l;
		}
		ball1->connections.push_back(this);
		ball2->connections.push_back(this);
	}

	void Update()
	{
		if (!ball1->fixed || !ball2->fixed)
		{
			const vf2d displacement = ball1->position - ball2->position;
			const float distance = displacement.mag();
			const vf2d normal = displacement / distance;
			const vf2d overlap = normal * (length - distance);

			if (ball1->fixed)
			{
				ball2->position -= overlap;
			}
			else if (ball2->fixed)
			{
				ball1->position += overlap;
			}
			else
			{
				const float invMass = 1.0f / (ball1->mass + ball2->mass);

				ball1->position += overlap * ball2->mass * invMass;
				ball2->position -= overlap * ball1->mass * invMass;
			}
		}
	}
};