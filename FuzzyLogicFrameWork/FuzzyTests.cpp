#include "ASSERT.h"
#include "NotMinus1.h"
#include "IsTriangle.h"
#include "AndMin.h"
#include "AggMax.h"
#include "AggPlus.h"
#include "ThenMin.h"
#include "OrMax.h"
#include "OrPlus.h"
#include "IsTrapeze.h"
#include "IsBell.h"
#include "IsGauss.h"
#include "IsTrapezeLeft.h"
#include "IsTrapezeRight.h"
#include "ThenSugeno.h"
#include "SugenoDefuzz.h"
#include "IsZshaped.h"
#include "Core/ValueModel.h"
#include "Tests.h"



//NotMinus1Test
void not_minus1_test(){
    double _d=1.0;
    core::ValueModel<double> vm(_d);

    fuzzy::NotMinus1<double> notm1;
    ASSERT(0==notm1.evaluate(&vm));
}

//isTriangleTest
void is_triangle_test(){
    double _d=3.0;
    core::ValueModel<double> vm(_d);

    //case _d<=_mid
    double _min=0.0;
    double _mid=5.0;
    double _max=10.0;
    fuzzy::IsTriangle<double> iT(_min,_mid,_max);
    double ExpectedRes=((_d - _min)/(_mid - _min));
    double CurrenRes=iT.evaluate(&vm);
    ASSERT(ExpectedRes == CurrenRes);
}

//AndMinTest
void and_min_test(){
    double _l=2.0;
    core::ValueModel<double> vmLeft(_l);
    double _r=5.0;
    core::ValueModel<double> vmRight(_r);

    fuzzy::AndMin<double> andM;

    ASSERT(_l==andM.evaluate(&vmLeft,&vmRight));
}

//ThenMinTest
void then_min_test(){
    double _l=1.0;
    core::ValueModel<double> vmLeft(_l);
    double _r=1.0;
    core::ValueModel<double> vmRight(_r);

    fuzzy::ThenMin<double> thenM;

    ASSERT(_l==thenM.evaluate(&vmLeft,&vmRight));
}
//aggMaxTest
void agg_max_test(){
    double _l=2.0;
    core::ValueModel<double> vmLeft(_l);
    double _r=5.0;
    core::ValueModel<double> vmRight(_r);

    fuzzy::AggMax<double> aggMax;

    ASSERT(_l==aggMax.evaluate(&vmLeft,&vmRight));
}

//aggMinTest
void agg_plus_test(){
    double _l=2.0;
    core::ValueModel<double> vmLeft(_l);
    double _r=5.0;
    core::ValueModel<double> vmRight(_r);

    fuzzy::AggPlus<double> aggPlus;

    ASSERT(_l+_r==aggPlus.evaluate(&vmLeft,&vmRight));
}

//orMaxTest
void or_max_test(){
    double _l=2.0;
    core::ValueModel<double> vmLeft(_l);
    double _r=5.0;
    core::ValueModel<double> vmRight(_r);

    fuzzy::OrMax<double> orMax;

    ASSERT(_r==orMax.evaluate(&vmLeft,&vmRight));
}

//orPlusTest
void or_plus_test(){
    double _l=2.0;
    core::ValueModel<double> vmLeft(_l);
    double _r=5.0;
    core::ValueModel<double> vmRight(_r);

    fuzzy::OrPlus<double> orPlus;

    ASSERT(_r+_l==orPlus.evaluate(&vmLeft,&vmRight));
}

//isTrapezeTest
void is_trapeze_test(){

    //case _d<=_mid
    double _min=0.0;
    double _midmin=5.0;
    double _midmax=8.0;
    double _max=10.0;

    fuzzy::IsTrapeze<double> iTra(_min,_midmin,_midmax,_max);
    ASSERT(_min==iTra.getMin());
    ASSERT(_midmin==iTra.getMidMin());
    ASSERT(_midmax==iTra.getMidMax());
    ASSERT(_max==iTra.getMax());

    double _dmax=11.0;
    core::ValueModel<double> vmMax(_dmax);
    ASSERT(0==iTra.evaluate(&vmMax));

    double _dmiddle=7.0;
    core::ValueModel<double> vmMiddle(_dmiddle);
    ASSERT(1==iTra.evaluate(&vmMiddle));

    double dElse_entreMin_midMin=3.0;
    core::ValueModel<double> vmElse1(dElse_entreMin_midMin);
    double ExpectedRes= (dElse_entreMin_midMin - _min)/(_midmin - _min);
    double CurrenRes=iTra.evaluate(&vmElse1);
    ASSERT(ExpectedRes == CurrenRes);

    double dElse_entreMidMax_max=9.0;
    core::ValueModel<double> vmElse2(dElse_entreMidMax_max);
    double ExpectedRes2=(_max - dElse_entreMidMax_max)/(_max - _midmax);
    double CurrenRes2=iTra.evaluate(&vmElse2);
    ASSERT(ExpectedRes2 == CurrenRes2);
}

