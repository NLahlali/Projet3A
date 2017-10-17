#include <iostream>
#include <assert.h>
#include "ASSERT.h"
#include "Tests.h"
#include "Core/ValueModel.h"
#include "Core/UnaryExpressionModel.h"
#include "Fuzzy/IsTriangle.h"
#include "Fuzzy/AggPlus.h"
#include "Fuzzy/AggPlus.h"
#include "Fuzzy/AndMin.h"
#include "Core/Evaluator.h"
#include "Core/MandaniDefuzz.h"
#include "Core/CogDefuzz.h"
#include "Core/FuzzyFactory.h"
#include "Fuzzy/SugenoDefuzz.h"
#include "Core/BinaryExpressionModel.h"
#include "Fuzzy/ThenMin.h"
#include "Fuzzy/ThenSugeno.h"
#include "Fuzzy/NotMinus1.h"
#include "Fuzzy/OrMax.h"
#include "Fuzzy/OrPlus.h"
#include "Fuzzy/IsGauss.h"
#include "Fuzzy/IsTrapezeLeft.h"
#include "Fuzzy/IsTrapezeRight.h"

using namespace fuzzy;
using namespace core;

void sample_test_1(){
                    /***example : food is rancid AND(min) service is poor ****/
    //operators
    AndMin<double> and_min;

    //functions for services
    IsTriangle<double> poor(-5,0,5);

    //functions for tips
    IsTriangle<double> rancid(0,5,10);

    //values
    ValueModel<double> service; //default value is 0
    ValueModel<double> food;    //default value is 0

    //here we change value of objects ValueModel
    food.setValue(3); //value must be between 0 and 10
    service.setValue(4);  //value must be between -5 and 5


    //unaryExpression
    UnaryExpressionModel<double> uem_food_is_rancid(&rancid, &food); //calculate the value of food in the function isTriangle rancid
    UnaryExpressionModel<double> uem_service_is_poor(&poor, &service); //calculate the value of service in the function isTriangle poor
    std::cout<<"value of food is rancid : > "<<uem_food_is_rancid.evaluate()<<std::endl;
    std::cout<<"value of service is poor : > "<<uem_service_is_poor.evaluate()<<std::endl;

    ValueModel<double> Vuem_food_is_rancid(uem_food_is_rancid.evaluate());
    ValueModel<double> Vuem_service_is_poor(uem_service_is_poor.evaluate());
    BinaryExpressionModel<double> bem_AND_MIN(&and_min,&Vuem_food_is_rancid,&Vuem_service_is_poor);//calculate the lowest value between "value of food is rancid" and "value of service is poor" : Operator AND_MIN
    std::cout<<"value after using operator AND_MIN : > "<<bem_AND_MIN.evaluate()<<std::endl;

}

void sample_test_2(){
                    /***example : food is rancid AND(min) service is poor THEN(min) tips is cheap****/

    //operators
    AndMin<double> and_min;
    ThenMin<double> then_min;

    //functions
    IsTriangle<double> poor(-5,0,5);
    IsTriangle<double> rancid(0,5,10);
    IsTriangle<double> cheap(0,5,10);

    //values
    ValueModel<double> service; //default value is 0
    ValueModel<double> food;    //default value is 0
    ValueModel<double> tips;    //default value is 0
    //here we change value of objects ValueModel
    food.setValue(5); //value must be between 0 and 10
    service.setValue(-5);  //value must be between -5 and 5
    tips.setValue(5);

    //evaluation : food is rancid
    UnaryExpressionModel<double> uem_food_is_rancid(&rancid, &food);
    ASSERT(1==uem_food_is_rancid.evaluate()); //1 because the value of the member function with 5 is 1

    //evaluation : service is poor
    UnaryExpressionModel<double> uem_service_is_poor(&poor, &service);
    ASSERT(0==uem_service_is_poor.evaluate()); //1 because the value of the member function with 0 is 1

    //evaluation : tips is cheap
    UnaryExpressionModel<double> uem_tips_is_cheap(&cheap, &tips);
    ASSERT(1==uem_tips_is_cheap.evaluate()); //1 because the value of the member function with 5 is 1

    std::cout<<"value of food is rancid : > "<<uem_food_is_rancid.evaluate()<<std::endl;
    std::cout<<"value of service is poor : > "<<uem_service_is_poor.evaluate()<<std::endl;
    std::cout<<"value of tips is cheap : > "<<uem_tips_is_cheap.evaluate()<<std::endl;

    /**operator THEN and AND : I think the operator THEN should be an UnaryExpression
      but the UML given but the teacher is saying the opposite**/

    //evaluation : AND
    BinaryExpressionModel<double> bem_AND_MIN(&and_min,&uem_food_is_rancid,&uem_service_is_poor);
    ASSERT(0==bem_AND_MIN.evaluate());
    std::cout<<"value after using operator AND_MIN : > "<<bem_AND_MIN.evaluate()<<std::endl;

    //evaluation : THEN tips is cheap
    BinaryExpressionModel<double> bem_THEN_MIN(&then_min,&uem_tips_is_cheap,&bem_AND_MIN);
    ASSERT(0==bem_THEN_MIN.evaluate());
    std::cout<<"value after using operator THEN_MIN : > "<< bem_THEN_MIN.evaluate()<<std::endl;

    //Expression<double> *e_AND_MIN=&bem_AND_MIN;

}

