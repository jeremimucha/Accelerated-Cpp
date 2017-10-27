#ifndef GUARD_Core_h_
#define GUARD_Core_h_

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <utility>
#include <memory>

/* Core */
/* ------------------------------------------------------------------------- */
class Core
{
public:
// -- constructors
    Core()
        : midterm_(0), final_(0) { }
    Core( std::istream& is )
        { read(is); }
    
    Core( const Core& ) = default;
    Core( Core&& ) = default;
    Core& operator=( const Core& ) = default;
    Core& operator=( Core&& ) = default;

    std::string name() const;

    virtual std::istream& read( std::istream& );
    virtual double grade() const;

    virtual ~Core() = default;

protected:
// -- member variables
    double midterm_;
    double final_;
    std::vector<double> homework_;

// -- member functions
    std::istream& read_common( std::istream& );

    virtual Core* clone() const &
        { return new Core(*this); }
    virtual Core* clone() &&
        { return new Core(std::move(*this)); }
private:
// -- member variables
    std::string name_;
    
// -- friends
    friend class Student_info;
};
/* ------------------------------------------------------------------------- */


/* Grad */
/* ------------------------------------------------------------------------- */
class Grad : public Core
{
public:
    Grad()
        : thesis_(0) { }
    Grad( std::istream& is )
        { read(is); }
    
    Grad( const Grad& ) = default;
    Grad( Grad&& ) = default;
    Grad& operator=( const Grad& ) = default;
    Grad& operator=( Grad&& ) = default;

// -- virtual functions
    double grade() const override;
    std::istream& read( std::istream& ) override;

private:
// -- member variables
    double thesis_;

// -- virtual functions
    Grad* clone() const& override
        { return new Grad(*this); }
    Grad* clone() && override
        { return new Grad(std::move(*this)); }
};
/* ------------------------------------------------------------------------- */

bool compare( const Core&, const Core& );
bool compare_Core_ptrs( const Core* cp1, const Core* cp2 );

#endif /* GUARD_Core_h_ */
