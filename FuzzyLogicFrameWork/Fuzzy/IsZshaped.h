#ifndef ISZSHAPED_H_INCLUDED
#define ISZSHAPED_H_INCLUDED

#include "Operators.h"

namespace fuzzy{

template <class T>
class IsZshaped : public Is<T>
{
public:
	IsZshaped(T&, T&);
	T evaluate(Expression<T>*) const;

private:
	T _a;
	T _b;

};


template <class T>
IsZshaped<T>::IsZshaped(T& a, T& b):_a(a),_b(b){}

template <class T>
T IsZshaped<T>::evaluate(Expression<T>* e) const
{
	T ev=e->evaluate();
	if(ev<=_a)
        return 1;
    else if(ev>_a && ev<= (_a + _b)/2)
        return 1 - 2*pow((ev - _a)/(_b - _a),2);
    else if((ev > (_a + _b)/2) && (ev < _b))
        return 2*pow(_b - (ev/(_b - _a)),2);
	return 0;
}

}

#endif // ISZSHAPED_H_INCLUDED
