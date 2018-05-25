class Hit_MeatBones : EffBulletImpactBase
{
	void Hit_MeatBones()
	{
		SetEnterParticle(ParticleList.IMPACT_MEATBONES_ENTER);
		SetExitParticle(ParticleList.IMPACT_MEATBONES_EXIT);
		//SetRicochetParticle(ParticleList.IMPACT_MEATBONES_RICOCHET);
		
		m_AngledEnter = 0;
		m_EnterSplashCoef = 0.003;
		m_ExitSplashCoef = 0.02;
	}
	
	override float CalculateStoppingForce(float in_speedf, float out_speedf, string ammoType)
	{
		if ( m_impact_type == ImpactTypes.MELEE )
		{
			return 500;
		}
		
		return in_speedf;
	}

	override void OnPlay()
	{
		super.OnPlay();
		
		if (m_impact_type != ImpactTypes.MELEE)
		{
			vector in_speed = m_inSpeed*(-1); // Compiler demands this variable
			
			BloodSplatGround( GetPosition(), in_speed , 0.5 );
			
			if (m_outSpeed.Length() > 0)
			{
				BloodSplatGround( m_exitPos, m_outSpeed, 0.8  );
			}
		}
	}
	
	void BloodSplatGround( vector start_pos, vector speed_vector, float decay_coef )
	{
		vector pos = start_pos;
		float power = m_stopping_force;
		float upscale = 0;
		
		while (power > 250)
		{
			pos = pos + ( speed_vector * 0.001 );
			pos[1] = GetGame().SurfaceY(pos[0], pos[2]);
			Print( pos );
			Particle blood = Particle.Play(ParticleList.BLOOD_SURFACE_DROPS, pos); // BLOOD_SURFACE_DROPS IMPACT_TEST_ENTER_DEBUG

			// TO DO: Align to surface			
			//vector ori = GetGame().GetSurfaceOrientation(pos[0], pos[2]);
			vector ori = blood.GetOrientation();
			ori[0] = Math.RandomFloat(0, 360);
			
			blood.SetOrientation(ori);
			blood.IncrementParticleParam(EmitorParam.SIZE, upscale);
			
			Particle blood_chunks = Particle.Play(ParticleList.BLOOD_SURFACE_CHUNKS, pos);
			blood_chunks.SetOrientation(ori);
			
			power = power * decay_coef;
			upscale += 0.12;
		}
	}
	
	// TO DO: Some of the following calculations must be commented out to avoid issue with DAYZ-31222!
	
	override void OnEnterCalculations( Particle p )
	{
		
		float velocity_rnd = m_stopping_force * m_EnterSplashCoef;
		float birth_rate_rnd = m_stopping_force;
		
		vector camera_pos = GetGame().GetCurrentCameraPosition();
		float distance = vector.Distance(camera_pos, m_pos);
		float scaling = m_stopping_force*0.00035 + distance*0.01;
		
		p.ScaleParticleParam(EmitorParam.SIZE, scaling * 5);
		p.IncrementParticleParam(EmitorParam.VELOCITY_RND, velocity_rnd);
		
		/*
		p.SetParticleParam(EmitorParam.BIRTH_RATE_RND, birth_rate_rnd);
		p.IncrementParticleParam(EmitorParam.BIRTH_RATE, birth_rate_rnd);*/
		
	}
	
	override void OnExitCalculations(Particle p, float outSpeedf)
	{
		
		float velocity_rnd = outSpeedf * m_ExitSplashCoef;
		float birth_rate_rnd = outSpeedf;
		Print(velocity_rnd);
		p.SetParticleParam(EmitorParam.VELOCITY_RND, velocity_rnd);
		//p.SetParticleParam(EmitorParam.BIRTH_RATE_RND, birth_rate_rnd);
		//p.IncrementParticleParam(EmitorParam.BIRTH_RATE, birth_rate_rnd);
		
	}
	
	/*override void OnRicochetCalculations(Particle p, float outSpeedf)
	{
		
		float velocity_rnd_def = m_stopping_force * m_RicochetSplashCoef;
		float birth_rate_rnd_def = m_stopping_force;
		
		p.SetParticleParam(EmitorParam.VELOCITY_RND, velocity_rnd_def);
		p.SetParticleParam(EmitorParam.BIRTH_RATE_RND, birth_rate_rnd_def);
		p.IncrementParticleParam(EmitorParam.BIRTH_RATE, birth_rate_rnd_def);
		
	}*/
	
	/*override void OnEnterAngledCalculations(Particle p)
	{
		
		float velocity_rnd_def2 = m_stopping_force * m_EnterAngledSplashCoef;
		float birth_rate_rnd_def2 = m_stopping_force;
		
		p.SetParticleParam(EmitorParam.VELOCITY_RND, velocity_rnd_def2);
		p.SetParticleParam(EmitorParam.BIRTH_RATE_RND, birth_rate_rnd_def2);
		p.IncrementParticleParam(EmitorParam.BIRTH_RATE, birth_rate_rnd_def2);
		
	}*/
}