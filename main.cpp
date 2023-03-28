#include <iostream>
#include <vector>
#include <queue>
using namespace std;

template <typename T>
class Node {
public:
    T id;
    vector<Node*> edges;
    Node(T _id) : id(_id) {}

    
    void addEdge(Node* node) {
        edges.push_back(node);
    }

  
    void print() {
        cout << "Node " << id << endl;
    }
};


template <typename T>
class Graph {
public:
    vector<Node<T>*> nodes;

   
    void addNode(T id) {
        Node<T>* node = new Node<T>(id);
        nodes.push_back(node);
    }

  
    void addEdge(T id1, T id2) {
        Node<T>* node1 = findNode(id1);
        Node<T>* node2 = findNode(id2);
        if (node1 && node2) {
            node1->addEdge(node2);
            node2->addEdge(node1);
        }
    }

   
    Node<T>* findNode(T id) {
        for (Node<T>* node : nodes) {
            if (node->id == id) {
                return node;
            }
        }
        return nullptr;
    }

   
    void print() {
        cout << "Граф:" << endl;
        for (Node<T>* node : nodes) {
            node->print();
            cout << "Вершины: ";
            for (Node<T>* edge : node->edges) {
                cout << edge->id << " ";
            }
            cout << endl;
        }
    }

   
    vector<T> findPath(T start, T end) {
        Node<T>* startNode = findNode(start);
        Node<T>* endNode = findNode(end);
        if (!startNode || !endNode) {
            return vector<T>();
        }

        queue<pair<Node<T>*, vector<T>>> q;
        q.push(make_pair(startNode, vector<T>({start})));
        while (!q.empty()) {
            auto curr = q.front();
            q.pop();

            Node<T>* currNode = curr.first;
            vector<T> currPath = curr.second;
            if (currNode == endNode) {
                return currPath;
            }

            for (Node<T>* next : currNode->edges) {
                if (find(currPath.begin(), currPath.end(), next->id) == currPath.end()) {
                    vector<T> nextPath = currPath;
                    nextPath.push_back(next->id);
                    q.push(make_pair(next, nextPath));
                }
            }
        }

        return vector<T>();
    }
};

int main() {
    Graph<int> graph;
    graph.addNode(1);
    graph.addNode(2);
    graph.addNode(3);
    graph.addNode(4);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(3, 4);
    graph.print();
    vector<int> path = graph.findPath(1, 4);
    cout << "Путь: ";
    for (int i : path) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}