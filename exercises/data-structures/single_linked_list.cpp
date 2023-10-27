#include <iostream>

template<class T>
class Single_Link_List {

    //C++11 create a type alias 
    using value_type = T;
    using pointer_type = T*;
    using size_type = size_t;
    using reference = value_type&;
    typedef std::size_t size_type;
    
    private:
        struct Node {
            value_type data;
            Node* next;
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
            Node* temp = new Node{
                .data = value,
                .next = nullptr
            };
            
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
            Node* temp = new Node{
                .data = value,
                .next = nullptr
            };

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
            // create some working pointers
            // Notes:
            // - Set the current node to the head.
            // - We will insert the new node in front of the "current" node
            // - Create a temporary node that we plan to insert
            Node* pre = new Node;
            Node* cur = new Node;
            cur = head;

            Node* temp = new Node{
                .data = value,
                .next = nullptr
            };

            // Iterate to the desired index in the list
            for(int i = 0; i < index; ++i){
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
            // create some working pointers
            // Notes:
            // - Set the current node to the head.
            // - We will remove the node where its found
            // - Create a temporary node that we plan to use to track pointers. No danglers
            Node* pre = new Node;
            Node* cur = new Node;
            cur = head;

            // Iterate to the desired index in the list
            for(int i = 0; i < index; ++i){
                pre = cur;
                cur = cur->next;
            }
            
            // save the pointer to the object we are going to delete
            // so we can clean it up! Dont leak memory.
            Node* to_delete = cur;

            // update the prior nodes pointer to point
            // to the next node from the current node
            pre->next = cur->next;
            
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

    std::cout << "The list size is: " << list.getSize() << std::endl;
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

    return 0;
}