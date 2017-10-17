#ifndef BINARYSHADOWEXPRESSION_H_INCLUDED
#define BINARYSHADOWEXPRESSION_H_INCLUDED

#include"BinaryExpression.h"

namespace core
{

template <class T>
class BinaryShadowExpression:public BinaryExpression<T>
{
public:
	BinaryShadowExpression(BinaryExpression<T>*);
	T evaluate(Expression<T>*,Expression<T>*) const;
	void setTarget(BinaryExpression<T>*);
	BinaryExpression<T>* getTarget();

private:
	BinaryExpression<T>* target;

};

template <class T>
BinaryShadowExpression<T>::BinaryShadowExpression(BinaryExpression<T>* _target):target(_target){}



template <class T>
T BinaryShadowExpression<T>::evaluate(Expression<T>* l,Expression<T>* r) const
{
	if (target==NULL) throw std::string("Operator null\n"); //later create exception class
    return target->evaluate(l,r);
}

template <class T>
void BinaryShadowExpression<T>::setTarget(BinaryExpression<T>* t){
    target=t;
}
template <class T>
BinaryExpression<T>* BinaryShadowExpression<T>::getTarget()
{
	return target;
}

}

#endif // BINARYSHADOWEXPRESSION_H_INCLUDED
