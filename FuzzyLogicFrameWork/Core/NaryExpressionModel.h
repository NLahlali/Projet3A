#ifndef NARYEXPRESSIONMODEL_H_INCLUDED
#define NARYEXPRESSIONMODEL_H_INCLUDED

#include"NaryExpression.h"

namespace core
{

template <class T>
class NaryExpressionModel:public Expression<T>,public NaryExpression<T>
{
public :
    NaryExpressionModel();
	NaryExpressionModel(NaryExpression<T>* ,std::vector<Expression<T>* >*);
	~NaryExpressionModel(){};
	T evaluate() const;
	T evaluate(std::vector<Expression<T>* >*) const;

private :
	NaryExpression<T>* operatr;
	std::vector<Expression<T>* >* operands;

};
template <class T>
NaryExpressionModel<T>::NaryExpressionModel(){}

template <class T>
NaryExpressionModel<T>::NaryExpressionModel(NaryExpression<T>* _ope,std::vector<Expression<T>* >* _operands):
operatr(_ope),operands(_operands){}

template <class T>
T NaryExpressionModel<T>::evaluate() const
{
	if (operands==NULL) throw std::string("Operands null\n"); //later create exception class
    return evaluate(operands);
}

template <class T>
T NaryExpressionModel<T>::evaluate(std::vector<Expression<T>* >* o)  const
{
    if (operatr==NULL) throw std::string("Operator null\n"); //later create exception class
	return operatr->evaluate(o);
}

}

#endif // NARYEXPRESSIONMODEL_H_INCLUDED
