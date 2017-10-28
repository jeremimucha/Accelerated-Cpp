#include "Picture.hpp"

using std::max;
using std::endl;
using std::ostream;
using std::string;
using std::vector;
using std::shared_ptr;

/* Picture */
/* ------------------------------------------------------------------------- */
// Picture frame( const Picture& pic )
// {
//     return new Frame_Pic( pic.p_ );
// }

Picture hcat( const Picture& lhs, const Picture& rhs )
{
    return new HCat_Pic( lhs.p_, rhs.p_ );
}

Picture vcat( const Picture& top, const Picture& bottom )
{
    return new VCat_Pic( top.p_, bottom.p_ );
}

Picture::Picture( const vector<string>& v )
    : p_( new String_Pic(v) ) { }

Picture::Picture( vector<string>&& v )
    : p_( new String_Pic(std::move(v)) ) { }

ostream& operator<<( ostream& os, const Picture& picture )
{
    const auto ht = picture.p_->height();
    for( Pic_base::ht_sz i = 0; i != ht; ++i ){
        picture.p_->display( os, i, false );
        os << endl;
    }
    return os;
}
/* ------------------------------------------------------------------------- */

/* Pic_base */
/* ------------------------------------------------------------------------- */
Pic_base::wd_sz String_Pic::width() const
{
    Pic_base::wd_sz n = 0;
    for( Pic_base::ht_sz i = 0; i != data_.size(); ++i ){
        n = std::max( n, data_[i].size() );
    }
    return n;
}
/* ------------------------------------------------------------------------- */

/* String_Pic */
/* ------------------------------------------------------------------------- */
void String_Pic::display( ostream& os, ht_sz row, bool do_pad ) const
{
    wd_sz start = 0;

    // write the row if we're still in range
    if( row < height() ){
        os << data_[row];
        start = data_[row].size();
    }

    // pad the output if necessary
    if( do_pad ){
        pad( os, start, width() );
    }
}
/* ------------------------------------------------------------------------- */

/* VCat_Pic */
/* ------------------------------------------------------------------------- */
void VCat_Pic::display( ostream& os, ht_sz row, bool do_pad ) const
{
    wd_sz w = 0;
    if( row < first_->height() ){
        // we are in the top subpicture
        first_->display( os, row, do_pad );
        w = first_->width();
    }
    else if( row < height() ){
        // we are in the bottom subpicture
        second_->display( os, row - first_->height(), do_pad );
        w = second_->width();
    }
    if( do_pad ){
        pad( os, w, width() );
    }
}
/* ------------------------------------------------------------------------- */

/* HCat_Pic */
/* ------------------------------------------------------------------------- */
void HCat_Pic::display( ostream& os, ht_sz row, bool do_pad ) const
{
    first_->display( os, row, do_pad || row < second_->height() );
    second_->display( os, row, do_pad );
}
/* ------------------------------------------------------------------------- */

/* Frame_Pic */
/* ------------------------------------------------------------------------- */
void Frame_Pic::display( ostream& os, ht_sz row, bool do_pad ) const
{
    if( row >= height() ){
        // out of range
        if( do_pad )
            pad( os, 0, width() );
    }
    else{
        if( row == 0 || row == height() - 1 ){
            // top or bottom row
            os << string( width(), '*' );
        }
        else if( row == 1 || row == height() - 2 ){
            // second from top or bottom row
            os << '*';
            pad( os, 1, width() - 1 );
            os << '*';
        }
        else{
            // interior row
            os << "* ";
            p_->display( os, row-2, true );
            os << " *";
        }
    }
}
/* ------------------------------------------------------------------------- */

/* Pic_base */
/* ------------------------------------------------------------------------- */
void Pic_base::pad( std::ostream& os, wd_sz beg, wd_sz end )
{
    while( beg != end ){
        os << " ";
        ++beg;
    }
}
/* ------------------------------------------------------------------------- */
