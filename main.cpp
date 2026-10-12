#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    
    Node(int val) : data(val), next(nullptr) {}
};

class CircularLinkedList {
private:
    Node* head;
    int size;
    
public:
    CircularLinkedList(int n) {
        head = nullptr;
        size = 0;
        
        // Create nodes with values 1 to n
        for (int i = n; i >= 1; i--) {
            Node* newNode = new Node(i);
            if (head == nullptr) {
                head = newNode;
                head->next = head; // Point to itself
            } else {
                newNode->next = head->next;
                head->next = newNode;
            }
            size++;
        }
    }
    
    ~CircularLinkedList() {
        if (head == nullptr) return;
        
        Node* current = head;
        Node* nextNode;
        
        // Traverse and delete all nodes
        do {
            nextNode = current->next;
            delete current;
            current = nextNode;
        } while (current != head);
    }
    
    void deleteAtPosition(int m) {
        if (head == nullptr || size == 0) return;
        
        // Find the node before the one to delete
        Node* prev = head;
        for (int i = 1; i < m - 1; i++) {
            prev = prev->next;
        }
        
        // Node to be deleted
        Node* toDelete = prev->next;
        int deletedValue = toDelete->data;
        
        // If deleting the head node
        if (toDelete == head) {
            // Find the last node to update its next pointer
            Node* last = head;
            while (last->next != head) {
                last = last->next;
            }
            head = head->next;
            last->next = head;
        } else {
            prev->next = toDelete->next;
        }
        
        cout << deletedValue << endl;
        delete toDelete;
        size--;
        
        // Update head to the next node after deletion
        if (size > 0) {
            head = prev->next;
        }
    }
    
    bool isEmpty() {
        return size == 0;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    
    CircularLinkedList list(n);
    
    // Delete n-1 nodes
    for (int i = 0; i < n; i++) {
        list.deleteAtPosition(m);
    }
    
    return 0;
}