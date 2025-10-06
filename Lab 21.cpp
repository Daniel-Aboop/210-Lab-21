// COMSC-210 | Lab 21 | Daniel Santisteban
// IDE used: VS Code

#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;
class Goat{
    private:
    int age;
    string name;
    string color;
    string names[15]={"Billy", "Clover", "Nibbles", "Pepper", "Daisy","Butterscotch", "Gizmo","Maple", "Oreo", "Hazel","Rocky", "Poppy", "Pickles", "Luna", "Moose"};
    string colors[15]={"Crimson", "Azure", "Olive", "Coral", "Indigo","Lavender", "Teal", "Amber", "Mint", "Scarlet","Cyan", "Magenta", "Beige", "Charcoal", "Plum"};
    public:
    Goat(){
        int random1=rand()%20+1;
        int random2=rand()%15;
        int random3=rand()%15;
        age=random1;
        name=names[random2];
        color=colors[random3];
    }
    Goat(int age,string name,string color){
        this->age=age;
        this->name=name;
        this->color=color;
    }
    int getage(){return age;}
    string getname(){return name;}
    string getcolor(){return color;}

};

class DoublyLinkedList {
private:
    struct Node {
        Goat data;
        Node* prev;
        Node* next;
        Node(Goat val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void push_back(Goat value) {
        Node* newNode = new Node(value);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(Goat value) {
        Node* newNode = new Node(value);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insert_after(Goat value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }

    void delete_node(Goat* value) {
        if (!head) return; // Empty list

        Node* temp = head;
        while (temp && &temp->data != value)
            temp = temp->next;

        if (!temp) return; // Value not found

        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }

        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }

        delete temp;
    }

    void print() {
        Node* current = head;
         if(!head){
        cout<<"Empty list.\n";
        return;
        }
        while (current) {
            cout << current->data.getname() << " "<<"( "<<current->data.getcolor()<<", "<<current->data.getage()<<")"<<endl;
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
       
       if (!tail){
        cout<<"Empty list.\n";
        return;
       } 
        while (current) {
            cout << current->data.getname() << " "<<"( "<<current->data.getcolor()<<", "<<current->data.getage()<<")"<<endl;
            current = current->prev;
        }
        cout << endl;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
            head=tail=nullptr;
        }
    }
};

// Driver program
int main() {
    srand(time(0));
    DoublyLinkedList list;
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;

    for (int i = 0; i < size; ++i){
        Goat temp;
        list.push_back(temp);
    }
    cout << "List forward: "<<endl;;
    list.print();

    cout << "List backward: "<<endl;
    list.print_reverse();

    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    cout << "List forward: ";
    list.print();
    cout<<"List backward:";
    list.print_reverse();

    return 0;
}
