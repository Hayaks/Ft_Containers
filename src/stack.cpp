#include "../include/container.hpp"
#include <string>
#include <vector>

const std::string CLEAN = "\033[0m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string WHITE = "\033[1m\033[37m";

void ft_stack_constructor()
{
    FT::stack< int >                      empty;
    FT::vector< int >                     vec(5, 2);
    FT::stack< int, FT::vector< int > >   stack_int(vec);
    FT::vector< bool >                    vec2(8, false);
    FT::stack< bool, FT::vector< bool > > stack_bool(vec2);

    std::cout << WHITE + "\n||||| Constructor/Destructor |||||" + CLEAN
              << std::endl;
    std::cout << YELLOW + "\nEmpty:" + CLEAN << std::endl;
    std::cout << GREEN << "\t-Size: " << empty.size() << CLEAN << std::endl;

    std::cout << YELLOW + "\nvector<int>(5,2):" + CLEAN << std::endl;
    std::cout << GREEN << "\t-Size: " << vec.size() << CLEAN << std::endl;

    std::cout << YELLOW + "\nStack_int(vector<int>):" + CLEAN << std::endl;
    std::cout << GREEN << "\t-Size: " << stack_int.size() << CLEAN << std::endl;

    std::cout << YELLOW + "\nvector<bool>(8, false):" + CLEAN << std::endl;
    std::cout << GREEN << "\t-Size: " << vec2.size() << CLEAN << std::endl;

    std::cout << YELLOW + "\nStack_bool(vector<bool>):" + CLEAN << std::endl;
    std::cout << GREEN << "\t-Size: " << stack_bool.size() << CLEAN
              << std::endl;
}

void ft_stack_member_functions()
{
    FT::stack< int > sta;

    std::cout << WHITE + "\n||||| Members functions |||||" + CLEAN << std::endl;
    std::cout << YELLOW + "\nEmpty stack<int>" + CLEAN << std::endl;
    std::cout << GREEN << "\t-Empty: " << sta.empty() << CLEAN << std::endl;
    std::cout << GREEN << "\t-Size: " << sta.size() << CLEAN << std::endl;

    sta.push(5);
    std::cout << YELLOW + "\nPush (5)" + CLEAN << std::endl;
    std::cout << GREEN << "\t-Empty: " << sta.empty() << CLEAN << std::endl;
    std::cout << GREEN << "\t-Size: " << sta.size() << CLEAN << std::endl;
    std::cout << GREEN << "\t-Value top: " << sta.top() << CLEAN << std::endl;

    sta.push(20);
    std::cout << YELLOW + "\nPush (20)" + CLEAN << std::endl;
    std::cout << GREEN << "\t-Empty: " << sta.empty() << CLEAN << std::endl;
    std::cout << GREEN << "\t-Size: " << sta.size() << CLEAN << std::endl;
    std::cout << GREEN << "\t-Value top: " << sta.top() << CLEAN << std::endl;

    sta.pop();
    std::cout << YELLOW + "\nPop" + CLEAN << std::endl;
    std::cout << GREEN << "\t-Empty: " << sta.empty() << CLEAN << std::endl;
    std::cout << GREEN << "\t-Size: " << sta.size() << CLEAN << std::endl;
    std::cout << GREEN << "\t-Value top: " << sta.top() << CLEAN << std::endl;
}

void ft_stack_relational()
{
    FT::stack< int > sta1;
    FT::stack< int > sta2;

    sta1.push(4);
    sta2.push(4);
    std::cout << WHITE + "\n||||| Relationnal |||||" + CLEAN << std::endl;
    std::cout << YELLOW + "\nComparaison identique value (4):" + CLEAN
              << std::endl;
    std::cout << GREEN
              << "\t-sta1(4) == sta2(4) = " << (sta1.top() == sta2.top())
              << std::endl;
    std::cout << GREEN
              << "\t-sta1(4) != sta2(4) = " << (sta1.top() != sta2.top())
              << std::endl;

    sta1.push(5);
    std::cout << YELLOW + "\nPush value (5) for sta1:" + CLEAN << std::endl;
    std::cout << YELLOW + "\nComparaison different value:" + CLEAN << std::endl;
    std::cout << GREEN
              << "\t-sta1(5) == sta2(4) = " << (sta1.top() == sta2.top())
              << std::endl;
    std::cout << GREEN
              << "\t-sta1(5) != sta2(4) = " << (sta1.top() != sta2.top())
              << std::endl;
    std::cout << GREEN << "\t-sta1(5) > sta2(4) = " << (sta1.top() > sta2.top())
              << std::endl;
    std::cout << GREEN << "\t-sta1(5) < sta2(4) = " << (sta1.top() < sta2.top())
              << std::endl;
    std::cout << GREEN
              << "\t-sta1(5) >= sta2(4) = " << (sta1.top() >= sta2.top())
              << std::endl;
    std::cout << GREEN
              << "\t-sta1(5) <= sta2(4) = " << (sta1.top() <= sta2.top())
              << CLEAN << std::endl;
}