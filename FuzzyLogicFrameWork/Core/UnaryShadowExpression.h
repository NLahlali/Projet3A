#ifndef UNARYSHADOWEXPRESSION_H_INCLUDED
#define UNARYSHADOWEXPRESSION_H_INCLUDED

#include"UnaryExpression.h"

namespace core
{

template <class T>
class UnaryShadowExpression:public UnaryExpression<T>
{
public:
	UnaryShadowExpression(UnaryExpression<T>*);
	T evaluate(Expression<T>*) const;
	void setTarget(UnaryExpression<T>*);

private:
	UnaryExpression<T>* target;
};


template <class T>
UnaryShadowExpression<T>::UnaryShadowExpression(UnaryExpression<T>* _target):target(_target){}

template <class T>
void UnaryShadowExpression<T>::setTarget(UnaryExpression<T>* t)
{
	target=t;
}

template <class T>
T UnaryShadowExpression<T>::evaluate(Expression<T>* e) const
{
	if (target!=NULL)
        return target->evaluate(e);

	return NULL;
}

}

#endif // UNARYSHADOWEXPRESSION_H_INCLUDED
