#include "bigDecimal.h"

#include <iostream>
#include <sstream>
#include <string.h>

#define TRUE "1"
#define FALSE "0"

#define SECTION(name) cout << "----------\n\n" << (name) << ": \n";

#define TEST(test_expr, test_case) {\
    BigDecimal r = test_expr;\
    ostringstream oss;\
    ostringstream p;\
    oss << r;\
    bool t = oss.str() == (test_case);\
    p << (total + 1) << ". ";\
    p << (t ? "SUCCESS    " : "!!FAIL!!   ");\
    p << (#test_expr) << " = "; \
    if (#test_case == "TRUE" || #test_case == "FALSE") p << (oss.str() == "1" ? "TRUE" : "FALSE");\
    else p << r;\
    p << endl;\
    if (!t) {\
        cout << "   `- test case is: " << #test_case << endl;\
        fail_rate++;\
        fails << p.str();\
    } else success_rate++;\
    cout << p.str();\
    total++;\
};

using namespace std;

int main() {
    int success_rate = 0;
    int fail_rate = 0;
    int total = 0;
    ostringstream fails;

    SECTION("Construction Test")
    TEST(BigDecimal(), "0")
    TEST(BigDecimal("0"), "0")
    TEST(BigDecimal("-0"), "0")
    TEST(BigDecimal("12345.6789"), "12345.6789")
    TEST(BigDecimal(123456), "123456")
    TEST(BigDecimal(12.345678), "12.34568")
    TEST(BigDecimal(12345.678901), "12345.6789")

    SECTION("String Test")
    TEST([](){BigDecimal a = 1000; char s[1024]; a.to_string(s); return BigDecimal(s);}(), "1000")
    TEST([](){BigDecimal a = 5; char s[1024] = "1.24"; a.from_string(s); return a;}(), "1.24")
    TEST([](){BigDecimal a = 5; char s[1024] = "a1.24"; a.from_string(s); return a;}(), "5")

    SECTION("Input Operator Test")
    TEST([](){stringstream ss; ss << "0 1000"; BigDecimal a; BigDecimal b; ss >> a >> b; return b;}(), "1000")

    SECTION("Addition Test")
    TEST(BigDecimal("9999.159768") + BigDecimal(3000.297), "12999.456768")
    TEST(BigDecimal(9999.159768) + (3000.297), "12999.45677")
    TEST(BigDecimal(0.1) + (9.9), "10")

    SECTION("Assignment Test")
    TEST([](){BigDecimal a = BigDecimal("1000"); BigDecimal b = BigDecimal("2000"); b = a; return b;}(), "1000")
    TEST([](){BigDecimal a = 1000; return a;}(), "1000")
    TEST([](){BigDecimal a = 1000.1; return a;}(), "1000.1")

    SECTION("Comparison Test");
    TEST(BigDecimal(1.231) == BigDecimal("1.231"), TRUE)
    TEST(BigDecimal(1.231) != BigDecimal("1.231"), FALSE)
    TEST(BigDecimal(1.231) > BigDecimal(-3000.297), TRUE)
    TEST(BigDecimal(1.231) < BigDecimal(3000.297), TRUE)
    TEST(BigDecimal(1.231) < BigDecimal(-3000.297), FALSE)
    TEST(BigDecimal(1.231) < BigDecimal(3000.297), TRUE)
    TEST(BigDecimal("123456") == BigDecimal("123456.00000"), TRUE)
    TEST(BigDecimal(3) > 2, TRUE)
    TEST(BigDecimal(-3) > 2, FALSE)
    TEST(BigDecimal(3) > -2, TRUE)
    TEST(BigDecimal(-3) > -2, FALSE)
    TEST(BigDecimal(3) < 2, FALSE)
    TEST(BigDecimal(-3) < 2, TRUE)
    TEST(BigDecimal(3) < -2, FALSE)
    TEST(BigDecimal(-3) < -2, TRUE)
    TEST(BigDecimal(3) < 4, TRUE)
    TEST(BigDecimal(-3) < 4, TRUE)
    TEST(BigDecimal(3) < -4, FALSE)
    TEST(BigDecimal(-3) < -4, FALSE)
    TEST(BigDecimal("0") > BigDecimal("-0"), FALSE)
    TEST(BigDecimal("-0") > BigDecimal("0"), FALSE)
    TEST(BigDecimal("0") < BigDecimal("-0"), FALSE)
    TEST(BigDecimal("-0") < BigDecimal("0"), FALSE)
    TEST(BigDecimal("-0") == BigDecimal("0"), TRUE)

    SECTION("Increment Decrement Test")
    TEST([](){BigDecimal a; return a++;}(), "0")
    TEST([](){BigDecimal a; return ++a;}(), "1")
    TEST([](){BigDecimal a; return a--;}(), "0")
    TEST([](){BigDecimal a; return --a;}(), "-1")
    TEST([](){BigDecimal a = BigDecimal("3.3"); return ++a;}(), "4.3")

    SECTION("Subtraction Test")
    TEST(BigDecimal("9999.159768") - 3000.297, "6998.862768")
    TEST(BigDecimal(3000.297) - "9999.159768", "-6998.862768")
    TEST(BigDecimal("9999.159768") - -3000.297, "12999.456768")
    TEST(BigDecimal(-3000.297) - "9999.159768", "-12999.456768")
    TEST(BigDecimal("20") - BigDecimal("18"), "2")
    TEST(BigDecimal("18") - BigDecimal("20"), "-2")

    SECTION("Multiplication Test")
    TEST(BigDecimal("2") * BigDecimal("2"), "4")
    TEST(BigDecimal("10") * BigDecimal("10"), "100")
    TEST(BigDecimal("1234") * BigDecimal("56"), "69104")
    TEST(BigDecimal("56") * BigDecimal("1234"), "69104")
    TEST(BigDecimal("123.4") * BigDecimal("-5.6"), "-691.04")
    TEST(BigDecimal("-123.4") * BigDecimal("-0.56"), "69.104")
    TEST(BigDecimal("1.23456123456") * BigDecimal("-987.65439876543"), "-1219.3198338584638006492608")

    SECTION("Division Test")
    TEST(BigDecimal("2") / BigDecimal("2"), "1")
    TEST(BigDecimal("4") / BigDecimal("2"), "2")
    TEST(BigDecimal("10") / BigDecimal("1"), "10")
    TEST(BigDecimal("590") / BigDecimal("5"), "118")
    TEST(BigDecimal("8") / BigDecimal("3"), "3")
    TEST(BigDecimal("8.00000") / BigDecimal("3"), "2.66667")
    TEST(BigDecimal("-22.00000") / BigDecimal("-7"), "3.14286")
    TEST(BigDecimal("-2.00000") / BigDecimal("3"), "-0.66667")
    TEST(BigDecimal("20") / BigDecimal("10"), "2")
    TEST(BigDecimal("20") / BigDecimal("-0"), "0") //division by zero
    TEST(BigDecimal("200.36") / BigDecimal("6"), "33.39")
    TEST(BigDecimal("19999.99999") / BigDecimal("2"), "10000") //result rounding

    SECTION("Power Test")
    TEST(BigDecimal("2") ^ BigDecimal("2"), "4")
    TEST(BigDecimal("2") ^ BigDecimal("7"), "128")
    TEST(BigDecimal("2") ^ BigDecimal("2.564"), "4")
    TEST(BigDecimal("2") ^ BigDecimal("0"), "1")
    TEST(BigDecimal("0") ^ BigDecimal("-5"), "0")
    TEST(BigDecimal("2") ^ BigDecimal("-1"), "1")
    TEST(BigDecimal("2") ^ BigDecimal("-1.0"), "0.5")

    //-----

    SECTION("Summary")
    cout << "Total: " << total << endl;
    cout << "Successes: " << success_rate << endl;
    cout << "Fails: " << fail_rate << endl;
    cout << "Fail cases: " << endl;
    cout << "--End Summary--" << endl;
    cout << fails.str();
}
