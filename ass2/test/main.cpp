#include "bigDecimal.h"

#include <iostream>
#include <string.h>

using namespace std;

char str[1024];

void test_1(bool debug = false) {
  BigDecimal b1;
  BigDecimal b2("100");
  BigDecimal b3("+2.4");
  BigDecimal b4("2.4");
  BigDecimal b5("-2.4");
  BigDecimal b6("+02.4");
  BigDecimal b7("02.4");
  BigDecimal b8("-02.4");
  BigDecimal b9("+0.4");
  BigDecimal b10("0.4");
  BigDecimal b11("-0.4");
  BigDecimal b12("0");
  BigDecimal b13("-0");
  BigDecimal b14("2");
  BigDecimal b15("2.0");
  BigDecimal b16("2.40");

  bool correct = true;
  b1.to_string(str);
  correct &= !strcmp(str, "0");
  if (debug) cout << str << " " << correct << endl;
  b2.to_string(str);
  correct &= !strcmp(str, "100");
  if (debug) cout << str << " " << correct << endl;
  b3.to_string(str);
  correct &= !strcmp(str, "2.4");
  if (debug) cout << str << " " << correct << endl;
  b4.to_string(str);
  correct &= !strcmp(str, "2.4");
  if (debug) cout << str << " " << correct << endl;
  b5.to_string(str);
  correct &= !strcmp(str, "-2.4");
  if (debug) cout << str << " " << correct << endl;
  b6.to_string(str);
  correct &= !strcmp(str, "2.4");
  if (debug) cout << str << " " << correct << endl;
  b7.to_string(str);
  correct &= !strcmp(str, "2.4");
  if (debug) cout << str << " " << correct << endl;
  b8.to_string(str);
  correct &= !strcmp(str, "-2.4");
  if (debug) cout << str << " " << correct << endl;
  b9.to_string(str);
  correct &= !strcmp(str, "0.4");
  if (debug) cout << str << " " << correct << endl;
  b10.to_string(str);
  correct &= !strcmp(str, "0.4");
  if (debug) cout << str << " " << correct << endl;
  b11.to_string(str);
  correct &= !strcmp(str, "-0.4");
  if (debug) cout << str << " " << correct << endl;
  b12.to_string(str);
  correct &= !strcmp(str, "0");
  if (debug) cout << str << " " << correct << endl;
  b13.to_string(str);
  correct &= !strcmp(str, "0");
  if (debug) cout << str << " " << correct << endl;
  b14.to_string(str);
  correct &= !strcmp(str, "2");
  if (debug) cout << str << " " << correct << endl;
  b15.to_string(str);
  correct &= !strcmp(str, "2");
  if (debug) cout << str << " " << correct << endl;
  b16.to_string(str);
  correct &= !strcmp(str, "2.4");
  if (debug) cout << str << " " << correct << endl;

  cout << "Test 1: \t" << correct << endl;
}

void test_2(bool debug = false) {
  BigDecimal b; bool correct = true;
  correct &= b.from_string("0");
  b.to_string(str);
  correct &= !strcmp(str, "0");
  if (debug) cout << str << " " << correct << endl;
  correct &= b.from_string("-0.2");
  b.to_string(str);
  correct &= !strcmp(str, "-0.2");
  if (debug) cout << str << " " << correct << endl;
  correct &= b.from_string("100");
  b.to_string(str);
  correct &= !strcmp(str, "100");
  if (debug) cout << str << " " << correct << endl;
  correct &= !b.from_string("asb");
  b.to_string(str);
  correct &= !strcmp(str, "100");
  if (debug) cout << str << " " << correct << endl;
  correct &= !b.from_string(".2");
  b.to_string(str);
  correct &= !strcmp(str, "100");
  if (debug) cout << str << " " << correct << endl;
  correct &= !b.from_string("-.2");
  b.to_string(str);
  correct &= !strcmp(str, "100");
  if (debug) cout << str << " " << correct << endl;
  correct &= !b.from_string("");
  b.to_string(str);
  correct &= !strcmp(str, "100");
  if (debug) cout << str << " " << correct << endl;

  cout << "Test 2: \t" << correct << endl;
}

