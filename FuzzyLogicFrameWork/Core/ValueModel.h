#ifndef VALUEMODEL_H_INCLUDED
#define VALUEMODEL_H_INCLUDED

#include "Expression.h"

namespace core{

template <class T>
class ValueModel : public Expression<T>{

private:
    T value;

public:
    ValueModel();
    ValueModel(const T&);
    virtual T evaluate() const;
    void setValue(const T&);

};

template <class T>
ValueModel<T>::ValueModel(const T& v):value(v){
}
template <class T>
ValueModel<T>::ValueModel():value(0){
}
template <class T>
void ValueModel<T>::setValue(const T& v){
    value=v;
}
template <class T>
T ValueModel<T>::evaluate() const{
    return value;
}

}
#endif // VALUEMODEL_H_INCLUDED
