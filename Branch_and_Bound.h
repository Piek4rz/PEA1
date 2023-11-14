#ifndef BRANCH_AND_BOUND_H_
#define BRANCH_AND_BOUND_H_

#include <vector>

struct Node
{
    int level;             // poziom wierzchołka
    std::vector<int> path; // ścieżka od korzenia
    int bound;             // dolna granica możliwych długości poniżej danego węzła
};

// struktura pomocnicza do porównywania wierzchołków, potrzebna do kolejki
struct nodeComparator
{
    bool operator()(Node a, Node b)
    {
        return a.bound / a.path.size() > b.bound / b.path.size();
    }
};

class BranchAndBound
{
private:
    std::vector<std::vector<int>> matrix;
    int number_of_towns;
    std::vector<int> route;
    Node m, n; // wierzchołki pomocnicze
    // sprawdzenie czy dane miasto zostało już odwiedzone
    bool visited(Node node, int city, bool column);

public:
    BranchAndBound(std::vector<std::vector<int>> towns);
    // odległość przez całą ścieżkę do danego miasta
    int pathDistance(Node node);
    // wyznaczenie dolnego ograniczenia poprzez obliczenie sumy ścieżki i najniższych wartości w wierszach
    int lowerBound(Node node);
    void boundBranch(); // główna część algorytmu
    void printRoute();
};

#endif /* BRANCH_AND_BOUND_H_ */
