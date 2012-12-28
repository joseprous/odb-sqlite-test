#ifndef PERSON_HPP
#define PERSON_HPP

#include <odb/core.hxx>
#include <string>

#pragma db object
class person
{
public:
    person (const std::string& first,
            const std::string& last,
            unsigned short age);

    const std::string& first () const;
    const std::string& last () const;

    unsigned short age () const;
    void age (unsigned short);

private:
    person () {}

    friend class odb::access;

#pragma db id auto
    unsigned long id_;

    std::string first_;
    std::string last_;
    unsigned short age_;
};

#endif
