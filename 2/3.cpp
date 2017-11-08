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
    
    Node* h = list;
    Node* m = list->next;
    while(m&&m->next){
        Node* n = m->next;
        Node* k = n->next;
        h->next = n;
        n->next = m;
        m->next = k;
//        print(list);
//        while(1);
        if(!m->next)break;
        h = m;
        m = m->next;
    }
    
    print(list->next);
}