void test_3(bool debug = false) {
  BigDecimal b1(0);
  BigDecimal b2(-2);
  BigDecimal b3(-1.40000);
  BigDecimal b4(2.0);
  BigDecimal b5(0.5);
  BigDecimal b6(0.123112);
  BigDecimal b7(0.123457);

  bool correct = true;
  b1.to_string(str);
  correct &= !strcmp(str, "0");
  if (debug) cout << str << " " << correct << endl;
  b2.to_string(str);
  correct &= !strcmp(str, "-2");
  if (debug) cout << str << " " << correct << endl;
  b3.to_string(str);
  correct &= !strcmp(str, "-1.4");
  if (debug) cout << str << " " << correct << endl;
  b4.to_string(str);
  correct &= !strcmp(str, "2");
  if (debug) cout << str << " " << correct << endl;
  b5.to_string(str);
  correct &= !strcmp(str, "0.5");
  if (debug) cout << str << " " << correct << endl;
  b6.to_string(str);
  correct &= !strcmp(str, "0.12311");
  if (debug) cout << str << " " << correct << endl;
  b7.to_string(str);
  correct &= !strcmp(str, "0.12346");
  if (debug) cout << str << " " << correct << endl;

  cout << "Test 3: \t" << correct << endl;
}

void test_4(bool debug = false) {
  bool correct = true;
  BigDecimal b("-0.5");
  BigDecimal bb = b;
  char str1[1024], str2[1024];
  b.to_string(str1);
  bb.to_string(str2);
  correct &= !strcmp(str1, str2);
  if (debug) cout << str1 << " " << str2 << " " << correct << endl;
  BigDecimal bbb("-10.4");
  bb = bbb;
  bb.to_string(str1);
  bbb.to_string(str2);
  correct &= !strcmp(str1, str2);
  if (debug) cout << str1 << " " << str2 << " " << correct << endl;
  bbb = 23;
  bbb.to_string(str1);
  correct &= !strcmp(str1, "23");
  if (debug) cout << str1 << " " << correct << endl;
  bbb = 3.1213;
  bbb.to_string(str1);
  correct &= !strcmp(str1, "3.1213");
  if (debug) cout << str1 << " " << correct << endl;

  cout << "Test 4: \t" << correct << endl;
}

void test_5(bool debug = false) {
  bool correct = true;
  BigDecimal b1("1");
  BigDecimal b2("9.9");
  (b1+b2).to_string(str);
  correct &= !strcmp(str, "10.9");
  if (debug) cout << b1 << " " << b2 << " " << str << " " << correct << endl;

  b2 = "-0.1";
  (b1+b2).to_string(str);
  correct &= !strcmp(str, "0.9");
  if (debug) cout << b1 << " " << b2 << " " << str << " " << correct << endl;

  b1 = "-1";
  b2 = "9.9";
  (b1+b2).to_string(str);
  correct &= !strcmp(str, "8.9");
  if (debug) cout << b1 << " " << b2 << " " << str << " " << correct << endl;

  b1 = "3";
  b2 = "-99";
  (b1+b2).to_string(str);
  correct &= !strcmp(str, "-96");
  if (debug) cout << b1 << " " << b2 << " " << str << " " << correct << endl;


  b1 = "-112";
  b2 = "-9.9";
  (b1+b2).to_string(str);
  correct &= !strcmp(str, "-121.9");
  if (debug) cout << b1 << " " << b2 << " " << str << " " << correct << endl;


  b1 = "100";
  b2 = "0.9";
  (b1-b2).to_string(str);
  correct &= !strcmp(str, "99.1");
  if (debug) cout << b1 << " " << b2 << " " << str << " " << correct << endl;


  b1 = "112";
  b2 = "-9.9";
  (b1-b2).to_string(str);
  correct &= !strcmp(str, "121.9");
  if (debug) cout << b1 << " " << b2 << " " << str << " " << correct << endl;


  b1 = "-112";
  b2 = "9.9";
  (b1-b2).to_string(str);
  correct &= !strcmp(str, "-121.9");
  if (debug) cout << b1 << " " << b2 << " " << str << " " << correct << endl;


  b1 = "-112";
  b2 = "-9.9";
  (b1-b2).to_string(str);
  correct &= !strcmp(str, "-102.1");
  if (debug) cout << b1 << " " << b2 << " " << str << " " << correct << endl;

  b1 = "999.9";
  (b1++).to_string(str);
  correct &= !strcmp(str, "999.9");
  if (debug) cout << b1 << " " << b2 << " " << str << " " << correct << endl;
  (++b1).to_string(str);
  correct &= !strcmp(str, "1001.9");
  if (debug) cout << b1 << " " << b2 << " " << str << " " << correct << endl;

  b1 = "1000.9";
  (b1--).to_string(str);
  correct &= !strcmp(str, "1000.9");
  if (debug) cout << b1 << " " << b2 << " " << str << " " << correct << endl;
  (--b1).to_string(str);
  correct &= !strcmp(str, "998.9");
  if (debug) cout << b1 << " " << b2 << " " << str << " " << correct << endl;


  b1 = "999.9";
  (1 + b1).to_string(str);
  correct &= !strcmp(str, "1000.9");
  if (debug) cout << b1 << " " << b2 << " " << str << " " << correct << endl;
  (0.1 + b1).to_string(str);
  correct &= !strcmp(str, "1000");
  if (debug) cout << b1 << " " << b2 << " " << str << " " << correct << endl;
  (1 - b1).to_string(str);
  correct &= !strcmp(str, "-998.9");
  if (debug) cout << b1 << " " << b2 << " " << str << " " << correct << endl;
  (0.1 - b1).to_string(str);
  correct &= !strcmp(str, "-999.8");
  if (debug) cout << b1 << " " << b2 << " " << str << " " << correct << endl;

  cout << "Test 5: \t" << correct << endl;
}

