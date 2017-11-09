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
    cout<<"each node is any numeric charater, other characters implies the end of link list"<<endl;
    cout<<"sample input: 123456789."<<endl;
    cout<<"sample output: 2->1->4->3->6->5->8->7->9->NULL"<<endl;
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
    
    cout<<"result;"<<endl;
    print(list->next);
}