//bellTest
void is_bell_test(){
    double _l=6.0;
    core::ValueModel<double> vm(_l);

    double a=2.0,b=4.0,c=6.0;
    fuzzy::IsBell<double> isBell(a,b,c);

    ASSERT(1==isBell.evaluate(&vm));
}

//gaussTest
void is_gauss_test(){
    double _l=5.0;
    core::ValueModel<double> vm(_l);

    double sigma=2.0,c=5.0;
    fuzzy::IsGauss<double> isGauss(sigma,c);

    ASSERT(1==isGauss.evaluate(&vm));
}

//isTrapezeLeftTest
void is_trapeze_left_test(){

    double _min=1.0;
    double _mid=5.0;
    double _max=10.0;

    fuzzy::IsTrapezeLeft<double> iTraL(_min,_mid,_max);
    ASSERT(_min==iTraL.getMin());
    ASSERT(_mid==iTraL.getMid());
    ASSERT(_max==iTraL.getMax());

    double _dmax=11.0;
    core::ValueModel<double> vmMax(_dmax);
    ASSERT(0==iTraL.evaluate(&vmMax));

    double _dmin=0.0;
    core::ValueModel<double> vmMin(_dmin);
    ASSERT(0==iTraL.evaluate(&vmMin));

    double _dmiddleMidMax=3.0;
    core::ValueModel<double> vmMiddleMidMax(_dmiddleMidMax);
    ASSERT(1==iTraL.evaluate(&vmMiddleMidMax));

    double dBetweenMinMid=7.0;
    core::ValueModel<double> vmBetweenMinMid(dBetweenMinMid);
    double ExpectedRes= (_max-dBetweenMinMid)/(_max-_mid);
    double CurrenRes=iTraL.evaluate(&vmBetweenMinMid);
    ASSERT(ExpectedRes == CurrenRes);

}

//isTrapezeRightTest
void is_trapeze_right_test(){

    double _min=1.0;
    double _mid=5.0;
    double _max=10.0;

    fuzzy::IsTrapezeRight<double> iTraR(_min,_mid,_max);
    ASSERT(_min==iTraR.getMin());
    ASSERT(_mid==iTraR.getMid());
    ASSERT(_max==iTraR.getMax());

    double _dmax=11.0;
    core::ValueModel<double> vmMax(_dmax);
    ASSERT(0==iTraR.evaluate(&vmMax));

    double _dmin=0.0;
    core::ValueModel<double> vmMin(_dmin);
    ASSERT(0==iTraR.evaluate(&vmMin));

    double _dmiddleMidMax=7.0;
    core::ValueModel<double> vmMiddleMidMax(_dmiddleMidMax);
    ASSERT(1==iTraR.evaluate(&vmMiddleMidMax));

    double dBetweenMinMid=3.0;
    core::ValueModel<double> vmBetweenMinMid(dBetweenMinMid);
    double ExpectedRes=(dBetweenMinMid-_min)/(_mid-_min);
    double CurrenRes=iTraR.evaluate(&vmBetweenMinMid);
    ASSERT(ExpectedRes == CurrenRes);

}

//isZshapedTest
void is_Z_shaped_test(){

    double _a=3.0;
    double _b=7.0;

    fuzzy::IsZshaped<double> iZshaped(_a,_b);

    double _dmin=3.0;
    core::ValueModel<double> vmMin(_dmin);
    ASSERT(1==iZshaped.evaluate(&vmMin));

    double _dmax=7.0;
    core::ValueModel<double> vmMax(_dmax);
    ASSERT(0==iZshaped.evaluate(&vmMax));

    double _dBetween_a_ab2=5.0;
    core::ValueModel<double> vmBetween_a_ab2(_dBetween_a_ab2);
    ASSERT(1 - 2*pow((_dBetween_a_ab2 - _a)/(_b - _a),2)==iZshaped.evaluate(&vmBetween_a_ab2));

    double _dBetween_ab2_a=5.5;
    core::ValueModel<double> vmBetween_ab2_a(_dBetween_ab2_a);
    double resultatExpected=2*pow(_b - (_dBetween_ab2_a/(_b - _a)),2);
    double resultat=iZshaped.evaluate(&vmBetween_ab2_a);
    ASSERT(resultatExpected==resultat);


}

