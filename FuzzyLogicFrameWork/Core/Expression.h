#ifndef EXPRESSION_H_INCLUDED
#define EXPRESSION_H_INCLUDED

namespace core{

template <class T>
class Expression{

public:
    virtual T evaluate() const=0;

};

}

#endif // EXPRESSION_H_INCLUDED
