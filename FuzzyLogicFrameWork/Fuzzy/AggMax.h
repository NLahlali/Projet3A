#ifndef AGGMAX_H_INCLUDED
#define AGGMAX_H_INCLUDED

#include "Operators.h"

namespace fuzzy{

template <class T>
class AggMax : public Agg<T>
{
public :
	T evaluate(Expression<T>*, Expression<T>*) const;
};

template <class T>
T AggMax<T>::evaluate(Expression<T>* left, Expression<T>* right) const{
	T lv=left->evaluate();
	T rv=right->evaluate();
	return (lv<rv)?lv:rv;
}

}

#endif // AGGMAX_H_INCLUDED
