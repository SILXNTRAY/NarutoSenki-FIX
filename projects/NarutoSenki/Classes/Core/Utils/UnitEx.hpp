#pragma once
#include "CharacterBase.h"

namespace UnitEx
{
	template <typename T>
	typename std::enable_if<std::is_base_of<CharacterBase, T>::value, void>::type
	clearMainTarget(CharacterBase *target, const vector<T *> &list)
	{
		for (auto unit : list)
		{
			if (unit->_mainTarget)
			{
				if (unit->_mainTarget == target)
					unit->_mainTarget = nullptr;
			}
		}
	}
}
