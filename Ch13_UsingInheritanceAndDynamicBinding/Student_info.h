#ifndef GUARD_Student_info_h_
#define GUARD_Student_info_h_

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <memory>
#include <utility>

#include "Core.h"


/* Student_info */
/* ------------------------------------------------------------------------- */
class Student_info
{
public:
// -- ctors and copy control
    Student_info()
        : pc_(nullptr) { }
    Student_info( std::istream& is )
        : pc_(nullptr) { read(is); }
    Student_info( const Student_info& );
    Student_info( Student_info&& ) = default;
    Student_info& operator=( const Student_info& );
    Student_info& operator=( Student_info&& ) = default;
    ~Student_info() = default;

// inteface
    std::istream& read( std::istream& );

    std::string name() const
    {
        if( pc_ )
            return pc_->name();
        else
            throw std::runtime_error("uninitialized Student");
    }

    double grade() const
    {
        if( pc_ )
            return pc_->grade();
        else
            throw std::runtime_error("uninitialized Student");
    }

    static bool compare( const Student_info& s1, const Student_info& s2 )
    {
        return s1.name() < s2.name();
    }

private:
    std::unique_ptr<Core> pc_;
};
/* ------------------------------------------------------------------------- */


#endif /* GUARD_Student_info_h_ */
