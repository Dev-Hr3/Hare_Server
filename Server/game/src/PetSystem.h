#ifndef	__HEADER_PET_SYSTEM__
#define	__HEADER_PET_SYSTEM__
#include "../../common/CommonDefines.h"

class CHARACTER;

struct SPetAbility
{
};

class CPetActor
{
public:
	enum EPetOptions
	{
		EPetOption_Followable		= 1 << 0,
		EPetOption_Mountable		= 1 << 1,
		EPetOption_Summonable		= 1 << 2,
		EPetOption_Combatable		= 1 << 3,
	};

protected:
	friend class CPetSystem;

	CPetActor(LPCHARACTER owner, DWORD vnum, DWORD options = EPetOption_Followable | EPetOption_Summonable);

	virtual ~CPetActor();

	virtual bool	Update(DWORD deltaTime);

protected:
	virtual bool	_UpdateFollowAI();
	virtual bool	_UpdatAloneActionAI(float fMinDist, float fMaxDist);

private:
	bool Follow(float fMinDistance = 50.f);

public:
	LPCHARACTER		GetCharacter()	const					{ return m_pkChar; }
	LPCHARACTER		GetOwner()	const						{ return m_pkOwner; }
	DWORD			GetVID() const							{ return m_dwVID; }
	DWORD			GetVnum() const							{ return m_dwVnum; }

	bool			HasOption(EPetOptions option) const		{ return m_dwOptions & option; }

	void			SetName(const char* petName);

	bool			Mount();
	void			Unmount();

	DWORD			Summon(const char* petName, LPITEM pSummonItem, bool bSpawnFar = false);
	void			Unsummon(
							#ifdef USE_ACTIVE_PET_SEAL_EFFECT
							bool updateSocket = true
							#endif
					);

	bool			IsSummoned() const			{ return 0 != m_pkChar; }
	bool			SetSummonItem(LPITEM pItem
									#ifdef USE_ACTIVE_PET_SEAL_EFFECT
									, bool updateSocket = true
									#endif
					);
	DWORD			GetSummonItemVID () { return m_dwSummonItemVID; }

	void			GiveBuff();
	void			ClearBuff();

private:
	DWORD			m_dwVnum;
	DWORD			m_dwVID;
	DWORD			m_dwOptions;
	DWORD			m_dwLastActionTime;
	DWORD			m_dwSummonItemVID;
	DWORD			m_dwSummonItemVnum;

	short			m_originalMoveSpeed;

	std::string		m_name;

	LPCHARACTER		m_pkChar;					// Instance of pet(CHARACTER)
	LPCHARACTER		m_pkOwner;
};

/**
*/
class CPetSystem
{
public:
	typedef	boost::unordered_map<DWORD,	CPetActor*>		TPetActorMap;

public:
	CPetSystem(LPCHARACTER owner);
	virtual ~CPetSystem();

	CPetActor*	GetByVID(DWORD vid) const;
	CPetActor*	GetByVnum(DWORD vnum) const;

	bool		Update(DWORD deltaTime);
	void		Destroy();

	size_t		CountSummoned() const;

public:
	void		SetUpdatePeriod(DWORD ms);

	CPetActor*	Summon(DWORD mobVnum, LPITEM pSummonItem, const char* petName, bool bSpawnFar, DWORD options = CPetActor::EPetOption_Followable | CPetActor::EPetOption_Summonable);

	void		Unsummon(DWORD mobVnum, bool bDeleteFromList = false);
	void		Unsummon(CPetActor* petActor, bool bDeleteFromList = false);
	void		UnsummonAll();

	CPetActor*	AddPet(DWORD mobVnum, const char* petName, const SPetAbility& ability, DWORD options = CPetActor::EPetOption_Followable | CPetActor::EPetOption_Summonable | CPetActor::EPetOption_Combatable);

	void		DeletePet(DWORD mobVnum);
	void		DeletePet(CPetActor* petActor);
	void		RefreshBuff();

private:
	TPetActorMap	m_petActorMap;
	LPCHARACTER		m_pkOwner;
	DWORD			m_dwUpdatePeriod;
	DWORD			m_dwLastUpdateTime;
	LPEVENT			m_pkPetSystemUpdateEvent;
};

#endif	//__HEADER_PET_SYSTEM__
//martysama0134's a288e6779da68f768431f9975e780da3
