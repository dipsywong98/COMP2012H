/*
 * main.cpp
 * This is only a demo of BigDecimal test program. 
 * The one which grades your homework will be more complete and more strict.
 */

#include "bigDecimal.h"

#include <iostream>
#include <sstream>
#include <string.h>

using namespace std;

char str[1024];

int main(){
    printf("hello world\n");
    BigDecimal a("-1235.124534"),b("+999325237.1345");
    a.print();
    b.print();
    a+b;
}