void test_6(bool debug = false) {
  bool correct = true;
  BigDecimal b1("3");
  BigDecimal b2("4");
  correct &= (b1 < b2);
  if (debug) cout << b1 << " " << b2 << " " << (b1 < b2) << " " << correct << endl;

  b1 = "-3";
  b2 = "4";
  correct &= (b1 < b2);
  if (debug) cout << b1 << " " << b2 << " " << (b1 < b2) << " " << correct << endl;

  b1 = "3";
  b2 = "-4";
  correct &= !(b1 < b2);
  if (debug) cout << b1 << " " << b2 << " " << (b1 < b2) << " " << correct << endl;

  b1 = "33";
  b2 = "4";
  correct &= !(b1 < b2);
  if (debug) cout << b1 << " " << b2 << " " << (b1 < b2) << " " << correct << endl;

  b1 = "3";
  b2 = "43";
  correct &= (b1 < b2);
  if (debug) cout << b1 << " " << b2 << " " << (b1 < b2) << " " << correct << endl;

  b1 = "3.0";
  b2 = "4";
  correct &= (b1 < b2);
  if (debug) cout << b1 << " " << b2 << " " << (b1 < b2) << " " << correct << endl;

  b1 = "3.33";
  b2 = "3.34";
  correct &= (b1 < b2);
  if (debug) cout << b1 << " " << b2 << " " << (b1 < b2) << " " << correct << endl;

  b1 = "3.45";
  b2 = "3.34";
  correct &= !(b1 < b2);
  if (debug) cout << b1 << " " << b2 << " " << (b1 < b2) << " " << correct << endl;

  b1 = "3";
  b2 = "3.334";
  correct &= (b1 < b2);
  if (debug) cout << b1 << " " << b2 << " " << (b1 < b2) << " " << correct << endl;

  b1 = "3.33";
  b2 = "3.334";
  correct &= (b1 < b2);
  if (debug) cout << b1 << " " << b2 << " " << (b1 < b2) << " " << correct << endl;

  b1 = "3.3345";
  b2 = "3.334";
  correct &= !(b1 < b2);
  if (debug) cout << b1 << " " << b2 << " " << (b1 < b2) << " " << correct << endl;

  b1 = "3";
  b2 = "3";
  correct &= !(b1 < b2);
  if (debug) cout << b1 << " " << b2 << " " << (b1 < b2) << " " << correct << endl;

  b1 = "3.334";
  b2 = "3.334";
  correct &= !(b1 < b2);
  if (debug) cout << b1 << " " << b2 << " " << (b1 < b2) << " " << correct << endl;

  b1 = "-3";
  b2 = "-4";
  correct &= !(b1 < b2);
  if (debug) cout << b1 << " " << b2 << " " << (b1 < b2) << " " << correct << endl;

  b1 = "-33";
  b2 = "-4";
  correct &= (b1 < b2);
  if (debug) cout << b1 << " " << b2 << " " << (b1 < b2) << " " << correct << endl;

  b1 = "-3";
  b2 = "-43";
  correct &= !(b1 < b2);
  if (debug) cout << b1 << " " << b2 << " " << (b1 < b2) << " " << correct << endl;

  b1 = "-3.0";
  b2 = "-4";
  correct &= !(b1 < b2);
  if (debug) cout << b1 << " " << b2 << " " << (b1 < b2) << " " << correct << endl;

  b1 = "-3.33";
  b2 = "-3.34";
  correct &= !(b1 < b2);
  if (debug) cout << b1 << " " << b2 << " " << (b1 < b2) << " " << correct << endl;

  b1 = "-3.45";
  b2 = "-3.34";
  correct &= (b1 < b2);
  if (debug) cout << b1 << " " << b2 << " " << (b1 < b2) << " " << correct << endl;

  b1 = "-3";
  b2 = "-3.334";
  correct &= !(b1 < b2);
  if (debug) cout << b1 << " " << b2 << " " << (b1 < b2) << " " << correct << endl;

  b1 = "-3.33";
  b2 = "-3.334";
  correct &= !(b1 < b2);
  if (debug) cout << b1 << " " << b2 << " " << (b1 < b2) << " " << correct << endl;

  b1 = "-3.3345";
  b2 = "-3.334";
  correct &= (b1 < b2);
  if (debug) cout << b1 << " " << b2 << " " << (b1 < b2) << " " << correct << endl;

  b1 = "-3";
  b2 = "-3";
  correct &= !(b1 < b2);
  if (debug) cout << b1 << " " << b2 << " " << (b1 < b2) << " " << correct << endl;

  b1 = "-3.334";
  b2 = "-3.334";
  correct &= !(b1 < b2);
  if (debug) cout << b1 << " " << b2 << " " << (b1 < b2) << " " << correct << endl;

  cout << "Test 6: \t" << correct << endl;
}

