#include "Base.h"

CBase::CBase()
{
    id = 0;
}

CBase::~CBase()
{
}

bool CBase::isNumber()
{
    return (id & MID_NUMBER);
}

bool CBase::isVar()
{
    return (id & MID_VARIABLE);
}

bool CBase::isSymbol()
{
    return (id & MID_SYMBOL);
}
//martysama0134's 46874603054404b0f36b515fa835e0da
