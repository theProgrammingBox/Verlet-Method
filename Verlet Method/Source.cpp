#include "Link.h"

class Example : public olc::PixelGameEngine
{
private:
	const vf2d Gravity = { 0.0f, 1000.0f };
	const int SimulationSteps = 10;
	const float subElapsedTime = 1.0 / (SimulationSteps * 60);

	vf2d ScreenEdge;
	vf2d ScreenCenter;
	float ScreenRadius;

	vector<Ball*> ballArr;
	vector<Link*> linkArr;

	Pixel mapToRainbow(double d) { // 0 - 1
		d *= 6;
		const double r = (d > 4) ? max(0.0, min(1.0, 6 - d)) : max(0.0, min(1.0, d - 2));
		const double g = (d > 2) ? max(0.0, min(1.0, 4 - d)) : max(0.0, min(1.0, d));
		const double b = (d > 3) ? max(0.0, min(1.0, d - 4)) : max(0.0, min(1.0, 2 - d));

		return Pixel(r * 0xff, g * 0xff, b * 0xff);
	}

	void ClearVelocities()
	{
		for (Ball* ball : ballArr)
		{
			ball->ClearVelocity();
		}
	}

	void ClearScreen()
	{
		for (Ball* ball : ballArr)
		{
			FillCircle(ball->position, ball->radius, Pixel(50, 50, 50));
		}
	}

	void ApplyGravity()
	{
		for (Ball* ball : ballArr)
		{
			ball->Accelerate(Gravity);
		}
	}

	void UpdatePosition(float fElapsedTime)
	{
		for (Ball* ball : ballArr)
		{
			ball->Update(fElapsedTime);
		}
	}

	void ApplyCircleScreenConstraint()
	{
		for (Ball* ball : ballArr)
		{
			ball->CircleConstraint(ScreenCenter, ScreenRadius);
		}
	}

	void ApplyRectScreenConstraint()
	{
		for (Ball* ball : ballArr)
		{
			ball->RectConstraint(vf2d(0, 0), ScreenEdge);
		}
	}

	void SolveCollisions()
	{
		for (int i = 0; i < ballArr.size(); i++)
		{
			for (int j = i + 1; j < ballArr.size(); j++)
			{
				ballArr[i]->collide(ballArr[j]);
			}
		}
	}

	void SolveLinks()
	{
		for (Link* link : linkArr)
		{
			link->Update();
		}
	}

	void Render()
	{
		for (Ball* ball : ballArr)
		{
			FillCircle(ball->position, ball->radius, ball->color);
		}
	}

	void StablizeConstraints(int iteratons)
	{
		for (int i = 0; i < iteratons; i++)
		{
			SolveCollisions();
			SolveLinks();
			ApplyCircleScreenConstraint();
			//ApplyRectScreenConstraint();
		}
	}

public:
	Example()
	{
		sAppName = "Circle Physics";
	}

