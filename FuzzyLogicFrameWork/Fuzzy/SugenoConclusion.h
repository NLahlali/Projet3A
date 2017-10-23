#ifndef SUGENOCONCLUSION_H
#define SUGENOCONCLUSION_H

#include "../Core/NaryExpression.h"

namespace fuzzy
{
    template <class T>
    class SugenoConclusion : public core::NaryExpression<T>
    {
    public:
        SugenoConclusion();
        SugenoConclusion(const std::vector<T> *coeff_);
        virtual ~SugenoConclusion() {};
    

        virtual T evaluate(std::vector<core::Expression<T>*>* operands) const;

    private:
		const std::vector<T> *coeff;
    };
    template<class T>
    SugenoConclusion<T>::SugenoConclusion(){}
    template<class T>
    SugenoConclusion<T>::SugenoConclusion(const std::vector<T> *coeff_):coeff(coeff_)
    {
    }

    template<class T>
    T SugenoConclusion <T>::evaluate(std::vector<core::Expression<T>*>* operands) const
    {
    typename std::vector<T>::const_iterator iteratorCoef = this->coeff->begin();
    typename std::vector<const core::Expression<T>*>::const_iterator iteratorExpr = operands->begin();
    T result = 0;
    
    for(iteratorCoef = this->coeff->begin(), iteratorExpr = operands->begin(); iteratorExpr != operands->end() && iteratorCoef != this->coeff->end(); iteratorExpr++, iteratorCoef++) {
        T eval = (*iteratorExpr)->evaluate();
        result += *iteratorCoef * eval;
    }
    
    // Si les 2 vectors n'avaient pas le mme nombre d'Žlements.
    if (iteratorExpr != operands->end())
        throw(std::exception());
    
    return result;
    }
}

#endif
