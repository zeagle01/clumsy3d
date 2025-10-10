
#pragma once

#define ENTRY(name,...)		struct name{__VA_ARGS__;}; name*  name##_var ;
#define USE(name,...)		using name = __VA_ARGS__;
#define LIST(name,...)		using name = clumsy::type_list<__VA_ARGS__>;
#define VALUE(name,...)		static constexpr auto name = __VA_ARGS__;