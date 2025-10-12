
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
		static void apply(const std::string& name, std::function<void()> fn)
		{
			if (ImGui::Button(name.c_str()))
			{
				fn();
			}
		}
	};

	template<>
	struct ui_wrapper<ui::check_box>
	{
		static void apply(const std::string& name, bool& value)
		{
			ImGui::Checkbox(name.c_str(), &value);
		}
	};

	template<>
	struct ui_wrapper<ui::input_float>
	{
		static void apply(const std::string& name, float& value)
		{
			//ImGui::InputFloat(name.c_str(), &value, 1e-2f, 1e-1f, "%f", ImGuiInputTextFlags_EnterReturnsTrue);
			ImGui::InputFloat(name.c_str(), &value, 1e-2f, 1e-1f, "%f");
		}

	};

	template<>
	struct ui_wrapper<ui::input_int>
	{
		static void apply(const std::string& name, int& value)
		{
			//ImGui::InputInt(name.c_str(), &value, 1, 100, ImGuiInputTextFlags_EnterReturnsTrue);
			ImGui::InputInt(name.c_str(), &value, 1, 100);
		}

	};

	template<>
	struct ui_wrapper<ui::slider_float>
	{
		static void apply(const std::string& name, float& value, float min, float max)
		{
			ImGui::SliderFloat(name.c_str(), &value, min, max ,"%2.2f");
		}

	};

}

