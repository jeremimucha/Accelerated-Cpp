#include "Student_info.hpp"

using std::istream;     using std::vector;


bool compare( const Student_info& lhs, const Student_info& rhs )
{
    return lhs.name < rhs.name;
}

istream& read( istream& is, Student_info& s )
{
    // read and store the student's name and midterm and final exam greades
    is >> s.name >> s.midterm >> s.final;

    read_hw( is, s.homework );  // read ans store all the sutdent's homework grades
    return is;
}

//  read homework grades from an input stream into a 'vector'
istream& read_hw( istream& in, vector<double>& hw )
{
    if( in ){
        // get rid of previous contents
        hw.clear();

        // read homework grades
        double x;
        while( in >> x ){
            hw.push_back(x);
        }

        // clear the stream so that input will work for the next student
        in.clear();
    }

    return in;
}
