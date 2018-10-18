class EffVomit : EffectParticle
{
	Object m_Character;
	
	void EffVomit()
	{
		SetParticleID(ParticleList.VOMIT);
//		SetSoundName("Action_Vomitting_0");
	}
	
	void SetDecalOwner(Object o)
	{
		m_Character = o;
	}
	
	override void Event_OnStarted()
	{
		// Uncomment this to spawn fake decal of vomit on ground.
		/*
		vector pos = m_Character.GetPosition();
		vector ori = m_Character.GetOrientation();
		
		Particle p = Particle.Play(ParticleList.VOMIT_CHUNKS, pos);
		p.SetOrientation(ori);
		*/
	}
}