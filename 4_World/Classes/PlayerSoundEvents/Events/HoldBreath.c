class HoldBreathSoundEvent extends PlayerSoundEventBase
{
	void HoldBreathSoundEvent()
	{
		EPlayerSoundEventType m_Type = EPlayerSoundEventType.GENERAL;
		m_ID = EPlayerSoundEventID.HOLD_BREATH;
		m_SoundSetNameRoot = "holdBreath";
	}
}


class ReleaseBreathSoundEvent extends PlayerSoundEventBase
{
	void ReleaseBreathSoundEvent()
	{
		EPlayerSoundEventType m_Type = EPlayerSoundEventType.GENERAL;
		m_ID = EPlayerSoundEventID.RELEASE_BREATH;
		m_SoundSetNameRoot = "releaseBreath";
	}
}