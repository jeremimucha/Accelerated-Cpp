#include <iostream>
#include <iomanip>
#include <string>

using std::cout;        using std::setprecision;
using std::endl;        using std::setw;
using std::to_string;   using std::streamsize;
                        using std::fixed;
                        using std::defaultfloat;

int main()
{
    int N = 100;
    const auto width = static_cast<streamsize>(
                        to_string( (N-1)*(N-1) ).size() + 2 );

    const auto prec = cout.precision();
    for( double d=0; d<N; ++d ){
        cout << fixed << setprecision(1)
             << setw( to_string(N-1).size() + 2 ) << d << " squared = "
             << setw( width ) << d*d
             << setprecision(prec) << defaultfloat << endl;
    }
}
