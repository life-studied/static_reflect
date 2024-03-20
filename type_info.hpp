#pragma once
#include "function_traits.hpp"
#include "variable_traits.hpp"
#include <string_view>

template <typename T>
struct is_function
{
    static constexpr bool value = std::is_function_v<std::remove_pointer_t<T>> ||
                                 std::is_member_function_pointer_v<T>;
};

template <typename T>
using is_function_v = is_function<T>::value;

template <typename T>
struct field_traits;

template <typename T, typename Class>
struct field_traits<T Class::*> : variable_traits<T Class::*>{
    constexpr field_traits(std::string_view name, T Class::* ptr) : name(name), ptr(ptr) {};
    std::string_view name;
    T Class::*ptr;
};

template <typename Ret, typename Class, typename... Args>
struct field_traits<Ret(Class::*)(Args...)> : function_traits<Ret(Class::*)(Args...)>{
    using func_ptr_type = Ret(Class::*)(Args...);
    constexpr field_traits(std::string_view name, func_ptr_type ptr) : name(name), ptr(ptr) {};
    std::string_view name;
    func_ptr_type ptr;
};

template <typename T>
struct TypeInfo;


#define BEGIN_CLASS(T)  \
template <> \
struct TypeInfo<T>  \
{

#define DECLARE_FUNCTIONS(...)   \
    static constexpr auto functions = std::make_tuple(__VA_ARGS__);

#define FUNCTION(F)    function_traits<decltype(F)>{}
#define FUNCTION_FIELD(F)    field_traits<decltype(F)>{#F, F}

#define DECLARE_VARIABLES(...)     \
    static constexpr auto variables = std::make_tuple(__VA_ARGS__);

#define VARIABLE(F)    variable_traits<decltype(F)>{}
#define VARIABLE_FIELD(F)    field_traits<decltype(F)>{#F, F}

#define END_CLASS()   };

