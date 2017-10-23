// Chapter 7 Using associative containers
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>


using std::cout;        using std::map;
using std::cin;         using std::vector;
using std::endl;        using std::string;
using std::istream;     using std::find_if;


vector<string> split( const string& str )
{
    typedef string::const_iterator iter;
    vector<string> ret;

    iter i = str.begin();
    while( i != str.end() ){
        // ignore leading blanks
        i = find_if( i, str.end(), [](char c){ return !::isspace(c); } );

        // find end of next word
        iter j = find_if( i, str.end(), [](char c){ return ::isspace(c); } );

        // copy the characters in [i, j)
        if( i != str.end() )
            ret.push_back( string(i, j) );
        
        i = j;
    }

    return ret;
}


// find all the lines that refer to each word in the input
map<string,vector<int>>
    xref( istream& in,
            vector<string> find_words(const string&) = split)
{
    string line;
    int line_number = 0;
    map<string, vector<int>> ret;

    // read the next line
    while( getline(in, line) ){
        ++line_number;

        // break the input line into words
        vector<string> words = find_words(line);
    
        // remember that each word occurs on the current line
        for( vector<string>::const_iterator it = words.begin();
             it != words.end(); ++it ){
            ret[*it].push_back(line_number);
        }
    }
    return ret;
}


int main()
{
    // call xref using split by default
    map<string, vector<int>> ret = xref( cin );

    // write the results
    for( auto it = ret.cbegin(); it != ret.cend(); ++it ){
        // write the word
        cout << it->first << " occurs in line(s): ";
        // followed by one or more line numbers
        auto line_it = it->second.cbegin();
        cout << *line_it;
        ++line_it;
        //write the rest of the line numbers, if any
        while( line_it != it->second.cend() ){
            cout << ", " << *line_it;
            ++line_it;
        }
        // write a new line to separate each word from the next
        cout << endl;
    }

    return 0;
}
