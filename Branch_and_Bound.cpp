#include "Branch_and_Bound.h"

#include <iostream>
#include <climits>
#include <queue>
#include <algorithm> // do find

using namespace std;

BranchAndBound::BranchAndBound(std::vector<std::vector<int>> towns)
{
    matrix = towns;
    number_of_towns = matrix[0].size();
}

int BranchAndBound::pathDistance(Node node)
{
    int path_distance = 0;
    // zliczenie sumy odległości w ścieżce aż do danego wierzchołka
    for (int i = 0; i < node.path.size() - 1; i++)
        path_distance += matrix[node.path[i]][node.path[i + 1]];
    return path_distance;
}

bool BranchAndBound::visited(Node node, int city, bool column)
{
    // w przypadku wierszy nie chcemy ograniczać ostatniej pozycji w ścieżce
    // czyli możliwości wyjścia z wierzchołka, w którym aktualnie jesteśmy
    int limit = -1;
    int i = 0;
    if (column)
    {
        i++;       // jeżeli sprawdzamy kolumny, to pomijamy miejsce startu ponieważ musimy tam wrócić
        limit = 0; // w przypadku kolumn możemy ograniczyć aktualny wierzchołek, ponieważ do niego nie wrócimy
    }
    for (; i < node.path.size() + limit; i++)
        if (node.path[i] == city) // sprawdzenie czy podane miasto zostało już odwiedzone
            return true;
    return false;
}

int BranchAndBound::lowerBound(Node node)
{
    int bound = pathDistance(node); // dolne ograniczenie złożone z dotychczasowych długości
    for (int i = 0; i < number_of_towns; i++)
    {
        if (visited(node, i, false))
            continue; // jeśli miasto zostało odwiedzone to pomijamy

        int minimum = INT_MAX;

        for (int j = 0; j < number_of_towns; j++)
        {
            if (visited(node, j, true))
                continue; // jeśli nie będziemy wracać do tego miasta to pomijamy
            if (i == j)
                continue;                                       // pomiń ponieważ to jest to samo miasto
            if (node.path[node.path.size() - 1] == i && j == 0) // żeby nie zakończyć przedwcześnie
                continue;                                       // jeśli ostatnia pozycja w ścieżce prowadziłaby do startu to pomijamy
            if (matrix[i][j] < minimum)
                minimum = matrix[i][j];
        }
        if (minimum != INT_MAX)
            bound += minimum;
    }
    return bound;
}

void BranchAndBound::boundBranch()
{
    vector<int> temp;
    temp.push_back(0);
    m.level = 0;
    m.path = temp;
    m.bound = lowerBound(m);
    n.bound = 0;
    n.level = 0;
    priority_queue<Node, vector<Node>, nodeComparator> q;
    q.push(m);

    int min_length = INT_MAX; // minimalna długość do której będziemy porównywać wyliczone ograniczenia wierzchołków

    while (!q.empty())
    {
        m = q.top();
        q.pop();

        if (m.bound < min_length) // jeśli ograniczenie rozpatrywanego wierzchołka jest mniejsze niż obecna najniższa droga
        {
            n.level = m.level + 1; // schodzimy poziom niżej w grafie

            // tworzymy i dodajemy do kolejki możliwe drogi
            for (int i = 1; i < number_of_towns; i++)
            {
                // jeśli  wierzchołka do tej pory nie odwiedzono
                // jeśli find nie znajdzie to zwróci ostatni element,
                //  end() wskazuje element "za" ostatnim elementem
                if (find(m.path.begin(), m.path.end(), i) == m.path.end())
                {
                    n.path = m.path;
                    n.path.push_back(i); // dołożenie nowego wierzchołka

                    if (n.level == number_of_towns - 2) // jeśli zostało już tylko jedno miasto i powrót do początkowego
                    {
                        // szukamy ostatniego nieodwiedzonego miasta, poza początkowym
                        for (int j = 1; j < number_of_towns; j++)
                        {
                            if (find(n.path.begin(), n.path.end(), j) == n.path.end())
                            {
                                n.path.push_back(j); // dodajemy ostatnie nieodwiedzone miast do ścieżki
                                break;
                            }
                        }
                        // odwiedziliśmy wszystkie, wracamy do początkowego
                        n.path.push_back(0);

                        if (pathDistance(n) < min_length) // jeśli znaleziona ścieżka jest najlepsza
                        {
                            min_length = pathDistance(n);
                            route = n.path; // to przypisujemy ją jako najlepszą
                        }
                    }
                    else // jeśli nie jesteśmy na końcówce algorytmu
                    {
                        n.bound = lowerBound(n);  // obliczenie dolnego ograniczenia nowego wierzchołka
                        if (n.bound < min_length) // jeśli jest ono mniejsze niż dotychczasowe najmniejsze
                            q.push(n);            // to wrzucamy do kolejki
                    }
                }
            }
        }
    }
}

void BranchAndBound::printRoute()
{
    for (auto i = 0; i < route.size() - 1; i++)
        cout << route[i] << " -> ";
    cout << route[number_of_towns] << endl;
    n.path = route;
    cout << "Cost = " << pathDistance(n) << endl;
}
