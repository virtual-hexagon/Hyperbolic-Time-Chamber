#include <iostream>
#include <string>
#include <iomanip>

template<class T>
class Circular_Single_Link_List {

    //C++11 create a type alias to prevent us having to typedef a bunch of stuff
    using value_type = T;
    using pointer_type = T*;
    using size_type = size_t;
    using reference = value_type&;
    typedef std::size_t size_type;
    
    private:
        struct Node {
            value_type data;
            Node* next;

            Node(){
                data = value_type();
                next = nullptr;
            }
        };

        Node* head;
        //Node* tail; // should factor in a tail. it would make some ops more ergonomic
        size_type size;

    public:
        Circular_Single_Link_List():
            head(nullptr),
            size(0)
        { } 

        size_type getSize(){ return size; }
        Node*     getHead(){ return head; }

        Node* getNext(size_t index){ 
            Node* t = head; 
            for(auto i=0; i<index; ++i) { 
                t = t->next; 
            }
            return t->next;
        }

        value_type getData(size_t index){ 
            Node* t = head;
            for(auto i=0; i<index; ++i){
                t = t->next;
            }
            return t->data;
        }
        
        void insert(value_type value){
            // Insert new value after indicated node.
            // Notes:
            // - Create a new node with the value that we plan to insert
            // - If list is empty, then assign value to head and point to ourself
            // - Insert after head and before other values
            Node* cur = new Node;
            cur = head;
            Node* n = new Node;
            n->data = value;       

            if( head == nullptr){
                n->next = n;
                head = n;
            } else {
                while(cur->next != head){
                    cur = cur->next;
                }      
                cur->next = n;
                n->next = head;
            }
            ++size;
        }

        void remove(size_t index){
            // Notes:
            // - Create some pointer to track iteration through the list
            // - Iterate to current index
            // - Set the current node to the head
            // - Create a temporary node that we plan to use to track pointers. No danglers
            Node* to_delete = new Node;
            Node* pre = new Node;
            Node* cur = new Node;
            cur = head;
            
            // Notes:
            // - handle the case where the list only has one element
            //   and the case where we remove the first element aka head
            // - handle case where we are removing the first node
            // - handle all other removals          
            if(cur->next == head && size == 1){
                head->data = T();
                head->next = nullptr;
            }else if(index == 0){
                while(cur->next != head){
                    cur = cur->next;
                }
                to_delete = head;
                head = head->next;
                cur->next = head;
            }else{
                for(auto i = 0; i<index; ++i){
                    pre = cur;
                    cur = cur->next;
                }
                to_delete = cur;
                pre->next = cur->next;
            }
            
            --size;
            delete to_delete;
        }

        void display(){
            Node* temp = head;
            if(temp->next == nullptr){return;}
            while(temp->next != head){
                std::cout << temp->data << ", ";
                temp = temp->next;
            }
            if(temp->next == head){
                std::cout << temp->data << std::endl;
            }
        }
};


int main() {

    Circular_Single_Link_List<int> list;

    std::cout << "The list size is: " << list.getSize() << std::endl;
    std::cout << "Inserting nodes ..." << std::endl;
    for(int i=0; i<5; ++i){
        list.insert(i);
    }
    std::cout << "The list size is now: " << list.getSize() << std::endl;
    std::cout << "The list data is: " << std::endl;
    list.display();

    // lets get the data in the first node
    std::cout << "The data in the first node is: " << list.getData(0) << std::endl;

    // lets get the data in the middle node
    auto pos = list.getSize()/2;
    std::cout << "The data in the node at " << pos <<" is: " << list.getData(pos) << std::endl;

    // lets get the data in the last node
    std::cout << "The data in the last node is: " << list.getData(list.getSize()) << std::endl;

    // lets check that the last node points to the first node
    std::cout << "The head node value is: " << list.getHead()->data
              << " and the last node points to: " << list.getNext(list.getSize()-1)->data
              << std::endl;

    // lets drain the list
    std::cout << std::endl << "Draining nodes ..." << std::endl;
    auto list_size = list.getSize();
    list.display();
    while( list_size > 0 ){
        list.remove(0);
        list_size = list.getSize();
        list.display();
    }
    std::cout << "The list size is now: " << list.getSize() << std::endl;
    std::cout << "The list data is: " << std::endl;
    list.display();
    std::cout << std::endl;

    return 0;
}