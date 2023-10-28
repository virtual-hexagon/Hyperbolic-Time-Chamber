#include <iostream>
#include <exception>
#include <string>

template<class T>
class Single_Link_List {

    //C++11 create a type alias to prevent us having to typedef a bunch of stuff
    using value_type = T;
    using pointer_type = T*;
    using size_type = size_t;
    using reference = value_type&;
    
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
        Node* tail;
        size_type size;

    public:
        Single_Link_List():
            head(nullptr),
            tail(nullptr),
            size(0)
        { } 

        size_type getSize(){ return size; }

        void insert_back(value_type value){
            Node* temp = new Node();
            temp->data = value;
            
            if(head == nullptr){
                head = temp;
                tail = temp;
            } else {
                tail->next = temp;
                tail = temp;
            }

            ++size;
        }

        void insert_front(value_type value){
            Node* temp = new Node;
            temp->data = value;

            if(head == nullptr){
                head = temp;
                tail = temp;
            } else {
                temp->next = head;
                head = temp;
            }
            ++size;
        }

        void insert(size_t index , value_type value){
            // Notes:
            // - Check if we are trying to insert the node out of bounds
            // - Create pointers to track prior and current node as we iterate through list
            // - Create a temporary node to insert at the desired index.
            // - We will insert the new node in front of the "current" node
            // - Create a temporary node that we plan to insert
            if(index > size){
                std::string msg = "Trying to insert at index beyond the end of the list. List Size: "
                    + std::to_string(size)
                    + " Index: "
                    + std::to_string(index);
                throw std::range_error(msg);
            }

            Node* pre = new Node;
            Node* cur = new Node;
            cur = head;

            Node* temp = new Node;
            temp->data = value;

            // Iterate to the desired index in the list
            for(size_t i = 0; i < index; ++i){
                pre = cur;
                cur = cur->next;
            }
            
            // link our new node to same location as the pre node points to
            // link the prior node to our new node
            temp->next = pre->next;
            pre->next  = temp;
        
            ++size;
        }

        void remove(size_t index){
            // Notes:
            // - Create some working pointers to track iterations through the list
            // - Set the current working node to the head.
            // - We will remove the node where its found in the list
            Node* pre = new Node;
            Node* cur = new Node;
            cur = head;

            // save the pointer to the object we are going to delete
            // so we can clean it up! Dont leak memory.
            Node* to_delete = new Node;
            
            // Notes:
            // - Bounds check and make sure we are not trying to remove beyond the size of the list.
            // - Check if the head and tail point to the same element. That means we are removing our last element.
            // - Check if we are removing from the front and the next pointer isn't null and handle that edge case.
            // - Otherwise iterate through list. Track the prior node and current node so we can link "over" the 
            //   node we want to remove.
            if( index > size){
                std::string msg = "Trying to remove index beyond the end of the list. List Size: "
                    + std::to_string(size)
                    + " Index: "
                    + std::to_string(index);
                throw std::range_error(msg);
            }else if(head == tail){
                head->data = T();
                head->next = nullptr;
            }else if(index == 0){
                to_delete = head;
                head = head->next;
            }
            else{
                for(int i = 0; i < index; ++i){
                    pre = cur;
                    cur = cur->next;
                }
                pre->next = cur->next;
            }   
            --size;
            delete to_delete;
        }
    
        void display(){
            Node* temp = new Node;
            temp = head;
            while(temp != nullptr){

                // handle pretty printing. no trailing comma!
                if(temp->next == nullptr){
                    std::cout << temp->data << std::endl;
                } else {
                    std::cout << temp->data << ", ";
                }

                // advance to next node
                temp = temp->next;
            }
            
            delete temp;
        }
};


int main() {

    Single_Link_List<int> list;

    // print initial size of list. Should be empty aka 0
    std::cout << "The list size is: " << list.getSize() << std::endl;

    // insert nodes into the back of the list
    std::cout << "Inserting nodes ..." << std::endl;
    for(int i=0; i<10; ++i){
        list.insert_back(i);
    }
    std::cout << "The list size is now: " << list.getSize() << std::endl;
    std::cout << "The list data is: " << std::endl;
    list.display();

    // lets insert something at the beginning of the list
    std::cout << std::endl <<"Inserting data at front of list ..." << std::endl;
    list.insert_front(99);
    std::cout << "The list size is now: " << list.getSize() << std::endl;
    std::cout << "The list data is: " << std::endl;
    list.display();

    // lets insert something in the middle of the list.
    auto pos = list.getSize()/2;
    std::cout << std::endl <<"Inserting data at position "<< pos <<" ..." << std::endl;
    list.insert( pos, 55 );
    std::cout << "The list size is now: " << list.getSize() << std::endl;
    std::cout << "The list data is: " << std::endl;
    list.display();

    // lets insert something beyond the end of the list
    std::cout << std::endl << "Try to insert at index beyond the end of the list ..." << std::endl;
    pos = list.getSize()+2;
    try{
        list.insert(pos,666);
    } catch ( const std::range_error& e ) {
        std::cout << "Caught the Range Error!" << std::endl;
        std::cout << e.what() << std::endl;
        std::cout << "Continuing ..." << std::endl;
    };

    std::cout << std::endl << "Remove node 2nd to last node ..." << std::endl;
    pos = list.getSize()-2;
    list.remove(pos);
    std::cout << "The list size is now: " << list.getSize() << std::endl;
    std::cout << "The list data is: " << std::endl;
    list.display();

    std::cout << std::endl << "Try to remove index beyond the end of the list ..." << std::endl;
    pos = list.getSize()+2;
    try{
        list.remove(pos);
    } catch ( const std::range_error& e ) {
        std::cout << "Caught the Range Error!" << std::endl;
        std::cout << e.what() << std::endl;
        std::cout << "Continuing ..." << std::endl;
    };
    
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

    return 0;
}