#include "type_info.hpp"
#include <string>
#include <iostream>

class Person
{
public:
    std::string familyName = "Hat";
    std::string name = "John";
    bool GetMerried(Person& p) { return true; }
    std::string IntroduceMyself() { return name;}
};

BEGIN_CLASS(Person)
    DECLARE_FUNCTIONS(FUNCTION_FIELD(&Person::GetMerried), FUNCTION_FIELD(&Person::IntroduceMyself))
    DECLARE_VARIABLES(VARIABLE_FIELD(&Person::familyName), VARIABLE_FIELD(&Person::name))
END_CLASS()

template <typename Tuple, size_t ...Idx>
void print_tuple(const Tuple& t, std::index_sequence<Idx...>)
{
    ((std::cout << std::get<Idx>(t).name << '\n'), ...);
}

#define print_tuple_helper(tuple) print_tuple(tuple, std::make_index_sequence<std::tuple_size_v<decltype(tuple)>>())

template <size_t Idx, typename Class, typename Tuple>
void print_variables(Class& instance, Tuple& t)
{
    if constexpr(Idx >= std::tuple_size_v<Tuple>)
    {
        return;
    }
    else    
    {
        auto elem = instance.*(std::get<Idx>(t).ptr);
        std::cout << elem << '\n';
        print_variables<Idx + 1>(instance, t);
    }
}

int main(int argc, char const *argv[])
{
    TypeInfo<Person> info;
    Person p;
    print_tuple_helper(info.functions);
    print_variables<0>(p, info.variables);
    return 0;
}