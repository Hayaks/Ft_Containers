#include "../include/container.hpp"
#include <string>

const std::string CLEAN = "\033[0m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string WHITE = "\033[1m\033[37m";

void ft_map_constructor()
{
    FT::map< std::string, std::string > empty;
    FT::map< int, std::string >         map_1;
    map_1[0] = "A";
    map_1.insert(FT::make_pair(1, "BB"));
    map_1[2] = "CCC";
    map_1.insert(FT::make_pair(3, "DDDD"));
    FT::map< int, std::string > map_2(++map_1.begin(), --map_1.end());
    FT::map< int, std::string > map_copy(map_2);
    FT::map< int, std::string > map_assign;
    map_assign = map_1;

    std::cout << WHITE + "\n||||| Constructor/Destructor |||||" + CLEAN
              << std::endl;
    std::cout << YELLOW + "\nEmpty:" + CLEAN << std::endl;
    std::cout << GREEN << "\t-Size: " << empty.size() << CLEAN << std::endl;

    std::cout << YELLOW + "\nmap_1:" + CLEAN << std::endl;
    std::cout << GREEN << "\t-Size: " << map_1.size() << CLEAN << std::endl;
    std::cout << GREEN + "\t-Elements: " << std::endl;
    for (FT::map< int, std::string >::iterator it = map_1.begin();
         it != map_1.end(); ++it)
        std::cout << "\t\t-Key: " << (*it).first << " -Value: " << (*it).second
                  << std::endl;
    std::cout << CLEAN;

    std::cout << YELLOW + "\nmap_2 (range):" + CLEAN << std::endl;
    std::cout << GREEN << "\t-Size: " << map_2.size() << CLEAN << std::endl;
    std::cout << GREEN + "\t-Elements: " << std::endl;
    for (FT::map< int, std::string >::iterator it = map_2.begin();
         it != map_2.end(); ++it)
        std::cout << "\t\t-Key: " << (*it).first << " -Value: " << (*it).second
                  << std::endl;
    std::cout << CLEAN;

    std::cout << YELLOW + "\nmap_copy:" + CLEAN << std::endl;
    std::cout << GREEN << "\t-Size: " << map_copy.size() << CLEAN << std::endl;
    std::cout << GREEN + "\t-Elements: " << std::endl;
    for (FT::map< int, std::string >::iterator it = map_copy.begin();
         it != map_copy.end(); ++it)
        std::cout << "\t\t-Key: " << (*it).first << " -Value: " << (*it).second
                  << std::endl;
    std::cout << CLEAN;

    std::cout << YELLOW + "\nmap_assign:" + CLEAN << std::endl;
    std::cout << GREEN << "\t-Size: " << map_assign.size() << CLEAN
              << std::endl;
    std::cout << GREEN + "\t-Elements: " << std::endl;
    for (FT::map< int, std::string >::iterator it = map_assign.begin();
         it != map_assign.end(); ++it)
        std::cout << "\t\t-Key: " << (*it).first << " -Value: " << (*it).second
                  << std::endl;
    std::cout << CLEAN;
}

void ft_map_iterator_element_access()
{
    FT::map< int, std::string >                   map_1;
    FT::map< int, std::string >::iterator         it;
    FT::map< int, std::string >::reverse_iterator rit;

    map_1[0] = "Bonjour";
    map_1[1] = "Adieu";
    map_1[2] = "Te revoila";

    std::cout << WHITE + "\n||||| Iterators |||||" + CLEAN << std::endl;
    std::cout << YELLOW + "\nMap with 3 values:" + CLEAN << std::endl;
    std::cout << GREEN + "\t-Elements: " << std::endl;
    for (FT::map< int, std::string >::iterator it = map_1.begin();
         it != map_1.end(); ++it)
        std::cout << "\t\t-Key: " << (*it).first << " -Value: " << (*it).second
                  << std::endl;
    std::cout << CLEAN;

    it = map_1.begin();
    std::cout << YELLOW + "\nChange it for (Hi):" + CLEAN << std::endl;
    it->second = "Hi";
    std::cout << GREEN << "\t-Key: " << (*it).first
              << " -Value: " << (*it).second << CLEAN << std::endl;

    std::cout << YELLOW + "\nChange it++ for (Hola):" + CLEAN << std::endl;
    it++;
    it->second = "Hola";
    std::cout << GREEN << "\t-Key: " << (*it).first
              << " -Value: " << (*it).second << CLEAN << std::endl;

    std::cout << YELLOW + "\nChange it-- for (ADIOS AMIGOS):" + CLEAN
              << std::endl;
    it--;
    it->second = "ADIOS AMIGOS";
    std::cout << GREEN << "\t-Key: " << (*it).first
              << " -Value: " << (*it).second << CLEAN << std::endl;

    std::cout << YELLOW + "\nFinal:" + CLEAN << std::endl;
    std::cout << GREEN + "\t-Elements: " << std::endl;
    for (FT::map< int, std::string >::iterator it = map_1.begin();
         it != map_1.end(); ++it)
        std::cout << "\t\t-Key: " << (*it).first << " -Value: " << (*it).second
                  << std::endl;
    std::cout << CLEAN;

    rit = map_1.rbegin();
    std::cout << YELLOW + "\nChange rit for (Wesh):" + CLEAN << std::endl;
    rit->second = "Wesh";
    std::cout << GREEN << "\t-Key: " << (*rit).first
              << " -Value: " << (*rit).second << CLEAN << std::endl;

    std::cout << YELLOW + "\nChange rit++ for (YO):" + CLEAN << std::endl;
    rit++;
    rit->second = "Hola";
    std::cout << GREEN << "\t-Key: " << (*rit).first
              << " -Value: " << (*rit).second << CLEAN << std::endl;

    std::cout << YELLOW + "\nFinal en reverse:" + CLEAN << std::endl;
    std::cout << GREEN + "\t-Elements: " << std::endl;
    for (FT::map< int, std::string >::reverse_iterator rit2 = map_1.rbegin();
         rit2 != map_1.rend(); ++rit2)
        std::cout << "\t\t-Key: " << (*rit2).first
                  << " -Value: " << (*rit2).second << std::endl;
    std::cout << CLEAN;

    std::cout << WHITE + "\n||||| Element access |||||" + CLEAN << std::endl;
    std::cout << YELLOW + "\n[1]" + CLEAN << std::endl;
    std::cout << GREEN << "\t-map_1tor[1]: " << map_1[1] << CLEAN << std::endl;
}

void ft_map_compare()
{
    FT::map< int, std::string > map_1;
    FT::map< int, std::string > map_2;

    map_1[0] = "Hola mi amigo";
    map_1[2] = "Godbye my friend";
    map_1[1] = "A bientot mon ami";

    map_2[87] = "J'ai plus trop d'idée";
    map_2[9] = "Ah si j'ai une idée";
    map_2[807] = "Non au final";

    std::cout << WHITE + "\n||||| Comparaison |||||" + CLEAN << std::endl;
    std::cout << YELLOW + "\nmap_1:" + CLEAN << std::endl;
    std::cout << GREEN + "\t-Elements: " << std::endl;
    for (FT::map< int, std::string >::iterator it = map_1.begin();
         it != map_1.end(); ++it)
        std::cout << "\t\t-Key: " << (*it).first << " -Value: " << (*it).second
                  << std::endl;

    std::cout << YELLOW + "\nmap_2:" + CLEAN << std::endl;
    std::cout << GREEN + "\t-Elements: " << std::endl;
    for (FT::map< int, std::string >::iterator it = map_2.begin();
         it != map_2.end(); ++it)
        std::cout << "\t\t-Key: " << (*it).first << " -Value: " << (*it).second
                  << std::endl;

    std::cout << GREEN << "\t-map_1 == map_2 = " << (map_1 == map_2)
              << std::endl;
    std::cout << GREEN << "\t-map_1 != map_2 = " << (map_1 != map_2)
              << std::endl;
    std::cout << GREEN << "\t-map_1 < map_2 = " << (map_1 < map_2) << std::endl;
    std::cout << GREEN << "\t-map_1 > map_2 = " << (map_1 > map_2) << std::endl;
    std::cout << GREEN << "\t-map_1 <= map_2 = " << (map_1 <= map_2)
              << std::endl;
    std::cout << GREEN << "\t-map_1 >= map_2 = " << (map_1 >= map_2)
              << std::endl;
    std::cout << CLEAN;
}

void ft_map_capacity()
{
    std::cout << WHITE + "\n||||| Capacity |||||" + CLEAN << std::endl;

    FT::map< int, std::string > map_1;
    std::cout << YELLOW + "\nmap empty:" + CLEAN << std::endl;
    std::cout << GREEN << "\t-Empty: " << map_1.empty() << CLEAN << std::endl;
    std::cout << GREEN << "\t-Size: " << map_1.size() << CLEAN << std::endl;
    std::cout << GREEN << "\t-Max_size: " << map_1.max_size() << CLEAN
              << std::endl;

    map_1[3] = "SURPRISE";
    std::cout << YELLOW + "\nmap with a value:" + CLEAN << std::endl;
    std::cout << GREEN << "\t-Empty: " << map_1.empty() << CLEAN << std::endl;
    std::cout << GREEN << "\t-Size: " << map_1.size() << CLEAN << std::endl;
    std::cout << GREEN << "\t-Max_size: " << map_1.max_size() << CLEAN
              << std::endl;
}

void ft_map_modifiers()
{
    FT::map< int, std::string > map_1;
    FT::map< int, std::string > map_2;

    map_2[0] = "A";
    map_2[1] = "BB";
    map_2[2] = "CCC";

    std::cout << WHITE + "\n||||| Modifiers |||||" + CLEAN << std::endl;
    map_1.insert(FT::make_pair(3, "DDDD"));
    std::cout << YELLOW + "\nInsert pair<3, DDDD>" + CLEAN << std::endl;
    std::cout << GREEN + "\t-Elements: " << std::endl;
    for (FT::map< int, std::string >::iterator it = map_1.begin();
         it != map_1.end(); ++it)
        std::cout << "\t\t-Key: " << (*it).first << " -Value: " << (*it).second
                  << std::endl;
    std::cout << CLEAN;

    map_1.insert(map_2.begin(), --map_2.end());
    std::cout << YELLOW + "\nInsert range map_2" + CLEAN << std::endl;
    std::cout << GREEN + "\t-Elements: " << std::endl;
    for (FT::map< int, std::string >::iterator it = map_1.begin();
         it != map_1.end(); ++it)
        std::cout << "\t\t-Key: " << (*it).first << " -Value: " << (*it).second
                  << std::endl;
    std::cout << CLEAN;

    map_1.erase(--map_1.end());
    std::cout << YELLOW + "\nErase --end" + CLEAN << std::endl;
    std::cout << GREEN + "\t-Elements: " << std::endl;
    for (FT::map< int, std::string >::iterator it = map_1.begin();
         it != map_1.end(); ++it)
        std::cout << "\t\t-Key: " << (*it).first << " -Value: " << (*it).second
                  << std::endl;
    std::cout << CLEAN;

    map_1.erase(map_1.begin(), map_1.end());
    std::cout << YELLOW + "\nErase begin at end" + CLEAN << std::endl;
    std::cout << GREEN + "\t-Elements: " << std::endl;
    for (FT::map< int, std::string >::iterator it = map_1.begin();
         it != map_1.end(); ++it)
        std::cout << "\t\t-Key: " << (*it).first << " -Value: " << (*it).second
                  << std::endl;
    std::cout << CLEAN;

    std::cout << YELLOW + "\nBefore swap map_1 and map_2" + CLEAN << std::endl;
    std::cout << GREEN + "\t-Elements map_1: " << std::endl;
    for (FT::map< int, std::string >::iterator it = map_1.begin();
         it != map_1.end(); ++it)
        std::cout << "\t\t-Key: " << (*it).first << " -Value: " << (*it).second
                  << std::endl;
    std::cout << GREEN + "\t-Elements map_2: " << std::endl;
    for (FT::map< int, std::string >::iterator it = map_2.begin();
         it != map_2.end(); ++it)
        std::cout << "\t\t-Key: " << (*it).first << " -Value: " << (*it).second
                  << std::endl;
    std::cout << CLEAN;

    map_1.swap(map_2);
    std::cout << YELLOW + "\nAfter swap map_1 and map_2" + CLEAN << std::endl;
    std::cout << GREEN + "\t-Elements map_1: " << std::endl;
    for (FT::map< int, std::string >::iterator it = map_1.begin();
         it != map_1.end(); ++it)
        std::cout << "\t\t-Key: " << (*it).first << " -Value: " << (*it).second
                  << std::endl;
    std::cout << GREEN + "\t-Elements map_2: " << std::endl;
    for (FT::map< int, std::string >::iterator it = map_2.begin();
         it != map_2.end(); ++it)
        std::cout << "\t\t-Key: " << (*it).first << " -Value: " << (*it).second
                  << std::endl;
    std::cout << CLEAN;

    map_1.clear();
    std::cout << YELLOW + "\nClear map_1" + CLEAN << std::endl;
    std::cout << GREEN + "\t-Elements: " << std::endl;
    for (FT::map< int, std::string >::iterator it = map_1.begin();
         it != map_1.end(); ++it)
        std::cout << "\t\t-Key: " << (*it).first << " -Value: " << (*it).second
                  << std::endl;
    std::cout << CLEAN;
}

void ft_map_observers()
{
    FT::map< int, int >              map_1;
    FT::map< int, int >::key_compare cmp_map = map_1.key_comp();

    map_1[76] = 22;
    map_1[0] = 90;
    map_1[2] = 2012;

    std::cout << WHITE + "\n||||| Observers |||||" + CLEAN << std::endl;
    std::cout << YELLOW + "\nKey_comp:" + CLEAN << std::endl;
    std::cout << GREEN
              << "Cmp(map_1[0], map_1[76]) = " << cmp_map(map_1[0], map_1[76])
              << CLEAN << std::endl;
    std::cout << GREEN
              << "Cmp(map_1[76], map_1[0]) = " << cmp_map(map_1[76], map_1[0])
              << CLEAN << std::endl;
    std::cout << GREEN
              << "Cmp(map_1[2], map_1[2]) = " << cmp_map(map_1[2], map_1[2])
              << CLEAN << std::endl;

    std::cout << YELLOW + "\nValue_Comp:" + CLEAN << std::endl;
    std::cout << GREEN << "Value_cmp(begin(), end()) = "
              << map_1.value_comp()(*map_1.begin(), *map_1.end()) << CLEAN
              << std::endl;
}

void ft_map_operations()
{
    FT::map< int, std::string >           map_1;
    FT::map< int, std::string >::iterator it;

    map_1[6] = "Banane";
    map_1[3] = "Pomme";
    map_1[1] = "Avocat";
    map_1[14] = "Litchi";

    std::cout << WHITE + "\n||||| Operations |||||" + CLEAN << std::endl;
    it = map_1.find(1);
    std::cout << YELLOW + "\nFind[1]:" + CLEAN << std::endl;
    std::cout << GREEN << "Find? = " << (*it).first << CLEAN << std::endl;

    it = map_1.find(14);
    std::cout << YELLOW + "\nFind[14]:" + CLEAN << std::endl;
    std::cout << GREEN << "Find? = " << (*it).first << CLEAN << std::endl;

    std::cout << YELLOW + "\nCount[1]:" + CLEAN << std::endl;
    std::cout << GREEN << "Count = " << map_1.count(1) << CLEAN << std::endl;

    std::cout << YELLOW + "\nCount[9]:" + CLEAN << std::endl;
    std::cout << GREEN << "Count = " << map_1.count(9) << CLEAN << std::endl;

    it = map_1.lower_bound(5);
    std::cout << YELLOW + "\nLower_bound[5]:" + CLEAN << std::endl;
    std::cout << GREEN << "Value? = " << (*it).first << CLEAN << std::endl;

    it = map_1.lower_bound(1);
    std::cout << YELLOW + "\nLower_bound[1]:" + CLEAN << std::endl;
    std::cout << GREEN << "Value? = " << (*it).first << CLEAN << std::endl;

    it = map_1.lower_bound(12);
    std::cout << YELLOW + "\nLower_bound[12]:" + CLEAN << std::endl;
    std::cout << GREEN << "Value? = " << (*it).first << CLEAN << std::endl;

    it = map_1.upper_bound(5);
    std::cout << YELLOW + "\nUpper_bound[5]:" + CLEAN << std::endl;
    std::cout << GREEN << "Value? = " << (*it).first << CLEAN << std::endl;

    it = map_1.upper_bound(1);
    std::cout << YELLOW + "\nUpper_bound[1]:" + CLEAN << std::endl;
    std::cout << GREEN << "Value? = " << (*it).first << CLEAN << std::endl;

    it = map_1.upper_bound(12);
    std::cout << YELLOW + "\nUpper_bound[12]:" + CLEAN << std::endl;
    std::cout << GREEN << "Value? = " << (*it).first << CLEAN << std::endl;

    FT::pair< FT::map< int, std::string >::iterator,
              FT::map< int, std::string >::iterator >
        ret = map_1.equal_range(8);
    std::cout << YELLOW + "\nEqual_range[8]:" + CLEAN << std::endl;
    std::cout << GREEN << ret.first->first << " => " << ret.first->second
              << CLEAN << std::endl;
    std::cout << GREEN << ret.second->first << " => " << ret.second->second
              << CLEAN << std::endl;
}