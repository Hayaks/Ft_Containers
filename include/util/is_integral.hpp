#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP
namespace ft
{
    template < class T >
    struct is_integral
    {
        const static bool value = false;
    };

    template <>
    struct is_integral< bool >
    {
        const static bool value = true;
    };

    template <>
    struct is_integral< char >
    {
        const static bool value = true;
    };

    template <>
    struct is_integral< signed char >
    {
        const static bool value = true;
    };

    template <>
    struct is_integral< short >
    {
        const static bool value = true;
    };

    template <>
    struct is_integral< int >
    {
        const static bool value = true;
    };

    template <>
    struct is_integral< long >
    {
        const static bool value = true;
    };

    template <>
    struct is_integral< unsigned char >
    {
        const static bool value = true;
    };

    template <>
    struct is_integral< unsigned short >
    {
        const static bool value = true;
    };

    template <>
    struct is_integral< unsigned int >
    {
        const static bool value = true;
    };

    template <>
    struct is_integral< unsigned long >
    {
        const static bool value = true;
    };
} // namespace ft

#endif