#ifndef ANT
#define ANT

#include <vector>
#include "Randoms.cpp"
#include <numeric>

#define SQUARE(x) (x) * (x)
#define SQRT(x) pow(x, .5)

class Ant
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
        Ant(cint& initCity, cmatrix& adjacencyCitiesMatrix,
            cmatrixd& adjacencyPheromonesMatrix,
            cvector<int*>& citiesPos, cint& alpha, cint& beta,
            Randoms& random);
        
        void go();
        double getDistance() const;

        cvector<int>& getRoute() const;
    
    private:
        double length(cint& cityi, cint& cityj) const;
        bool isVisited(cint& city) const;

        double index_ij(cint& cityi, cint& cityj) const;
        int city(cvector<double>& probs) const;

        bool exists(cint& cityi, cint& cityj) const;
    
    private:
        int initCity_;
        cvector<int*>& citiesPos_;

        cmatrix& citiesGraph_;
        cmatrixd& pheromonesMatrix_;

        std::vector<int> route_;
        double routeLength_;

        int alpha_, beta_;
        Randoms& rand_;
};

#endif