#ifndef GUARD_Student_info_hpp_
#define GUARD_Student_info_hpp_

#include <iostream>
#include <string>
#include "Core.hpp"
#include "Handle.hpp"


/* Student_info */
/* ------------------------------------------------------------------------- */
class Student_info
{
public:
    Student_info() { }
    Student_info( std::istream& is ) { read(is); }
    Student_info( const Student_info& ) = default;
    Student_info( Student_info&& ) = default;
    Student_info& operator=( const Student_info& ) = default;
    Student_info& operator=( Student_info&& ) = default;
    ~Student_info() = default;

    std::istream& read(std::istream&);

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
                throw std::runtime_error( "uninitialized Student" );
        }
    
    static bool compare( const Student_info& lhs, const Student_info& rhs )
        { return lhs.name() < rhs.name(); }

private:
    Handle<Core> pc_;
};
/* ------------------------------------------------------------------------- */


#endif /* GUARD_Student_info_hpp_ */
