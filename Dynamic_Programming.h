#ifndef DYNAMIC_PROGRAMMING_H_
#define DYNAMIC_PROGRAMMING_H_

#include <vector>

class DynamicProgramming {
public:
    DynamicProgramming(std::vector<std::vector<int>> towns);

    void reset();  // Reset all relevant variables
    void startDP();
    void printRoute();

private:
    int recDP(int start_vertex, int set_of_vertices);
    void calculateRoute();

    std::vector<std::vector<int>> matrix;
    int number_of_towns;
    int all_vertices_bits;
    std::vector<std::vector<int>> sub_problems;
    std::vector<int> route;
    int route_cost;
};

#endif /* DYNAMIC_PROGRAMMING_H_ */
