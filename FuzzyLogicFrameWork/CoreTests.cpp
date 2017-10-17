#include <iostream>
#include <vector>
#include "ASSERT.h"
#include "ValueModel.h"
#include "Evaluator.h"
#include "MandaniDefuzz.h"
#include "CogDefuzz.h"
#include "UnaryExpressionModel.h"
#include "BinaryExpressionModel.h"
#include "ExpressionFactory.h"
#include "Fuzzy/NotMinus1.h"
#include "Fuzzy/ThenMin.h"
#include "Fuzzy/IsTriangle.h"
#include "Fuzzy/IsGauss.h"
#include "Fuzzy/AndMin.h"
#include "Fuzzy/OrPlus.h"
#include "Fuzzy/OrMax.h"
#include "Fuzzy/AggPlus.h"
#include "Fuzzy/IsTrapezeLeft.h"
#include "Fuzzy/IsTrapezeRight.h"
#include "FuzzyFactory.h"
#include "Tests.h"
#include "UnaryShadowExpression.h"
#include "BinaryShadowExpression.h"
#include "NaryExpressionModel.h"

using namespace core;

//ValueModelTest
void value_model_test(){
    ValueModel<double> vm0;
    ASSERT(0==vm0.evaluate());

    double _d=1.0;
    ValueModel<double> vm(_d);
    ASSERT(_d==vm.evaluate());

    double d=2.0;
    vm.setValue(d);
    ASSERT(d==vm.evaluate());
}

//UnaryExpressionModelTest
void unary_expression_model_test(){
    double _d=1.0;
    ValueModel<double> vm(_d);

    UnaryExpressionModel<double> _uemOP;

    try{//case operand is null
        _uemOP.evaluate();
    }catch(std::string const& e){
        ASSERT("Operand null\n"==e);
    }
    try{//case operator is null
        _uemOP.evaluate(&vm);
    }catch(std::string const& e){
        ASSERT("Operator null\n"==e);
    }

    UnaryExpressionModel<double> uem(&_uemOP,&vm);

     try{//case operand is null : the operator given is not "real" an operator
       ASSERT(uem.evaluate()==uem.evaluate(&vm));
    }catch(std::string const& e){
        ASSERT("Operator null\n"==e);
    }
    //test using "real" operator
    fuzzy::NotMinus1<double> notm1;
    UnaryExpressionModel<double> uem2(&notm1,&vm);
    ASSERT(uem2.evaluate()==uem2.evaluate(&vm));

}
//BinaryExpressionModelTest
void binary_expression_model_test(){
    double _d=1.0;
    ValueModel<double> left(_d);
    Expression<double> *leftPT=&left;
    ValueModel<double> right(_d);
    Expression<double> *rigthPT=&right;

    BinaryExpressionModel<double> _bem;

    try{//case operands are null
        _bem.evaluate();
    }catch(std::string const& e){
        ASSERT("Operands null\n"==e);
    }
    try{//case operator is null
       _bem.evaluate(&left, &right);
    }catch(std::string const& e){
        ASSERT("Operator null\n"==e);
    }

    BinaryExpressionModel<double> bem(&_bem,leftPT, rigthPT);

    try{//case operator is null : the operator given is not "real" an operator
      ASSERT(bem.evaluate()==bem.evaluate(&left, &right));
    }catch(std::string const& e){
        ASSERT("Operator null\n"==e);
    }

    //test using "real" operator
    fuzzy::ThenMin<double> thmin;
    BinaryExpression<double> *thminPT=&thmin;
    BinaryExpressionModel<double> bem2(thminPT,leftPT, rigthPT);
    ASSERT(bem2.evaluate()==bem2.evaluate(&left, &right));


}
//evaluator_test
void evaluator_test(){
    fuzzy::IsTriangle<double> iT(-5,0,5);
    core::ValueModel<double> viT;
    core::ValueModel<double> v;
    UnaryExpressionModel<double> express(&iT, &viT);
    Expression<double> *ex=&express;

    core::Evaluator<double>::Shape iT_Shape=core::Evaluator<double>::BuildShape(-5,5,1,&viT,ex);
    //core::Evaluator<double>::PrintShape(std::cout, iT_Shape);

    std::vector<double>::const_iterator it=iT_Shape.second.begin();
    double j=-5;
    for (;it!=iT_Shape.second.end();++it,j++){
        core::ValueModel<double> tmpv;
        tmpv.setValue(j);
        //std::cout<<iT.evaluate(&tmpv)<<std::endl;
        //std::cout<<*it<<"ih"<<std::endl;
        double tmpIt=*it;
        double tmpIT_evaluate=iT.evaluate(&tmpv);
        ASSERT(tmpIt==tmpIT_evaluate);
    }
}

