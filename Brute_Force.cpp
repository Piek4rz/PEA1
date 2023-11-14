#include "Brute_Force.h"

#include <iostream>
#include <algorithm> // do next_permutation
#include <climits>

using namespace std;

BruteForce::BruteForce(std::vector<std::vector<int>> towns)
{
    matrix = towns;
    number_of_towns = matrix[0].size();
}

void BruteForce::startBF()
{
    int minimum = INT_MAX;
    vector<int> temp;
    for (int i = 0; i < number_of_towns; i++)
        temp.push_back(i); // wypełnienie vectora indeksami miast

    do
    {
        int path_distance = 0;
        // zliczenie sumy odległości w ścieżce aż do danego wierzchołka
        for (int i = 0; i < temp.size() - 1; i++)
        {
            path_distance += matrix[temp[i]][temp[i + 1]];
            if (path_distance > minimum) // jeśli obliczona odległość już jest większa niż minimalna
                goto continue_outer;     // to przerywamy liczenie
        }
        path_distance += matrix[temp.back()][0]; // dodanie odległości do wierzchołka początkowego
        if (path_distance < minimum)             // jeśli jest to nowa najlepsza trasa
        {
            minimum = path_distance;
            route_cost = path_distance;
            route = temp;
        }
    continue_outer:;
    } while (next_permutation(temp.begin() + 1, temp.end())); // dopóki nie przerobimy wszystkich permutacji
}

void BruteForce::printRoute()
{
    for (auto i = 0; i < route.size(); i++)
        cout << route[i] << " -> ";
    cout << route[0] << endl;
    cout << "Cost = " << route_cost << endl;
}
