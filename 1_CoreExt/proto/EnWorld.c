/**																																											 /**
 * \defgroup World World API definition
 * @{
 */

//----------------------------------------------
/**
 * \defgroup WorldCommon World
 * @{
 */

typedef int[] WorldHandle;

proto native float GetWorldTime();

/*!nastavi aktualni world. Umozni tim pracovat s entitama i mimo obdobi zpracovani worldu
//vraci predchozi aktualni world
*/
proto native WorldHandle SetCurrentWorld(WorldHandle world);

proto native IEntity FindEntityByName(IEntity worldEnt, string name);
proto native IEntity FindEntityByID(IEntity worldEnt, int ID);

//!returns number of active (simulated) Entities in the world
proto native int GetNumActiveEntities(IEntity worldEntity);
//!returns active entity
proto native IEntity GetActiveEntity(IEntity worldEntity, int index);
//@}

//----------------------------------------------
/**
 * \defgroup Camera Camera
 * @{
 */

enum CameraType
{
	PERSPECTIVE,
	ORTHOGRAPHIC
};

//!urcuje ze ktere kamery se bude brat pozice posluchace pro zvukovy engine
proto native void SetListenerCamera(int camera);

/*!
zmeni pozici kamery
\param cam Index of camera
\param origin	pozice kamery
\param angle	uhly kamery
*/
proto native void SetCamera(int cam, vector origin, vector angle);

//!zmeni pozici kamery matici
proto native void SetCameraEx(int cam, const vector mat[4]);

//!Returns current camera transformation
proto native void GetCamera(int cam, out vector mat[4]);

proto native void SetCameraVerticalFOV(int cam, float fovy);
proto native void SetCameraFarPlane(int cam, float farplane);		//default 160000 units
proto native void SetCameraNearPlane(int cam, float nearplane);	//default 5 units

proto native void SetCameraType(int cam, CameraType type);

//ent can be NULL for world-space coords
proto vector	ProjectVector(int cam, Class ent, vector vec);
proto vector	UnprojectVector(int cam, float x, float y, vector dir);

//@}

//----------------------------------------------
/**
 * \defgroup Light Light API
 * @{
 */

//!Light handle
typedef int[] HLIGHT;

enum LightType
{
	POINT, //<bodovy zdroj svetla, siri se vsemi smery
	SPOT,	//<			- orientovany zdroj svetla, smer se ridi uhly entity 'owner'
	DIRECTIONAL,
	AMBIENT
};

enum LightFlags
{
/*!
Dynamic light. There is limit 512 dynamic lights per world and
32 per camera view. They are faster when moving and changing shape.
Also they are always attached to owner entity
*/
	DYNAMIC, 
	CASTSHADOW,
//! for cheaper dynamic lights, like muzzle flashes (might use cheaper rendering method)
	CHEAP
};

/*!
creates light
*/
proto HLIGHT AddLight(IEntity owner, LightType type, LightFlags flags, float radius, vector color);
//!removes light
proto native bool RemoveLight(HLIGHT light);
proto native bool SetLightEx(HLIGHT light, float radius, vector color);
//!sets lookup texture for projection lights
proto native bool SetLightTexture(HLIGHT light, string cubemap);
proto native int SetLightFlags(HLIGHT light, LightFlags flags);
proto native int ClearLightFlags(HLIGHT light, LightFlags flags);
//!Sets light cone in degrees (for LightType.SPOT).
proto native bool SetLightCone(HLIGHT light, float cone);
//@}


//----------------------------------------------
/**
 * \defgroup WorldTrace Trace&Visibility API
 * @{
 */

enum TraceFlags
{
	BONES, //<testuje kolizni obalky kolem kosti animovanych objektu
	ENTS, //<testuje i entity
	LINE,
	WORLD, //<testuje i world-bounds
	ONLY_PHYSICS,
	WATER, //< testuje kolize s vodni hladinou
	PASSTRANSLUCENT,//< Do not intersects with entities with EntityFlags.TRANSLUCENT set
	RAGDOLLS, //<testuje ragdolly
	VISTEST, //<provadi nejprve visibility test. Zbytecne u entit pri EntityEvent.VISIBLE -> kamera (zde uz je jistota, ze podle visibility je viditelna)
	NOTRACE,
	TRANSPARENT_OCCLUDERS
};

