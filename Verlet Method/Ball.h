#pragma once
#include "Header.h"
#include "Link.h"

struct Link;

struct Ball
{
	vf2d position;
	vf2d oldPosition;
	vf2d acceleration;
	bool fixed;
	float radius;
	float mass;
	Pixel color;
	vector<Link*> connections;

	Ball(float X = 0, float Y = 0, float YV = 0, float XV = 0, bool F = false, float R = 10, Pixel C = Pixel(255, 0, 0, 0))
	{
		position = vf2d(X, Y);
		oldPosition = vf2d(X, Y);
		acceleration = vf2d(XV, YV);
		fixed = F;
		radius = R;
		mass = 3.14159265359 * radius * radius;
		color = C;
	}

	Ball(vf2d pos = vf2d(0, 0), vf2d vel = vf2d(0, 0), bool F = false, float R = 10, Pixel C = Pixel(255, 0, 0, 0))
	{
		position = pos;
		oldPosition = pos;
		acceleration = vel;
		fixed = F;
		radius = R;
		mass = 3.14159265359 * radius * radius;
		color = C;
	}

	void Update(float fElapsedTime)
	{
		if (!fixed)
		{
			vf2d velocity = position - oldPosition;
			oldPosition = position;
			position += velocity + acceleration * fElapsedTime * fElapsedTime;
			acceleration = vf2d(0, 0);
		}
	}

	void Accelerate(vf2d acc)
	{
		if (!fixed)
		{
			acceleration += acc;
		}
	}

	void ClearVelocity()
	{
		oldPosition = position;
	}

	void CircleConstraint(vf2d centerPos, float centerRadius)
	{
		if (!fixed)
		{
			const vf2d displacement = position - centerPos;
			const float distanceSquared = displacement.mag2();
			const float innerlap = centerRadius - radius;

			if (distanceSquared > innerlap * innerlap)
			{
				const float distance = sqrtf(distanceSquared);
				const vf2d normal = displacement / distance;
				position = centerPos + normal * innerlap;
			}
		}
	}

	void RectConstraint(vf2d startEdge, vf2d endEdge)
	{
		if (!fixed)
		{
			position.x = max(min(position.x, endEdge.x - radius), startEdge.x + radius);
			position.y = max(min(position.y, endEdge.y - radius), startEdge.y + radius);
		}
	}

	void collide(Ball* ball)
	{
		if (!fixed || !ball->fixed)
		{
			vf2d displacement = position - ball->position;
			const float combinedRadius = radius + ball->radius;

			if (displacement.abs() <= combinedRadius);
			{
				if (displacement == 0)
				{
					displacement += 0.00001;
				}
				const float distanceSquared = displacement.mag2();

				if (distanceSquared < combinedRadius * combinedRadius)
				{
					const float distance = sqrtf(distanceSquared);
					const vf2d normal = displacement / distance;
					const vf2d overlap = normal * (combinedRadius - distance);

					if (fixed)
					{
						ball->position -= overlap;
					}
					else if (ball->fixed)
					{
						position += overlap;
					}
					else
					{
						const float invMass = 1.0f / (mass + ball->mass);

						position += overlap * ball->mass * invMass;
						ball->position -= overlap * mass * invMass;
					}
				}
			}
		}
	}
};