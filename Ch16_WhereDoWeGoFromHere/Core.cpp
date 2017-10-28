#include <algorithm>
#include "Core.hpp"
#include "grade.hpp"

using std::istream;
using std::string;
using std::vector;

std::istream& read_hw( std::istream& in, std::vector<double>& hw );


/* Core */
/* ------------------------------------------------------------------------- */
string Core::name() const
{
    return name_;
}

double Core::grade() const
{
    return ::grade( midterm_, final_, homework_ );
}

istream& Core::read_common( istream& in )
{
    // read and store the student's name and exam grades
    in >> name_ >> midterm_ >> final_;
    return in;
}

istream& Core::read( istream& in )
{
    read_common(in);
    read_hw(in, homework_);
    return in;
}
/* ------------------------------------------------------------------------- */


/* Grad */
/* ------------------------------------------------------------------------- */
istream& Grad::read( istream& in )
{
    read_common(in);
    in >> thesis_;
    read_hw(in, homework_);
    return in;
}

double Grad::grade() const
{
    return std::min(Core::grade(), thesis_);
}

bool compare( const Core& c1, const Core& c2 )
{
    return c1.name() < c2.name();
}
/* ------------------------------------------------------------------------- */


bool compare_Core_ptrs( const Core* cp1, const Core* cp2 )
{
    return compare( *cp1, *cp2 );
}
