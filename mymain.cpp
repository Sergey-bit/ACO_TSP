#include <iostream>
#include "AntAlgorithm.hpp"

void init(int* city, int x, int y)
{
    city[0] = x;
    city[1] = y;
}

int main()
{
    Ant::matrix cities = {
        { 0, 1, 1, 1, 0, 0, 0, 0 },
        { 1, 0, 0, 1, 0, 1, 0, 1 },
        { 1, 0, 0, 0, 1, 1, 1, 0 },
        { 1, 1, 0, 0, 1, 0, 0, 0 },
        { 0, 0, 1, 1, 0, 1, 0, 1 },
        { 0, 1, 1, 0, 1, 0, 0, 0 },
        { 0, 0, 1, 0, 0, 0, 0, 1 },
        { 0, 1, 0, 0, 1, 0, 1, 0 }
    };
    std::vector<int*> poses;
    
    for (int i = 0; i < cities.size(); i++)
    {
        poses.push_back(new int[2]);
    }

    init(poses[0], 1, 1);
    init(poses[1], 10, 10);
    init(poses[2], 20, 10);
    init(poses[3], 10, 30);
    init(poses[4], 15, 5);
    init(poses[5], 10, 1);
    init(poses[6], 20, 20);
    init(poses[7], 20, 30);

    AntAlgorithm tsp(cities, poses);
    tsp.start();

    for (const int& city : tsp.getRoute())
    {
        std::cout << city << " ";
    }

    std::cout << "\n" << tsp.getDistance() << std::endl;

    for (int* el : poses)
    {
        delete[] el;
    }

    return 0;
}