
module;

#include "imgui.h"
#include <functional>
#include <string>

module clumsy.ui:ui_wrappers;

import :ui_type_table;

import  clumsy.core;

namespace clumsy
{
	template<is_in_list<ui_list>>
	struct ui_wrapper;

	template<>
	struct ui_wrapper<ui::button>
	{
		static bool apply(const std::string& name, empty, empty)
		{
			return ImGui::Button(name.c_str());
		}
	};

	template<>
	struct ui_wrapper<ui::check_box>
	{
		static bool apply(const std::string& name, bool& value, empty)
		{
			return ImGui::Checkbox(name.c_str(), &value);
		}
	};

	template<>
	struct ui_wrapper<ui::input_float>
	{
		static bool apply(const std::string& name, float& value, empty)
		{
			//ImGui::InputFloat(name.c_str(), &value, 1e-2f, 1e-1f, "%f", ImGuiInputTextFlags_EnterReturnsTrue);
			return ImGui::InputFloat(name.c_str(), &value, 1e-2f, 1e-1f, "%f");
		}

	};

	template<>
	struct ui_wrapper<ui::input_int>
	{
		static bool apply(const std::string& name, int& value, empty)
		{
			//ImGui::InputInt(name.c_str(), &value, 1, 100, ImGuiInputTextFlags_EnterReturnsTrue);
			return ImGui::InputInt(name.c_str(), &value, 1, 100);
		}

	};

	template<>
	struct ui_wrapper<ui::slider_float>
	{
		static bool apply(const std::string& name, float& value, range rng)
		{
			return ImGui::SliderFloat(name.c_str(), &value, rng.min, rng.max, "%2.2f");
		}

	};

}

