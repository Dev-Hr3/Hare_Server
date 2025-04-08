#ifndef __INC_LZO_MANAGER_H
#define __INC_LZO_MANAGER_H

#include "minilzo.h"

class LZOManager : public singleton<LZOManager>
{
	public:
		LZOManager();
		virtual ~LZOManager();

		bool	Compress(const BYTE* src, size_t srcsize, BYTE* dest, lzo_uint * puiDestSize);
		bool	Decompress(const BYTE* src, size_t srcsize, BYTE* dest, lzo_uint * puiDestSize);
		static constexpr size_t GetMaxCompressedSize(size_t original) {
			return (original + (original >> 4) + 64 + 3);
		}

		BYTE *	GetWorkMemory() { return m_workmem; }

	private:
		BYTE *	m_workmem;
};

#endif
//martysama0134's a288e6779da68f768431f9975e780da3
