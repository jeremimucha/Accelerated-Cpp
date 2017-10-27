#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <utility>

#include "Ptr.hpp"
#include "Student_info.hpp"

using std::cin;
using std::cout;
using std::domain_error;
using std::endl;
using std::streamsize;
using std::setprecision;
using std::setw;
using std::string;
using std::vector;
using std::max;


bool compare_Core_handles( const Ptr<Core>& lhs, const Ptr<Core>& rhs )
{ return compare(*lhs, *rhs); }


int main()
{
    vector<Ptr<Core>> students;
    Ptr<Core> record;
    char ch;
    string::size_type maxlen = 0;

    // read and store the data
    while( cin >> ch ){
        if( ch == 'U' )
            record = new Core;  // allocate a 'Core' object
        else
            record = new Grad;

        record->read(cin);
        maxlen = max(maxlen, record->name().size());
        students.push_back(std::move(record));
    }

    // compare must be rewriten to work on 'const Ptr<Core>&'
    sort(students.begin(), students.end(), compare_Core_handles);

    for( auto it = students.cbegin(); it != students.cend(); ++it ){
        cout << (*it)->name()
             << string( maxlen + 1 - (*it)->name().size(), ' ' );
        try{
            auto final_grade = (*it)->grade();
            auto prec = cout.precision();
            cout << setprecision(3) << final_grade
                 << setprecision(prec) << endl;
        }catch( domain_error e ){
            cout << e.what() << endl;
        }
    }
    return 0;
}