//cogDefuzz_test
void cogDefuzz_test(){
    core::CogDefuzz<double> cDefuzz(-5,5,1);
    core::MandaniDefuzz<double> *defuzzStep=&cDefuzz;

    fuzzy::IsTriangle<double> iT(-5,0,5);
    core::ValueModel<double> viT;
    core::ValueModel<double> v;
    UnaryExpressionModel<double> express(&iT, &viT);
    Expression<double> *ex=&express;

    //defuzzStep->evaluate(&viT,ex);
    //std::cout<<defuzzStep->evaluate(&viT,ex)<<std::endl;

    core::Evaluator<double>::Shape iT_Shape=core::Evaluator<double>::BuildShape(-5,5,1,&viT,ex);
    double x,y,num=0,den=0;
	for(unsigned int i=0; i<(iT_Shape.first.size()-1); i++)
	{
		x=iT_Shape.first.at(i);
		//std::cout<<"iT_Shape.first.at("<<i<<") => "<<x<<std::endl;
		y=iT_Shape.second.at(i);
        //std::cout<<"iT_Shape.second.at("<<i<<") =========> "<<y<<std::endl;
		num+=x*y;
		den+=y;
		//std::cout<<"num U => "<<num<<std::endl;
	}
    //std::cout<<"num T => "<<num<<std::endl;
	//std::cout<<"den => "<<den<<std::endl;
	std::cout<<"This test is to improve -> num/den => "<<num/den<<std::endl;

}

//Expression Factory_test
void expression_factory_test(){

    core::ExpressionFactory<double> ef;

    double _d=1.0;
    core::ValueModel<double> vm(_d);
    fuzzy::NotMinus1<double> nm1;

    core::UnaryExpressionModel<double>* nuem=ef.newUnary(&nm1,&vm);
    double resultExpected=nm1.evaluate(&vm);
    double result=nuem->evaluate();
    ASSERT(resultExpected==result);

    double _l=2.0;
    core::ValueModel<double> vmLeft(_l);
    double _r=5.0;
    core::ValueModel<double> vmRight(_r);

    fuzzy::AndMin<double> andM;

    core::BinaryExpressionModel<double>* nbem=ef.newBinary(&andM,&vmLeft,&vmRight);
    double resultExpected2=andM.evaluate(&vmLeft,&vmRight);
    double result2=nbem->evaluate();
    ASSERT(resultExpected2==result2);

    ASSERT(2==ef.size());

}

//Unary Shadow Expression test
void unary_shadow_expression_test(){

    double _d=1.0;
    core::ValueModel<double> vm(_d);

    fuzzy::NotMinus1<double> notm1;
    UnaryShadowExpression<double> use(&notm1);

    ASSERT(0==use.evaluate(&vm));
}
//Binary Shadow Expression test
void binary_shadow_expression_test(){

    double _l=2.0;
    core::ValueModel<double> vmLeft(_l);
    double _r=5.0;
    core::ValueModel<double> vmRight(_r);

    fuzzy::AndMin<double> andM;
    BinaryShadowExpression<double> bse(&andM);

    ASSERT(_l==bse.evaluate(&vmLeft,&vmRight));

    BinaryExpression<double>* begetTarget=bse.getTarget();

    ASSERT(andM.evaluate(&vmLeft,&vmRight)==begetTarget->evaluate(&vmLeft,&vmRight));

}

