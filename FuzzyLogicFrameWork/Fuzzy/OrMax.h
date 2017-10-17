#ifndef ORMAX_H_INCLUDED
#define ORMAX_H_INCLUDED

#include "Operators.h"

namespace fuzzy{

template <class T>
class OrMax: public Or<T>
{
public:
	T evaluate(Expression<T>*, Expression<T>*) const;
};

template <class T>
T OrMax<T>::evaluate(Expression<T>* l, Expression<T>* r) const{
	T lv = l->evaluate();
	T rv = r->evaluate();
	return (lv>=rv)? lv : rv;
}

}

#endif // ORMAX_H_INCLUDED
