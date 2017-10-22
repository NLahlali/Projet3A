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

    template <class T>
    T SugenoConclusion<T>::evaluate(std::vector<core::Expression<T>*>* operands) const
    {
		typename std::vector<T>::const_iterator itcoef = coeff->begin();
		typename std::vector<core::Expression<T>*>::const_iterator itexpr = operands->begin();
		T z = 0;

		// calcul de la somme des Zi
		for (; itexpr != operands->end() && itcoef != coeff->end(); itexpr++, itcoef++)
		{
			// evaluation de la rËgle courante
			T eval = (*itexpr)->evaluate();

			// multiplication par le coefficient associé à cette régle
			z += (*itcoef) * eval;
		}

		return z;
    }
}

#endif
