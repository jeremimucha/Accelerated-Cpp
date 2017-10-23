// Chapter 8 Writing generic functions
#include <iostream>
#include <utility>


template<typename InIter1, typename InIter2>
bool equal( InIter1 b1, InIter1 e1, InIter2 b2 )
{
    while( b1 != e1 ){
        if( *b1++ != *b2++ )
            return false;
    }
    return true;
}


template<typename InIter, typename T>
auto find( InIter b, InIter e, const T& x )
{
    while( b != e && *b != x )
        ++b;
    return b;
}


template<typename InIter, typename OutIter>
auto copy( InIter b, InIter e, OutIter dst )
{
    while( b != e ){
        *dst++ = *b++;
    }
    return dst;
}

template<typename InIter, typename OutIter, typename Predicate>
auto remove_copy_if( InIter b, InIter e, OutIter dst, Predicate pred )
{
    while( b != e ){
        if( !pred(*b) )
            *dst++ = *b;
        ++b;
    }
    return dst;
}

template<typename InIter, typename T>
auto accumulate( InIter b, InIter e, T acc )
{
    while( b != e ){
        acc += *b++;
    }
    return acc;
}

template<typename InIter1, typename InIter2>
auto search( InIter1 b, InIter1 e, InIter2 b2, InIter2 e2 )
{
    for( ; b!=e; ++b ){
        auto outer = b;
        for( auto inner = b2; ; ++outer, ++inner ){
            if( inner == e2 )
                return b;
            if( inner == e )
                return e;
            if( *inner != *outer )
                break;
        }
    }
    return e;
}

template<typename InIter, typename Predicate>
auto find_if( InIter b, InIter e, Predicate pred )
{
    while( b != e && !pred(*b) ){
        ++b;
    }
    return b;
}

template<typename InIter, typename OutIter, typename T>
auto remove_copy( InIter b, InIter e, OutIter dst, const T& val )
{
    while( b != e ){
        if( *b != val )
            *dst++ = *b;
        ++b;
    }
    return dst;
}


int main()
{

}
