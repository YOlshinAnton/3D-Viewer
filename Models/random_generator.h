//
//  random_generator.h
//
//
//  Created by Angelena Piece on 28.12.2023.
//

#ifndef MAZE_MODEL_RANDOM_GENERATOR_H
#define MAZE_MODEL_RANDOM_GENERATOR_H

#include <chrono>
#include <random>
#include <vector>

namespace s21::model::utils::generator {

class RandomNumberGenerator
{
public:
    RandomNumberGenerator(int min, int max) : min_(min), max_(max)
    {
        std::random_device rd;
        std::mt19937::result_type seed = rd() ^ (
                (std::mt19937::result_type)
                std::chrono::duration_cast<std::chrono::seconds>(
                    std::chrono::system_clock::now().time_since_epoch()
                    ).count() +
                (std::mt19937::result_type)
                std::chrono::duration_cast<std::chrono::microseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch()
                    ).count() );

        generator_ = std::mt19937(seed);
        distribInteger_ = std::uniform_int_distribution<int>(min_, max_);
        distribDouble_ = std::uniform_real_distribution<double>(min_, max_);
    }

    RandomNumberGenerator(double min, double max) : min_(min), max_(max)
    {
        std::random_device rd;
        std::mt19937::result_type seed = rd() ^ (
                (std::mt19937::result_type)
                std::chrono::duration_cast<std::chrono::seconds>(
                    std::chrono::system_clock::now().time_since_epoch()
                    ).count() +
                (std::mt19937::result_type)
                std::chrono::duration_cast<std::chrono::microseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch()
                    ).count() );

        generator_ = std::mt19937(seed);
        distribInteger_ = std::uniform_int_distribution<int>(min_, max_);
        distribDouble_ = std::uniform_real_distribution<double>(min_, max_);
    }

    int NextInteger()
    {
        return distribInteger_(generator_);
    }

    std::vector<int> GenerateListInteger(long n)
    {
        std::vector<int> list(n);
        for(long i = 0; i < n; ++i )
        {
            list.push_back(NextInteger());
        }
        return list;
    }

    double NextDouble()
    {
        return distribDouble_(generator_);
    }

    std::vector<double> GenerateListDouble(long n)
    {
        std::vector<double> list(n);
        for(long i = 0; i < n; ++i)
        {
            list.push_back(NextDouble());
        }
        return list;
    }

private:
    int min_, max_;
    std::mt19937 generator_;
    std::uniform_int_distribution<int> distribInteger_;
    std::uniform_real_distribution<double> distribDouble_;
};

}

#endif  // MAZE_MODEL_RANDOM_GENERATOR_H