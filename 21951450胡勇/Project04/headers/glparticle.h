#include "base.h"
class glParticleSystem;

struct glParticle
{
	vec3    m_pos;
	vec3    m_prevPos;
	vec3    m_velocity;
	vec3    m_acceleration;
	float   m_energy;

	float   m_size;
	float   m_sizeDelta;

	float   m_weight;
	float   m_weightDelta;

	float   m_color[4];
	float   m_colorDelta[4];
};


class glParticleSystem
{
public:

	glParticleSystem(int maxParticles, vec3 origin);

	virtual ~glParticleSystem() { KillSystem(); }

	virtual void  Update(float elapsedTime) = 0;
	virtual void  Render() = 0;

	virtual int   Emit(int numParticles);

	virtual void  InitializeSystem();
	virtual void  KillSystem();

protected:
	//���麯��������override
	virtual void  InitializeParticle(int index) = 0;

	//ָ��ָ��glParticle�����׵�ַ
	//���� = m_maxParticles
	//��������ϵͳ�����������С���������Ԥ�ȷ����ڴ淽ʽ���Ч��
	glParticle    *m_particleList;

	//�����Բ�������������
	int            m_maxParticles;

	//��ǰ����������
	int            m_numParticles;

	//���ӷ�����λ������
	vec3           m_origin;

	float          m_accumulatedTime;

	vec3           m_force;
};