	bool OnUserCreate() override
	{
		ScreenEdge = vf2d(ScreenWidth(), ScreenHeight());
		ScreenCenter = ScreenEdge / 2.0;
		ScreenRadius = min(ScreenCenter.x, ScreenCenter.y);

		ballArr.clear();
		linkArr.clear();

		Random random;

		ballArr.push_back(
			new Ball(vf2d(0.5, 0.1) * ScreenEdge,
				vf2d(0, 0),
				true,
				4,
				WHITE)
		);

		ballArr.push_back(
			new Ball(vf2d(0.6, 0.1) * ScreenEdge,
				vf2d(0, 0),
				false,
				4,
				WHITE)
		);

		ballArr.push_back(
			new Ball(vf2d(0.6, 0.1) * ScreenEdge,
				vf2d(0, 0),
				false,
				4,
				WHITE)
		);

		ballArr.push_back(
			new Ball(vf2d(0.6, 0.1) * ScreenEdge,
				vf2d(0, 0),
				false,
				4,
				WHITE)
		);

		ballArr.push_back(
			new Ball(vf2d(0.6, 0.1) * ScreenEdge,
				vf2d(0, 0),
				false,
				4,
				WHITE)
		);

		ballArr.push_back(
			new Ball(vf2d(0.6, 0.1) * ScreenEdge,
				vf2d(0, 0),
				false,
				4,
				WHITE)
		);

		ballArr.push_back(
			new Ball(vf2d(0.6, 0.1) * ScreenEdge,
				vf2d(0, 0),
				false,
				4,
				WHITE)
		);

		ballArr.push_back(
			new Ball(vf2d(0.6, 0.1) * ScreenEdge,
				vf2d(0, 0),
				false,
				4,
				WHITE)
		);

		ballArr.push_back(
			new Ball(vf2d(0.6, 0.1) * ScreenEdge,
				vf2d(0, 0),
				false,
				4,
				WHITE)
		);

		ballArr.push_back(
			new Ball(vf2d(0.6, 0.1) * ScreenEdge,
				vf2d(0, 0),
				false,
				4,
				WHITE)
		);

		ballArr.push_back(
			new Ball(vf2d(0.6, 0.1) * ScreenEdge,
				vf2d(0, 0),
				false,
				4,
				WHITE)
		);

		ballArr.push_back(
			new Ball(vf2d(0.6, 0.1) * ScreenEdge,
				vf2d(0, 0),
				false,
				4,
				WHITE)
		);

		ballArr.push_back(
			new Ball(vf2d(0.6, 0.1) * ScreenEdge,
				vf2d(0, 0),
				false,
				4,
				WHITE)
		);

		ballArr.push_back(
			new Ball(vf2d(0.6, 0.1) * ScreenEdge,
				vf2d(0, 0),
				false,
				4,
				WHITE)
		);

		ballArr.push_back(
			new Ball(vf2d(0.6, 0.1) * ScreenEdge,
				vf2d(0, 0),
				false,
				4,
				WHITE)
		);

		ballArr.push_back(
			new Ball(vf2d(0.6, 0.1) * ScreenEdge,
				vf2d(0, 0),
				false,
				64,
				WHITE)
		);

		linkArr.push_back(
			new Link(ballArr[0], ballArr[1])
		);

		linkArr.push_back(
			new Link(ballArr[1], ballArr[2])
		);

		linkArr.push_back(
			new Link(ballArr[2], ballArr[3])
		);

		linkArr.push_back(
			new Link(ballArr[3], ballArr[4])
		);

		linkArr.push_back(
			new Link(ballArr[4], ballArr[5])
		);

		linkArr.push_back(
			new Link(ballArr[5], ballArr[6])
		);

		linkArr.push_back(
			new Link(ballArr[6], ballArr[7])
		);

		linkArr.push_back(
			new Link(ballArr[7], ballArr[8])
		);

		linkArr.push_back(
			new Link(ballArr[8], ballArr[9])
		);

		linkArr.push_back(
			new Link(ballArr[9], ballArr[10])
		);

		linkArr.push_back(
			new Link(ballArr[10], ballArr[11])
		);

		linkArr.push_back(
			new Link(ballArr[11], ballArr[12])
		);

		linkArr.push_back(
			new Link(ballArr[12], ballArr[13])
		);

		linkArr.push_back(
			new Link(ballArr[13], ballArr[14])
		);

		linkArr.push_back(
			new Link(ballArr[14], ballArr[15])
		);

		for (int i = 0; i < 1000; i++)
		{
			const vf2d pos = vf2d(random.UDoubleRandom(), random.UDoubleRandom()) * ScreenEdge;
			const vf2d vel = (ScreenCenter - pos).perp().norm() * 1000000;
			const bool fixed = false;
			const float radius = random.UDoubleRandom() * 8 + 4;
			const Pixel color = mapToRainbow(random.UDoubleRandom());

			ballArr.push_back(
				new Ball(pos, vel, fixed, radius, color)
			);
		}/**/

		StablizeConstraints(100);
		ClearVelocities();

		FillRect(vf2d(0, 0), ScreenEdge, BLACK);
		FillCircle(ScreenCenter, ScreenRadius, Pixel(50, 50, 50));

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		ClearScreen();

		for (int i = 0; i < SimulationSteps; i++)
		{
			ApplyGravity();
			StablizeConstraints(1);
			UpdatePosition(subElapsedTime);
		}

		Render();

		return true;
	}
};

int main()
{
	Example demo;
	if (demo.Construct(1000, 1000, 1, 1))
		demo.Start();

	return 0;
}