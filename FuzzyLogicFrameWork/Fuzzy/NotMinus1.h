#ifndef NOTMINUS1_H_INCLUDED
#define NOTMINUS1_H_INCLUDED

#include "Operators.h"

namespace fuzzy{

template <class T>
class NotMinus1 : public Not<T>{

public :
    virtual T evaluate(Expression<T>*) const;
};

template <class T>
T NotMinus1<T>::evaluate(Expression<T>* e) const{
    T ev=e->evaluate();
    return 1-ev;
}

}
#endif // NOTMINUS1_H_INCLUDED
