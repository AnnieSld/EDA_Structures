#include <bits/stdc++.h>
using namespace std;

struct Operation {
    string type;
    int x;
};

class RetroactivePQ {
private:
    vector<Operation> history;
    priority_queue<int, vector<int>, greater<int>> pq;

    // Ejecutar una operación normalmente
    void apply(Operation op) {
        if (op.type == "insert") {
            pq.push(op.x);
        }
        else if (op.type == "delete-min") {
            if (!pq.empty())
                pq.pop();
        }
    }

    void rebuild() {
        pq = priority_queue<int, vector<int>, greater<int>>();

        for (auto op : history) {
            apply(op);
        }
    }

public:

    // Operación normal al final de la historia
    void insert(int x) {
        history.push_back({"insert", x});
        pq.push(x);
    }

    void deleteMin() {
        history.push_back({"delete-min", 0});

        if (!pq.empty())
            pq.pop();
    }

    void retroactiveInsert(int t, Operation op) {

        history.insert(history.begin() + t, op);

        rebuild();
    }

    void printCurrent() {

        auto temp = pq;

        cout << "Q ahora = { ";

        while (!temp.empty()) {
            cout << temp.top() << " ";
            temp.pop();
        }

        cout << "}\n";
    }
};

int main() {

    RetroactivePQ Q;

    Q.insert(5);       // t0
    Q.insert(2);       // t1
    Q.deleteMin();     // t2
    Q.insert(8);       // t3
    Q.deleteMin();     // t4

    Q.printCurrent();

    // Insertar retroactivamente Insert(3) en t1
    Q.retroactiveInsert(1, {"insert", 3});

    Q.printCurrent();

    return 0;
}