#ifndef __INC_METIN_II_GAME_PACKET_HEADER_INFO_H__
#define __INC_METIN_II_GAME_PACKET_HEADER_INFO_H__

#include "packet.h"

typedef struct SPacketElement
{
	int		iSize;
	std::string	stName;
	int		iCalled;
	DWORD	dwLoad;
// #ifdef ENABLE_SEQUENCE_SYSTEM
	bool	bSequencePacket;
// #endif
} TPacketElement;

class CPacketInfo
{
	public:
		CPacketInfo();
		virtual ~CPacketInfo();

		void Set(int header, int size, const char * c_pszName, bool bSeq=false);
		bool Get(int header, int * size, const char ** c_ppszName);

		void Start();
		void End();

		void Log(const char * c_pszFileName);

#ifdef ENABLE_SEQUENCE_SYSTEM
		bool IsSequence(int header);
		void SetSequence(int header, bool bSeq);
#endif

	private:
		TPacketElement * GetElement(int header);

	protected:
		std::map<int, TPacketElement *> m_pPacketMap;
		TPacketElement * m_pCurrentPacket;
		DWORD m_dwStartTime;
};

class CPacketInfoCG : public CPacketInfo
{
	public:
		CPacketInfoCG();
		virtual ~CPacketInfoCG();
};

// PacketInfo P2P
class CPacketInfoGG : public CPacketInfo
{
	public:
		CPacketInfoGG();
		virtual ~CPacketInfoGG();
};

#endif
//martysama0134's a288e6779da68f768431f9975e780da3
