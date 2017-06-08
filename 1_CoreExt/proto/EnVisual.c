/**
 * \defgroup Visual Visual objects
 * @{
 */

//!Loads object from data, or gets it from cache. Object must be released when not used
proto native vobject GetObject(string name);

/*!
Release object. When there are not any other references, object is stored into cache and ready to be victed if necessary.
\param object Object handle
\param flag If RF_RELEASE is used, the object is evicted immediatelly, if not used by anyone else
*/
proto native void ReleaseObject(vobject object, int flag = 0);

//!Returns number of frames, if the object is animation
proto native int GetNumAnimFrames(vobject anim);

//!Returns name of visual object
proto string vtoa(vobject vobj);

/**
 * \defgroup MeshObject Mesh object (XOB)
 * @{
 */

proto int GetObjectMaterials(vobject object, string materials[]);

// specialitka, aby se daly delat dynamicky triggery
//proto void CreateModel(IEntity ent, vector mins, vector maxs);
//proto void RemoveModel(IEntity ent);

//Dynamic MeshObject
proto vobject CreateXOB(int nsurfaces, int nverts[], int numindices[], string materials[]);
proto void UpdateVertsEx(notnull IEntity ent, int surf, vector verts[], float uv[]);
proto void UpdateIndices(vobject obj, int surf, int indices[]);

proto native void	SetBone(notnull IEntity ent, int bone, vector angles, vector trans, float scale);
proto native bool	SetBoneMatrix(notnull IEntity ent, int bone, vector mat[4]);
proto native void	SetBoneGlobal(notnull IEntity ent, int bone, vector mat[4]);
proto native bool	GetBoneMatrix(notnull IEntity ent, int bone, vector mat[4]);
proto native bool	GetBoneLocalMatrix(notnull IEntity ent, int bone, vector mat[4]);

proto native void	SetFrame(notnull IEntity ent, int slot, float frame);

// pokud je v jakemkoliv API pouzito BoneMask == NULL, bere se, ze jsou nastavene vsechny bity
class BoneMask
{
	int Mask[3]
}

#ifdef DOXYGEN
enum AnimSlotFlags
{
	//! animace se prehraje jen jednou, zustane "zamrzla" na poslednim frame a vyvola se EntityEvent.ANIMEND	
	AF_ONCE,
/*! defaultne zustava animace pri prehravani a AF_ONCE po skonceni na posledni frame "zamrzla", dokud neni nahrazena jinou,
 nebo neni kanal vynulovan. Pokud se nastavi AF_BLENDOUT, postara se engine o vyhozeni animace sam a pro preblendovani pouzije hodnotu
 blendout. Pokud je odchycen EOnAnimEnd a byla zmenena animace na jinou, nebo byl kanal rucne vynulovan, tak se tato
 funkcnost neprovede. */
	AF_BLENDOUT,

//! animace stoji na prvnim frame. Snimek se nastavuje rucne pomoci SetFrame
	AF_USER,

//! vynuti nastaveni animace na zacatek a pripadne blend i v pripade, ze ve slotu uz tato animace bezi.
	AF_RESET,

/*! defaultne se bere framerate z anim.def. Pokud tam neni uveden, bere se parametr 'fps'.
Pomoci tohoto flagu je mozne prednostne pouzit parametr 'fps' i prestoze je framerate uveden v anim.def
*/
	AF_FORCEFPS,

//! nevyvola se na konci EntityEvent.ANIMEND
	AF_NOANIMEND,

//! nevyvolaji se animhooky
	AF_NOANIMHOOKS
};
#endif

proto native void	SetAnimSlot(notnull IEntity ent, int slot, vobject anim, float blendin, float blendout, BoneMask mask, int fps, int flags);

//jen zmeni masku, a blendne, pokud je nejaky 'blendin' nastaven
proto native void ChangeAnimSlotMask(notnull IEntity ent, int slot, float blendin, BoneMask mask);

