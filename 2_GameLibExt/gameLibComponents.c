#ifdef COMPONENT_SYSTEM
//Generic components from GameLib (script side of c++ classes)

/**
* Parent class for all components created in script.
* Every ScriptComponent is being created in Entity's constructor and may recieve following events
* 1. OnComponentInsert is being called when component is created. This is last event Workbench sents in World Editor edit mode.
* 2. EOnInit is being called after all components have been inserted and if the component registred event mask EV_INIT
* 3. EOnActivate is being called if the entity was flaged as TFL_ACTIVE and if the component is active. The component is active by default.
* 4. EOnXXXs are being called base on event mask component registred
* 5. EOnComponentRemove is being called after a component is removed.
* 6. EOnDelete is being called after entity is going to be destroyed.
*/
class ScriptComponent
{
	/**
	* Gets current eventmask. Component accepts only events which has set bits in eventmask.
	* \return Returns bitmask of events the component accepts
	*/
	proto native int GetEventMask();
	
	/**
	* Sets eventmask. Component accepts only events which has set bits in eventmask.
	* Bits are or'ed with existing bitmask. See enf::EntityEvents.
	* \param mask Mask of those bits, which will be set.
	* \return Returns bitmask of events the component accepts (result of mask|GetEventMask())
	*/
	proto native int SetEventMask(IEntity owner, int mask);
	
	/**
	* Clears bitmask. Component accepts only events which has set bits in eventmask.
	* Only bits set in the mask are cleared. See enf::EntityEvents
	* \param mask Mask of those bits, which will be cleared.
	* \return returns these bits that were set before and now are cleared.
	*/
	proto native int ClearEventMask(IEntity owner, int mask);

	/**
	* Activate component and calls EOnActivate().
	*/
	proto native void Activate();

	/**
	* Deactivate component and calls EOnDectivate().
	*/
	proto native void Deactivate();

	/*
	Event when owner entity is touched
	\param owner
	Touched entity
	\param extra
	Bitmask of touch types TODO
	*/
	private void EOnTouch(IEntity owner, int extra);

	/*!
	Event after component is initialized. At this point all entity's components have recieved OnComponentInsert.
	\param owner
	\param extra
	Number of entity
	*/
	private void EOnInit(IEntity owner, int extra);

	/*!
	Extra event of various functional extensions. ATM it's used
	by Trigger when some insider is leaving
	\param owner
	owner actor of event
	\param extra
	Extra value of event
	*/
	private void EOnExtra(IEntity owner, int extra);

	/*!
	Event when we are out of visibility
	\param owner
	\param extra
	Frame number
	*/
	private void EOnNotVisible(IEntity owner, int extra);

	/*!
	Event when we are visible
	\param owner
	\param extra
	Frame number
	*/
	private void EOnVisible(IEntity owner, int extra);

	/*!
	Event every frame
	\param owner
	\param timeSlice
	Time passed since last frame
	*/
	private void EOnFrame(IEntity owner, float timeSlice);

	/*!
	Even after physics update
	\param owner
	\param extra
	Frame number
	*/
	private void EOnPostFrame(IEntity owner, int extra);

	/*!
	Event from animation system
	\param owner
	\param extra
	extra data
	*/
	private void EOnAnimEvent(IEntity owner, AnimEvent extra);

	/*!
	Event from sound system
	\param owner
	\param extra
	extra data
	*/
	private void EOnSoundEvent(IEntity owner, SoundEvent extra);

	/*!
	Event after simulated by physics engine (once per frame)
	\param owner
	\param timeslice
	Time slice of simulation step
	*/
	private void EOnPostSimulate(IEntity owner, float timeslice);

	/*!
	Event before simulated by physics engine (called from sub-iterations!
	\param owner
	\param timeslice
	Time slice of simulation step
	*/
	private void EOnSimulate(IEntity owner, float timeslice);

	/*!
	Event when joint attached to RigidBody of this entity is broken
	\param owner
	owner Entity attached to the joint
	\param extra
	Not used ATM
	*/
	private void EOnJointBreak(IEntity owner, int extra);
	/*!
	Event when physics engine has moved with this Entity
	\param owner
	World Entity
	\param extra
	Not used ATM
	*/
	private void EOnPhysicsMove(IEntity owner, int extra);

	/*!
	Event when physics engine registered contact with owner RigidBody
	\param owner
	\param contact
	Structure describing the contact
	*/
	private void EOnContact(IEntity owner, Contact extra);

	/**
    * Event when component is activated.
    */
    private void EOnActivate();

    /**
    * Event when component is deactivated.
    */
    private void EOnDeactivate();

	/*!
	Event when a component is created and added to Entity.
	\param owner Entity into which component is added
	\param other Component which is being added into Entity
	*/
	private void OnComponentInsert(IEntity owner, ScriptComponent other);

	/*!
	Event when a component is being removed from Entity.
	\param owner Entity from which component is being removed
	\param other Component which is being removed from the Entity
	*/
	private void OnComponentRemove(IEntity owner, ScriptComponent other);

	/*!
	Called when Entity is beaing to be destroyed (deleted).
	\param owner Entity which is being destroyed
	*/
	private void OnDelete(IEntity owner);
}
#endif