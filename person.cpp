#include "person.hpp"

person::person (const std::string& first,
            const std::string& last,
            unsigned short age)
{
    first_ = first;
    last_ = last;
    age_ = age;
}

const std::string& person::first () const
{
    return first_;
}

const std::string& person::last () const
{
    return last_;
}

unsigned short person::age () const
{
    return age_;
}
