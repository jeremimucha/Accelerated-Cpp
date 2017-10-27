#include <iostream>
#include "Core.h"
#include "Student_info.h"

using std::istream;


/* Student_info */
/* ------------------------------------------------------------------------- */
istream& Student_info::read( istream& is )
{
    char ch;
    is >> ch;   // get record type

    if( ch == 'U' ){
        pc_.reset( new Core(is) );
    }
    else{
        pc_.reset( new Grad(is) );
    }

    return is;
}

Student_info::Student_info( const Student_info& rhs )
    : pc_( rhs.pc_ ? rhs.pc_->clone() : nullptr )
{
}

Student_info& Student_info::operator=( const Student_info& rhs )
{
    if( &rhs != this ){
        if( rhs.pc_ )
            pc_.reset( rhs.pc_->clone() );
        else
            pc_.release();
    }
    
    return *this;
}
/* ------------------------------------------------------------------------- */