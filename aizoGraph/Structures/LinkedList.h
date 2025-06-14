#pragma once

struct Edge {
    int vertex;
    int weight;

    Edge(int v, int w) {
    vertex = v;
    weight = w;
    }
};

class LinkedList {
public:
    void append(int successorVertex, int weight) {
        Node* node = new Node(Edge(successorVertex, weight));
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
private:
    struct Node {
        Edge data;
        Node* next;

        Node(Edge e) {
            data = e;
            next = nullptr;
        }
    };

    Node* head = nullptr;
};



