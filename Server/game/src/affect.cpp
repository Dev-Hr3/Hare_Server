#include "stdafx.h"

#include <boost/pool/object_pool.hpp>

#include "affect.h"

boost::object_pool<CAffect> affect_pool;

CAffect* CAffect::Acquire()
{
	return affect_pool.malloc();
}

void CAffect::Release(CAffect* p)
{
	affect_pool.free(p);
}
//martysama0134's a288e6779da68f768431f9975e780da3
