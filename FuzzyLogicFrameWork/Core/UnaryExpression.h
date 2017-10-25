#ifndef UNARYEXPRESSION_H_INCLUDED
#define UNARYEXPRESSION_H_INCLUDED

#include "Expression.h"

namespace core{

template <class T>
class UnaryExpression{

public :
    virtual ~UnaryExpression(){};
    virtual T evaluate(Expression<T>*) const=0;

};

}

#endif // UNARYEXPRESSION_H_INCLUDED
