#ifndef ISTRAPEZERIGHT_H_INCLUDED
#define ISTRAPEZERIGHT_H_INCLUDED

#include "Operators.h"

namespace fuzzy
{

template <class T>
class IsTrapezeRight:public Is<T>
{
public:
	IsTrapezeRight(T, T,T);
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
IsTrapezeRight<T>::IsTrapezeRight(T mini, T mid, T maxi):_min(mini),_mid(mid),_max(maxi){}

template <class T>
T IsTrapezeRight<T>::getMin()
{
	return _min;
}

template <class T>
T IsTrapezeRight<T>::getMid()
{
	return _mid;
}

template <class T>
T IsTrapezeRight<T>::getMax()
{
	return _max;
}

template <class T>
void IsTrapezeRight<T>::setMin(T& mini)
{
	_min=mini;
}

template <class T>
void IsTrapezeRight<T>::setMid(T& mid)
{
	_mid=mid;
}

template <class T>
void IsTrapezeRight<T>::setMax(T& maxi)
{
	_max=maxi;
}

template <class T>
T IsTrapezeRight<T>::evaluate(Expression<T>* e) const
{
	T ev=e->evaluate();
	if (ev<=_min || ev >=_max)
		return 0;
	return (ev>=_mid)?1:((ev-_min)/(_mid-_min));
}

}

#endif // ISTRAPEZERIGHT_H_INCLUDED
