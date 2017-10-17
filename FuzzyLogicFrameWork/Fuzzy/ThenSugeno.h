#ifndef THENSUGENO_H_INCLUDED
#define THENSUGENO_H_INCLUDED

#include "Operators.h"

namespace fuzzy
{

template<class T>
class ThenSugeno : public Then<T>
{
    public:
       ThenSugeno();
       virtual ~ThenSugeno(){}
       virtual T evaluate(core::Expression<T> *l, core::Expression<T> *r) const;
       virtual T premiseValue();
    private:
       mutable T m_premiseValue;
};

template<class T>
ThenSugeno<T>::ThenSugeno(){}

template<class T>
T ThenSugeno<T>::evaluate(core::Expression<T> *l, core::Expression<T> *r) const
{
    T _l = l->evaluate();
    T _r = r->evaluate();
    T _mult = _l * _r;
    m_premiseValue = _l;
    return _mult;
}

template<class T>
T ThenSugeno<T>::premiseValue()
{
    return m_premiseValue;
}

}

#endif // THENSUGENO_H_INCLUDED
