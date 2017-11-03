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
    std::ostringstream ss;
    ss << i;
    std::string str(ss.str());
    if(!from_string(str))from_string("0"); 
}

BigDecimal::BigDecimal(float f){
    linkList=NULL;
    char str[1024];
    sprintf(str,"%f",f);
    if(!from_string(str))from_string("0");
}

BigDecimal::BigDecimal(double f){
    linkList=NULL;
    char str[1024];
    sprintf(str,"%lf",f);
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
    return bi-BigDecimal(i);
}

BigDecimal operator-(const float& f,const BigDecimal& bi){
    return bi-BigDecimal(f);
}

BigDecimal operator-(const double& d,const BigDecimal& bi){
    return bi-BigDecimal(d);
}

BigDecimal BigDecimal::operator*(const BigDecimal& bi)const {
    return multi(*this,bi,true);
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

BigDecimal BigDecimal::multi(BigDecimal th, const BigDecimal& bi, bool root)const{
    string a=th.pure_num(),b=bi.pure_num();
    
    cout<<a<<"*"<<b<<endl;
    
    BigDecimal result;
    if(b.size()==0)return result;
    int index = 1;
//    cout<<"last of b:"<<b[b.size()-1]<<endl;
    for(int i=a.size()-1; i>=0;i--,index*=10){
//        cout<<"index plus:"<<index*(b[b.size()-1]-'0')*(a[i]-'0')<<" | "<<result<<" | ";
        result = result + (index*(b[b.size()-1]-'0')*(a[i]-'0'));
//        cout<<result<<endl;
    }
    BigDecimal delta;
    if(b.size()>1){
        delta = this->multi(th, BigDecimal(b.substr(0,b.size()-1).c_str()),false);
//        cout<<b.size()<<" delta:"<<delta<<endl;
        Node* temp=delta.linkList;
        while(temp->next!=NULL)temp=temp->next;
        temp->next = new Node;
        temp=temp->next;
        temp->data='0';
        temp->next=NULL;
    }
//    cout<<b.size()<<"delta:"<<delta<<endl;
//    cout<<b.size()<<"result:"<<result<<endl;
    result = result+delta;
//    cout<<b.size()<<"result+delta:"<<result<<endl;
    //give back sign and decimal point
    if(th.sign()!=bi.sign())result.linkList->data = '-';
    int length = result.pure_num().size();
//    cout<<"l"<<length<<" a"<<a.size()<<" b"<<b.size()<<" c"<<th.dot_index()<<" d"<<bi.dot_index()<<endl;
    int dot = length-(a.size()+b.size()-th.dot_index()-bi.dot_index());
    if(dot<length&&root){
//        cout<<"Ydecimal point "<<dot<<endl;
        Node* temp = result.linkList;
        while(dot--)temp=temp->next;
//        cout<<temp->data<<endl;         //temp is pointing right before dot
        Node* temp2 = temp->next;
        temp->next = new Node;
        temp = temp->next;
        temp->data='.';
        temp->next = temp2;
    }
//    else cout<<"Ndecimal point "<<dot<<endl;
    return result;
}

BigDecimal BigDecimal::operator/(const BigDecimal &bi) const{
    cout<<"hi"<<endl;
    
    BigDecimal a(abs());
    BigDecimal b(bi.abs());
    a.remove_dot();
    b.remove_dot();
    a.append('0');
    cout<<"before "<<a<<" / "<<b<<endl;
    string s = div(a,b,"");
    cout<<"this string"<<s<<endl;
    
    return BigDecimal(s.c_str());
}

string BigDecimal::div(BigDecimal a, BigDecimal b,string s) const{
//    string sa = a.pure_num(), sb = b.pure_num();
    if(b>a)return s;
    BigDecimal c(b);
    char d='0',e=0;
    cout<<endl<<"DIV1"<<endl<<a<<" > "<<c<<endl;
    while(a>=10*c){
        cout<<endl<<"DIV2"<<endl<<a<<" > "<<c<<endl;
        c=c*10;
        cout<<"********"<<endl;
        e++;
    }
    cout<<endl<<"DIV3"<<endl<<a<<" >= "<<c<<endl;
    while(a>=c){
        a = a - c;
        d++;
    }
    cout<<endl<<"DIV4"<<endl<<a<<" > "<<c<<endl;
    if(a==0){
        cout<<"e"<<e<<endl;
        while(e--)s+="0";
    }
    return s+d+div(a,b,s);
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

//***********
//* Helpers *
//***********

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
        cout<<(temp->data)<<" ";
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
            cout<<s[index]<<" ";
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
