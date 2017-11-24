//
//  ThenMult.h
//  FuzzyLogicFrameWork
//
//  Created by Nabil Lahlali on 24/11/2017.
//  Copyright © 2017 Nabil Lahlali. All rights reserved.
//

#ifndef ThenMult_h
#define ThenMult_h
namespace fuzzy{
    
    template <class T>
    class ThenMult : public Then<T>
    {
    public :
    T evaluate(Expression<T>*, Expression<T>*) const;
    };
    
    template <class T>
    T ThenMult<T>::evaluate(Expression<T>* left, Expression<T>* right) const{
        T lv=left->evaluate();
        T rv=right->evaluate();
        return lv*rv;
    }
    
}

#endif /* ThenMult_h */
