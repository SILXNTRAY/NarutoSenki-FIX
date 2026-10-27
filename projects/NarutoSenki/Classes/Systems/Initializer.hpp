#pragma once
#include "Systems/CommandSystem.hpp"

namespace Internal
{
	static void initAllSystems()
	{
		CommandSystem::reset();
	}
} // namespace Internal
