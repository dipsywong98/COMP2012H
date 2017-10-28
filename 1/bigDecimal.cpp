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

char BigDecimal::sign() const {
    return (linkList->data=='-'?'-':'+');
}

BigDecimal BigDecimal::operator+(const BigDecimal& bi) const {
    string a = numerical_part(), b = bi.numerical_part();
    int c=dot_index(a),d=dot_index(b);
    cout<<a<<" + "<<b<<endl;
    int append = b.size()-d-a.size()+c;
    if(append>0){
        a+=".";
        for(int i=0;i<append-1;i++)a+="0";
    }
    else if(append<0){
        b+=".";
        for(int i=0;i<-append+1;i++)b+="0";
    }
    append=d-c;
    if(append>0){
        for(int i=0;i<append;i++)a="0"+a;
    }
    else if(append<0){
        for(int i=0;i<-append;i++)b="0"+b;
    }
    string s="";
    if(a.size()!=b.size())cout<<"warning: bug occurs, two lengths not same not allign: "<<a<<" "<<b<<endl;
    int increment=0;
    if(sign()==bi.sign()){
        for(int i=a.size()-1;i>=0;i--){
            if(a[i]=='.'){
                s='.'+s;
            }
            else{
                int temp = a[i]+b[i]+increment-2*'0';
                cout<<a[i]<<"+"<<b[i]<<"+"<<increment<<"="<<temp<<" ";
                s=char(temp%10+'0')+s;
                increment=temp/10;
            }
        }
        if(increment>0) s=char(increment+'0')+s;
        s=sign()+s;
    }
    else{
        int ca=1,cb=-1;
        if(sign()=='-'){
            ca=-1;cb=1;
        }
        for(int i=a.size()-1;i>=0;i--){
            if(a[i]=='.'){
                s='.'+s;
            }
            else{
                int temp = ca*(a[i]-'0')-cb*(b[i]-'0')+increment;
                cout<<sign()<<a[i]<<"+"<<bi.sign()<<b[i]<<"+"<<increment<<"="<<temp<<" ";
                if(temp>=0){
                    s=char(temp+'0')+s;
                    increment=0;
                }
                else{
                    s=char(-temp+'0')+s;
                    increment=-1;
                }
            }
        }
        s=(increment==-1?'-':'+')+s;
    }
    
    cout<<endl<<a<<" + "<<b<<"="<<s<<endl;
    return *this;
}

int BigDecimal::dot_index(const string& str) const{
    for(int i=0; i<str.size();i++)if(str[i]=='.')return i;
    return str.length();
}

void BigDecimal::print(){
    Node* temp = linkList;
    while(temp){
        cout<<temp->data<<" ";
        temp = temp->next;
    }
    cout<<endl;
}
