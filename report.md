# COMP2012H Assignment 2 Report

##### Author: WONG Yuk Chun (20419764)

## Task 1

the link list is from most significant digit to least significant digit with sign as head.

### iostream operators

##### a. `<<` : 

it is just similar to the `to_string` function, loop through the link list and print, then return ostream object passed.

##### b. `>>` : 
it is just calling the `from_string` function using the input string as parameter, then return istream object passed.

### Comparison operators

##### a. `a == b`: 

it is just looping through the two link list on the same time, once there is a different character at the same corresponding position of the two lists, return false. If the list have different length, return false. else it is true.

##### b. `a != b` : 

it is inversing the result of `a==b`

##### c. `a > b` : 

   if a is positive and b is negative, a of course bigger than b, true. 
   if a is negative and b is positive, a of course smaller than b, false. 
   if both are positive, if index of decimal point of a is bigger than that of b, a of course bigger than b, it is true. If index of decimal point of a is smaller than that of b, a of course smaller than b, false.  if index of dot are the same, loop through the two link list from most significant digit to least, pointed digits must be coefficient of same power of ten. Once there is digit from a bigger than corresponding one in b, a is bigger than b, true; inversely there it reach a digit in a smaller than b, a is smaller than b, false; if they are not equal length, if a is longer, it is true, else false. The left over case is all corresponding digits are same and length is the same, it is false also.
   if both are negative, the return result is the inverse of result of both are positive.

##### d. `a < b`: 

equivalent with `b > a`

##### e. `a >= b`: 

equivalent with inverse of `b > a`

##### f. `a <= b`: 

equivalent with inverse of `a > b`

### Assignment operator

##### a. `=`:

remove all nodes in the link list, construct new link list by copying the value of the source link list.

### Arithmetic operators

##### a. `a + b` :

1. compare the absolute value of a and b, let a be the bigger and b be the smaller.


2. align the dot position of a and b by adding zero at front and at the back, like
   a = XXXXXX.XX
   b = X.XXXXX
   will become
   a = XXXXXX.XX000
   b = 00000X.XXXXX
3. loop from least significant figure to the most, if same sign, preform addition, else preform subtraction, increment or decrement LHS digit correspondingly when necessary. 
4. finally return the value with sign of a

##### b. `a - b`:

1. flip the sign of copy of b, b', '+' to '-' or '-' to '+' 
2. return value of a+b'.

##### c. `a * b`:

1. remove the dot of absolute value of a and b, namely `a'` and `b'`.

2. if b' equals to 10, semi-product is appending `0` to `a'`, a base case for recurrence relationship of `*`
   if a' equals to 10, semi-product is appending `0` to `b'`, a base case for recurrence relationship of `*`
   if b' is one digit, semi-product (initially = 0) is the loop from first digit of a', each time multiply by 10 and add the multiple of the digit and b. 
   else b' is more than one digit, semi-product is a' * last digit of b' + 10* a*remaining digits of b'

3. add dot to the semi-product, location from right is the sum of number of decimal digits of a and b.

4. set sign of the semi-product, if sign of a and b are the same, sign is +, if not sign is -, and now it is the final product.

##### d. `a / b`: //TODO

1. if b equals to 0, throw division by zero error
2. remove dot of absolute value of a and b, namely `a'` and `b'`.
3. calculate the quota for decimal points in the quotient, which is max of precision of a and b +1 (for rounding)
4. Record the biggest possible digit place, which should be dropping one by one in each evaluation, if it skips, 
5. if `a' < b'`, remove one quota and evaluate a'*10/b'. if it is the first time to use quota, append a dot. If quota have been used in a combo (the previous evaluation is also using quota), append 0. If there is no quota left, see if the max possible digit is 0, not 0 append an amount of "max possible digit" character '0's, and terminate but if the last digit is a dot, append 0 before terminate.
6. if `a' >= b'`, multiply b' by 10 until it is just smaller than 

##### e. `a ^ b `:

1. if b<0, it is `a/abs(b)` with precision of max of that of a and b, and round off accordingly.
2. if b equals 0, result is 1
3. if b equals 1, result is a
4. if b equals 2, result is a*a
5. else 
   1. turn $b$ to a bit-string, set result as 1.
   2. for each digit $b_i$ in $b$, if $b_i$ is 1,result multiply by ${a}^{2^i}$ 
   3. return result

##### f. increment and decrement

`++a` : add 1 to this and return this

`a++` : make a copy of a, add 1 to this, return the copy

`--a` : minus 1 from this and return this

`a--` : make a copy of a, minus 1 from this, return the copy

## Task 2