//!kolize a trasovani
class TraceContact
{
	float	Fraction;
	int		Content;
	int		Surfparm;
	int		MaterialFlags;
	int		Triangle;
	int		SurfaceID;
	owned string	MaterialName;
	owned string	OriginalMaterialName;
	float		Plane[4];
	vector	Point;
}

proto native bool TraceLineToEntity(IEntity ent, vector start, vector end, out TraceContact contact);

/*!
trasuje primku start->end, vraci 0..1 pokud kolize. do end se uklada posledni pozice
// z ent se zjistuje bbox
//jeste pribydou flagy jako u P2PVisibilityEx
\param ent		Entita se kterou se pohybuje po primce
\param start	Odkud
\param end		Kam
//OUTPUT:
\param cent		vraci entitu, se kterou se srazila
\param plane	vraci plane polygonu se kterym se srazila (X,Y,Z,D)
\param content	obsah prostoru, se kterym se srazila
\param surfparm	parametry surfacu, se kterym se srazila
\returns	hodnota 0...1, kolik procent drahy urazila
*/
proto float 	TraceLine(IEntity ent,vector start,vector end, out Class cent, out float plane[4], out int content, out int surfparm);

//bool FilterCallback(Class target [, vector rayorigin, vector raydirection])
proto volatile float TraceLineEx(vector start,vector end, vector mins, vector maxs, out IEntity cent, out float plane[4], out int content, out int surfparm, TraceFlags flags, func filtercallback, int layerMask);


//pomocne globalni fce pri TraceLine(Ex)
// g_iTraceSphere	obsahuje zasazenou hitsphere X objektu
// g_iTraceBone	obsahuje zasazenou kost X objektu
//g_iTraceBrush
//g_iTraceSurfaceType


/*!
zjistuje viditelnost
\param from		-		odkud
\param to			-		kam
\param flags
//TraceFlags.VISTEST	- 
//TraceFlags.DETAIL		- testuje proti detailnim brushum
//TraceFlags.ENT			- testuje proti brush entitam
//TraceFlags.NOTRACE	- netestuje geometrii (ma smysl ve spojeni s TraceFlags.VISTEST)
\returns		true je videt/false neni videt
*/
proto native int P2PVisibilityEx(vector from, vector to,int flags);

//!najde vsechny entity v radiusu.
proto int SphereQuery(vector origin, float radius, out IEntity visents[], int ents, int fmask);

/*!zjisti, jestli je bbox viditelny, podle view-frustum a PVS
\param flags & 1 - testuje i PVS
\returns true/false je videt/neni videt
*/
proto native bool IsBoxVisible(vector mins, vector maxs, int flags);

/*!najde vsechny viditelne entity (jen nahrubo,podle visibility. Je vhodne po vyberu entit, ktere nas zajima vyzkouset jeste preciznejsi metody viditelnosti)
\param origin		-		misto ze ktereho se "koukame"
\param look		-		kterym smerem se kouka
\param angle		-		zorny uhel (dava se tak 90). -1 pokud nas zorny uhel nezajima
\param ents		-		pole int, libovolne velikosti
\param maxents	-		velikost pole (zamezeni preteceni pole)
\param fmask		-		maska flagu (SetFlags()). Hledana entita musi mit nastaveny vsechny uvedene flagy
						s vyhodou lze pouzit rezervovane flagy EntityFlags.USER1, EntityFlags.USER2, EntityFlags.USER6 pro rychle
						nalezeni konkretni kategorie entit
*/
proto int		VisEntities(vector origin, vector look, float angle, float radius, out IEntity ents[2], int maxents, int fmask);

/*!
Object that handles visibility on GPU. Used for coronas etc.
*/
class OcclusionQuery
{
	proto private void ~OcclusionQuery();

