#ifndef AGGPLUS_H_INCLUDED
#define AGGPLUS_H_INCLUDED

#include "Operators.h"

namespace fuzzy{

template <class T>
class AggPlus : public Agg<T>{

public :
	T evaluate(Expression<T>*, Expression<T>*) const;
};

template <class T>
T AggPlus<T>::evaluate(Expression<T>* l, Expression<T>* r) const{
	T lv=l->evaluate();
	T rv=r->evaluate();
	return lv+rv;
}

}



#endif // AGGPLUS_H_INCLUDED