void test_7(bool debug = false) {
  bool correct = true;
  BigDecimal b1, b2;
  correct &= (b1 == b2);
  if (debug) cout << b1 << " " << b2 << " " << (b1 == b2) << " " << correct << endl;

  b1 = "23"; b2 = "-23";
  correct &= !(b1 == b2);
  if (debug) cout << b1 << " " << b2 << " " << (b1 == b2) << " " << correct << endl;
  correct &= !(23 == b2);
  if (debug) cout << b1 << " " << b2 << " " << (b1 == b2) << " " << correct << endl;
  correct &= !(b2 == 23);
  if (debug) cout << b1 << " " << b2 << " " << (b1 == b2) << " " << correct << endl;

  b1 = "23"; b2 = "2";
  correct &= !(b1 == b2);
  if (debug) cout << b1 << " " << b2 << " " << (b1 == b2) << " " << correct << endl;

  b1 = "23"; b2 = "23.1";
  correct &= !(b1 == b2);
  if (debug) cout << b1 << " " << b2 << " " << (b1 == b2) << " " << correct << endl;

  b1 = "23"; b2 = "24";
  correct &= !(b1 == b2);
  if (debug) cout << b1 << " " << b2 << " " << (b1 == b2) << " " << correct << endl;

  b1 = "23.134"; b2 = "-23.151";
  correct &= !(b1 == b2);
  if (debug) cout << b1 << " " << b2 << " " << (b1 == b2) << " " << correct << endl;

  b1 = "23.17782"; b2 = "23.17782";
  correct &= (b1 == b2);
  if (debug) cout << b1 << " " << b2 << " " << (b1 == b2) << " " << correct << endl;

  b1 = "0"; b2 = "-0";
  correct &= (b1 == b2);
  if (debug) cout << b1 << " " << b2 << " " << (b1 == b2) << " " << correct << endl;

  cout << "Test 7: \t" << correct << endl;
}

