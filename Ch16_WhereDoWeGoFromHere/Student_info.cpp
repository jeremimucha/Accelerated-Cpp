#include <iostream>
#include "Core.hpp"
#include "Student_info.hpp"

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

istream& operator>>( istream& is, Student_info& s )
{
    char ch;
    
    if( is >> ch ){
        if( ch == 'U' )
            s.pc_.reset( new Core(is) );
        else
            s.pc_.reset( new Grad(is) );
    }
    // else
        // throw std::runtime_error( "Error reading Student_info." );

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