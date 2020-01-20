#include "../headers/glparticle.h"
glParticleSystem::glParticleSystem(int maxParticles, vec3 origin)
{
	//��¼���������ԭʼ����
	m_maxParticles = maxParticles;
	m_origin = origin;
	m_particleList = NULL;
	m_numParticles = 0;
	m_accumulatedTime = 0.0f;
}

int glParticleSystem::Emit(int numParticles)
{
	//����������಻�ܳ���m_maxParticles
	while (numParticles && (m_numParticles < m_maxParticles))
	{

		InitializeParticle(m_numParticles++);
		--numParticles;
	}

	return numParticles;
}



void glParticleSystem::InitializeSystem()
{
	if (m_particleList)
	{
		delete[] m_particleList;
		m_particleList = NULL;
	}

	m_particleList = new glParticle[m_maxParticles];

	m_numParticles = 0;
	m_accumulatedTime = 0.0f;
}

void glParticleSystem::KillSystem()
{
	if (m_particleList)
	{
		delete[] m_particleList;
		m_particleList = NULL;
	}

	m_numParticles = 0;
	m_accumulatedTime = 0.0f;
}