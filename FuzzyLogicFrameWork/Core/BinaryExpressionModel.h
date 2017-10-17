#ifndef BINARYEXPRESSIONMODEL_H_INCLUDED
#define BINARYEXPRESSIONMODEL_H_INCLUDED

#include"BinaryExpression.h"
#include"Expression.h"

namespace core{

template <class T>
class BinaryExpressionModel : public BinaryExpression<T>, public Expression<T>{

private:
    Expression<T>* left;
    Expression<T>* right;
    BinaryExpression<T>* operatr;

public:
    BinaryExpressionModel();
    BinaryExpressionModel(BinaryExpression<T>*,Expression<T>*, Expression<T>*);
    T evaluate() const;
    T evaluate(Expression<T>*, Expression<T>*) const;

    virtual BinaryExpression<T>* getOperator() const;

};

template <class T>
BinaryExpressionModel<T>::BinaryExpressionModel():operatr(NULL),left(NULL), right(NULL){
}
template <class T>
BinaryExpressionModel<T>::BinaryExpressionModel(BinaryExpression<T>* be, Expression<T>* l, Expression<T>* r):operatr(be), left(l), right(r){
}
template <class T>
T BinaryExpressionModel<T>::evaluate() const{
    if(left==NULL && right==NULL) throw std::string("Operands null\n"); //later create exception class
    return evaluate(left, right);
}

template <class T>
T BinaryExpressionModel<T>::evaluate(Expression<T>* l, Expression<T>* r) const
{
    if(operatr==NULL) throw std::string("Operator null\n"); //later create exception class
    return operatr->evaluate(l, r);
}

template<class T>
BinaryExpression<T>* BinaryExpressionModel<T>::getOperator() const{
    return operatr;
}

}

#endif // BINARYEXPRESSIONMODEL_H_INCLUDED
