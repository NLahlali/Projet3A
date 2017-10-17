#include <iostream>
#include "Fuzzy/NotMinus1.h"
#include "Fuzzy/AndMin.h"
#include "Fuzzy/OrMax.h"
#include "Fuzzy/ThenMin.h"
#include "Fuzzy/AggPlus.h"
#include "Core/CogDefuzz.h"
#include "Core/FuzzyFactory.h"
#include "Fuzzy/IsGauss.h"
#include "Fuzzy/IsTrapezeLeft.h"
#include "Fuzzy/IsTrapezeRight.h"
#include "Fuzzy/IsTriangle.h"
#include "Core/ValueModel.h"
#include "Fuzzy/ThenSugeno.h"
#include "Fuzzy/AggMax.h"
#include "Fuzzy/SugenoDefuzz.h"
#include "Fuzzy/SugenoConclusion.h"


void Mamdani()
{

                    /***example : service is poor OR food is rancid THEN(min) tips is cheap
                                  service is good THEN tips is average
                                  service is excellent OR food is delicious THEN(min) tips is generous   ****/


    fuzzy::NotMinus1<float> opNot;
    fuzzy::AndMin<float> opAnd;
    fuzzy::OrMax<float> opOr;
    fuzzy::ThenMin<float> opThen;
    fuzzy::AggPlus<float> opAgg;
    core::CogDefuzz<float> opDefuzz;

    core::FuzzyFactory<float> f(&opNot,&opAnd,&opOr,&opThen,&opAgg,&opDefuzz);

    //membership function
    //service
    fuzzy::IsGauss<float> poor(2.0,0);
    fuzzy::IsGauss<float> good(2.0,5.0);
    fuzzy::IsGauss<float> excellent(2.0,10.0);
    //food
    fuzzy::IsTrapezeLeft<float> rancid(0,1,3.0);
    fuzzy::IsTrapezeRight<float> delicious(7.0,9.0,10.0);
    //tips
    fuzzy::IsTriangle<float> cheap(0,5,10);
    fuzzy::IsTriangle<float> average(10,15,20);
    fuzzy::IsTriangle<float> generous(20,25,30);

    //values
    core::ValueModel<float> service(3);
    core::ValueModel<float> food(8);
    core::ValueModel<float> tips(0);

    core::Expression<float> *r =f.newAgg(
                                    f.newAgg(
                                        f.newThen(
                                            f.newOr(f.newIs(&poor, &service), f.newIs(&rancid, &food)),
                                            f.newIs(&cheap, &tips)
                                        ),
                                        f.newThen(
                                            f.newIs(&good, &service),
                                            f.newIs(&average, &tips)
                                        )
                                    ),
                                    f.newThen(
                                            f.newOr(f.newIs(&excellent, &service), f.newIs(&delicious, &food)),
                                            f.newIs(&generous, &tips)

                                    )
                                );
    core::Expression<float> *system = f.newDefuzz(&tips, r, 0, 30, 1);

    float s, foo;

    while (true)
    {
        std::cout << "service : ";
        std::cin >> s;
        service.setValue(s);
        std::cout<< "food : ";
        std::cin >> foo;
        food.setValue(foo);
        std::cout<< "tips -> " << system->evaluate() << std::endl;
    }

}

void SugenoDefuzz()
{
    
    //operators
    fuzzy::NotMinus1<float>     opNot;
    fuzzy::AndMin<float>       opAnd;
    fuzzy::OrMax<float>        opOr;
    fuzzy::ThenSugeno<float>   opThen;
    fuzzy::AggMax<float>       opAgg;
    fuzzy::SugenoDefuzz<float> opSugDefuzz;
    
    std::vector<float> coef;
    coef.push_back(1);
    coef.push_back(1);
    coef.push_back(1);
    fuzzy::SugenoConclusion<float> opConclusion(&coef);
    
    //fuzzy expression factory
    FuzzyFactory<float> f(&opNot,&opAnd,&opOr,&opThen,&opAgg,&opSugDefuzz,&opConclusion);
    
    //membership function
    // service
    fuzzy::IsTriangle<float> poor(-5,0,5);
    fuzzy::IsTriangle<float> good(0,5,10);
    fuzzy::IsTriangle<float> excellent(5,10,15);
    // food
    fuzzy::IsTriangle<float> rancid(-5,0,5);
    fuzzy::IsTriangle<float> delicious(5,10,15);
    //values
    core::ValueModel<float> service(0);
    core::ValueModel<float> food(0);
    
    //output : ces variables vont stocker le résultat de SujenoConclusion (zi)
    std::vector<core::Expression<float>*> SC_service_food;
    SC_service_food.push_back(&service);
    SC_service_food.push_back(&food);
    
    std::vector<core::Expression<float>*> SC_service;
    SC_service.push_back(&service);
    
    //rules
    std::vector<core::Expression<float>*> rules;
    
    rules.push_back(
                    f.newThen(
                              f.newOr(
                                      f.newIs(&poor, &service),
                                      f.newIs(&rancid, &food)
                                      ),
                              f.newNConclusion(&SC_service_food)
                              ));
    
    rules.push_back(
                    f.newThen(
                              f.newIs(&good, &service),
                              f.newNConclusion(&SC_service)
                              ));
    
    rules.push_back(
                    f.newThen(
                              f.newOr(
                                      f.newIs(&excellent, &service),
                                      f.newIs(&delicious, &food)
                                      ),
                              f.newNConclusion(&SC_service_food)
                              ));
    
    //defuzzification
    core::Expression<float> *system = f.newSugeno(&rules);
    
    //apply input
    float s, foo;
    while (true)
        {
        std::cout << "service : ";
        std::cin >> s;
        //service.SetValue(s);
        std::cout << "food : ";
        std::cin >> foo;
        //food.SetValue(foo);
        std::cout << "tips -> " <<  0/*system->Evaluate()*/ << std::endl;
        }
}

void execution_fuzzy()
{
    unsigned select;
    std::cout << "1: Mamdani" << std::endl;
    std::cout << "2: Sugeno" << std::endl;
    std::cout << "> ";
    std::cin >> select;
    
    if (select == 1)
        Mamdani();
    else
        SugenoDefuzz();
    
}
