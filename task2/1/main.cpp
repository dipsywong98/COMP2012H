#include <iostream>
using namespace std;

typedef struct Node{
    char data;
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
    cout<<"each node is any numeric charater, other characters implies the end of link list"<<endl;
    cout<<"sample input: 123456789. 1 9"<<endl;
    cout<<"sample output: 9->8->7->6->5->4->3->2->1->NULL"<<endl;
    while(cin>>in){
        if(in>='0'&&in<='9'){
            temp->next = new Node;
            temp = temp->next;
            temp->data = in;
        }
        else{
            temp->next = NULL;
            break;
        }
    }
    
//    print(list);
    cout<<"m:\n";
    cin>>m;
    cout<<"n:\n";
    cin>>n;
    
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
    cout<<"result:"<<endl;
    print(list->next);
    
    temp = list;
    while(temp){
        Node* t = temp->next;
        delete temp;
        temp=t;
    }
}
