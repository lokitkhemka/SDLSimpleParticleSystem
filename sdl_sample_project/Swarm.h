#pragma once
#include "Particle.h"
class Swarm
{
public:
	static const int nParticles = 5000;
private:
	Particle * m_pParticles;
	int lastTime;
public:
	Swarm();
	virtual ~Swarm();
	void Update(int elapsed);
	Particle * const particles();
};

