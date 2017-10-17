#ifndef COGDEFUZZ_H_INCLUDED
#define COGDEFUZZ_H_INCLUDED

#include"Evaluator.h"
#include"MandaniDefuzz.h"

namespace core
{

template <class T>
class CogDefuzz:public MandaniDefuzz<T>{

public :
    CogDefuzz();
	CogDefuzz(const T&,const T&,const T&);
	T defuzz(const typename Evaluator<T>::Shape&)const;
};

template <class T>
CogDefuzz<T>::CogDefuzz(const T& _min,const T& _max,const T& _step):MandaniDefuzz<T>(_min,_max,_step){
}

template <class T>
CogDefuzz<T>::CogDefuzz(){}


template <class T>
T CogDefuzz<T>::defuzz(const typename Evaluator<T>::Shape &s)const
{
	T x,y,num=0,den=0;
	for(unsigned int i=0; i<(s.first.size()-1); i++)
	{
		x=s.first.at(i);
		y=s.second.at(i);
		num+=x*y;
		den+=y;
	}
	return num/den;
}

}


#endif // COGDEFUZZ_H_INCLUDED
