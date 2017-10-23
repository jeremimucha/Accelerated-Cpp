// Chapter 7 Using associative containers

#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <iterator>
#include <algorithm>

using std::cin;         using std::string;
using std::cout;        using std::vector;
using std::endl;        using std::map;
using std::istream;     using std::istringstream;
                        using std::domain_error;
                        using std::logic_error;
                        using std::istream_iterator;
                        using std::back_inserter;



// return a random integer in the range [0, n)
int nrand( int n )
{
    if( n<= 0 || n > RAND_MAX )
        throw domain_error( "Argument to nrand is out of range" );

    const int bucket_size = RAND_MAX / n;
    int r;

    do
        r = rand() / bucket_size;
    while( r >= n );

    return r;
}


using Rule = vector<string>;
using Rule_collection = vector<Rule>;
using Grammar = map<string, Rule_collection>;

// read a grammar from a given input stream
Grammar read_grammar( istream& in )
{
    Grammar ret;
    string line;
    istringstream iss;
    // read the input
    while( getline(in, line) ){
        // split the input into words
        iss.clear();
        iss.str(line);
        vector<string> entry( (istream_iterator<string>(iss))
                            , (istream_iterator<string>()) );
        if( !entry.empty() ){
            // use the category to store the associated rule
            ret[entry[0]].push_back( Rule(entry.begin()+1, entry.end()) );
        }
    }
    return ret;
}

bool bracketed( const string& s )
{
    return s.size() > 1 && s[0] == '<' && s[s.size() - 1] == '>';
}

void gen_aux( const Grammar& g, const string& word, vector<string>& ret )
{
    if( !bracketed(word) ){
        ret.push_back(word);
    }
    else{
        // locate the rule that corresponds to word
        auto it = g.find( word );
        if( it == g.cend() )
            throw logic_error( "empty rule" );

        // fetch the set of possible rules
        const auto& c = it->second;

        // from which we select one at random
        const auto& r = c[nrand(c.size())];

        // recursively expand the selected rule
        for( auto i = r.cbegin(); i != r.cend(); ++i ){
            gen_aux( g, *i, ret );
        }
    }
}

vector<string> gen_sentence( const Grammar& g )
{
    vector<string> ret;
    gen_aux( g, "<sentence>", ret );
    return ret;
}


int main()
{
    srand( std::time(nullptr) );
    // generate the sentence
    auto sentence = gen_sentence( read_grammar(cin) );

    // write the first word, if any
    auto it = sentence.cbegin();
    if( !sentence.empty() ){
        cout << *it;
        ++it;
    }
    // write the rest of the words, each preceded by a space
    while( it != sentence.cend() ){
        cout << " " << *it;
        ++it;
    }
    cout << endl;
    return 0;
}