#include "Ant.hpp"

Ant::Ant(cint& initCity, cmatrix& adjacencyCitiesMatrix,
            cmatrixd& adjacencyPheromonesMatrix,
            cvector<int*>& citiesPos, cint& alpha, cint& beta,
            Randoms& random) :
            initCity_(initCity), citiesGraph_(adjacencyCitiesMatrix),
            pheromonesMatrix_(adjacencyPheromonesMatrix),
            citiesPos_(citiesPos), routeLength_(0),
            alpha_(alpha), beta_(beta), rand_(random)
{
    for (int i = 0; i < citiesPos.size(); i++)
    {
        route_.push_back(initCity_);
    }
}

double Ant::getDistance() const
{
    return routeLength_;
}
Ant::cvector<int>& Ant::getRoute() const
{
    return route_;
}

double Ant::length(cint& cityi, cint& cityj) const
{
    return SQRT(SQUARE(citiesPos_[cityi][0] - citiesPos_[cityj][0]) + 
                SQUARE(citiesPos_[cityi][1] - citiesPos_[cityj][1]));
}
bool Ant::isVisited(cint& city) const
{
    for (cint& c : route_)
    {
        if (c == city)
        {
            return true;
        }
    }

    return false;
}

// Returns tao^alpha * (1/length)^beta
double Ant::index_ij(cint& cityi, cint& cityj) const
{
    return  pow(pheromonesMatrix_[cityi][cityj], alpha_) * 
            pow(1.0 / length(cityi, cityj), beta_);
}
int Ant::city(cvector<double>& probs) const
{
    double prob = rand_.Uniforme();
    double sum = 0.0;
    int i = 0;
    
    for (i = 0; i < probs.size() && sum < prob; i++)
    {
        sum += probs[i];
    }

    return i - 1;
}

bool Ant::exists(cint& cityi, cint& cityj) const
{
    return citiesGraph_.at(cityi).at(cityj) == 1;
}
void Ant::go()
{
    int curCity = initCity_;
    for (int i = 0; i < citiesPos_.size() - 1; i++)
    {
        std::vector<double> probs;
        std::vector<int> cities;

        for (int j = 0; j < citiesPos_.size(); j++)
        {
            if (curCity != j && j != initCity_ &&
                exists(curCity, j) && !isVisited(j))
            {
                cities.push_back(j);
                probs.push_back(index_ij(curCity, j));
            }
        }

        // Calculating probability for every road
        double sum = std::accumulate(probs.begin(), probs.end(), 0.0);
        if(sum == 0)
        {
            routeLength_ = -1;
            return;
        }

        for (int k = 0; k < probs.size(); k++)
        {
            probs[k] /= sum;
        }

        route_[i + 1] = cities[city(probs)];
        routeLength_ += length(curCity, route_[i + 1]);
        curCity = route_[i + 1];
    }

    // if there is no way to get back init city from current city
    // then it is impossible to solve the TSP the way the ant was going
    if (route_[curCity] == initCity_ || !exists(route_[curCity], initCity_))
    {
        routeLength_ = -1.0;
        return;
    }

    routeLength_ += length(route_[curCity], initCity_);
    route_.push_back(initCity_);
}
