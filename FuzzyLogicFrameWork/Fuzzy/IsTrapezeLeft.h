#ifndef ISTRAPEZELEFT_H_INCLUDED
#define ISTRAPEZELEFT_H_INCLUDED

#include "Operators.h"

namespace fuzzy
{

template <class T>
class IsTrapezeLeft:public Is<T>
{
public:
	IsTrapezeLeft(T, T,T);
	T getMin();
	T getMid();
	T getMax();
	void setMin(T&);
	void setMid(T&);
	void setMax(T&);
	T evaluate(Expression<T>*) const;

private:
	T _min;
	T _mid;
	T _max;
};


template <class T>
IsTrapezeLeft<T>::IsTrapezeLeft(T mini, T mid, T maxi):_min(mini),_mid(mid),_max(maxi){}

template <class T>
T IsTrapezeLeft<T>::getMin()
{
	return _min;
}

template <class T>
T IsTrapezeLeft<T>::getMid()
{
	return _mid;
}

template <class T>
T IsTrapezeLeft<T>::getMax()
{
	return _max;
}

template <class T>
void IsTrapezeLeft<T>::setMin(T& mini)
{
	_min=mini;
}

template <class T>
void IsTrapezeLeft<T>::setMid(T& mid)
{
	_mid=mid;
}

template <class T>
void IsTrapezeLeft<T>::setMax(T& maxi)
{
	_max=maxi;
}

template <class T>
T IsTrapezeLeft<T>::evaluate(Expression<T>* e) const
{
	T ev=e->evaluate();
	if (ev<=_min || ev >=_max)
		return 0;
	return (ev<=_mid)?1:((_max-ev)/(_max-_mid));
}

}

#endif // TRAPEZELEFT_H_INCLUDED
