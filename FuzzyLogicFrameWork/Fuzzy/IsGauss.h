#ifndef ISGAUSS_H_INCLUDED
#define ISGAUSS_H_INCLUDED

#include <cmath>
#include "Operators.h"

namespace fuzzy{

template <class T>
class IsGauss : public Is<T>
{
public:
    IsGauss(T, T);
	T evaluate(Expression<T>*) const;

private:
	T _sigma;
    T _c;
};

template <class T>
IsGauss<T>::IsGauss (T sigma, T c):_sigma(sigma),_c(c){}

template <class T>
T IsGauss<T>::evaluate(Expression<T>* e) const
{
	T ev=e->evaluate();
	return std:: exp((-pow((ev-_c),2))/2*pow(_sigma,2));
}

}


#endif // GAUSS_H_INCLUDED
