//Generic entities from GameLib (script side of c++ classes)

#ifdef COMPONENT_SYSTEM
class GenericEntity extends IEntity
{
	//native method implemented on c++ side
	proto native void Show(bool show);
}

class GenericWorldEntity extends GenericEntity
{
}

class GenericTerrainEntity extends GenericEntity
{
}

class GenericWorldLightEntity extends GenericEntity
{
}

class GenericWeapon extends GenericEntity
{	
}

class BasicEntity extends GenericEntity
{
}

class WorldEntityClass
{
}

class WorldEntity extends GenericWorldEntity
{
}

class ModelEntity extends BasicEntity
{
}

class BasicCamera extends BasicEntity
{
}
#endif