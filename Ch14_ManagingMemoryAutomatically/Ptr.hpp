#ifndef GUARD_Ptr_hpp_
#define GUARD_Ptr_hpp_

#include <cstddef>
#include <stdexcept>


template<typename T>
T* clone( const T* p );


/* Ptr */
/* ------------------------------------------------------------------------- */
template<typename T>
class Ptr
{
public:
    // -- new member to copy the object conditionally when needed
    void make_unique()
        {
            if( *refptr_ != 1  ){
                --*refptr_;
                refptr_ = new std::size_t(1);
                p_ = p_ ? clone(p_) : nullptr;
            }
        }

    // the rest of the class looks like "Ref_handle" except for its name
    Ptr()
        : p_(nullptr), refptr_(new std::size_t(1)) { }
    Ptr( T* p )
        : p_(p), refptr_(new std::size_t(1)) { }
    Ptr( const Ptr& rhs )
        : p_(rhs.p_), refptr_(rhs.refptr_)
        { ++*refptr_; }
    Ptr( Ptr&& rhs )
        : p_(rhs.p_), refptr_(rhs.refptr_)
        { rhs.p_ = nullptr; rhs.refptr_ = new std::size_t(1); }
    ~Ptr() noexcept
        { free(); }

    Ptr& operator=( const Ptr& rhs );
    Ptr& operator=( Ptr&& rhs );

    operator bool() const noexcept{ return p_; }
    
    inline T& operator*() const;
    inline T* operator->() const;
private:
// -- member variables
    T* p_;
    std::size_t* refptr_;
// -- impl detail
    void free() noexcept
        {
            if( --*refptr_ == 0 ){
                delete refptr_;
                delete p_;
            }
        }
};
/* ------------------------------------------------------------------------- */

template<typename T>
T* clone( const T* p )
{
    return p->clone();
}
/* specialize for types which don't expose the clone() method
template<>
std::vector<char>* clone( const std::vector<char>* p )
{
    return new std::vector<char>(*p);
}
 */


template<typename T>
Ptr<T>& Ptr<T>::operator=( const Ptr& rhs )
{
    ++*rhs.refptr_;
    free();
    refptr_ = rhs.refptr_;
    p_ = rhs.p_;

    return *this;
}

template<typename T>
Ptr<T>& Ptr<T>::operator=( Ptr&& rhs )
{
    if( this != &rhs ){
        free();
        refptr_ = rhs.refptr_;
        p_ = rhs.p_;
        rhs.refptr_ = new std::size_t(1);
        rhs.p_ = nullptr;
    }
    return *this;
}

template<typename T>
inline T& Ptr<T>::operator*() const
{
    if( p_ )
        return *p_;
    throw std::runtime_error( "Unbound Ptr" );
}

template<typename T>
inline T* Ptr<T>:: operator->() const
{
    if( p_ )
        return p_;
    throw std::runtime_error( "Unbound Ptr" );
}
/* ------------------------------------------------------------------------- */


#endif /* GUARD_Ptr_hpp_ */
