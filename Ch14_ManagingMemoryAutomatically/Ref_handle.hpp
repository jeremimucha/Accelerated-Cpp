#ifndef GUARD_Ref_handle_hpp_
#define GUARD_Ref_handle_hpp_

#include <cstddef>
#include <stdexcept>


/* Ref_handle */
/* A reference-counting pointer handler that implements reference-like
 * behavior. Assumes the type T exposes a virtual clone() member that
 * returns a copy of itself.                                                 */
/* ------------------------------------------------------------------------- */
template<typename T>
class Ref_handle
{
public:
    Ref_handle()
        : p_(nullptr), refptr_(new std::size_t(1)) { }
    Ref_handle( T* ptr )
        : p_(ptr), refptr_(new std::size_t(1)) { }
    Ref_handle( const Ref_handle& rhs )
        : p_(rhs.p_), refptr_(rhs.refptr_)
        { ++*refptr_; }
    Ref_handle( Ref_handle&& rhs )
        : p_(rhs.p_), refptr_(rhs.refptr_)
        { rhs.p_ = nullptr; rhs.refptr_ = new std::size_t(1); }
    ~Ref_handle() noexcept;

    inline Ref_handle& operator=( const Ref_handle& rhs );
    inline Ref_handle& operator=( Ref_handle&& ) ;

    operator bool() const noexcept { return p_; }
    T& operator*() const
        {
            if( p_ )
                return *p_;
            throw std::runtime_error( "unbound Ref_handle" );
        }
    T* operator->() const
        {
            if( p_ )
                return p_;
            throw std::runtime_error( "unbound Ref_handle" );
        }
private:
    T* p_;
    std::size_t* refptr_;
};
/* ------------------------------------------------------------------------- */
template<typename T>
inline Ref_handle<T>& Ref_handle<T>::operator=( const Ref_handle& rhs )
{
    // incrementing first protects against self-assignment
    ++*rhs.refptr_;
    // free the left-hand size, destroying pointers if appropriate
    if( --*refptr == 0 ){
        delete refptr_;
        delete p_;
    }

    // copy in values from the right-hand side
    refptr_ = rhs.refptr_;
    p_ = rhs.p_;
    
    return *this;
}

template<typename T>
inline Ref_handle<T>& Ref_handle<T>::operator=( Ref_handle&& rhs )
{
    if( &rhs != this ){
        if( --*refptr_ == 0 ){
            delete refptr_;
            delete p_;
        }
        p_ = rhs.p_;
        refptr_ = rhs.refptr_;
        rhs.p_ = nullptr;
        rhs.refptr_ = new sdt::size_t(1);
    }
    return *this;
}

template<typename T>
Ref_handle<T>::~Ref_handle()
{
    if( --*refptr_ == 0 ){
        delete refptr_;
        delete p_;
    }
}
/* ------------------------------------------------------------------------- */


#endif /* GUARD_Ref_handle_hpp_ */
