#include <bits/stdc++.h>
using namespace std;

struct Operation {
    string type;
    int x;
};

struct State {
    multiset<int> pq;
};

class RetroactivePQ {

private:

    // Historial de operaciones, ordenadas por tiempo
    vector<Operation> history;

    // Estado de la PQ en cada instante
    vector<State> states;

    // Tiempos que son bridges
    set<int> bridges;

public:

    // ----------------------------------
    // Ejecutar una operación
    // ----------------------------------

    void apply(State &state, Operation op) {

        if (op.type == "insert") {

            state.pq.insert(op.x);

        }
        else if (op.type == "delete-min") {

            if (!state.pq.empty()) {
                state.pq.erase(state.pq.begin());
            }
        }
    }


    // ----------------------------------
    // Reconstruir estados
    // ----------------------------------

    void rebuild() {

        states.clear();

        State current;

        // Estado inicial: vacío
        states.push_back(current);

        for (auto op : history) {

            apply(current, op);

            states.push_back(current);
        }

        updateBridges();
    }


    // ----------------------------------
    // Determinar los bridges
    // ----------------------------------

    void updateBridges() {

        bridges.clear();

        // Estado actual
        const multiset<int> &now =
            states.back().pq;

        for (int t = 0; t < (int)history.size(); t++) {

            const multiset<int> &past =
                states[t + 1].pq;

            bool isBridge = true;

            // Q(t) ⊆ Q(now)
            for (int x : past) {

                auto it = now.find(x);

                if (it == now.end()) {
                    isBridge = false;
                    break;
                }

                // Importante si hay duplicados
                auto temp = now;

                // Esta versión sencilla solo sirve
                // como demostración conceptual.
            }

            if (isBridge) {
                bridges.insert(t);
            }
        }
    }


    // ----------------------------------
    // Buscar el bridge más cercano <= t
    // ----------------------------------

    int findBridge(int t) {

        auto it = bridges.upper_bound(t);

        if (it == bridges.begin()) {
            return -1;
        }

        --it;

        return *it;
    }


    // ----------------------------------
    // Insertar normalmente
    // ----------------------------------

    void insert(int x) {

        history.push_back({
            "insert",
            x
        });

        rebuild();
    }


    // ----------------------------------
    // Delete-Min normal
    // ----------------------------------

    void deleteMin() {

        history.push_back({
            "delete-min",
            0
        });

        rebuild();
    }


    // ----------------------------------
    // Insertar retroactivamente
    // ----------------------------------

    void retroactiveInsert(int t, int x) {

        cout << "\nInsertando Insert("
             << x << ") en t = "
             << t << "\n";

        // Buscar bridge antes de modificar
        int bridge = findBridge(t);

        cout << "Bridge encontrado: ";

        if (bridge == -1)
            cout << "ninguno\n";
        else
            cout << bridge << "\n";

        // Insertar operación en la historia
        history.insert(
            history.begin() + t,
            {
                "insert",
                x
            }
        );

        // Por ahora reconstruimos.
        // Luego reemplazaremos esto por
        // la actualización eficiente usando
        // bridges + BST.
        rebuild();
    }


    // ----------------------------------
    // Mostrar bridges
    // ----------------------------------

    void printBridges() {

        cout << "Bridges: ";

        for (int t : bridges) {
            cout << t << " ";
        }

        cout << "\n";
    }


    // ----------------------------------
    // Mostrar PQ actual
    // ----------------------------------

    void printPQ() {

        cout << "Q ahora = { ";

        for (int x : states.back().pq) {
            cout << x << " ";
        }

        cout << "}\n";
    }
};


int main() {

    RetroactivePQ pq;

    pq.insert(5);       // t0
    pq.insert(2);       // t1
    pq.deleteMin();     // t2
    pq.insert(8);       // t3

    pq.printPQ();

    pq.printBridges();

    // Insertar 3 retroactivamente
    // en t = 1

    pq.retroactiveInsert(1, 3);

    pq.printPQ();
    pq.printBridges();

    return 0;
}