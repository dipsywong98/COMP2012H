#include "bigDecimal.h"

typedef unsigned long long int ull;

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
    char str[1024];
    sprintf(str,"%d",i);
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
}

BigDecimal::~BigDecimal(){
    clear();
}

void BigDecimal::clear(){
    Node* temp2 = NULL;
    while(linkList!=NULL){
        if(linkList->next==linkList->next)temp2 = linkList->next;
        delete linkList;
        if(linkList->next==linkList->next)linkList = temp2;
    }
}

bool BigDecimal::from_string(const char* str){
    //check if valid string
    if(str[0]=='\0')return false;
    if(str[0]!='+'&&str[0]!='-'&&!(str[0]>='0'&&str[0]<='9'))return false;
    bool contain_decimal = false;
    int length=1;
    for(int i=1; str[i];i++,length++){
        if(str[i]<'0'&&str[i]>'9'&&str[i]!='.') return false;
        if(str[i]=='.')contain_decimal = true;
    }
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
    for(int i=0;i<length; i++){
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
    if(str[0]!='+'&&str[0]!='-'){
        linkList = new Node;
        linkList->data = '+';
        linkList->next = head;
    }
    else{
        linkList = head;
    }
    return true;
}

bool BigDecimal::from_string(string str){
    if(!str[0])return false;
    if(str[0]!='+'&&str[0]!='-'&&str[0]<'0'&&str[0]>'9')return false;
    for(int i=1; str[i];i++)if(str[i]<'0'&&str[i]>'9'&&str[i]!='.') return false;
    clear();
    Node* head = new Node,*temp = head;
    for(int i=0;; i++){
        temp->data = str[i];
        if(str[i+1]){
            temp->next = new Node;
            temp = temp->next;
        }
        else{
            temp->next = NULL;
            break;
        }
    }
    if(str[0]!='+'&&str[0]!='-'){
        linkList = new Node;
        linkList->data = '+';
        linkList->next = head;
    }
    else{
        linkList = head;
    }
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

BigDecimal BigDecimal::operator+(const BigDecimal& bi) const {
    string a, b;
    int c,d;
    char sa,sb;
    bool this_larger=false;
    if(dot_index()>bi.dot_index()){
        this_larger=true;
    }
    else if(dot_index()==bi.dot_index()&&linkList->next->data > bi.linkList->next->data){
        this_larger=true;
    }
    if(this_larger){
        a=pure_num(),b=bi.pure_num(),c=dot_index(),d=bi.dot_index(),sa=sign(),sb=bi.sign();
    }
    else{
        b=pure_num(),a=bi.pure_num(),d=dot_index(),c=bi.dot_index(),sb=sign(),sa=bi.sign();
    }
    cout<<a<<" + "<<b<<endl;
    
    //back zeros
    int append = b.size()-d-a.size()+c;
    if(append>0){
        for(int i=0;i<append;i++)a+="0";
    }
    else if(append<0){
        for(int i=0;i<-append;i++)b+="0";
    }
    
    //fore zeros
    append=d-c;
    if(append>0){
        for(int i=0;i<append;i++)a="0"+a;
    }
    else if(append<0){
        for(int i=0;i<-append;i++)b="0"+b;
    }
    
    //combine
    string s="";
    if(a.size()!=b.size())cout<<"warning: bug occurs, two lengths not same not allign: "<<a<<" "<<b<<endl;
    else cout<<"processed: "<<a<<" "<<b<<endl;
    int increment=0;
    
    int ca=1,cb=1;
    cout<<sa<<sb<<endl;
    if(sa!=sb){
        ca=1;cb=-1;
    }
    for(int i=a.size()-1;i>=0;i--){
        if(i+1==c){
            cout<<"dot at "<<c<<endl;
            s='.'+s;
        }
        int temp = ca*(a[i]-'0')+cb*(b[i]-'0')+increment;
        cout<<sa<<a[i]<<"+"<<sb<<b[i]<<"+"<<increment<<"="<<temp<<" ";
        if(temp>=10){
            s=char(temp%10+'0')+s;
            increment=1;
        }
        if(temp>=0){
            s=char(temp+'0')+s;
            increment=0;
        }
        else{
            s=char(10+temp+'0')+s;
            increment=-1;
        }
        
    }
    s=sa+s;
    
    
    cout<<endl<<sa<<a<<" + "<<sb<<b<<"="<<s<<endl;
    return *this;
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

void BigDecimal::print(){
    Node* temp = linkList;
    while(temp){
        cout<<temp->data<<" ";
        temp = temp->next;
    }
    cout<<endl;
}
