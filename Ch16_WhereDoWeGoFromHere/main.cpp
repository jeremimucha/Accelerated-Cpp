#include <algorithm>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <vector>
#include <utility>
#include "Student_info.hpp"
#include "Picture.hpp"

using std::cin;             using std::domain_error;
using std::cout;            using std::sort;
using std::endl;            using std::string;
using std::setprecision;    using std::vector;
using std::setw;            using std::max;
using std:: streamsize;


Picture histogram( const vector<Student_info>& students );


int main()
{
    vector<Student_info> students;
    Student_info s;

    // read the names and grades
    while( cin >> s )
        students.push_back( s );

    // put the students in alphabetical order
    sort( students.begin(), students.end(), Student_info::compare );

    // write the names and histograms
    cout << frame( histogram(students) ) << endl;

    return 0;
}


Picture histogram( const vector<Student_info>& students )
{
    Picture names;
    Picture grades;

    // for each student
    for( auto it = students.cbegin(); it != students.cend(); ++it ){
        // create vertically concatenated pictures of the names and grades
        names = vcat( names, vector<string>(1, it->name()) );
        grades = vcat( grades,
                       vector<string>(1, " " + string(it->grade()/5, '=')));
    }
    // horizontally concatenate the name and grade pictures to combine them
    return hcat( names, grades );
}
