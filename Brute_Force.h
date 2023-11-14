#ifndef BRUTE_FORCE_H_
#define BRUTE_FORCE_H_

#include <vector>

class BruteForce
{
private:
    std::vector<std::vector<int>> matrix;
    int number_of_towns;
    int route_cost;
    std::vector<int> route;

public:
    BruteForce(std::vector<std::vector<int>> towns);
    void startBF();    // główna część algorytmu
    void printRoute(); // wyświela wynik
};

#endif /* BRUTE_FORCE_H_ */
