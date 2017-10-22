#ifndef NARYSHADOWEXPRESSION_H
#define NARYSHADOWEXPRESSION_H

#include"NaryExpression.h"

namespace core
{

	template <class T>
	class NaryShadowExpression:public NaryExpression<T>
	{
	public:
		NaryShadowExpression(NaryExpression<T>*);
		T evaluate(std::vector<Expression<T>*>* operands) const;
	private:
		NaryExpression<T>* target;
	};


	template<class T>
	NaryShadowExpression<T>::NaryShadowExpression(NaryExpression<T>*_target):
	target(_target)
	{}


	template<class T>
	T NaryShadowExpression<T>::evaluate(std::vector<Expression<T>*>* operands) const
	{
		if(target!=NULL)
			return target->evaluate(operands);
		return NULL;
	}

}



#endif
