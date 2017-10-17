#ifndef ISTRIANGLE_H_INCLUDED
#define ISTRIANGLE_H_INCLUDED

#include "Operators.h"

namespace fuzzy{

template <class T>
class IsTriangle : public Is<T>{

public :
    IsTriangle(T,T,T);
    virtual T evaluate(Expression<T>*) const;

private:
    T _min, _mid, _max;
};
template <class T>
IsTriangle<T>::IsTriangle(T mi, T mid, T ma):_min(mi),_mid(mid),_max(ma){
}
template <class T>
T IsTriangle<T>::evaluate(Expression<T>* e) const{
    T ev=e->evaluate();
    if (ev<=_min || ev >=_max)
        return 0;
	return (ev<=_mid)?((ev - _min)/(_mid - _min)):((_max - ev)/(_max - _mid));
}

}
#endif // ISTRIANGLE_H_INCLUDED
