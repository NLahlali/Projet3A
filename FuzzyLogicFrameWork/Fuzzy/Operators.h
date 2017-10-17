#ifndef OPERATORS_H_INCLUDED
#define OPERATORS_H_INCLUDED

#include "../Core/UnaryExpression.h"
#include "../Core/BinaryExpression.h"
#include "../Core/Expression.h"

using namespace core;

template <class T>
class And : public BinaryExpression<T>{

public :
    virtual T evaluate(Expression<T>*, Expression<T>*) const=0;
};

template <class T>
class Is : public UnaryExpression<T>{

public :
    virtual T evaluate(Expression<T>*) const=0;
};

template <class T>
class Not : public UnaryExpression<T>{

public :
    virtual T evaluate(Expression<T>*) const=0;
};

template <class T>
class Then : public BinaryExpression<T>
{
public:
	virtual T evaluate(Expression<T>*,Expression<T>*) const=0;
};

template <class T>
class Agg : public BinaryExpression<T>
{
public:
	virtual T evaluate(Expression<T>*,Expression<T>*) const=0;
};

template <class T>
class Or : public BinaryExpression<T>
{
public:
	virtual T evaluate(Expression<T>*,Expression<T>*) const=0;
};




#endif // OPERATORS_H_INCLUDED
