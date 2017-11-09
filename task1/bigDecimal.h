/*
 * bigDecimal.h
 */

#ifndef BIGDECIMAL_H_
#define BIGDECIMAL_H_
#include <iostream>
#include <vector>
#include <string.h>
#include <sstream>

using namespace std;

struct Node { 
  char data;
  Node* next;
};

class BigDecimal {
public:
	BigDecimal();
	BigDecimal(const char* str);
	BigDecimal(int i);
	BigDecimal(float f);
	BigDecimal(double d);
	BigDecimal(const BigDecimal& bi);
	~BigDecimal();

	/* #### You need to implement from_string(const char*) and to_string(char*) methods. #### */
	/**
	 * Method: void from_string(const char* str)
	 * Description:
	 * 		from_string method will read the number from str.
	 * 		If str is valid, it will be parsed and stored into sign and storage, and then return true. Otherwise, false will be returned.
	 */
	bool from_string(const char* str);

	/**
	 * Method: void to_string(const char* str)
	 * Description:
	 * 		to_string method will output the current number to str.
	 */
	void to_string(char* str);

	/* #### Please add your overloading methods below. #### */
	friend ostream& operator<<(ostream& o, const BigDecimal& f);
	friend istream& operator>>(istream& i, BigDecimal bi);
	
	bool operator==(const BigDecimal &bi)const;
	bool operator==(const int &bi)const;
	bool operator==(const float &bi)const;
	bool operator==(const double &bi)const;
	bool operator!=(const BigDecimal &bi)const;
	bool operator!=(const int &bi)const;
	bool operator!=(const float &bi)const;
	bool operator!=(const double &bi)const;
	bool operator>(const BigDecimal &bi)const;
    bool operator>(const int &bi)const;
    bool operator>(const float &bi)const;
    bool operator>(const double &bi)const;
    bool operator<(const BigDecimal &bi)const;
    bool operator<(const int &bi)const;
    bool operator<(const float &bi)const;
    bool operator<(const double &bi)const;
    bool operator<=(const BigDecimal &bi)const;
    bool operator<=(const int &bi)const;	
    bool operator<=(const float &bi)const;
    bool operator<=(const double &bi)const;
    bool operator>=(const BigDecimal &bi)const;
    bool operator>=(const int &bi)const;
    bool operator>=(const float &bi)const;
    bool operator>=(const double &bi)const;
    friend bool operator==(const int &bi, const BigDecimal& th);
    friend bool operator==(const float &bi, const BigDecimal& th);
    friend bool operator==(const double &bi, const BigDecimal& th);
    friend bool operator!=(const int &bi, const BigDecimal& th);
    friend bool operator!=(const float &bi, const BigDecimal& th);
    friend bool operator!=(const double &bi, const BigDecimal& th);
    friend bool operator>(const int &bi, const BigDecimal& th);
    friend bool operator>(const float &bi, const BigDecimal& th);
    friend bool operator>(const double &bi, const BigDecimal& th);
    friend bool operator<(const int &bi, const BigDecimal& th);
    friend bool operator<(const float &bi, const BigDecimal& th);
    friend bool operator<(const double &bi, const BigDecimal& th);
    friend bool operator<=(const int &bi, const BigDecimal& th);
    friend bool operator<=(const float &bi, const BigDecimal& th);
    friend bool operator<=(const double &bi, const BigDecimal& th);
    friend bool operator>=(const int &bi, const BigDecimal& th);
    friend bool operator>=(const float &bi, const BigDecimal& th);
    friend bool operator>=(const double &bi, const BigDecimal& th);
	
	BigDecimal operator+(const BigDecimal& bi) const;
	BigDecimal operator+(const int& i) const;
	BigDecimal operator+(const float& f) const;
	BigDecimal operator+(const double& d) const;
	friend BigDecimal operator+(const int& i,const BigDecimal& bi);
	friend BigDecimal operator+(const float& f,const BigDecimal& bi);
	friend BigDecimal operator+(const double& d,const BigDecimal& bi);
	
	BigDecimal operator-(const BigDecimal& bi) const;
	BigDecimal operator-(const int& i) const;
	BigDecimal operator-(const float& f) const;
	BigDecimal operator-(const double& d) const;
	friend BigDecimal operator-(const int& i,const BigDecimal& bi);
	friend BigDecimal operator-(const float& f,const BigDecimal& bi);
	friend BigDecimal operator-(const double& d,const BigDecimal& bi);
	
	BigDecimal operator*(const BigDecimal& bi) const;
	BigDecimal operator*(const int& i) const;
	BigDecimal operator*(const float& f) const;
	BigDecimal operator*(const double& d) const;
	friend BigDecimal operator*(const int& i,const BigDecimal& bi);
	friend BigDecimal operator*(const float& f,const BigDecimal& bi);
	friend BigDecimal operator*(const double& d,const BigDecimal& bi);

    BigDecimal operator/(const BigDecimal& bi) const;
    BigDecimal operator/(const int& i) const;
    BigDecimal operator/(const float& f) const;
    BigDecimal operator/(const double& d) const;
    friend BigDecimal operator/(const int &i, const BigDecimal& bi);    
    friend BigDecimal operator/(const float &f, const BigDecimal& bi);
    friend BigDecimal operator/(const double &d, const BigDecimal& bi);
    
    BigDecimal operator^(const BigDecimal& bi) const;

	
	BigDecimal& operator=(const BigDecimal &bi);
	BigDecimal& operator=(const int &i);
	BigDecimal& operator=(const float &f);
	BigDecimal& operator=(const double &d);
	
    BigDecimal& operator++();
    BigDecimal operator++(int);
    
    BigDecimal& operator--();
    BigDecimal operator--(int);

    void print() const;
	string roundoff_1d(string s)const;
	string to_string()const;
	void drop_decimal();
	bool odd()const;
private:
	Node* linkList;
	void clear();
	bool from_string(string str);
	string numerical_part() const ;
	string pure_num()const;
	char sign()const ;
	int dot_index() const;
	BigDecimal& copy(const BigDecimal& bi);
	BigDecimal multi(string a, string b) const;
	string div(BigDecimal a, BigDecimal b, int quota, bool start_using_quota, int max_d,bool combo) const;
	bool greater(string a, string b)const;
	BigDecimal abs()const;
	void remove_dot();
	void append(char data);
	int precision()const{return pure_num().size()-dot_index();}
};

#endif 