	/*!
	vraci vysledek Query
	\returns  -1 vysledek jeste neni k dispozici. Zkus to o frame pozdeji
  >0 bod je videt
 ==0 bod je neviditelny
	*/
	proto native int GetResult();

	//!Sets world position
	proto native void SetPosition(vector pos);
	//!Destroys the object
	proto native void Destroy();
};

//@}

//----------------------------------------------
/**
 * \defgroup Decals Decals API
 * @{
 */
typedef int[] hDecal;

/*!
Creates single visual mark, e.g. from shots
//when lifetime=0, pointer to decal is returned, that can be removed by RemoveDecal then
\param entity		entity where the landmark should be created
\param origin		first point of the decal, nothing is done now
\param project	projection direction (length is far clipping distance)
\param nearclip	near clipping distance
\param materialName Material used for decal
\param lifetime	Lifetime in seconds
\param flags Not used ATM
\return Decal pointer or null
*/
proto native hDecal CreateDecal(IEntity entity, vector origin, vector project, float nearclip, float angle, float size, string materialName, float lifetime, int flags);

proto native void RemoveDecal(hDecal decal);

/*!
Creates continous visual mark, e.g. from wheel when a car is moving on the ground
\param entity		entity where the landmark should be created (only terrain is supported ATM)
\param origin		first point of the decal, nothing is done now
\param normal		normal of surface
\param edgesize	Edge size of decal
\param lifetime	Lifetime in seconds
\param materialName Material used for decal
\param prev			Previous decal, we are connecting to
\param alpha		translucency of point
\return Decal pointer or null
*/
proto native hDecal CreateLandMarkDecal(IEntity entity, vector origin, vector normal, float edgeSize, float lifeTime, string materialName, hDecal prevDecal, float alpha);


/*!
is it possible to add new point to landmark decal?
\param lmDecal		entity to add new landmark point
\param entity		entity to add new landmark point
\param mat			material of decal
\param newpoint 	new point to add
\return
	LMD_ERROR 	= error when adding new point (invalid decal)
	LMD_VALID 	= can add new point
	LMD_DIFF_ENT 	= new point is on different entity
	LMD_TOO_FAR	= new point is too far from previous point
*/
proto native int CanAddToLandMarkDecal(hDecal lmDecal, IEntity entity, string mat, vector newPoint);

/*!
add new point to decal, internally, new point is added when previous point is in some
distance or the angle is more than some threshold
\param lmDecal		entity to add new landmark point
\param point		contact point
\param normal		normal of contact
\param alpha		translucency in point
\return true if everything was OK, false if not. In this case, the application MUST not used later the pointer to decal, it's finalized internally !
*/
proto native bool AddPointToLandMarkDecal(hDecal lmDecal, vector point, vector normal, float alpha);

/*!
finalize landmark adding, e.g. when entity lose contact with ground -> the pointer to decal
should have only world and entity if it has something to render, otherwise it's destroyed here
\param lmDecal		entity to add new landmark point
\param addAlpha	if to add last point with transition to zero alpha
\param alphaDist	distance to add last point
*/
proto native void FinalizeLandMarkDecal(hDecal lmDecal, bool addAlpha, float alphaDist);

/*!
return if landmark was finalized
\param lmDecal		decal to test
*/
proto native bool IsLandMarkFinalized(hDecal lmDecal);

/*!
return last landmark point or -65535.0 in all components
\param lmDecal		decal to test
*/
proto native vector GetLastLandMarkPoint(hDecal lmDecal);

/*!
set global parameters for landmark generation
\param minSegmentLength		minimum length segment, when new point is added (4 default), when is less, just the end position is on the fly updated
\param maxSegmentLength		maximum segment length, when length is bigger, the path is finished
\param degAngle				angle in degrees, when is more, the path is finished
*/
proto native void SetGlobalLandMarkParams(float minSegmentLength, float maxSegmentLength, float degAngle);


//@}

//@}
 
