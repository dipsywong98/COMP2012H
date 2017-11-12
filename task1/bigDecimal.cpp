#include "bigDecimal.h"

typedef unsigned long long int ull;

//****************
//* Constructors *
//****************
BigDecimal::BigDecimal(){
//    from_string("0");
    linkList = new Node;
    linkList->data = '+';
    linkList->next = new Node;
    linkList->next->data = '0';
    linkList->next->next = NULL;
}

BigDecimal::BigDecimal(const char* str){
    linkList=NULL;
    if(!from_string(str))from_string("0");
}

BigDecimal::BigDecimal(int i){
    linkList=NULL;
    ostringstream ss;
    ss << i;
    std::string str(ss.str());
    if(!from_string(str))from_string("0"); 
}

BigDecimal::BigDecimal(float f){
    linkList=NULL;
    ostringstream ss;
    ss.precision(5);
    ss <<fixed<< f;
    std::string str(ss.str());
    if(!from_string(str))from_string("0"); 
}

BigDecimal::BigDecimal(double f){
    linkList=NULL;
    ostringstream ss;
    ss.precision(5);
    ss <<fixed<< f;
    std::string str(ss.str());
    if(!from_string(str))from_string("0"); 
}

BigDecimal::BigDecimal(const BigDecimal& bi){
    linkList = NULL;
    copy(bi);
}

BigDecimal::~BigDecimal(){
    clear();
}

//****************
//* Methods *
//****************

bool BigDecimal::from_string(const char* str){
    return from_string(string(str));
}

bool BigDecimal::from_string(string str){
    //check if valid string
    if(str[0]=='\0')return false;
    if(str[0]!='+'&&str[0]!='-'&&!(str[0]>='0'&&str[0]<='9'))return false;
    if(str[0]!='+'&&str[0]!='-')str='+'+str;
    //shrink front zero
    int start=1;
    for(;str[start+1]!='\0'&&str[start]=='0'&&str[start+1]!='.';start++);
    
    bool contain_decimal = false;
    int length=1;
    for(int i=1; str[i];i++,length++){
        if(str[i]<'0'&&str[i]>'9'&&str[i]!='.') return false;   //non digit
        if(str[i]=='.'){
            if(!contain_decimal)contain_decimal = true;         //mark contain decimal
            else return false;                                  //more than one decimal
        }
    }
    
    //shrink back zeros
    if(contain_decimal){
        for(int i=length-1;i>=0;i--){
            if(str[i]=='0')length--;
            else if(str[i]=='.'){
                length--;
                break;
            }
            else{
                break;
            }
        }
    }
    
    //remove old data
    clear();        
    
    Node* head = new Node,*temp = head;
    for(int i=start;i<length; i++){
        temp->data = str[i];
        if(i+1<length){
            temp->next = new Node;
            temp = temp->next;
        }
        else{
            break;
        }
    }
    temp->next = NULL;
    linkList = new Node;
    if(head->data=='0'&&head->next==NULL)linkList->data = '+';
    else linkList->data = str[0];
    linkList->next = head;
    return true;
}

void BigDecimal::to_string(char* str){
    Node* temp = linkList;
    int i=0;
    while(temp){
        if(!(i==0&&temp->data=='+'))str[i++]=temp->data;
        temp = temp->next;
    }
    str[i]='\0';
}

//****************
//* IO Operators *
//****************

ostream& operator<<(ostream& o, const BigDecimal& f){
    f.print();
    return o;
}

istream& operator>>(istream& i, BigDecimal bi){
    string s;
    i>>s;
    bi.from_string(s);
    return i;
}