void sample_test_3(){
                    /***example : service is poor THEN(min) tips is cheap
                                  service is good THEN tips is average
                                  service is excellent THEN tips is generous   ****/

    //operators
    AggPlus<double> agg_plus;
    ThenMin<double> then_min;

    //service functions
    IsTriangle<double> poor(-5,0,5);
    IsTriangle<double> good(0,5,10);
    IsTriangle<double> excellent(5,10,15);

    //tips functions
    IsTriangle<double> cheap(0,5,10);
    IsTriangle<double> average(10,15,20);
    IsTriangle<double> generous(20,25,30);

    //values
    ValueModel<double> service; //default value is 0
    ValueModel<double> tips;    //default value is 0

    //here we change value of objects ValueModel
    service.setValue(5);  //value must be between -5 and 5

                            /***service is poor THEN(min) tips is cheap***/
    //evaluation : food is rancid
    UnaryExpressionModel<double> uem_service_is_poor(&poor, &service);
    //evaluation : tips is cheap
    UnaryExpressionModel<double> uem_tips_is_cheap(&cheap, &tips);
    //evaluation : THEN
    BinaryExpressionModel<double> bem_THEN_MIN_1(&then_min,&uem_service_is_poor,&uem_tips_is_cheap);

                                /***service is good THEN tips is average***/
    //evaluation : service is good
    UnaryExpressionModel<double> uem_service_is_good(&good, &service);
    //evaluation : tips is average
    UnaryExpressionModel<double> uem_tips_is_average(&average, &tips);
    //evaluation : THEN
    BinaryExpressionModel<double> bem_THEN_MIN_2(&then_min,&uem_service_is_good,&uem_tips_is_average);

                                /***AGG1 (
                                         service is poor THEN(min) tips is cheap,
                                         service is good THEN tips is average
                                         )                              ***/
    //evaluation : aggregation plus
    BinaryExpressionModel<double> bem_agg_plus_1(&agg_plus,&bem_THEN_MIN_1,&bem_THEN_MIN_2);


                                /***service is excellent THEN tips is generous ***/
    //evaluation : service is excellent
    UnaryExpressionModel<double> uem_service_is_excellent(&excellent, &service);
    //evaluation : tips is generous
    UnaryExpressionModel<double> uem_tips_is_generous(&generous, &tips);
    //evaluation : THEN
    BinaryExpressionModel<double> bem_THEN_MIN_3(&then_min,&uem_service_is_excellent,&uem_tips_is_generous);


                                /***AGG2 (
                                         AGG1,
                                         service is excellent THEN tips is generous
                                         )                              ***/

    //evaluation : aggregation plus
    BinaryExpressionModel<double> bem_agg_plus_2(&agg_plus,&bem_agg_plus_1,&bem_THEN_MIN_3);

    //display the defuzz shape
    core::Evaluator<double>::Shape iT_Shape=core::Evaluator<double>::BuildShape(0,25,1,&tips,&bem_agg_plus_2);
    core::Evaluator<double>::PrintShape(std::cout, iT_Shape);

    //choice of defuzzification method
    core::CogDefuzz<double> cDefuzz(0,25,1);
    core::MandaniDefuzz<double> *defuzzStep=&cDefuzz;

    //calculate centroid of defuzzification shape
    defuzzStep->evaluate(&tips,&bem_agg_plus_2);
    std::cout<<"value of tips : > "<<defuzzStep->evaluate(&tips,&bem_agg_plus_2)<<std::endl;

}

