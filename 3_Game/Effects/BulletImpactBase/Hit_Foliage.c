class Hit_Foliage : EffBulletImpactBase
{
	void Hit_Foliage()
	{
		SetEnterParticle(ParticleList.IMPACT_FOLIAGE_ENTER);
		SetExitParticle(ParticleList.IMPACT_FOLIAGE_EXIT);
		SetRicochetParticle(ParticleList.IMPACT_FOLIAGE_RICOCHET);
	}
}