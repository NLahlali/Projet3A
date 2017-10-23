#ifndef SUGENODEFUZZ_H_INCLUDED
#define SUGENODEFUZZ_H_INCLUDED

#include "../Core/NaryExpression.h"
#include "../Core/BinaryShadowExpression.h"
#include "../Core/BinaryExpressionModel.h"
#include "ThenSugeno.h"
#include <vector>

namespace fuzzy {
    
    template<class T>
    class SugenoDefuzz : public core::NaryExpression<T> {
    public:
        virtual T evaluate(std::vector<core::Expression<T>*> *operands) const;
    };
    
    template<class T>
    T SugenoDefuzz<T>::evaluate(std::vector<core::Expression<T>*> *operands) const {
        typename std::vector<const core::Expression<T>*>::const_iterator iterator = operands->begin();
        T numerator = 0;
        T denominator = 0;
        
        // numérateur : calcule la somme
        for(iterator = operands->begin(); iterator != operands->end(); iterator++) {
            numerator += (*iterator)->evaluate();
        }
        
        for(iterator = operands->begin(); iterator != operands->end(); iterator++) {
            core::BinaryExpressionModel<T> *model = (core::BinaryExpressionModel<T>*) (*iterator);
            core::BinaryShadowExpression<T> *shadow = (core::BinaryShadowExpression<T>*) model->getOperator();
            Then<T> *then = (Then<T>*) shadow->getTarget();
            ThenSugeno<T> *sugeno = (ThenSugeno<T>*) then;
            
            denominator += sugeno->premiseValue();
        }
        
        if (denominator != 0)
            return numerator/denominator;
        else
            return 0;
        
    }
    
}

#endif // SUGENODEFUZZ_H_INCLUDED
