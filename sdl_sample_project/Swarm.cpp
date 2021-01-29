#include "Swarm.h"
#include "Particle.h"
#include <iostream>
using namespace std;

Swarm::Swarm():
	lastTime(0)
{
	m_pParticles = new Particle[nParticles];
}

Swarm::~Swarm()
{
	delete[] m_pParticles;
}

void Swarm::Update(int elapsed)
{
	int interval = elapsed - lastTime;
	for (int i = 0; i < nParticles; i++) {
		m_pParticles[i].Update(interval);
	}
	lastTime = elapsed;
}

Particle * const Swarm::particles()
{
	return m_pParticles;
}
