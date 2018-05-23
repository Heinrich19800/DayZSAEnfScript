class Hit_Wood : EffBulletImpactBase
{
	void Hit_Wood()
	{
		SetEnterParticle(ParticleList.IMPACT_WOOD_ENTER);
		SetExitParticle(ParticleList.IMPACT_WOOD_EXIT);
		SetRicochetParticle(ParticleList.IMPACT_WOOD_RICOCHET);
	}
}