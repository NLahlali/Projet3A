#ifndef MANDANIDEFUZZ_H_INCLUDED
#define MANDANIDEFUZZ_H_INCLUDED

#include"BinaryExpression.h"

namespace core
{

template <class T>
class MandaniDefuzz:public BinaryExpression<T>{

public :
    MandaniDefuzz();
	MandaniDefuzz(const T&,const T&,const T&);
	T evaluate(Expression<T>* l,Expression<T>* _r) const;
    virtual T defuzz(const typename Evaluator<T>::Shape&) const=0;
    void setMin(const T&);
    void setMax(const T&);
    void setStep(const T&);

private:
	T mini, maxi, step, current;

};

template<class T>
MandaniDefuzz<T>::MandaniDefuzz(const T& _min,const T& _max,const T& _step):mini(_min),maxi(_max),step(_step){
}
template<class T>
MandaniDefuzz<T>::MandaniDefuzz(){
}

template<class T>
T MandaniDefuzz<T>::evaluate(Expression<T>* s,Expression<T>* var) const{
    return defuzz( Evaluator<T>::BuildShape(mini, maxi, step,(ValueModel<T>*)s,var));
}

template<class T>
void MandaniDefuzz<T>::setMin(const T& _min){
    mini=_min;
}

template<class T>
void MandaniDefuzz<T>::setMax(const T& _max){
    maxi=_max;
}
template<class T>
void MandaniDefuzz<T>::setStep(const T& _step){
    step=_step;
}

}

#endif // MANDANIDEFUZZ_H_INCLUDED
