#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

using std::cin;         using std::string;
using std::cout;        using std::vector;
using std::endl;        using std::for_each;
using std::istream;     using std::sort;
using std::setw;        using std::equal_range;
                        using std::max_element;

string& trim_punct( string& str );
istream& read( istream& is, vector<string>& vec );


int main()
{
    vector<string> vec;
    if( read(cin, vec) ){
        for_each( vec.begin(), vec.end(), [](string& s)
                {
                    s = trim_punct(s);
                });

        sort( vec.begin(), vec.end() );
        const auto longest = max_element( vec.cbegin(), vec.cend(),
                                [](const string& a, const string& b)
                                { return a < b; })->size() + 1;
        for( auto it = vec.begin(); it != vec.end(); ){
            const auto er = equal_range( it, vec.end(), *it );
            cout << setw(longest) << *it 
                 << " occurs " << (er.second - er.first) << " times."
                 << endl;
            it = er.second;
        }
    }
    else{
        cout << "Failed to read data.\n";
        return 1;
    }

    return 0;
}


string& trim_punct( string& str )
{
    static const auto whitespace = std::string( " \t\n.,;:'\"-+=[]{}()!<>");
    auto pos = str.find_first_not_of(whitespace);
    if( pos == std::string::npos ){
        str.clear();
        return str;
    }
    str = str.substr( pos );
    pos = str.find_first_of(whitespace);
    if( pos != string::npos )
        str.erase( pos );
    return str;
}

istream& read( istream& is, vector<string>& vec )
{
    for( string s; is >> s; )
        vec.emplace_back( std::move(s) );
    if( !vec.empty() && !is.bad() ){
        is.clear();
    }
    return is;
}
