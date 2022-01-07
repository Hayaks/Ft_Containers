#ifndef IS_CONST_HPP
#define IS_CONST_HPP
namespace ft
{
    template < bool, class Isconst, class Notconst >
    struct is_const
    {
    };

    template < class Isconst, class Notconst >
    struct is_const< true, Isconst, Notconst >
    {
        typedef Isconst type;
    };

    template < class Isconst, class Notconst >
    struct is_const< false, Isconst, Notconst >
    {
        typedef Notconst type;
    };
} // namespace ft

#endif