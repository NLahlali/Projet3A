//
//  AndMult.h
//  FuzzyLogicFrameWork
//
//  Created by Nabil Lahlali on 24/11/2017.
//  Copyright © 2017 Nabil Lahlali. All rights reserved.
//

#ifndef AndMult_h
#define AndMult_h
#include "Operators.h"

namespace fuzzy{
    
    template <class T>
    class AndMult : public And<T>{
        
        public :
        virtual T evaluate(Expression<T>*, Expression<T>*) const;
    };
    
    template <class T>
    T AndMult<T>::evaluate(Expression<T>* left, Expression<T>* right) const{
        T lv=left->evaluate();
        T rv=right->evaluate();
        return lv*rv;
    }
    
}


#endif /* AndMult_h */
