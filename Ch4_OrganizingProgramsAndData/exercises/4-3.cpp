#include <iostream>
#include <iomanip>
#include <string>

using std::cout;    using std::setprecision;
using std::endl;    using std::setw;


int main()
{
    int N = 100;
    const auto width = std::to_string( (N-1)*(N-1) ).size();

    for( int i=0; i<N; ++i ){
        cout << setw(std::to_string(N-1).size()) << i << " squared = "
             << setw(width) << i*i
             << endl;
    }
}
