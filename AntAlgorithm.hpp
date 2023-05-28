#ifndef ANT_ALGORITHM
#define ANT_ALGORITHM

#include "Ant.hpp"
#include <climits>
#include <cfloat>

class AntAlgorithm
{
    public:
        using cint = const int;

        using matrix = std::vector<std::vector<int>>;
        using matrixd = std::vector<std::vector<double>>;

        using cmatrixd = const matrixd;
        using cmatrix = const matrix;

        template<typename T>
        using cvector = const std::vector<T>;

    public:
        AntAlgorithm(cmatrix& adjacencyCitiesMatrix, 
        cvector<int*>& citiesPos);

        void start();

        cvector<int>& getRoute() const;
        double getDistance() const;
    
    private:
        void updatePheromones(cvector<std::vector<int>>& routes, cvector<double>& lengths);
        bool isTherePath(cvector<int>& route, cint& cityi, cint& cityj) const;

    private:
        std::vector<int> bestRoute_;
        double bestLength_ = DBL_MAX;

        Randoms rand_ = Randoms(21);
        cint iterations_ = 100;

        double alpha_ = 2.0;
        double beta_ = 1.0;

        matrixd pheromonesMatrix_;
        cmatrix& citiesMatrix_;

        cvector<int*>& citiesPos_;
        double tauMax_ = 5.0;

        double q_ = 4.0;
        int antNumber_;

        double rho_ = 0.2;
};

#endif