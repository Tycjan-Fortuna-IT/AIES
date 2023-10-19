#include "pch.hpp"
#include "Panel.hpp"

#include "Engine/Core/Utils/StringUtils.hpp"
#include "spdlog/fmt/fmt.h"

namespace AI {
	Panel::Panel(const char* name, const char8_t* icon)
		: m_Name(name), m_Icon(icon) {
        m_ID = fmt::format(" {} {}\t\t###{}", Core::StringUtils::FromChar8T(icon), name, name);
	}
}
