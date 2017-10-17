#ifndef THENMIN_H_INCLUDED
#define THENMIN_H_INCLUDED

#include "Operators.h"

namespace fuzzy{

template <class T>
class ThenMin : public Then<T>
{
public :
	T evaluate(Expression<T>*, Expression<T>*) const;
};

template <class T>
T ThenMin<T>::evaluate(Expression<T>* left, Expression<T>* right) const{
		T lv=left->evaluate();
		T rv=right->evaluate();
		return (lv<rv)?lv:rv;
}

}
#endif // THENMIN_H_INCLUDED
