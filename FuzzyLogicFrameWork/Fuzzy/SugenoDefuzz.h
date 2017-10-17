#ifndef SUGENODEFUZZ_H_INCLUDED
#define SUGENODEFUZZ_H_INCLUDED

#include "../Core/NaryExpression.h"
#include "../Core/BinaryShadowExpression.h"
#include "../Core/BinaryExpressionModel.h"
#include "ThenSugeno.h"
#include <vector>

namespace fuzzy {

template<class T>
class SugenoDefuzz : public core::NaryExpression<T>{
    public:
        SugenoDefuzz();
        virtual ~SugenoDefuzz(){}
        virtual T evaluate(std::vector<core::Expression<T>*>* operands) const;
};

template<class T>
SugenoDefuzz<T>::SugenoDefuzz(){}

template<class T>
T SugenoDefuzz<T>::evaluate(std::vector<core::Expression<T>*>* operands) const
{
      T w=0;
      T wz=0;
      typename std::vector<core::Expression<T>*>::const_iterator it;
      for(it=operands->begin();it!=operands->end();it++)
      {
         core::BinaryExpressionModel<T>* bem = (core::BinaryExpressionModel<T>*) (*it);
         //core::BinaryShadowExpression<T>* bse = (core::BinaryShadowExpression<T>*) bem->getOperator();
         ThenSugeno<T>* st = (ThenSugeno<T>*) bem->getOperator();
         wz += bem->evaluate();
         //std::cout <<"Bem evaluate :"<< wz << std::endl;
         w += st->premiseValue();
         //std::cout <<"premise :"<< w << std::endl;
       }
     return wz/w;
}


}

#endif // SUGENODEFUZZ_H_INCLUDED