//********************
//* Compare operator *
//********************
bool BigDecimal::operator==(const BigDecimal &bi)const{
    Node* temp1 = linkList, *temp2 = bi.linkList;
    while(temp1&&temp2){
        if(temp1->data!=temp2->data)return false;
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    if(temp1==temp2)return true;
    return false;
}

bool BigDecimal::operator==(const int &bi)const{
    return *this==BigDecimal(bi);
}

bool BigDecimal::operator==(const float &bi)const{
    return *this==BigDecimal(bi);
}

bool BigDecimal::operator==(const double &bi)const{
    return *this==BigDecimal(bi);
}

bool BigDecimal::operator!=(const BigDecimal &bi)const{
    return !(*this==bi);
}

bool BigDecimal::operator!=(const int &bi)const{
    return !(*this==bi);
}

bool BigDecimal::operator!=(const float &bi)const{
    return !(*this==bi);
}

bool BigDecimal::operator!=(const double &bi)const{
    return !(*this==bi);
}

bool BigDecimal::operator>(const BigDecimal &bi)const{
    if(sign()=='+'&&bi.sign()=='-')return true;
    if(sign()=='-'&&bi.sign()=='+')return false;
    if(sign()=='+'){
        if(dot_index()>bi.dot_index())return true;
        if(dot_index()<bi.dot_index())return false;
        Node* temp1 = linkList->next,*temp2=bi.linkList->next;
        while(temp1&&temp2){
            if(temp1->data > temp2->data)return true;
            if(temp1->data < temp2->data)return false;
            temp1=temp1->next,temp2=temp2->next;
        }
        if(temp1!=temp2)return !!temp1;
        return false;
    }
    if(sign()=='-'){
        if(dot_index()>bi.dot_index())return !true;
        if(dot_index()<bi.dot_index())return !false;
        Node* temp1 = linkList->next,*temp2=bi.linkList->next;
        while(temp1&&temp2){
            if(temp1->data > temp2->data)return !true;
            if(temp1->data < temp2->data)return !false;
            temp1=temp1->next,temp2=temp2->next;
        }
        if(temp1!=temp2)return !temp1;
        return false;
    }
}

bool BigDecimal::operator>(const int &bi)const{
    return *this>BigDecimal(bi);
}

bool BigDecimal::operator>(const float &bi)const{
    return *this>BigDecimal(bi);
}

bool BigDecimal::operator>(const double &bi)const{
    return *this>BigDecimal(bi);
}

bool BigDecimal::operator<(const BigDecimal &bi)const{
    return bi>*this;
}

bool BigDecimal::operator<(const int &bi)const{
    return BigDecimal(bi)>*this;
}

bool BigDecimal::operator<(const float &bi)const{
    return BigDecimal(bi)>*this;
}

bool BigDecimal::operator<(const double &bi)const{
    return BigDecimal(bi)>*this;
}

bool BigDecimal::operator<=(const BigDecimal &bi)const{
    return !(*this>bi);
}

bool BigDecimal::operator<=(const int &bi)const{
    return !(*this>BigDecimal(bi));
}

bool BigDecimal::operator<=(const float &bi)const{
    return !(*this>BigDecimal(bi));
}

bool BigDecimal::operator<=(const double &bi)const{
    return !(*this>BigDecimal(bi));
}

bool BigDecimal::operator>=(const BigDecimal &bi)const{
    return !(*this<bi);
}

bool BigDecimal::operator>=(const int &bi)const{
    return !(*this<BigDecimal(bi));
}

bool BigDecimal::operator>=(const float &bi)const{
    return !(*this<BigDecimal(bi));
}

bool BigDecimal::operator>=(const double &bi)const{
    return !(*this<BigDecimal(bi));
}

bool operator==(const int &bi, const BigDecimal& th){
    return th==bi;
}

bool operator==(const float &bi, const BigDecimal& th){
    return th==bi;
}

bool operator==(const double &bi, const BigDecimal& th){
    return th==bi;
}

bool operator!=(const int &bi, const BigDecimal& th){
    return th!=bi;
}

bool operator!=(const float &bi, const BigDecimal& th){
    return th!=bi;
}

bool operator!=(const double &bi, const BigDecimal& th){
    return th!=bi;
}

bool operator>(const int &bi, const BigDecimal& th){
    return th<bi;
}

bool operator>(const float &bi, const BigDecimal& th){
    return th<bi;
}

bool operator>(const double &bi, const BigDecimal& th){
    return th<bi;
}

bool operator<(const int &bi, const BigDecimal& th){
    return th>bi;
}

bool operator<(const float &bi, const BigDecimal& th){
    return th>bi;
}

bool operator<(const double &bi, const BigDecimal& th){
    return th>bi;
}

bool operator<=(const int &bi, const BigDecimal& th){
    return th>=bi;
}

bool operator<=(const float &bi, const BigDecimal& th){
    return th>=bi;
}

bool operator<=(const double &bi, const BigDecimal& th){
    return th>=bi;
}

bool operator>=(const int &bi, const BigDecimal& th){
    return th<=bi;
}

bool operator>=(const float &bi, const BigDecimal& th){
    return th<=bi;
}

bool operator>=(const double &bi, const BigDecimal& th){
    return th<=bi;
}
//****************
//* Arithemetics *
//****************

BigDecimal BigDecimal::operator+(const BigDecimal& bi) const {
    string a, b;
    int c,d;
    char sa,sb;
    
    //find bigger absolute value
    if(abs()>bi.abs()){
        a=pure_num(),b=bi.pure_num(),c=dot_index(),d=bi.dot_index(),sa=sign(),sb=bi.sign();
    }
    else{
        b=pure_num(),a=bi.pure_num(),d=dot_index(),c=bi.dot_index(),sb=sign(),sa=bi.sign();
    }
//    cout<<a<<" + "<<b<<endl;
    
    //back zeros
    int append = b.size()-d-a.size()+c;
    if(append>0){
        for(int i=0;i<append;i++)a+="0";
    }
    else if(append<0){
        for(int i=0;i<-append;i++)b+="0";
    }
    
    //front zeros
    append=d-c;
    if(append>0){
        for(int i=0;i<append;i++)a="0"+a;
    }
    else if(append<0){
        for(int i=0;i<-append;i++)b="0"+b;
    }
    
    //combine
    string s="";
//    if(a.size()!=b.size())cout<<"warning: bug occurs, two lengths not same not allign: "<<a<<" "<<b<<endl;
//    else cout<<"processed: "<<a<<" "<<b<<endl;
    int increment=0;
    
    int ca=1,cb=1;
//    cout<<sa<<sb<<endl;
    if(sa!=sb){
        ca=1;cb=-1;
    }
    for(int i=a.size()-1;i>=0;i--){
        if(i+1<a.size()&&i+1==c){
//            cout<<"dot at "<<c<<endl;
            s='.'+s;
        }
        int temp = ca*(a[i]-'0')+cb*(b[i]-'0')+increment;
//        cout<<sa<<a[i]<<"+"<<sb<<b[i]<<"+"<<increment<<"="<<temp<<" ";
        if(temp>=10){
            s=char(temp%10+'0')+s;
            increment=1;
        }
        else if(temp>=0){
            s=char(temp+'0')+s;
            increment=0;
        }
        else{
            s=char(10+temp+'0')+s;
            increment=-1;
        }
        
    }
    if(increment==1)s='1'+s;
//    if(s[0]=='0')s=s.substr(1,s.size()-1);
    s=sa+s;

//    cout<<endl<<sa<<a<<" + "<<sb<<b<<"="<<s<<endl;
    
    return BigDecimal(s.c_str());
}

BigDecimal BigDecimal::operator+(const int& i) const {
    return *this+BigDecimal(i);
}

BigDecimal BigDecimal::operator+(const float& f) const {
    return *this+BigDecimal(f);
}

BigDecimal BigDecimal::operator+(const double& d) const {
    return *this+BigDecimal(d);
}

BigDecimal operator+(const int& i,const BigDecimal& bi){
    return bi+BigDecimal(i);
}

BigDecimal operator+(const float& f,const BigDecimal& bi){
    return bi+BigDecimal(f);
}

BigDecimal operator+(const double& d,const BigDecimal& bi){
    return bi+BigDecimal(d);
}

BigDecimal BigDecimal::operator-(const BigDecimal& bi) const {
    return *this+BigDecimal(((bi.sign()=='+'?'-':'+')+bi.numerical_part()).c_str());
}

BigDecimal BigDecimal::operator-(const int& i) const {
    return *this-BigDecimal(i);
}

BigDecimal BigDecimal::operator-(const float& f) const {
    return *this-BigDecimal(f);
}

BigDecimal BigDecimal::operator-(const double& d) const {
    return *this-BigDecimal(d);
}

BigDecimal operator-(const int& i,const BigDecimal& bi){
    BigDecimal b(bi);
    b.linkList->data = (bi.sign()=='+'?'-':'+');
    return b+BigDecimal(i);
}

BigDecimal operator-(const float& f,const BigDecimal& bi){
    BigDecimal b(bi);
    b.linkList->data = (bi.sign()=='+'?'-':'+');
    return b+BigDecimal(f);
}

BigDecimal operator-(const double& d,const BigDecimal& bi){
    BigDecimal b(bi);
    b.linkList->data = (bi.sign()=='+'?'-':'+');
    return b+BigDecimal(d);
}

BigDecimal BigDecimal::operator*(const BigDecimal& bi)const {
    string result = multi(this->pure_num(),bi.pure_num()).pure_num();
    int dot_pos=result.size()-precision()-bi.precision();
    if(dot_pos<=0){
        while(dot_pos<0){
            result="0"+result;
            dot_pos++;
        }
        result="0."+result;
    }
    else if(dot_pos<result.size()){
        result.insert(dot_pos,".");
    }
    result = (sign()==bi.sign()?'+':'-')+result;
    return BigDecimal(result.c_str());
}

BigDecimal BigDecimal::operator*(const int& i) const{
    return (*this)*BigDecimal(i);
}

BigDecimal BigDecimal::operator*(const float& i) const{
    return (*this)*BigDecimal(i);
}

BigDecimal BigDecimal::operator*(const double& i) const{
    return (*this)*BigDecimal(i);
}

BigDecimal operator*(const int& i, const BigDecimal& bi){
    return bi*BigDecimal(i);
}

BigDecimal operator*(const float& i, const BigDecimal& bi){
    return bi*BigDecimal(i);
}

BigDecimal operator*(const double& i, const BigDecimal& bi){
    return bi*BigDecimal(i);
}

BigDecimal BigDecimal::multi(string a, string b)const{
    if(a=="10"){
        BigDecimal result(b.c_str());
        result.append('0');
        return result;
    }
    if(b=="10"){
        BigDecimal result(a.c_str());
        result.append('0');
        return result;
    }
    if(b.size()==1){
        BigDecimal result;
        for(int i=0; i<a.size(); i++){
            result=result*10;
            result=result+(a[i]-'0')*(b[0]-'0');
        }
        return result;
    }
    BigDecimal x=multi(a,b.substr(b.size()-1,1)),y=multi(a,b.substr(0,b.size()-1));
//    cout<<x<<"+"<<y<<"*10"<<endl;
    return x+y*10;
}

BigDecimal BigDecimal::operator/(const BigDecimal &bi) const{
//    cout<<"hi"<<endl;
    if(bi==0){
        cout<<"division by zero"<<endl;
        return BigDecimal("0");
    }
    BigDecimal a(abs());
    BigDecimal b(bi.abs());
    int quota = max(a.precision(),b.precision())+1;
    
    for(int i=0; i<quota; i++){
        a=a*10;
    }
    
//    cout<<"quota "<<quota<<endl;
        
    BigDecimal result = div(a,b);
    result.linkList->data = (sign()==bi.sign()?'+':'-');
    result.set_precision(quota-1,true);
    
    return result;
}

BigDecimal BigDecimal::operator/(const int &i) const{
    return (*this)/BigDecimal(i);
}

BigDecimal BigDecimal::operator/(const float &f) const{
    return (*this)/BigDecimal(f);
}

BigDecimal BigDecimal::operator/(const double &d) const{
    return (*this)/BigDecimal(d);
}

BigDecimal operator/(const int &i,const BigDecimal &bi){
    return BigDecimal(i)/bi;
}

BigDecimal operator/(const float &f,const BigDecimal &bi){
    return BigDecimal(f)/bi;
}

BigDecimal operator/(const double &d,const BigDecimal &bi){
    return BigDecimal(d)/bi;
}

BigDecimal BigDecimal::div(BigDecimal a, BigDecimal b) const{
    if(a<b)return 0;
    BigDecimal pre = div(a,b*10);
//    cout<<"a/b*10 = "<<a<<" / "<<b<<"*10"<<" = "<<pre<<endl;
    pre=pre*10;
    a = a-b*pre;
    int d=0;
    for(;a>=b;d++){
        a=a-b;
    }
    return d+pre;
}

BigDecimal BigDecimal::operator^(const BigDecimal& bi)const{
    if(*this==0){
        if(bi>0)return 0;
        if(bi==0)return 1;
        if(bi<0){
            cout<<"division by zero"<<endl;
            return 0;
        }
    }
    if(bi<0){
        BigDecimal reciprocal = (*this)^(bi.abs());
        int quota = max(bi.precision(),this->precision())+1;
        BigDecimal a(1);
        for(int i=0; i<quota; i++){
            a=a*10;
        }
        BigDecimal result = div(a,reciprocal.abs());
        result.set_precision(quota-1,true);
        return result;
    }
    if(bi==0)return BigDecimal(1);
    if(bi==1)return *this;
    if(bi==2)return (*this)*(*this);
    BigDecimal b(bi);
    b.drop_decimal();
    string bits;
    while(b!=0){
//        cout<<b<<endl;
        if(b.odd()){
            bits=bits+"1";
            b=(b-1)/2;
        }
        else{
            bits=bits+"0";
            b=b/2;
        } 
        
    }
//    cout<<"bits"<<bits<<endl;
    BigDecimal result(1), temp=*this;
    for(int i=0; i<bits.size();i++){
        if(bits[i]=='1')result=result*temp;
        temp=temp*temp;
    }
    return result;
}

//**************
//* Assignment *
//**************

BigDecimal& BigDecimal::operator=(const BigDecimal &bi){
    copy(bi);
    return *this;
}

BigDecimal& BigDecimal::operator=(const int &i){
    copy(BigDecimal(i));
    return *this;
}

BigDecimal& BigDecimal::operator=(const float &f){
    copy(BigDecimal(f));
    return *this;
}

BigDecimal& BigDecimal::operator=(const double &d){
    copy(BigDecimal(d));
    return *this;
}

BigDecimal& BigDecimal::operator++(){
    *this = *this + 1;
    return *this;
}
BigDecimal BigDecimal::operator++(int){
    BigDecimal temp = *this;
    ++(*this);
    return temp;
}

BigDecimal& BigDecimal::operator--(){
    *this = *this-1;
    return *this;
}
BigDecimal BigDecimal::operator--(int){
    BigDecimal temp = *this;
    --(*this);
    return temp;
}

//***********
//* Helpers *
//***********

string BigDecimal::to_string() const {
    Node* temp = linkList;
    string str="";
    int i=0;
    while(temp){
        str+=temp->data;
        temp = temp->next;
        i++;
    }
    return str;
}

string BigDecimal::numerical_part() const {
    Node* temp = linkList;
    string str="";
    int i=0;
    while(temp){
        if(!(temp->data=='-'||temp->data=='+'))str+=temp->data;
        temp = temp->next;
        i++;
    }
    return str;
}

string BigDecimal::pure_num()const{
    Node* temp = linkList;
    string str="";
    int i=0;
    while(temp){
        if(!(temp->data=='-'||temp->data=='+'||temp->data=='.'))str+=temp->data;
        temp = temp->next;
        i++;
    }
    return str;
}

char BigDecimal::sign() const {
    return (linkList->data=='-'?'-':'+');
}

void BigDecimal::clear(){
    Node* temp2 = NULL;
    while(linkList!=NULL){
        if(linkList->next==linkList->next)temp2 = linkList->next;
        delete linkList;
        if(linkList->next==linkList->next)linkList = temp2;
    }
}

int BigDecimal::dot_index() const{
    Node* temp = linkList;
    int i=0;
    for(;temp;i++){
        if(temp->data=='.')return i-1;
        temp = temp->next;
    }
    return i-1;
}

void BigDecimal::print() const{
    Node* temp = linkList;
    while(temp){
        cout<<(temp->data);
        temp = temp->next;
    }
}

BigDecimal& BigDecimal::copy(const BigDecimal& bi){
    clear();
    linkList = new Node;
    Node* temp = linkList,*from = bi.linkList;
    while(from){
        temp->data = from->data;
        if(from->next){
            from = from->next;
            temp->next = new Node;
            temp = temp->next;
        }
        else{
            temp->next = NULL;
            break;
        }
    }
    return *this;   
}

bool BigDecimal::greater(string a, string b)const{
    if(a.size()>b.size())return true;
    if(a.size()<b.size())return false;
    for(int i=0;i<a.size();i++){
        if(a[i]>b[i])return true;
        if(a[i]<b[i])return false;
    }
    return false;
}

BigDecimal BigDecimal::abs()const{
    BigDecimal a(*this);
    a.linkList->data = '+';
    return a;
}

void BigDecimal::remove_dot(){
    Node* temp = linkList->next, *prev=linkList;
    while(temp){
        if(temp->data=='.'){
            prev->next = temp->next;
            delete temp;
            temp = prev->next;
            continue;
        }
        if(!temp->next)break;
        prev = prev->next;
        temp = temp->next;
    }
    
}

void BigDecimal::append(char data){
    Node* temp = linkList->next;
    while(temp){
        if(!temp->next)break;
        temp = temp->next;
    }
    temp->next = new Node;
    temp = temp->next;
    temp->data = data;
    temp->next = NULL;
}

string BigDecimal::roundoff_1d(string s)const{
    int index = s.size()-1;
    if(s[index]>='5'){
        int increment = 1;
        while(--index>=0&&increment){
//            cout<<s[index]<<" ";
            s[index]+=1;
            if(s[index]>'9'){
                s[index]='0';
                increment=1;
            }else {
                increment=0;
                break;
            }
        }
        if(increment)s='1'+s;
    }
    return s.substr(0,s.size()-1);
}

//remove all digit after dot
void BigDecimal::drop_decimal(){
    Node* temp = linkList->next;
    while(temp->next){
        if(temp->next->data=='.')goto drop;
        temp=temp->next;
    }
    return;
drop:
    Node* temp3 = temp;
    temp=temp->next;
    while(temp){
        Node* temp2=temp->next;
        delete temp;
        temp = temp2;
    }
    temp3->next=NULL;
    return;
}

bool BigDecimal::odd ()const{
    Node* temp=linkList->next;
    while(temp->next){
        if(temp->next->data=='.')break;
        temp=temp->next;
    }
    return (temp->data-'0')%2;
}

void BigDecimal::set_precision(int precision,bool roundoff_1d_flag){
    string s = pure_num();
    if(roundoff_1d_flag) s=roundoff_1d(s);
    if(precision>s.size()){
        while(precision>s.size()){
            s="0"+s;
        }
        s="0."+s;
    }
    else{
        s.insert(s.size()-precision,".");
        if(s[0]=='.')s="0"+s;
    }
    s=sign()+s;
    from_string(s.c_str());
}
