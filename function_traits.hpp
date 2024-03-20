#pragma once
#include <type_traits>
#include <tuple>

namespace detail
{
    template <typename Func>
    struct basic_function_traits;
    
    template <typename Ret, typename... Args>
    struct basic_function_traits<Ret(Args...)> {
        using args_type = std::tuple<Args...>;
        using return_type = Ret;
    };

    template <typename Ret, typename Class, typename... Args>
    struct basic_function_traits<Ret(Class::*)(Args...)> {
        using args_type = std::tuple<Args...>;
        using return_type = Ret;
    };
    
}	// namespace detail

template <typename Func>
struct function_traits;

template <typename Ret, typename... Args>
struct function_traits<Ret(Args...)> : detail::basic_function_traits<Ret(Args...)> {
    using type = Ret(Args...);
    using args_type = typename detail::basic_function_traits<Ret(Args...)>::args_type;
    using function_pointer_type = Ret(*)(Args...);
    static constexpr bool is_member = false;
    static constexpr bool is_const = false;
};

template <typename Ret, typename Class, typename... Args>
struct function_traits<Ret(Class::*)(Args...)> : detail::basic_function_traits<Ret(Class::*)(Args...)> {
    using type = Ret(Class::*)(Args...);
    using args_type = typename detail::basic_function_traits<Ret(Class::*)(Args...)>::args_type;
    using args_with_class_type = std::tuple<Class*, Args...>;
    using function_pointer_type = Ret(Class::*)(Args...);
    static constexpr bool is_member = true;
    static constexpr bool is_const = false;
};

template <typename Ret, typename Class, typename... Args>
struct function_traits<Ret(Class::*)(Args...) const> : detail::basic_function_traits<Ret(Class::*)(Args...) const> {
    using type = Ret(Class::*)(Args...) const;
    using args_type = typename detail::basic_function_traits<Ret(Class::*)(Args...) const>::args_type;
    using args_with_class_type = std::tuple<Class*, Args...>;
    using function_pointer_type = Ret(Class::*)(Args...) const;
    static constexpr bool is_member = true;
    static constexpr bool is_const = true;
};

