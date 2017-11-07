/*
 * main.cpp
 * This is only a demo of BigDecimal test program. 
 * The one which grades your homework will be more complete and more strict.
 */

#include "bigDecimal.h"

#include <iostream>
#include <sstream>
#include <string.h>
#include <vector>
#include <time.h>

using namespace std;

char str[1024];

vector<double> val = {0,1,-2,12.5,-12.34567,98765432.1,12446,356.25,43.6725,2353.6532,2.15262,0.00003};

void test_sum(){
    for(int i=0; i<val.size();i++){
        for(int j=i+1; j<val.size();j++){
            BigDecimal a(val[i]),b(val[j]);
            cout<<"i + j = "<<val[i]<<" + "<<val[j]<<" = "<<val[i]+val[j]<<endl
            <<a+b<<endl
            <<a+val[j]<<endl
            <<val[i]+b<<endl<<endl;
        }
    }
}

void test_minus(){
    for(int i=0; i<val.size();i++){
        for(int j=i+1; j<val.size();j++){
            BigDecimal a(val[i]),b(val[j]);
            cout<<"i - j = "<<val[i]<<" - "<<val[j]<<" = "<<val[i]-val[j]<<endl
            <<a-b<<endl
            <<a-val[j]<<endl
            <<val[i]-b<<endl<<endl;
        }
    }
}

void test_multi(){
    for(int i=0; i<val.size();i++){
        for(int j=i+1; j<val.size();j++){
            BigDecimal a(val[i]),b(val[j]);
            cout<<"i * j = "<<val[i]<<" * "<<val[j]<<" = "<<val[i]*val[j]<<endl
//            <<a*b<<endl
//            <<a*val[j]<<endl
            <<val[i]*b<<endl<<endl;
        }
    }
}

void test_div(){
    for(int i=0; i<val.size();i++){
        for(int j=0; j<val.size();j++){
            BigDecimal a(val[i]),b(val[j]);
            cout<<"i / j = "<<val[i]<<" / "<<val[j]<<" = "<<val[i]/val[j]<<endl
            <<a/b<<endl
            <<a/val[j]<<endl
            <<val[i]/b<<endl<<endl;
        }
    }
}

int main(){
    std::cout << std::fixed;
    std::cout.precision(5);
//    srand(time(NULL));
//    test_sum();
//    test_minus();
//    test_multi();
//cout<<BigDecimal("0.00000346")*1.234<<" "<<0.00000346*1234<<endl;
//    test_div();
//    cout<<"pause"<<endl;
//    while(1);

    BigDecimal a("-1");
//    a.drop_decimal();
    cout<<(a^3);
    
//    2353.65320 / 2.15262
    
//    BigDecimal b("12345");
//    BigDecimal c(b);
//    cout<<c<<endl;
//    cout<<((c*1)>c)<<endl;
//    cout<<c<<endl;
//cout<<"division result:"<<(BigDecimal("0.5")-BigDecimal("0.5"))<<endl<<endl;
//cout<<-2.00000<<"/" <<12446.00000<<"="<<-2.00000 / 12446.00000<<endl;
//    cout<<"division result:"<<(BigDecimal("900")/BigDecimal("10"))<<endl<<endl;
//    cout<<"division result:"<<BigDecimal(BigDecimal("79861200000").to_string().c_str())<<endl<<endl;
//cout<<"division result:"<<(BigDecimal("0.1")*BigDecimal("10"))<<endl<<endl;
    
//    BigDecimal a;
//    cout<<a.roundoff_1d("999999");
    
//    BigDecimal a;
//    a.from_string("-00001.4003000");
//    a.print();
    
//    printf("hello world\n");
//    BigDecimal a("90000"),b("12.345");
//    BigDecimal c(a+b);
//    c.print();

//    BigDecimal a("12.3450"),b("2.4690");
//    BigDecimal c(a*-2.4690);
//    cout<<"c:"<<c<<endl;

//    BigDecimal a("103"),b("100000");
//    BigDecimal c(a*b);
//    cout<<"c:"<<c;

//    BigDecimal a("0"),b(0);
//    cout<<a<<" "<<b<<endl;
//    a = a + b;
//    cout<<"c:"<<a;

//    BigDecimal a("11"),b("13.345");
//    BigDecimal c(a/b);
//    cout<<"c:";
//    c.print();

//    cout<<BigDecimal("0010.123445");

//    BigDecimal a("4556"),b("-4400");
//    BigDecimal c(a+b);
//    cout<<"c:";
//    c.print();

//    BigDecimal a("-10.234"),b("-10.234");
//    cout<<(a>b);
}
