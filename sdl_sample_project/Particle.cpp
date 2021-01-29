#include "Particle.h"
#include<stdlib.h>
#include <iostream>
#include <random>
#include <math.h>
#include "Screen.h"
#include<assert.h>

using namespace std;

Particle::Particle():
	m_x(0),m_y(0)
{
	//m_x = ((2.0 * rand()) / RAND_MAX) - 1;
	//m_y = ((2.0 * rand()) / RAND_MAX) - 1;
	init();
	
}

void Particle::init()
{
	m_x = 0;
	m_y = 0;
	m_direction = (2 * M_PI *rand()) / RAND_MAX;
	m_speed = (0.04 * rand()) / RAND_MAX;

	m_speed *= m_speed;
}

void Particle::Update(int interval)
{
	
	m_direction += interval * 0.0003;

	//if (m_x <= -1.0) {
	//	directionx = -1 * directionx;

	//}
	//if (m_x >= 1.0) {
	//	directionx = -1 * directionx;
	//}

	//if (m_y <= -1.0) {
	//	directiony = -1 * directiony;

	//}
	//if (m_y >= 1.0) {
	//	directiony = -1 * directiony;
	//}

	double xspeed = m_speed * cos(m_direction) * directionx;
	double yspeed = m_speed * sin(m_direction) * directiony;

	m_x += xspeed * interval;
	m_y += yspeed * interval;

	//m_x = (m_x >= 1.0) ? 1.0 : m_x;
	//m_x = (m_x <= -1.0) ? -1.0 : m_x;
	//m_y = (m_y >= 1.0) ? 1.0 : m_y;
	//m_y = (m_y <= -1.0) ? -1.0 : m_y;

	if (m_x < -1 || m_x > 1 || m_y < -1 || m_y > 1)
	{
		init();
	}

	if (rand() < RAND_MAX/100)
	{
		init();
	}
	
}


