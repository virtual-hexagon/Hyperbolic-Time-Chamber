#include <iostream>
#include <exception>
#include <string>
#include <random>

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

            Node* temp = new Node{
                .data = value,
                .next = nullptr
            };

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

        void insertion_sort( value_type val ){
            Node* sorted = new Node;
            Node* temp = new Node;
            Node* dummy = new Node;
            Node* s = new Node;

            Node* insert = new Node;
            insert->data = val;

            dummy->next = insert;
            insert->next = head;
            
            // Drain the list from dummy until only dummy remains
            while(dummy->next != nullptr) {
                //save node right after head
                temp = dummy->next;

                //Remove node right after dummy from list
                dummy->next = dummy->next->next;

                // walk through our ordered list
                // assuming dummy head node is smallest node
                // Notes:
                // - We will drain nodes into the ordered list as long
                //   as the next value in the chain is smaller than our current node
                //   because that means they are already ordered smallest to largest
                // - If we detect the next value in the chain is larger than our current node
                //   we break the loop and start the scan again.
                for(s = sorted; s->next != nullptr; s = s->next){

                    if( s->next->data > temp->data ){
                        tail = s->next;
                        break;
                    }

                }
                temp->next = s->next;
                s->next = temp;
            }
            head = sorted->next;
            ++ size;
            delete sorted;
            delete temp;
            delete dummy;
            delete s;
        }

};

int main() {    
    // dont seed with a random "device" lol
    // I have left this approach here for reference.
    // maybe I should move this to an article on rng generators!
    /*
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(1,6); // distribution in range [1, 6]
    */

    // Initialize c+11 style random numbers
    std::mt19937 rng;
    rng.seed(123456789);
    std::uniform_int_distribution<std::mt19937::result_type> dist(1,1000);

    // Initialize our list
    Single_Link_List<int> list;

    std::cout << "Inserting nodes ..." << std::endl;
    for(auto i=0; i<10; ++i){
        list.insert_back(dist(rng));
    }

    std::cout << "The list size is now: " << list.getSize() << std::endl;
    std::cout << "The list data is: " << std::endl;
    list.display();

    auto val = dist(rng);
    std::cout << "Inserting " << val << " and Sorting list ..." << std::endl;
    list.insertion_sort(val);
    std::cout << "The list size is now: " << list.getSize() << std::endl;
    std::cout << "The list data is: " << std::endl;
    list.display();
    
    return 0;
}