void sample_test_4(){
                    /***example : service is poor OR food is rancid THEN(min) tips is cheap
                                  service is good THEN tips is average
                                  service is excellent OR food is delicious THEN(min) tips is generous   ****/

    //operators
    AggPlus<double> agg_plus;
    ThenMin<double> then_min;
    OrMax<double> or_max;

    //service functions
    double sigma=2.0,cp=0,cg=5.0,ce=10.0;
    IsGauss<double> poor(sigma,cp);
    IsGauss<double> good(sigma,cg);
    IsGauss<double> excellent(sigma,ce);

    //food functions
    double ar=0,br=1,cr=3.0,ad=7.0,bd=9.0,cd=10.0;
    IsTrapezeLeft<double> rancid(ar,br,cr);
    IsTrapezeRight<double> delicious(ad,bd,cd);

    //tips functions
    IsTriangle<double> cheap(0,5,10);
    IsTriangle<double> average(5,15,20);
    IsTriangle<double> generous(20,25,30);

    //values
    ValueModel<double> service; //default value is 0
    ValueModel<double> food; //default value is 0
    ValueModel<double> tips;    //default value is 0

    //here we change value of objects ValueModel
    service.setValue(7.83);
    food.setValue(7.32);
    //with the values above the result is 25

    //with the values above the result is 24.9842
    service.setValue(3);
    food.setValue(8);
                            /***service is poor OR food is rancid THEN(min) tips is cheap***/
    //evaluation : service is poor
    UnaryExpressionModel<double> uem_service_is_poor(&poor, &service);
    //evaluation : food is rancid
    UnaryExpressionModel<double> uem_food_is_rancid(&rancid, &food);
    //evaluation : OR
    BinaryExpressionModel<double> bem_OR_MAX1(&or_max,&uem_service_is_poor,&uem_food_is_rancid);

    std::cout<<"value first OR MAX : > "<<bem_OR_MAX1.evaluate()<<std::endl;
    //evaluation : tips is cheap
    UnaryExpressionModel<double> uem_tips_is_cheap(&cheap, &tips);
    //evaluation : THEN
    BinaryExpressionModel<double> bem_THEN_MIN_1(&then_min,&bem_OR_MAX1,&uem_tips_is_cheap);

    //display the defuzz shape
    core::Evaluator<double>::Shape iT_Shape;
/*    std::cout<<"shape first rule : > "<<std::endl;
    iT_Shape=core::Evaluator<double>::BuildShape(0,10,1,&tips,&bem_THEN_MIN_1);
    core::Evaluator<double>::PrintShape(std::cout, iT_Shape);*/


                                /***service is good THEN tips is average***/

    //evaluation : service is good
    UnaryExpressionModel<double> uem_service_is_good(&good, &service);
    std::cout<<"value second OR MAX : > "<<uem_service_is_good.evaluate()<<std::endl;
    //evaluation : tips is average
    UnaryExpressionModel<double> uem_tips_is_average(&average, &tips);
    //evaluation : THEN
    BinaryExpressionModel<double> bem_THEN_MIN_2(&then_min,&uem_service_is_good,&uem_tips_is_average);

    //display the defuzz shape
//    std::cout<<"shape second rule : > "<<std::endl;
//    iT_Shape=core::Evaluator<double>::BuildShape(5,20,1,&tips,&bem_THEN_MIN_2);
//    core::Evaluator<double>::PrintShape(std::cout, iT_Shape);


                             /***service is excellent OR food is delicious THEN(min) tips is generous ***/


//evaluation : service is poor
    UnaryExpressionModel<double> uem_service_is_excellent(&excellent, &service);
    //evaluation : food is rancid
    UnaryExpressionModel<double> uem_food_is_delicious(&delicious, &food);
    //evaluation : OR
    BinaryExpressionModel<double> bem_OR_MAX3(&or_max,&uem_service_is_excellent,&uem_food_is_delicious);

    std::cout<<"value third OR MAX : > "<<bem_OR_MAX3.evaluate()<<std::endl;
    //evaluation : tips is cheap
    UnaryExpressionModel<double> uem_tips_is_generous(&generous, &tips);
    //evaluation : THEN
    BinaryExpressionModel<double> bem_THEN_MIN_3(&then_min,&bem_OR_MAX3,&uem_tips_is_generous);

    //display the defuzz shape
/*    std::cout<<"shape first rule : > "<<std::endl;
    iT_Shape=core::Evaluator<double>::BuildShape(5,30,1,&tips,&bem_THEN_MIN_3);
    core::Evaluator<double>::PrintShape(std::cout, iT_Shape);       */


                                /***AGG1 (
                                         service is poor OR food is rancid THEN(min) tips is cheap,
                                         service is good THEN tips is average
                                         )                              ***/
    //evaluation : aggregation plus
    BinaryExpressionModel<double> bem_agg_plus_1(&agg_plus,&bem_THEN_MIN_1,&bem_THEN_MIN_2);


                                /***AGG2 (
                                         AGG1,
                                         service is excellent OR food is delicious THEN(min) tips is generous
                                         )                              ***/

    //evaluation : aggregation plus
    BinaryExpressionModel<double> bem_agg_plus_2(&agg_plus,&bem_agg_plus_1,&bem_THEN_MIN_3);

    //display the defuzz shape
/*    std::cout<<"shape to defuzze : > "<<std::endl;
    iT_Shape=core::Evaluator<double>::BuildShape(0,30,1,&tips,&bem_agg_plus_2);
    core::Evaluator<double>::PrintShape(std::cout, iT_Shape);                       */

    //choice of defuzzification method
    core::CogDefuzz<double> cDefuzz(0,30,1);
    core::MandaniDefuzz<double> *defuzzStep=&cDefuzz;

    //calculate centroid of defuzzification shape
    defuzzStep->evaluate(&tips,&bem_agg_plus_2);
    double tipsToGive=defuzzStep->evaluate(&tips,&bem_agg_plus_2);
    std::cout<<"value of tips : > "<<tipsToGive<<std::endl;

}

