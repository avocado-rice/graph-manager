#pragma once



class LinkedList {
public:
    struct Edge {
        int vertex;
        int weight;

        Edge(int v, int w) {
            vertex = v;
            weight = w;
        }
    };

    struct Node {
        Edge data;
        Node* next;

        Node(Edge e) : data(e), next(nullptr) {}
    };

    void append(int successorVertex, int weight) {
        std::cout << "Creating Node with vertex = " << successorVertex << ", weight = " << weight << std::endl;
        Node* node = new Node(Edge(successorVertex, weight));
        std::cout << "enieodeolse";
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

private:
    Node* head = nullptr;
};



