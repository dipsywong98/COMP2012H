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
        if(m->data==m->next->data){
//            cout<<"deleting "<<m->data<<endl;
            while(m->data==m->next->data){
                Node* n = m->next;
                m->next = n->next;
                delete n;
                if(!m->next)break;
//                print(list);
            }
            h->next = m->next;
            delete m;
//            print(list);
        }
        else h = h->next;
        if(h&&h->next)m = h->next;
//        print(list);
    }
    
    print(list->next);
}