//fuzzy factory test
void fuzzy_factory_test(){

    fuzzy::NotMinus1<double> notm1;
    fuzzy::AndMin<double> andM;
    fuzzy::OrPlus<double> orPlus;
    fuzzy::ThenMin<double> thenM;
    fuzzy::AggPlus<double> aggPlus;
    core::CogDefuzz<double> cDefuzz(0,30,1);

    core::FuzzyFactory<double> ff(&notm1,&andM,&orPlus,&thenM,&aggPlus,&cDefuzz);

    //not
    double _d=1.0;
    core::ValueModel<double> vm(_d);
    fuzzy::NotMinus1<double> nm1;
    ASSERT(nm1.evaluate(&vm)==ff.newNot(&vm)->evaluate());

    //and
    double _l=2.0;
    core::ValueModel<double> vmLeft(_l);
    double _r=5.0;
    core::ValueModel<double> vmRight(_r);
    ASSERT(andM.evaluate(&vmLeft,&vmRight)==ff.newAnd(&vmLeft,&vmRight)->evaluate());

    //isTriangle
    double _min=0.0;
    double _mid=5.0;
    double _max=10.0;
    fuzzy::IsTriangle<double> iT(_min,_mid,_max);
    ASSERT(iT.evaluate(&vm)==ff.newIs(&iT,&vm)->evaluate());

    fuzzy::ThenMin<double> thnM;
    ASSERT(thnM.evaluate(&vmLeft,&vmRight)==ff.newThen(&vmLeft,&vmRight)->evaluate());

    //Defuzz
    ValueModel<double> tips;
    core::CogDefuzz<double> cDefuzz2(0,30,1);
    core::MandaniDefuzz<double> *defuzzStep=&cDefuzz2;

    UnaryExpressionModel<double> uem_is_triangle(&iT,&tips);
    defuzzStep->evaluate(&tips,&uem_is_triangle); //result expected

    ff.newDefuzz(&tips,&uem_is_triangle,0,30,1); //result gotten

    ASSERT(defuzzStep->evaluate(&tips,&uem_is_triangle)==ff.newDefuzz(&tips,&uem_is_triangle,0,30,1)->evaluate());

    //orPlus
    ASSERT(orPlus.evaluate(&vmLeft,&vmRight)==ff.newOr(&vmLeft,&vmRight)->evaluate());

    //setTarget
    fuzzy::OrMax<double> orMax;
    ff.changeOr(&orMax);
    ASSERT(orMax.evaluate(&vmLeft,&vmRight)==ff.newOr(&vmLeft,&vmRight)->evaluate());

}

//nary expression test
void nary_expression_test(){

    double _d=1.0;
    core::ValueModel<double> vm(_d);

    core::NaryExpressionModel<double> ope;
    std::vector<core::Expression<double>* > operand;

    //isTriangle
    double _min=0.0;
    double _mid=5.0;
    double _max=10.0;
    fuzzy::IsTriangle<double> iT(_min,_mid,_max);

    core::ValueModel<double> vmR(iT.evaluate(&vm));

    operand.push_back(&vmR);

    core::NaryExpressionModel<double> ne(&ope,&operand);

    //ASSERT(NULL==ne.evaluate());

}


void core_main_tests(){
    std::cout << ">value_model_test<" << std::endl;
    value_model_test();
    std::cout << ">unary_expression_model_test<" << std::endl;
    unary_expression_model_test();
    std::cout << ">binary_expression_model_test<" << std::endl;
    binary_expression_model_test();
    std::cout << ">evaluator_test<" << std::endl;
    evaluator_test();
    std::cout << ">cogDefuzz_test<" << std::endl;
    cogDefuzz_test();
    std::cout << ">expression_factory_test<" << std::endl;
    expression_factory_test();
    std::cout << ">unary_shadow_expression_test<" << std::endl;
    unary_shadow_expression_test();
    std::cout << ">binary_shadow_expression_test<" << std::endl;
    binary_shadow_expression_test();
    std::cout << ">fuzzy_factory_test<" << std::endl;
    fuzzy_factory_test();
    std::cout << ">nary_expression_test<" << std::endl;
    nary_expression_test();

}


