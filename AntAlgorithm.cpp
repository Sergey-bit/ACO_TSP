#include "AntAlgorithm.hpp"
#include <iostream>

AntAlgorithm::AntAlgorithm(cmatrix& adjacencyCitiesMatrix, 
        cvector<int*>& citiesPos) :
        citiesMatrix_(adjacencyCitiesMatrix),
        citiesPos_(citiesPos),
        antNumber_(citiesPos_.size())
{
    for (int* city : citiesPos_)
    {
        bestRoute_.push_back(0);
    }

    for (int i = 0; i < citiesPos_.size(); i++)
    {
        pheromonesMatrix_.push_back(std::vector<double>());
    }

    for (int i = 0; i < citiesPos_.size(); i++)
    {
        pheromonesMatrix_[i].push_back(0);

        for (int j = i + 1; j < citiesPos_.size(); j++)
        {
            pheromonesMatrix_[i].push_back(rand_.Uniforme() * tauMax_);
            pheromonesMatrix_[j].push_back(rand_.Uniforme() * tauMax_);
        }
    }
}

AntAlgorithm::cvector<int>& AntAlgorithm::getRoute() const
{
    return bestRoute_;
}
double AntAlgorithm::getDistance() const
{
    return bestLength_;
}

void AntAlgorithm::start()
{
    for (int l = 0; l < iterations_; l++)
    {
        matrix routes;
        std::vector<double> lengths;

        std::cout << "Iteration " << l << std::endl;

        for (int k = 0; k < antNumber_; k++)
        {
            // we have the same amount of ants as cities, that's why we can use its index
            // instead of the index of the city
            Ant ant(k, citiesMatrix_, pheromonesMatrix_, citiesPos_, alpha_, beta_, rand_);
            ant.go();

            const double& dist = ant.getDistance();
            if (dist > 0)
            {
                if (bestLength_ > dist)
                {
                    bestLength_ = dist;
                    bestRoute_ = ant.getRoute();
                }

                lengths.push_back(dist);
                routes.push_back(ant.getRoute());
            }
        }

        updatePheromones(routes, lengths);
    }
}

void AntAlgorithm::updatePheromones(cvector<std::vector<int>>& routes, cvector<double>& lengths)
{
    for (int i = 0; i < pheromonesMatrix_.size() - 1; i++)
    {
        for (int j = i + 1; j < pheromonesMatrix_.size(); j++)
        {
            double sum = 0.0;

            for (int k = 0; k < routes.size(); k++)
            {
                if(isTherePath(routes[k], i, j))
                {
                    sum += q_ / lengths[k];
                }
            }

            double nval = (1 - rho_) * pheromonesMatrix_[i][j] + sum;

            pheromonesMatrix_[i][j] = nval;
            pheromonesMatrix_[j][i] = nval;
        }
    }
}
bool AntAlgorithm::isTherePath(cvector<int>& route, cint& cityi, cint& cityj) const
{
    for (int i = 0; i < citiesPos_.size(); i++)
    {
        if (i == cityi || i == cityj)
        {
            cint& city = route[i + 1];
            if (city == cityi || city == cityj)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    return false;
}