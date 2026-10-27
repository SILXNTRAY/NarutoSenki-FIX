#pragma once
#include "Utils/Debug/Debug.h"

#if COCOS2D_DEBUG

DEBUG_NS_BEGIN

#include "CharacterBase.h"

void PrintDamgeInfo(CharacterBase *attacked, CharacterBase *realAttacker, CharacterBase *attacker, int attackValue, uint32_t damage, const string &effectType)
{
	if (attacked->isFlog() || attacker->isFlog())
		return;

	auto state = damage < attacked->getHP() ? "attacked" : "killed  ";
	if (realAttacker != attacker)
	{
		NSLOG("Unit {:<9}:{} -> {:<9}:{} {} {:<9}:{} HP: {:<4} -{:<4}HP [ Atk: {:<4}, Type: {}]",
			  realAttacker->getName(),
			  realAttacker->m_uID,
			  attacker->getName(),
			  attacker->getCharId(),
			  state,
			  attacked->getName(),
			  attacked->getCharId(),
			  attacked->getHP(),
			  damage,
			  attackValue,
			  effectType);
	}
	else
	{
		NSLOG("Unit {:<9}:{} {} {:<9}:{} HP: {:<4} -{:<4}HP [ Atk: {:<4}, Type: {}]",
			  attacker->getName(),
			  attacker->getCharId(),
			  state,
			  attacked->getName(),
			  attacked->getCharId(),
			  attacked->getHP(),
			  damage,
			  attackValue,
			  effectType);
	}
}

DEBUG_NS_END

#endif
