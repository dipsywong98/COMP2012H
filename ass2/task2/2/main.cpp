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
    cout<<"sample output: 1->2->3->4->5->6->7->8->9->NULL"<<endl;
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
    
    cout<<"result:"<<endl;
    print(list->next);
    
    temp = list;
    while(temp){
        Node* t = temp->next;
        delete temp;
        temp=t;
    }
}
