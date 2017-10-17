#include <iostream>
#include <iomanip>
#include "Tests.h"


void tests(){
    std::cout << std::setw(50);
    std::cout << "==========>UNITARY TESTS<==========" << std::endl;
    //core_main_tests();
    fuzzy_main_tests();
    std::cout << std::setw(50);
    std::cout << std::endl<< "==========>GLOBAL TESTS<==========" << std::endl;
    //global_main_tests();
}

void main_fuzzy_logic(){
    std::cout << std::setw(50);
    std::cout <<std::endl<< "==========>EXECUTION<==========" << std::endl;
    execution_fuzzy();
}


int main()
{
    tests();
    main_fuzzy_logic();
    return 0;
}