//thenSugenoTest
void then_sugeno_test(){

    double _l=2.0;
    core::ValueModel<double> vmLeft(_l);
    double _r=3.0;
    core::ValueModel<double> vmRight(_r);

    fuzzy::ThenSugeno<double> thenS;

    ASSERT(_l*_r==thenS.evaluate(&vmLeft,&vmRight));
    ASSERT(_l==thenS.premiseValue());

}
//sugenoDefuzzTest
void sugeno_defuzz_test(){

    double _l1=2.0;
    core::ValueModel<double> vmLeft1(_l1);
    double _r1=1.0;
    core::ValueModel<double> vmRight1(_r1);

    double _l2=2.0;
    core::ValueModel<double> vmLeft2(_l2);
    double _r2=3.0;
    core::ValueModel<double> vmRight2(_r2);

    fuzzy::ThenSugeno<double> thenS1;
    core::BinaryExpressionModel<double> bemThenS1(&thenS1,&vmLeft1,&vmRight1);
    core::Expression<double>* e_bemThenS1=&bemThenS1;

    ASSERT(2==e_bemThenS1->evaluate());

    fuzzy::ThenSugeno<double> thenS2;
    core::BinaryExpressionModel<double> bemThenS2(&thenS2,&vmLeft2,&vmRight2);
    core::Expression<double>* e_bemThenS2=&bemThenS2;

    ASSERT(6==e_bemThenS2->evaluate());

    std::vector<core::Expression<double>* > rules;
    rules.push_back(e_bemThenS1);
    rules.push_back(e_bemThenS2);

    //analyze process
    core::BinaryExpressionModel<double>* bemGot1 = (core::BinaryExpressionModel<double>*) (rules[0]);
    ASSERT(bemGot1->evaluate()==e_bemThenS1->evaluate());
    fuzzy::ThenSugeno<double>* st1 = (fuzzy::ThenSugeno<double>*) bemGot1->getOperator();
    ASSERT(vmLeft1.evaluate()==st1->premiseValue());


    core::BinaryExpressionModel<double>* bemGot2 = (core::BinaryExpressionModel<double>*) (rules[1]);
    ASSERT(bemGot2->evaluate()==e_bemThenS2->evaluate());
    fuzzy::ThenSugeno<double>* st2 = (fuzzy::ThenSugeno<double>*) bemGot2->getOperator();
    ASSERT(vmLeft1.evaluate()==st2->premiseValue());

    double w=0,wz=0;

    typename std::vector<core::Expression<double>*>::const_iterator it;
    for(it=rules.begin();it!=rules.end();it++){
        core::BinaryExpressionModel<double>* bem = (core::BinaryExpressionModel<double>*) (*it);
        fuzzy::ThenSugeno<double>* st = (fuzzy::ThenSugeno<double>*) bem->getOperator();
        wz += bem->evaluate();
        w += st->premiseValue();
    }
    //std::cout<<"Resultat : => "<<wz/w;

    fuzzy::SugenoDefuzz<double> sd;
    sd.evaluate(&rules);
    //std::cout<<std::endl<<"Resultat : => "<<sd.evaluate(&rules);

    ASSERT(wz/w==sd.evaluate(&rules));

}

/*void sugeno_test(){
    fuzzy::SugenoThen<float> sugThen;
    f.changeThen(sugThen);


    vector<core::Expression<float>*> sugenoConclSF;
    sugenoConclSF.push_back(&service);
    sugenoConclSF.push_back(&food);

    vector<core::Expression<float>*> sugenoConclS;
    sugenoConclS.push_back(&service);

    vector<core::Expression<float>*> sRules;
    sRules.push_back(
        f.newThen(
            f.newOr(
                f.newIs(&poor,&service),
                f.newIs(&rancid,&food)
            ),
            f.newSugenoConclusion(sugenoConclSF)
        )
    );
    sRules.push_back(
        f.newThen(
            f.newIs(&good,&service),
            f.newSugenoConclusion(sugenoConclS)
        )
    );
    sRules.push_back(
        f.newThen(
            f.newOr(
                f.newIs(&excellent,&service),
                f.newIs(&delicious,&food)
            ),
            f.newSugenoConclusion(sugenoConclSF)
        )
    );


    core::Expression<float>* sugeno =  f.newSugenoDefuzz(sRules);

    cout << "Sugeno tips -> " << sugeno->evaluate() << endl;
}

}*/




void fuzzy_main_tests(){
    std::cout << ">not_minus1_test<" << std::endl;
    not_minus1_test();
    std::cout << ">is_triangle_test<" << std::endl;
    is_triangle_test();
    std::cout << ">and_min_test<" << std::endl;
    and_min_test();
    std::cout << ">then_min_test<" << std::endl;
    then_min_test();
    std::cout << ">agg_max_test<" << std::endl;
    agg_max_test();
    std::cout << ">agg_plus_test<" << std::endl;
    agg_plus_test();
    std::cout << ">or_max_test<" << std::endl;
    or_max_test();
    std::cout << ">or_plus_test<" << std::endl;
    or_plus_test();
    std::cout << ">is_trapeze_test<" << std::endl;
    is_trapeze_test();
    std::cout << ">is_bell_test<" << std::endl;
    is_bell_test();
    std::cout << ">is_gauss_test<" << std::endl;
    is_gauss_test();
    std::cout << ">is_trapeze_left_test<" << std::endl;
    is_trapeze_left_test();
    std::cout << ">is_trapeze_right_test<" << std::endl;
    is_trapeze_right_test();
    std::cout << ">is_Z_shaped_test<" << std::endl;
    is_Z_shaped_test();
    std::cout << ">the_sugeno_test<" << std::endl;
    then_sugeno_test();
    std::cout << ">sugeno_defuzz_test<" << std::endl;
    //sugeno_defuzz_test();
}
