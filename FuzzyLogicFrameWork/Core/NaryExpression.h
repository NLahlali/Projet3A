#ifndef NARYEXPRESSION_H_INCLUDED
#define NARYEXPRESSION_H_INCLUDED

#include "Expression.h"
#include <vector>

namespace core
{

template <class T>
class NaryExpression
{
public:
    virtual ~NaryExpression(){};
    virtual T evaluate(std::vector<Expression<T>* >*) const=0;
};

}

#endif // NARYEXPRESSION_H_INCLUDED
