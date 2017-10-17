#ifndef GUARD_grade_hpp_
#define GUARD_grade_hpp_

#include <vector>
#include "Student_info.hpp"


double grade( double, double, double );
double grade( double, double, const std::vector<double>& );
double grade( const Student_info& );


#endif /* GUARD_grade_hpp_ */
