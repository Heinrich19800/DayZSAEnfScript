class Hit_Undefined : EffBulletImpactBase
{
	void Hit_Undefined()
	{
		SetEnterParticle(ParticleList.IMPACT_TEST);
		SetExitParticle(ParticleList.IMPACT_TEST_RICOCHET);
		SetRicochetParticle(ParticleList.IMPACT_TEST_RICOCHET);
	}
}