#ifndef FUZZYFACTORY_H_INCLUDED
#define FUZZYFACTORY_H_INCLUDED

#include "ExpressionFactory.h"
#include "UnaryShadowExpression.h"
#include "BinaryShadowExpression.h"
#include "MandaniDefuzz.h"
#include "../Fuzzy/Operators.h"
#include "NaryShadowExpression.h"
#include "SugenoConclusion.h"
#include "SugenoDefuzz.h"


namespace core
{

template <class T>
class FuzzyFactory: public core::ExpressionFactory<T>
{
public:
    FuzzyFactory() {};
    FuzzyFactory(Not<T>*, And<T>*, Or<T>*, Then<T>*, Agg<T>*, MandaniDefuzz<T>*);
    FuzzyFactory(Not<T>*, And<T>*, Or<T>*, Then<T>*, Agg<T>*, fuzzy::SugenoDefuzz<T>*, fuzzy::SugenoConclusion<T>*);

    virtual ~FuzzyFactory();

    core::Expression<T>* newNot(core::Expression<T>*);
    core::Expression<T>* newIs(Is<T>*, core::Expression<T>*);
    core::Expression<T>* newAnd(core::Expression<T>*, core::Expression<T>*);
    core::Expression<T>* newOr(core::Expression<T>*, core::Expression<T>*);
    core::Expression<T>* newThen(core::Expression<T>*, core::Expression<T>*);
    core::Expression<T>* newAgg(core::Expression<T>*, core::Expression<T>*);
    core::Expression<T>* newDefuzz(core::Expression<T>*, core::Expression<T>*, const T&, const T&, const T&);
    core::Expression<T>* newSugeno(std::vector<core::Expression<T>*>*);
    core::Expression<T>* newNConclusion(std::vector<core::Expression<T>*>*);
    //change les paramètres dans newDefuzz

    void changeNot(Not<T>*);
    void changeAnd(And<T>*);
    void changeOr(Or<T>*);
    void changeThen(Then<T>*);
    void changeAgg(Agg<T>*);
    void changeDefuzz(MandaniDefuzz<T>*);
   // void ChangeSugeno(SugenoDefuzz<T>*);

private:
    core::UnaryShadowExpression<T>* _not=NULL;
    core::BinaryShadowExpression<T>* _and=NULL;
    core::BinaryShadowExpression<T>* _or=NULL;
    core::BinaryShadowExpression<T>* _then=NULL;
    core::BinaryShadowExpression<T>* _agg=NULL;
    core::BinaryShadowExpression<T>* _defuzz=NULL;
    //add SugenoDefuzz
    core::NaryShadowExpression<T>* _defuzzS=NULL;
    core::NaryShadowExpression<T>* _conclusion=NULL;
    
};

template <class T>
FuzzyFactory<T>::FuzzyFactory(Not<T>* not_, And<T>* and_, Or<T>* or_, Then<T>* then_, Agg<T>* agg_,MandaniDefuzz<T>* defuzz_):ExpressionFactory<T>()
{
    _not = new core::UnaryShadowExpression<T>(not_);
    _and = new core::BinaryShadowExpression<T>(and_);
    _or = new core::BinaryShadowExpression<T>(or_);
    _then = new core::BinaryShadowExpression<T>(then_);
    _agg = new core::BinaryShadowExpression<T>(agg_);
    _defuzz = new core::BinaryShadowExpression<T>(defuzz_);
}

template <class T>
    FuzzyFactory<T>::FuzzyFactory(Not<T>* not_, And<T>* and_, Or<T>* or_, Then<T>* then_, Agg<T>* agg_,fuzzy::SugenoDefuzz<T>* defuzz_,fuzzy::SugenoConclusion<T>* conclusion_):ExpressionFactory<T>()
    {
    _not = new core::UnaryShadowExpression<T>(not_);
    _and = new core::BinaryShadowExpression<T>(and_);
    _or = new core::BinaryShadowExpression<T>(or_);
    _then = new core::BinaryShadowExpression<T>(then_);
    _agg = new core::BinaryShadowExpression<T>(agg_);
    _defuzzS = new core::NaryShadowExpression<T>(defuzz_);
    _conclusion = new core::NaryShadowExpression<T>(conclusion_);
    }
    
template <class T>
FuzzyFactory<T>::~FuzzyFactory(){
    delete _not;
    delete _and;
    delete _or;
    delete _then;
    delete _agg;
    delete _defuzz;
}

template <class T>
core::Expression<T>* FuzzyFactory<T>::newNot(core::Expression<T>* o)
{
    return FuzzyFactory::newUnary(_not, o);
}

template <class T>
core::Expression<T>* FuzzyFactory<T>::newIs(Is<T>* s, core::Expression<T>* o)
{
    return FuzzyFactory::newUnary(s, o);
}

template <class T>
core::Expression<T>* FuzzyFactory<T>::newAnd(core::Expression<T>* l, core::Expression<T>* r)
{
    return FuzzyFactory::newBinary(_and, l, r);
}

template <class T>
core::Expression<T>* FuzzyFactory<T>::newOr(core::Expression<T>* l, core::Expression<T>* r)
{
    return FuzzyFactory::newBinary(_or, l, r);
}

template <class T>
core::Expression<T>* FuzzyFactory<T>::newThen(core::Expression<T>* l, core::Expression<T>* r)
{
    return FuzzyFactory::newBinary(_then, l, r);
}

template <class T>
core::Expression<T>* FuzzyFactory<T>::newAgg(core::Expression<T>* l, core::Expression<T>* r)
{
    return FuzzyFactory::newBinary(_agg, l, r);
}

template <class T>
core::Expression<T>* FuzzyFactory<T>::newDefuzz(core::Expression<T>* l, core::Expression<T>* r, const T& mini, const T& maxi, const T& step)
{
    MandaniDefuzz<T>* target = (MandaniDefuzz<T>*) _defuzz->getTarget();
    target->setMin(mini);
    target->setMax(maxi);
    target->setStep(step);

    return FuzzyFactory::newBinary(_defuzz, l, r);
}
template <class T>
core::Expression<T>* FuzzyFactory<T>::newSugeno(std::vector<core::Expression<T>*>* operands)
    {
    return this-> newNary(_defuzzS, operands);
    }
    
template <class T>
core::Expression<T>* FuzzyFactory<T>::newNConclusion(std::vector<core::Expression<T>*>* operands)
    {
    return this-> newNary(_conclusion, operands);
    }



template <class T>
void FuzzyFactory<T>::changeNot(Not<T>* o)
{
    _not->setTarget(o);
}

template <class T>
void FuzzyFactory<T>::changeAnd(And<T>* o)
{
    _and->setTarget(o);
}

template <class T>
void FuzzyFactory<T>::changeOr(Or<T>* o)
{
    _or->setTarget(o);
}

template <class T>
void FuzzyFactory<T>::changeThen(Then<T>* o)
{
    _then->setTarget(o);
}

template <class T>
void FuzzyFactory<T>::changeAgg(Agg<T>* o)
{
    _agg->setTarget(o);
}

template <class T>
void FuzzyFactory<T>::changeDefuzz(MandaniDefuzz<T>* o)
{
    _defuzz->setTarget(o);
}



}


#endif // FUZZYFACTORY_H_INCLUDED
