#ifndef ANDMIN_H_INCLUDED
#define ANDMIN_H_INCLUDED

#include "Operators.h"

namespace fuzzy{

template <class T>
class AndMin : public And<T>{

public :
    virtual T evaluate(Expression<T>*, Expression<T>*) const;
};

template <class T>
T AndMin<T>::evaluate(Expression<T>* left, Expression<T>* right) const{
    T lv=left->evaluate();
	T rv=right->evaluate();
	return (lv<rv)?lv:rv;
}

}
#endif // ANDMIN_H_INCLUDED
