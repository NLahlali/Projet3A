#ifndef ISBELL_H_INCLUDED
#define ISBELL_H_INCLUDED

#include <cmath>
#include "Operators.h"

namespace fuzzy{

template <class T>
class IsBell : public Is<T>
{
public:
	IsBell(T&, T&, T&);
	T evaluate(Expression<T>*) const;

private:
	T _a;
	T _b;
	T _c;

};


template <class T>
IsBell<T>::IsBell(T& a, T& b, T& c):_a(a),_b(b),_c(c){}

template <class T>
T IsBell<T>::evaluate(Expression<T>* e) const
{
	T ev=e->evaluate();
	return 1/(1+ pow(std::abs((ev - _c)/_a),2*_b));
}

}

#endif // ISBELL_H_INCLUDED
