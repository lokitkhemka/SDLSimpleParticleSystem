#pragma once
class Particle
{
public:
	double m_x, m_y;
	double m_speed;
	double m_direction;
	int directionx = 1;
	int directiony = 1;

public:
	Particle();
	//virtual ~Particle();
	void Update(int interval);
	void init();
};