void test_8(bool debug = false) {
  bool correct = true;
  BigDecimal b1, b2;
  (b1*b2).to_string(str);
  correct &= !strcmp(str, "0");
  if (debug) cout << b1 << " " << b2 << " " <<  b1*b2 << " " << correct << endl;

  b1 = "1312312.4214124124124124124";
  b2 = "-1231.5";
  (b1*b2).to_string(str);
  correct &= !strcmp(str, "-1616112746.9693858858858858706");
  if (debug) cout << b1 << " " << b2 << " " <<  b1*b2 << " " << correct << endl;

  b2 = "1312312.4214124124124124124";
  b1 = "-1231.5";
  (b1*b2).to_string(str);
  correct &= !strcmp(str, "-1616112746.9693858858858858706");
  if (debug) cout << b1 << " " << b2 << " " <<  b1*b2 << " " << correct << endl;
  (-1231.5*b2).to_string(str);
  correct &= !strcmp(str, "-1616112746.9693858858858858706");
  if (debug) cout << b1 << " " << b2 << " " <<  b1*b2 << " " << correct << endl;
  (b2*-1231.5).to_string(str);
  correct &= !strcmp(str, "-1616112746.9693858858858858706");
  if (debug) cout << b1 << " " << b2 << " " <<  b1*b2 << " " << correct << endl;

  b1 = "5";
  b2 = "2";
  (b1/b2).to_string(str);
  correct &= !strcmp(str, "3");
  if (debug) cout << b1 << " " << b2 << " " << str << " " << correct << endl;

  b1 = "1200";
  b2 = "60";
  (b1/b2).to_string(str);
  correct &= !strcmp(str, "20");
  if (debug) cout << b1 << " " << b2 << " " << str << " " << correct << endl;
  (b2/b1).to_string(str);
//  correct &= !strcmp(str, "0");
  if (debug) cout << b2 << " " << b1 << " " << str << " " << correct << endl;

  b1 = "1200.36";
  b2 = "60";
  (b1/b2).to_string(str);
  correct &= !strcmp(str, "20.01");
  if (debug) cout << b1 << " " << b2 << " " << str << " " << correct << endl;
  (b2/b1).to_string(str);
  correct &= !strcmp(str, "0.05");
  if (debug) cout << b2 << " " << b1 << " " << str << " " << correct << endl;

  b1 = "-1200.36";
  b2 = "60";
  (b1/b2).to_string(str);
  correct &= !strcmp(str, "-20.01");
  if (debug) cout << b1 << " " << b2 << " " << str << " " << correct << endl;
  (b2/b1).to_string(str);
  correct &= !strcmp(str, "-0.05");
  if (debug) cout << b2 << " " << b1 << " " << str << " " << correct << endl;

  b1 = "0.0036";
  b2 = "60";
  (b1/b2).to_string(str);
  correct &= !strcmp(str, "0.0001");
  if (debug) cout << b1 << " " << b2 << " " << str << " " << correct << endl;
  (b2/b1).to_string(str);
  correct &= !strcmp(str, "16666.6667");
  if (debug) cout << b2 << " " << b1 << " " << str << " " << correct << endl;

  b1 = "1";
  b2 = "0.000005";
  (b1/b2).to_string(str);
  correct &= !strcmp(str, "200000");
  if (debug) cout << b1 << " " << b2 << " " << str << " " << correct << endl;
  (b2/b1).to_string(str);
  correct &= !strcmp(str, "0.000005");
  if (debug) cout << b2 << " " << b1 << " " << str << " " << correct << endl;

  b1 = "12";
  b2 = "1.2";
  (b1/b2).to_string(str);
  correct &= !strcmp(str, "10");
  if (debug) cout << b1 << " " << b2 << " " << str << " " << correct << endl;
  (b2/b1).to_string(str);
  correct &= !strcmp(str, "0.1");
  if (debug) cout << b2 << " " << b1 << " " << str << " " << correct << endl;

  b1 = "-131315123124125";
  b2 = "0.12312561232141";
  (b1/b2).to_string(str);
  correct &= !strcmp(str, "-1066513462538865.65863634601595");
  if (debug) cout << b1 << " " << b2 << " " << str << " " << correct << endl;
  (b2/b1).to_string(str);
  correct &= !strcmp(str, "0");
  if (debug) cout << b2 << " " << b1 << " " << str << " " << correct << endl;

  b1 = "0.3423";
//  b2 = "0.19";
  (b1/0.19).to_string(str);
  correct &= !strcmp(str, "1.8016");
  if (debug) cout << b1 << " " << b2 << " " << str << " " << correct << endl;
  (0.19/b1).to_string(str);
  correct &= !strcmp(str, "0.5551");
  if (debug) cout << b2 << " " << b1 << " " << str << " " << correct << endl;

  b1 = b2 = 0;
  b1/b2; // exception

  cout << "Test 8: \t" << correct << endl;
}

void test_9(bool debug = false) {
  BigDecimal b1, b2;
  bool correct = true;

  b1 = "5";
  b2 = "3";
  (b1^b2).to_string(str);
  correct &= !strcmp(str, "125");
  if (debug) cout << b1 << " " << b2 << " " << (str) << " " << correct << endl;

  b1 = "123151.2312";
  b2 = "3.1235";
  (b1^b2).to_string(str);
  correct &= !strcmp(str, "1867739373286379.919726755328");
  if (debug) cout << b1 << " " << b2 << " " << (str) << " " << correct << endl;
  b1 = "1.13445";
  b2 = "-1.5";
  (b1^b2).to_string(str);
  correct &= !strcmp(str, "0.88148");
  if (debug) cout << b1 << " " << b2 << " " << str << " " << correct << endl;

  b1 = 0;
  b2 = -15;
  b1^b2; // exception
  cout << "Test 9: \t" << correct << endl;
}

int main() {
  test_1(); // tests string constructor, convert() and to_string()
  test_2(); // tests from_string() validity and clear()
  test_3(); // tests int/float/double constructors
  test_4(); // tests copy constructor and assignment
  test_5(); // tests operator+ and operator-
  test_6(); // tests operator<
  test_7(); // tests operator==
  test_8(); // tests operator* and operator/
  test_9(); // tests operator^


}
