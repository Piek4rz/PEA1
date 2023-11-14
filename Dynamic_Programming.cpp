#include "Dynamic_Programming.h"

#include <algorithm>
#include <iostream>
#include <climits>

using namespace std;

DynamicProgramming::DynamicProgramming(std::vector<std::vector<int>> towns)
{
    matrix = towns;
    number_of_towns = matrix[0].size();
    all_vertices_bits = (1 << number_of_towns) - 1; // all_vertices_bits = 2^number_of_towns
    // sub_problems to vector o rozmiarze number_of_towns na 2^number_of_towns wype³niony wartoœciami -1
    sub_problems = std::vector<std::vector<int>>(number_of_towns, std::vector<int>(all_vertices_bits, -1));
    // Inicjalizacja macierzy miast oraz wektora do przechowywania podproblemów
}

void DynamicProgramming::reset() {
    sub_problems.assign(number_of_towns, std::vector<int>(all_vertices_bits, -1));
    route.clear();
    route_cost = 0;
    // Resetowanie macierzy podproblemów, trasy i kosztu trasy
}

void DynamicProgramming::startDP() {
    reset();
    for (int i = 0; i < number_of_towns; i++)
        sub_problems[i][0] = matrix[i][0];
    // Inicjalizacja pierwszego wiersza macierzy podproblemów

    route_cost = recDP(0, all_vertices_bits - 1);
    calculateRoute();
    // Rozpoczêcie dynamicznego programowania, obliczenie kosztu trasy i trasy
}

int DynamicProgramming::recDP(int start_vertex, int set_of_vertices) {
    int result = -1;

    if (sub_problems[start_vertex][set_of_vertices] != -1)
        return sub_problems[start_vertex][set_of_vertices];
    // Sprawdzenie, czy podproblem zosta³ ju¿ rozwi¹zany

    for (int i = 0; i < number_of_towns; i++) {
        int mask = all_vertices_bits - (1 << i);
        int masked = set_of_vertices & mask;
        // Tworzenie maski do zaznaczenia odwiedzonych miast

        if (masked != set_of_vertices) {
            int value = matrix[start_vertex][i] + recDP(i, masked);
            // Obliczenie wartoœci podproblemu

            if (result == -1 || value < result)
                result = value;
            // Aktualizacja wyniku, jeœli nowa wartoœæ jest mniejsza
        }
    }
    sub_problems[start_vertex][set_of_vertices] = result;
    // Zapisanie wyniku podproblemu w macierzy
    return result;
}

void DynamicProgramming::calculateRoute() {
    route.push_back(0);
    int mask = all_vertices_bits - 1;

    while (mask != 0) {
        int min_sub_cost = INT_MAX;
        int index = INT_MAX;

        for (int i = 1; i < number_of_towns; i++) {
            if ((mask & (1 << i)) != 0) {
                int temp_mask = mask & ~(1 << i);
                int temp_cost = sub_problems[i][temp_mask] + matrix[route.back()][i];
                // Obliczenie kosztu dla ka¿dego mo¿liwego miasta

                if (temp_cost < min_sub_cost) {
                    min_sub_cost = temp_cost;
                    index = i;
                }
                // Aktualizacja minimalnego kosztu i indeksu miasta
            }
        }

        route.push_back(index);
        mask &= ~(1 << index);  // Wyczyszczenie bitu o indeksie
        // Dodanie indeksu miasta do trasy i odznaczenie go jako odwiedzonego
    }

    route.push_back(0);
    // Dodanie powrotu do miasta pocz¹tkowego
}

void DynamicProgramming::printRoute() {
    for (auto i = 0; i < route.size() - 1; i++)
        std::cout << route[i] << " -> ";
    std::cout << route[route.size() - 1] << std::endl;
    std::cout << "Koszt = " << route_cost << std::endl;
    // Wyœwietlenie trasy i kosztu trasy
}
