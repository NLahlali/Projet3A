#ifndef EXPRESSIONFACTORY_H_INCLUDED
#define EXPRESSIONFACTORY_H_INCLUDED

#include <set>
#include"BinaryExpressionModel.h"
#include"UnaryExpressionModel.h"
#include"Expression.h"
#include "NaryExpressionModel.h"

namespace core
{

template <class T>
class ExpressionFactory
{
public:
    typedef std::set<Expression<T>*> Memory;
    ExpressionFactory() {};
    virtual ~ExpressionFactory();

    UnaryExpressionModel<T>* newUnary(UnaryExpression<T>*, Expression<T>*);
    BinaryExpressionModel<T>* newBinary(BinaryExpression<T>*, Expression<T>*, Expression<T>*);
    NaryExpressionModel<T>* newNary(NaryExpression<T>*, std::vector<Expression<T>*>*);
    ValueModel<T>* newValue();

    unsigned long memorySize() const;


protected:
    Expression<T>* hold(Expression<T>*);

private:
   Memory memory;
};

template <class T>
ExpressionFactory<T>::~ExpressionFactory()
{
    typename Memory ::iterator it=memory.begin();
    for ( ;it != memory.end(); it++){
        delete *it;
    }
}

template <class T>
UnaryExpressionModel<T>* ExpressionFactory<T>::newUnary(UnaryExpression<T>* operateur, Expression<T>* operande)
{
    return (UnaryExpressionModel<T>*) hold(new UnaryExpressionModel<T>(operateur, operande));
}

template <class T>
BinaryExpressionModel<T>* ExpressionFactory<T>::newBinary(BinaryExpression<T>* operateur, Expression<T>* l, Expression<T>* r)
{
    return (BinaryExpressionModel<T>*) hold(new BinaryExpressionModel<T>(operateur, l, r));
}

template <class T>
NaryExpressionModel<T>* ExpressionFactory<T>::newNary(NaryExpression<T>* operateur, std::vector<Expression<T>*>* operandes)
{
    return (NaryExpressionModel<T>*) hold(new NaryExpressionModel<T>(operateur, operandes));
}

template <class T>
Expression<T>* ExpressionFactory<T>::hold(Expression<T>* e)
{
    memory.insert(e);
    return e;
}
template <class T>
unsigned long ExpressionFactory<T>::memorySize() const
{
    return memory.size();
}

}

#endif // EXPRESSIONFACTORY_H_INCLUDED
