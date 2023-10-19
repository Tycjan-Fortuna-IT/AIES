#pragma once

#include <string>

namespace AI {
	class Panel	{
	public:

		Panel(const char* name = "Unnamed Panel", const char8_t* icon = u8"");
		virtual ~Panel() = default;

		Panel(const Panel& other) = delete;
		Panel(Panel&& other) = delete;
		Panel& operator=(const Panel& other) = delete;
		Panel& operator=(Panel&& other) = delete;

		virtual void OnRender() = 0;

	protected:

		std::string m_Name;
        std::string m_ID;

		const char8_t* m_Icon;
	};
}
