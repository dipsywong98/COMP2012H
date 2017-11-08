#include <iostream>
using namespace std;

typedef struct Node{
    int data;
    Node* next;
}Node;

void print(Node* temp){
    if(!temp)cout<<"NULL"<<endl;
    else {
        cout<<temp->data<<"->";
        print(temp->next);
    }
}

int main(){
    char in;
    Node* list = new Node;
    Node* temp = list;
    int m,n;
    while(cin>>in){
        if(in>='0'&&in<='9'){
            temp->next = new Node;
            temp = temp->next;
            temp->data = in-'0';
        }
        else{
            temp->next = NULL;
            break;
        }
    }
    
//    print(list);
    cin>>m>>n;
    
    temp = list->next;
    Node* p = list;
    Node* M=NULL;
    for(int i=1; temp; i++){
        if(i==m)M=p;
        else if(i>m&&i<=n){
            p->next = temp->next;
            temp->next = M->next;
            M->next = temp;
            temp = p->next;
            continue;
        }
        p=p->next;
        temp=temp->next;
    }
    
    print(list->next);
}
