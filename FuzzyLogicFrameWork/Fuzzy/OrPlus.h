#ifndef ORPLUS_H_INCLUDED
#define ORPLUS_H_INCLUDED

#include "Operators.h"

namespace fuzzy{

template <class T>
class OrPlus : public Or<T>
{
public :
	T evaluate(Expression<T>*, Expression<T>*) const;
};

template <class T>
T OrPlus<T>::evaluate(Expression<T>* l, Expression<T>* r) const{
	T lv=l->evaluate();
	T rv=r->evaluate();
	return lv+rv;
}

}

#endif // ORPLUS_H_INCLUDED
