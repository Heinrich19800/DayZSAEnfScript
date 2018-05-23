class Hit_MeatBones_MeleeShovel : Hit_MeatBones
{
	void Hit_MeatBones_MeleeShovel()
	{
		SetEnterParticle(ParticleList.IMPACT_MEATBONES_ENTER);
	}
	
	override void OnPlay()
	{
		/*
		vector pos = GetPosition() + "0 0.5 0";
		Print( pos );
		GetGame().CreateObject("VomitBloodGround", pos, true);
		*/
	}
}