#ifndef ASSERT_H_INCLUDED
#define ASSERT_H_INCLUDED

#include <iostream>

#define ASSERT(x) \
	if (!(x)) \
		{ \
		std::cout << std::endl << "ASSERT ERROR " << #x << " failed" << std::endl; \
		std::cout << "on line " << __LINE__ << std::endl; \
		std::cout << "in file " << __FILE__ << std::endl; \
		}

#endif // ASSERT_H_INCLUDED
