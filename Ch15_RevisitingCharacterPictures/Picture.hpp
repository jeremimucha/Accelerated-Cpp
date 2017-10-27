#ifndef GUARD_Picture_hpp_
#define GUARD_Picture_hpp_

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <utility>


// -- Forward declaration
class Picture;


/* Pic_base */
/* Pure virtual base class for the Pic_ hierarchy                            */
/* ------------------------------------------------------------------------- */
class Pic_base
{
    friend std::ostream& operator<<( std::ostream&, const Picture& );
    friend class Frame_Pic;
    friend class Cat_Pic;
    friend class HCat_Pic;
    friend class VCat_Pic;
    friend class String_Pic;

// -- ABC - no public interface
    using ht_sz = std::vector<std::string>::size_type;
    using wd_sz = std::string::size_type;

// -- virtual member functions
    virtual wd_sz width() const = 0;
    virtual ht_sz height() const = 0;
    virtual void display( std::ostream&, ht_sz, bool ) const = 0;

public:
    virtual ~Pic_base() = default;

protected:
    static void pad( std::ostream& os, wd_sz, wd_sz );
};
/* ------------------------------------------------------------------------- */


/* Picture */
/* ------------------------------------------------------------------------- */
class Picture
{
public:
    friend std::ostream& operator<<( std::ostream&, const Picture& );
    friend Picture frame( const Picture& );
    friend Picture hcat( const Picture&, const Picture& );
    friend Picture vcat( const Picture&, const Picture& );

    Picture( const std::vector<std::string>& );
    Picture( std::vector<std::string>&& = std::vector<std::string>() );

private:
    Picture( Pic_base* ptr )
        : p_( ptr ) { }

// -- member variables
    std::shared_ptr<Pic_base> p_;
};
// -- Operations on `Picture's
Picture frame( const Picture& );
Picture hcat( const Picture&, const Picture& );
Picture vcat( const Picture&, const Picture& );
std::ostream& operator<<( std::ostream&, const Picture& );
/* ------------------------------------------------------------------------- */


/* String_pic */
/* ------------------------------------------------------------------------- */
class String_Pic : public Pic_base
{
    friend class Picture;
    String_Pic( const std::vector<std::string>& v )
        : data_( v ) { }
    String_Pic( std::vector<std::string>&& v )
        : data_( std::move(v) ) { }

// -- virtual member functions
    ht_sz height() const  override
        { return data_.size(); }
    wd_sz width() const override;
    void display( std::ostream&, ht_sz, bool ) const override;

// -- member variables
    std::vector<std::string> data_;
};
/* ------------------------------------------------------------------------- */


/* Cat_Pic */
/* ------------------------------------------------------------------------- */
class Cat_Pic : public Pic_base
{
protected:
    Cat_Pic( const std::shared_ptr<Pic_base>& first,
             const std::shared_ptr<Pic_base>& second )
        : first_( first ), second_( second ) { }
// -- ABC - virtual members not overriden

// -- member variables
    std::shared_ptr<Pic_base> first_, second_;
};
/* ------------------------------------------------------------------------- */

/* VCat_Pic */
/* ------------------------------------------------------------------------- */
class VCat_Pic : public Cat_Pic
{
    friend Picture vcat( const Picture&, const Picture& );

    using Cat_Pic::Cat_Pic;

// -- virtual member functions
    wd_sz width() const override
        { return std::max( first_->width(), second_->width() ); }
    ht_sz height() const override
        { return first_->height() + second_->height(); }
    void display( std::ostream&, ht_sz, bool ) const override;
};
/* ------------------------------------------------------------------------- */

/* HCat_Pic */
/* ------------------------------------------------------------------------- */
class HCat_Pic : public Cat_Pic
{
    friend Picture hcat( const Picture&, const Picture& );

    using Cat_Pic::Cat_Pic;

// -- virtual member functions
    wd_sz width() const override
        { return first_->width() + second_->width(); }
    ht_sz height() const override
        { return std::max( first_->height(), second_->height() ); }
    void display( std::ostream&, ht_sz, bool ) const override;
};
/* ------------------------------------------------------------------------- */

/* Frame_Pic */
/* ------------------------------------------------------------------------- */
class Frame_Pic : public Pic_base
{
    friend Picture frame( const Picture& );

    Frame_Pic( const std::shared_ptr<Pic_base>& pic )
        : p_( pic ) { }

// -- virtual member functions
    wd_sz width() const override
        { return p_->width() + 4; }
    ht_sz height() const override
        { return p_->height() + 4; }
    void display( std::ostream&, ht_sz, bool ) const override;

// -- member variables
    std::shared_ptr<Pic_base> p_;
};
/* ------------------------------------------------------------------------- */

#endif /* GUARD_Picture_hpp_ */
