#pragma once

class LinkedList {
public:
    struct Successor {
        int vertex;
        int weight;

        Successor(int v, int w) {
            vertex = v;
            weight = w;
        }
    };

    struct Node {
        Successor data;
        Node* next;

        Node(Successor e) : data(e), next(nullptr) {}
    };

    void append(int successorVertex, int weight) {
        Node* node = new Node(Successor(successorVertex, weight));
        if (head == nullptr) {
            head = node;
        } else {
            Node* current = head;
            while (current -> next != nullptr) {
                current = current -> next;
            }
            current -> next = node;
        }
    }

    ~LinkedList() {
        while (head) {
            Node* tmp = head;
            head = head -> next;
            delete tmp;
        }
    }

    bool contains(int end) {
        Node* current = head;

        while (current != nullptr) {
            if (current -> data.vertex == end) {
                return true;
            }
            current = current -> next;
        }
        return false;
    }

    void printList() {
        Node* current = head;
        while (current != nullptr) {
            std::cout << "(" << current -> data.vertex << ", " << current -> data.weight << ") ";
            current = current -> next;
        }
        std::cout << std::endl;
    }

    Node* getHead() {
        return head;
    };

private:
    Node* head = nullptr;
};



