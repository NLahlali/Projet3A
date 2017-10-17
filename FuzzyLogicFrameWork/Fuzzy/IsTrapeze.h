#ifndef ISTRAPEZE_H_INCLUDED
#define ISTRAPEZE_H_INCLUDED

#include "Operators.h"

namespace fuzzy{

template <class T>
class IsTrapeze : public Is<T>
{
public:
	IsTrapeze(T, T, T,T);
	T getMin();
	T getMidMin();
	T getMidMax();
	T getMax();
	void setMin(T&);
	void setMidMin(T&);
	void setMidMax(T&);
	void setMax(T&);
	T evaluate(Expression<T>*) const;

private:
	T _min;
	T _midmin;
	T _midmax;
	T _max;
};


template <class T>
IsTrapeze<T>::IsTrapeze(T mi, T midmin, T midmax, T ma):_min(mi),_midmin(midmin),_midmax(midmax),_max(ma){}

template <class T>
T IsTrapeze<T>::getMin()
{
	return _min;
}

template <class T>
T IsTrapeze<T>::getMidMin()
{
	return _midmin;
}

template <class T>
T IsTrapeze<T>::getMidMax()
{
	return _midmax;
}

template <class T>
T IsTrapeze<T>::getMax()
{
	return _max;
}

template <class T>
void IsTrapeze<T>::setMin(T& mi)
{
	_min=mi;
}

template <class T>
void IsTrapeze<T>::setMidMin(T& mid)
{
	_midmin=mid;
}

template <class T>
void IsTrapeze<T>::setMidMax(T& mid)
{
	_midmax=mid;
}

template <class T>
void IsTrapeze<T>::setMax(T& ma)
{
	_max=ma;
}

template <class T>
T IsTrapeze<T>::evaluate(Expression<T>* e) const
{
	T ev=e->evaluate();
	if (ev <= _min || ev >= _max)
		return 0;
	else if (ev >= _midmin && ev <=_midmax)
		return 1;
	return (ev <= _midmin)?((ev - _min)/(_midmin - _min)):((_max - ev)/(_max - _midmax));
}

}

#endif // ISTRAPEZE_H_INCLUDED
