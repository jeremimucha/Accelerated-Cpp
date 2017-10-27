#ifndef GUARD_Handle_hpp_
#define GUARD_Handle_hpp_


/* Handle */
/* A value-like copying pointer handler class. Assumes The handles class
 * has a virtual clone() member returning a copy of itself                   */
/* ------------------------------------------------------------------------- */
template< typename T >
class Handle
{
public:
    Handle()
        : p_(nullptr) { }
    Handle( T* ptr )
        : p_( ptr ) { }
    Handle( const Handle& rhs )
        : p_(rhs.p_ ? rhs.p_->clone() : nullptr) { }
    Handle( Handle&& rhs )
        : p_( rhs.p_ ) { rhs.p_ = nullptr; }
    inline Handle& operator=( const Handle& rhs );
    inline Handle& operator=( Handle&& rhs ) noexcept;
    ~Handle() { delete p_; }

    operator bool() const noexcept { return p_; }
    inline T& operator*() const;
    inline T* operator->() const;
private:
    T* p_;
};

/* ------------------------------------------------------------------------- */

#include <stdexcept>

template<typename T>
inline Handle<T>& Handle<T>::operator=( const Handle& rhs )
{
    if( &rhs != this ){
        delete p_;
        p_ = rhs.p_ ? rhs.p_->clone() : nullptr;
    }
    return *this;
}

template<typename T>
inline Handle<T>& Handle<T>::operator=( Handle&& rhs ) noexcept
{
    if( &rhs != this ){
        delete p_;
        p_ = rhs.p_;
        rhs.p_ = nullptr;
    }
    return *this;
}

template<typename T>
inline T& Handle<T>::operator*() const
{
    if( p_ )
        return *p_;
    throw std::runtime_error( "unbound Handle" );
}

template<typename T>
inline T* Handle<T>::operator->() const
{
    if( p_ )
        return p_;
    throw std::runtime_error( "unbound Handle" );
}
/* ------------------------------------------------------------------------- */


#endif /* GUARD_Handle_hpp_ */
