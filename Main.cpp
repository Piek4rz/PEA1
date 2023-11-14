#include "Towns.h"
#include "Branch_and_Bound.h"
#include "Brute_Force.h"
#include "Dynamic_Programming.h"

#include <iostream>
#include <limits>
#include <chrono>

using namespace std;

void menu()
{
    Towns towns;
    int choice;
    do
    {
        cout << endl
             << "Which action you want to perform? Type appropriate number " << endl;
        cout << "1 - Load data from file " << endl;
        cout << "2 - Generate random data" << endl;
        cout << "3 - Print data " << endl;
        cout << "4 - BruteForce algorithm " << endl;
        cout << "5 - Dynamic programming algorithm " << endl;
        cout << "6 - Branch and Bound algorithm " << endl;
        cout << "0 - Exit the program " << endl;
        cin >> choice;
        cout << endl;
        switch (choice)
        {

        case 1: // załadowanie danych z pliku;
            towns.displayAvailableFiles();
            break;
        case 2:
        {
            int value = 0;
            cout << "Enter how many towns you want to create: ";
            cin >> value;
            if (value <= 0)
            {
                cout << "Invalid number of towns" << endl;
                break;
            }
            towns.generateRandomData(value);
            towns.printData();
            break;
        }
        case 3: // wypisanie
            if (towns.getTowns().empty())
            {
                cout << "Load data first" << endl;
                break;
            }
            towns.printData();
            break;

        case 4: // BF
        {
            if (towns.getTowns().empty())
            {
                cout << "Load data first" << endl;
                break;
            }
            std::cout << "Enter the number of repetitions: " << endl;
            int n;
            cin >> n;
            std::chrono::steady_clock::time_point start =
                std::chrono::steady_clock::now();
            BruteForce bf(towns.getTowns());
            for (int i = 0; i < n; i++)
                bf.startBF();
            std::chrono::steady_clock::time_point end =
                std::chrono::steady_clock::now();
            bf.printRoute();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            std::cout << "Execution time: "
                << duration
                << "us\n";
            std::cout << "Execution time for one instance: "
                << duration / n
                << "us\n";
            break;
        }

        case 5: // DP
        {
            if (towns.getTowns().empty())
            {
                cout << "Load data first" << endl;
                break;
            }
            std::cout << "Enter the number of repetitions: " << endl;
            int n;
            cin >> n;
            std::chrono::steady_clock::time_point start =
                std::chrono::steady_clock::now();
            DynamicProgramming dp(towns.getTowns());
            for (int i = 0; i < n; i++) {
                dp.startDP();
            }
            std::chrono::steady_clock::time_point end =
                std::chrono::steady_clock::now();
            dp.printRoute();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            std::cout << "Execution time: "
                << duration
                << "us\n";
            std::cout << "Execution time for one instance: "
                << duration / n
                << "us\n";
            break;
        }
        case 6: // B&B
        {
            if (towns.getTowns().empty())
            {
                cout << "Load data first" << endl;
                break;
            }
            std::cout << "Enter the number of repetitions: " << endl;
            int n;
            cin >> n;
            std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
            BranchAndBound bnb(towns.getTowns());
            for (int i=0; i < n; i++) 
                bnb.boundBranch();
            
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            bnb.printRoute();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            
            std::cout << "Execution time: "
                      << duration
                      << "us\n";
            std::cout << "Execution time for one instance: "
                << duration/n
                << "us\n";
            break;
        }


        case 0: // wyjście
            break;
        default:
            cout << "Type appropriate number" << endl;
            break;
        }
    } while (choice != 0);
}

int main()
{
    menu();

    return 0;
}
