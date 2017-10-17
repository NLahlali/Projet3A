#ifndef UNARYEXPRESSIONMODEL_H_INCLUDED
#define UNARYEXPRESSIONMODEL_H_INCLUDED

#include <stdio.h>
#include <string>
#include"UnaryExpression.h"
#include"Expression.h"

namespace core{

template <class T>
class UnaryExpressionModel : public UnaryExpression<T>, public Expression<T>{

private:
    Expression<T>* operand;
    UnaryExpression<T>* operatr;

public:
    UnaryExpressionModel();
    UnaryExpressionModel(UnaryExpression<T>*,Expression<T>*);
    T evaluate() const;
    T evaluate(Expression<T>*) const;

};

template <class T>
UnaryExpressionModel<T>::UnaryExpressionModel():operatr(NULL),operand(NULL){
}

template <class T>
UnaryExpressionModel<T>::UnaryExpressionModel(UnaryExpression<T>* ue, Expression<T>* e):operatr(ue), operand(e){
}
template <class T>
T UnaryExpressionModel<T>::evaluate(Expression<T>* o) const{
    if(operatr==NULL) throw std::string("Operator null\n"); //later create exception class
    return operatr->evaluate(o);
}
template <class T>
T UnaryExpressionModel<T>::evaluate() const{
    if(operand==NULL) throw std::string("Operand null\n"); //later create exception class
    return evaluate(operand);
}

}
#endif // UNARYEXPRESSIONMODEL_H_INCLUDED