//jen zmeni framerate na hodnotu 'fps'
proto native void ChangeAnimSlotFPS(notnull IEntity ent, int slot, int fps);

//nastavuje masku prehravanych kanalu. Nastavuji se bity 0..3 (kanalu je 12)
proto native void	SetAnimMask(notnull IEntity ent, int mask);

//clearuje masku prehravanych kanalu. Vraci vyclearovane bity
proto native int	ClearAnimMask(notnull IEntity ent, int mask);

//vrati nastavene bity tech kanalu, ktere maji nastavenou animaci, nejsou na konci
// a pro ktere byla nastavena vstupni maska.
//Je tim mozno se dotazat na stav vice slotu najednou
proto native int IsAnimSlotPlaying(notnull IEntity ent, int mask);
//mask - 16bitu, pro 16 anim slotu. Maximalni hodnota je tedy 0xffff!

//sets how much this morph affect object
proto native bool SetMorphState(notnull IEntity ent, string morph, float value);
//morph name
//value 0...1
//@}


/**
 * \defgroup ParticleEffect Particle effect API
 * @{
 */

enum EmitorParam
{
	//! Vector3 R/W
	CONEANGLE,
	
	//! Vector3 R/W
	EMITOFFSET,
	
	//! Float R/W
	VELOCITY,
	
	//! Float R/W
	VELOCITY_RND,
	
	//! Float R/W
	AVELOCITY,
	
	//! Float R/W
	SIZE,
	
	//! Float R/W
	STRETCH,

	//! zacinej s nahodnym natocenim. Bool R/W
	RANDOM_ANGLE,
	
	//! otacej se nahodnym smerem. Bool R/W
	RANDOM_ROT,

	//! Float R/W
	AIR_RESISTANCE,
	
	//! Float R/W
	AIR_RESISTANCE_RND,

	//! Float R/W
	GRAVITY_SCALE,

	//! Float R/W
	GRAVITY_SCALE_RND,
	
	//! Float R/W
	BIRTH_RATE,

	//! Float R/W
	BIRTH_RATE_RND,

	//! Float R/W
	LIFETIME,

	//! Float R/W
	LIFETIME_RND,

	//! Bool R/W
	LIFETIME_BY_ANIM,

	//! Bool R/W
	ANIM_ONCE,

	//! Bool R/W
	RAND_FRAME,

	//! celkovy cas efektoru. Float R/W
	EFFECT_TIME,

	//! ma se efektor opakovat po uplynuti casu? Bool R/W
	REPEAT,

	//! momentalni cas efektoru. Float R/W
	CURRENT_TIME,

	//! pocet aktivnich particlu. Int R
	ACTIVE_PARTICLES,

	//! Bool R/W
	SORT,

	//! Bool R/W
	WIND,

	//! Float R/W
	SPRING
};

//vraci celkovy pocet aktivnich particles ve vsech emitorech
proto native int GetParticleCount(notnull IEntity ent);

//precte jmena nadefinovanych emitoru v particle effectu.
proto int GetParticleEmitors(notnull IEntity ent, out string emitors[], int max);
//vraci pocet emitoru, a pole emitors naplni jmeny (do maximalni poctu max)

//nastavi parametr particle emitoru
//pokud emitor == -1, nastavi tento parametr u vsech emitoru
proto void SetParticleParm(notnull IEntity ent, int emitor, EmitorParam parameter, void value);

//gets parameter of particle emitor
proto void GetParticleParm(notnull IEntity ent, int emitor, EmitorParam parameter, out void value);

//gets original parameter of particle emitor
proto void GetParticleParmOriginal(notnull IEntity ent, int emitor, EmitorParam parameter, out void value);

//Force-changes particle emitor position to the current one.
//Used for sudden changes of particle position to avoid spreading emitted
//particles between previous and the new one position
proto native void ResetParticlePosition(notnull IEntity ent);
//@}


//@}
