class EffBulletImpactBase : Effect
{
	float 		m_stopping_force
	int 		m_impact_type
	vector 		m_pos
	vector 		m_surfNormal
	vector 		m_exitPos
	vector 		m_inSpeed
	vector 		m_outSpeed
	string 		m_ammoType
	
	static vector INVALID = "0 0 0";
	
	// Particle Effects
	int m_ParticleEnter = -1;
	int m_ParticleExit = -1;
	int m_ParticleRicochet = -1;
	
	// Calculations
	float m_EnterSplashCoef = 0.01;
	float m_ExitSplashCoef = 0.05;
	float m_RicochetSplashCoef = 0.02;
	float m_EnterAngledSplashCoef = 0.015;
	float m_AngledEnter = 0.40;
	
	void EffBulletImpactBase()
	{
		
	}
	
	void SetEnterParticle(int id)
	{
		m_ParticleEnter = id;
	}
	
	void SetExitParticle(int id)
	{
		m_ParticleExit = id;
	}
	
	void SetRicochetParticle(int id)
	{
		m_ParticleRicochet = id;
	}
	
	void SetAngledEnterValue(float f)
	{
		m_AngledEnter = f;
	}
	
	void EvaluateEffect(vector pos, int impact_type, vector surfNormal, vector exitPos, vector inSpeed, vector outSpeed, string ammoType)
	{
		m_pos = pos;
		m_impact_type = impact_type;
		m_surfNormal = surfNormal;
		m_exitPos = exitPos;
		m_inSpeed = inSpeed;
		m_outSpeed = outSpeed;
		m_ammoType = ammoType;
		
		m_stopping_force = CalculateStoppingForce(m_inSpeed.Length(), m_outSpeed.Length(), ammoType);
	}
	
	float CalculateStoppingForce(float in_speedf, float out_speedf, string ammoType)
	{
		if ( m_impact_type == ImpactTypes.MELEE )
		{
			return 500;
		}
		
		return in_speedf - out_speedf;
	}
	
	void OnEnterCalculations( Particle p )
	{
		float velocity_rnd = m_stopping_force * m_EnterSplashCoef;
		float birth_rate_rnd = m_stopping_force;
		
		p.SetParameter(-1, EmitorParam.VELOCITY_RND, velocity_rnd);
		p.SetParticleParam(EmitorParam.VELOCITY_RND, velocity_rnd);
		p.SetParticleParam(EmitorParam.BIRTH_RATE_RND, birth_rate_rnd);
		p.IncrementParticleParam(EmitorParam.BIRTH_RATE, birth_rate_rnd);
	}
	
	void OnExitCalculations(Particle p, float outSpeedf)
	{
		float velocity_rnd = outSpeedf * m_ExitSplashCoef;
		float birth_rate_rnd = outSpeedf;
		
		p.SetParticleParam(EmitorParam.VELOCITY_RND, velocity_rnd);
		p.SetParticleParam(EmitorParam.BIRTH_RATE_RND, birth_rate_rnd);
		p.IncrementParticleParam(EmitorParam.BIRTH_RATE, birth_rate_rnd);
	}
	
	void OnRicochetCalculations(Particle p, float outspeedf)
	{
		float velocity_rnd_def = m_stopping_force * m_RicochetSplashCoef;
		float birth_rate_rnd_def = m_stopping_force;
		
		p.SetParticleParam(EmitorParam.VELOCITY_RND, velocity_rnd_def);
		p.SetParticleParam(EmitorParam.BIRTH_RATE_RND, birth_rate_rnd_def);
		p.IncrementParticleParam(EmitorParam.BIRTH_RATE, birth_rate_rnd_def);
	}
	
	void OnEnterAngledCalculations(Particle p)
	{
		float velocity_rnd_def2 = m_stopping_force * m_EnterAngledSplashCoef;
		float birth_rate_rnd_def2 = m_stopping_force;
		
		p.SetParticleParam(EmitorParam.VELOCITY_RND, velocity_rnd_def2);
		p.SetParticleParam(EmitorParam.BIRTH_RATE_RND, birth_rate_rnd_def2);
		p.IncrementParticleParam(EmitorParam.BIRTH_RATE, birth_rate_rnd_def2);
	}
	
	override void OnPlay()
	{
		Particle p;
		vector particle_orientation;
		float outSpeedf = m_outSpeed.Length();
		
		if ( m_impact_type == ImpactTypes.RICOCHET )
		{
			p = Particle.Play(m_ParticleRicochet, m_pos);
			
			if (p)
			{
				particle_orientation = m_outSpeed.VectorToAngles();
				particle_orientation = particle_orientation + "0 -90 0";
				p.SetOrientation(particle_orientation);
				
				OnRicochetCalculations(p, outSpeedf);
			}
		}
		else
		{
			p = Particle.Play(m_ParticleEnter, m_pos );
			
			if (p)
			{
				if (m_surfNormal != INVALID)
				{
					particle_orientation = m_surfNormal.VectorToAngles();
					particle_orientation = particle_orientation + "0 270 0";
				}
				else
				{
					particle_orientation = "0 0 0"; // This vector is in angles
				}
				
				p.SetOrientation(particle_orientation);
			
				OnEnterCalculations(p);
			}
			
			if (outSpeedf > 0  &&  m_surfNormal != INVALID)
			{
				p = Particle.Play(m_ParticleExit, m_exitPos);
				
				if (p)
				{
					particle_orientation = m_outSpeed.VectorToAngles();
					particle_orientation = particle_orientation + "0 -90 0";
					p.SetOrientation(particle_orientation);
					
					OnExitCalculations(p, outSpeedf);
				}
			}
			else
			{
				if (m_surfNormal != INVALID)
				{
					vector surfNormalN = m_surfNormal.Normalized();
					vector inSpeedN = m_inSpeed.Normalized();
					vector bounce_ori = surfNormalN + inSpeedN;
					
					float dot = vector.Dot(bounce_ori, surfNormalN);
					
					if ( dot > m_AngledEnter )
					{
						p = Particle.Play(m_ParticleRicochet, m_pos);
			
						if (p)
						{
							particle_orientation = bounce_ori.VectorToAngles();
							particle_orientation = particle_orientation + "0 -90 0";
							p.SetOrientation(particle_orientation);
							
							OnEnterAngledCalculations(p);
						}
					}
				}
			}
		}
		
		if (p)
		{
			p.SetEffectHolder(this);
		}
	}
}