void sample_test_4b(){
                    /***example : service is poor OR food is rancid THEN(min) tips is cheap
                                  service is good THEN tips is average
                                  service is excellent OR food is delicious THEN(min) tips is generous   ****/

    //operators
    AggPlus<double> agg_plus;
    ThenMin<double> then_min;
    OrMax<double> or_max;

    //service functions
    double sigma=2.0,cp=0,cg=5.0,ce=10.0;
    IsGauss<double> poor(sigma,cp);
    IsGauss<double> good(sigma,cg);
    IsGauss<double> excellent(sigma,ce);

    //food functions
    double ar=0,br=1,cr=3.0,ad=7.0,bd=9.0,cd=10.0;
    IsTrapezeLeft<double> rancid(ar,br,cr);
    IsTrapezeRight<double> delicious(ad,bd,cd);

    //tips functions
    IsTriangle<double> cheap(0,5,10);
    IsTriangle<double> average(5,15,20);
    IsTriangle<double> generous(20,25,30);

    //values
    ValueModel<double> service; //default value is 0
    ValueModel<double> food; //default value is 0
    ValueModel<double> tips;    //default value is 0

    //here we change value of objects ValueModel
    service.setValue(7.83);
    food.setValue(7.32);
    //with the values above the result is 25

    //with the values above the result is 24.9842
    service.setValue(3);
    food.setValue(8);


                            /***service is poor OR food is rancid THEN(min) tips is cheap***/
    //evaluation : service is poor
    UnaryExpressionModel<double> uem_service_is_poor(&poor, &service);
    //evaluation : food is rancid
    UnaryExpressionModel<double> uem_food_is_rancid(&rancid, &food);
    //evaluation : OR
    BinaryExpressionModel<double> bem_OR_MAX1(&or_max,&uem_service_is_poor,&uem_food_is_rancid);

    std::cout<<"value first OR MAX : > "<<bem_OR_MAX1.evaluate()<<std::endl;
    //evaluation : tips is cheap
    UnaryExpressionModel<double> uem_tips_is_cheap(&cheap, &tips);
    //evaluation : THEN
    BinaryExpressionModel<double> bem_THEN_MIN_1(&then_min,&bem_OR_MAX1,&uem_tips_is_cheap);

    //display the defuzz shape
    core::Evaluator<double>::Shape iT_Shape;
/*    std::cout<<"shape first rule : > "<<std::endl;
    iT_Shape=core::Evaluator<double>::BuildShape(0,10,1,&tips,&bem_THEN_MIN_1);
    core::Evaluator<double>::PrintShape(std::cout, iT_Shape);*/


                                /***service is good THEN tips is average***/

    //evaluation : service is good
    UnaryExpressionModel<double> uem_service_is_good(&good, &service);
    std::cout<<"value second OR MAX : > "<<uem_service_is_good.evaluate()<<std::endl;
    //evaluation : tips is average
    UnaryExpressionModel<double> uem_tips_is_average(&average, &tips);
    //evaluation : THEN
    BinaryExpressionModel<double> bem_THEN_MIN_2(&then_min,&uem_service_is_good,&uem_tips_is_average);

    //display the defuzz shape
//    std::cout<<"shape second rule : > "<<std::endl;
//    iT_Shape=core::Evaluator<double>::BuildShape(5,20,1,&tips,&bem_THEN_MIN_2);
//    core::Evaluator<double>::PrintShape(std::cout, iT_Shape);


                             /***service is excellent OR food is delicious THEN(min) tips is generous ***/


//evaluation : service is poor
    UnaryExpressionModel<double> uem_service_is_excellent(&excellent, &service);
    //evaluation : food is rancid
    UnaryExpressionModel<double> uem_food_is_delicious(&delicious, &food);
    //evaluation : OR
    BinaryExpressionModel<double> bem_OR_MAX3(&or_max,&uem_service_is_excellent,&uem_food_is_delicious);

    std::cout<<"value third OR MAX : > "<<bem_OR_MAX3.evaluate()<<std::endl;
    //evaluation : tips is cheap
    UnaryExpressionModel<double> uem_tips_is_generous(&generous, &tips);
    //evaluation : THEN
    BinaryExpressionModel<double> bem_THEN_MIN_3(&then_min,&bem_OR_MAX3,&uem_tips_is_generous);

    //display the defuzz shape
/*    std::cout<<"shape first rule : > "<<std::endl;
    iT_Shape=core::Evaluator<double>::BuildShape(5,30,1,&tips,&bem_THEN_MIN_3);
    core::Evaluator<double>::PrintShape(std::cout, iT_Shape);       */


                                /***AGG1 (
                                         service is poor OR food is rancid THEN(min) tips is cheap,
                                         service is good THEN tips is average
                                         )                              ***/
    //evaluation : aggregation plus
    BinaryExpressionModel<double> bem_agg_plus_1(&agg_plus,&bem_THEN_MIN_1,&bem_THEN_MIN_2);


                                /***AGG2 (
                                         AGG1,
                                         service is excellent OR food is delicious THEN(min) tips is generous
                                         )                              ***/

    //evaluation : aggregation plus
    BinaryExpressionModel<double> bem_agg_plus_2(&agg_plus,&bem_agg_plus_1,&bem_THEN_MIN_3);

    //display the defuzz shape
/*    std::cout<<"shape to defuzze : > "<<std::endl;
    iT_Shape=core::Evaluator<double>::BuildShape(0,30,1,&tips,&bem_agg_plus_2);
    core::Evaluator<double>::PrintShape(std::cout, iT_Shape);                       */

    //choice of defuzzification method
    core::CogDefuzz<double> cDefuzz(0,30,1);
    core::MandaniDefuzz<double> *defuzzStep=&cDefuzz;

    //calculate centroid of defuzzification shape
    defuzzStep->evaluate(&tips,&bem_agg_plus_2);
    double tipsToGive=defuzzStep->evaluate(&tips,&bem_agg_plus_2);
    std::cout<<"value of tips : > "<<tipsToGive<<std::endl;

}

void sample_test_5(){

    NotMinus1<double> notm1;
    AndMin<double> andM;
    OrPlus<double> orPlus;
    ThenSugeno<double> thenS;
    AggPlus<double> aggPlus;
    fuzzy::SugenoDefuzz<double> sDefuzz;

    //core::FuzzyFactory<double> ff(&notm1,&andM,&orPlus,&thenS,&aggPlus,&sDefuzz);


}

void global_main_tests(){
    std::cout << ">sample_test_1<" << std::endl;
    sample_test_1();
    std::cout <<std::endl<< ">sample_test_2<" << std::endl;
    sample_test_2();
    std::cout <<std::endl<< ">sample_test_3<" << std::endl;
    sample_test_3();
    std::cout <<std::endl<< ">sample_test_4<" << std::endl;
    sample_test_4();
    std::cout <<std::endl<< ">sample_test_5<" << std::endl;
    sample_test_5();
}
