//
//  cave_generator.h
//
//
//  Created by Angelena Piece on 24 February 2024
//

#ifndef MAZE_MODEL_CAVE_GENERATOR_H
#define MAZE_MODEL_CAVE_GENERATOR_H

#include <iostream>
#include <vector>
#include <cstddef>
#include <chrono>
#include <thread>

#include "random_generator.h"
#include "cave.h"
#include "cave_console_view.h"

namespace s21::model::generator {

class CaveGenerator {
    public:
        CaveGenerator(std::size_t rows, std::size_t cols,
            std::size_t birthLimit = 3, std::size_t deathLimit = 5, std::size_t simulationSteps = 1) {
            initialize(rows, cols, birthLimit, deathLimit, simulationSteps);
        }
        ~CaveGenerator() {
           utilize();
        }

        void Generate(std::size_t rows = 0, std::size_t cols = 0,
            std::size_t birthLimit = 9, std::size_t deathLimit = 3, std::size_t simulationSteps = 1) {
            if (rows != 0 && cols != 0) {
                reset(rows, cols, birthLimit, deathLimit, simulationSteps);
            } else {
                clear();
            }

            auto generator = s21::model::utils::generator::RandomNumberGenerator((int)0, (int)1);
            for (size_t row = 0; row < rows_; row++)
            {
                for (size_t col = 0; col < cols_; col++)
                {
                    at(row, col) = generator.NextInteger();
                }
            }

            for (std::size_t step = 0; step < simulationSteps_; step++)
            {
                Step(0);
            }
        }

        void Step(std::size_t delay) {
            if (delay) {
                std::this_thread::sleep_for(std::chrono::milliseconds(delay));
            }
            for (size_t row = 0; row < rows_; row++)
            {
                for (size_t col = 0; col < cols_; col++)
                {
                    if (isAlive(row, col) && aliveNeighborhoodCount(row, col) < deathLimit_) {
                        makeDie(row, col);
                    } else if (!isAlive(row, col) && aliveNeighborhoodCount(row, col) > birthLimit_) {
                        makeAlive(row, col);
                    }
                }
            }
        }

        CaveData Get() const {
            return CaveData(rows_, cols_, field_);
        }

        void Preview() {
            CaveConsoleView(field_, rows_, cols_, 2).Render();
            // std::cout << std::endl;
            // for (size_t step = 0; step < simulationSteps_; step++)
            // {
            //     Step(500);
            //     CaveConsoleView(field_, rows_, cols_, 2).Render();
            //     std::cout << std::endl;
            // }
        }

    private:
        void initialize(std::size_t rows, std::size_t cols,
            std::size_t birthLimit = 3, std::size_t deathLimit = 3, std::size_t simulationSteps = 3) {
            simulationSteps_ = simulationSteps;
            birthLimit_ = birthLimit;
            deathLimit_ = deathLimit;
            rows_ = rows;
            cols_ = cols;
            field_ = new bool[rows_ * cols_];
        }
        void utilize() {
            if (field_ != nullptr) {
                delete field_;
                field_ = nullptr;
            }
        }

        void reset(std::size_t rows, std::size_t cols,
            std::size_t birthLimit = 3, std::size_t deathLimit = 3, std::size_t simulationSteps = 3) {
            utilize();
            initialize(rows, cols, birthLimit, deathLimit, simulationSteps);
        }
        void clear() {
            for (size_t cell = 0; cell < rows_ * cols_; cell++)
            {
                field_[cell] = false;
            }
        }
        bool at(std::size_t row, std::size_t col) const {
            if (rows_ <= row || cols_ <= col) {
                throw std::out_of_range("Maze::at(...) const");
            }
            return field_[row * cols_ + col];
        }
        bool& at(std::size_t row, std::size_t col) {
            if (rows_ <= row || cols_ <= col) {
                throw std::out_of_range("&Maze::at(...)");
            }
            return field_[row * cols_ + col];
        }
        void makeDie(std::size_t row, std::size_t col) {
            at(row, col) = false;
        }
        void makeAlive(std::size_t row, std::size_t col) {
            at(row, col) = true;
        }
        std::size_t alive(std::size_t row, std::size_t col) {
            if (0 <= row && row < rows_ && 0 <= col && col < cols_) {
                return (int)isAlive(row, col);
            }
            else {
                return 0;
            }
        }
        bool isAlive(std::size_t row, std::size_t col) { return at(row, col); }
        std::size_t aliveNeighborhoodCount(std::size_t row, std::size_t col) {
            std::size_t count = alive(row - 1, col - 1) + alive(row - 1, col) + alive(row - 1, col + 1)
                              + alive(row,     col - 1) +          0          + alive(row,     col + 1)
                              + alive(row + 1, col - 1) + alive(row + 1, col) + alive(row + 1, col + 1);
            return count;
        }

    private:
        std::size_t simulationSteps_;
        std::size_t birthLimit_, deathLimit_;
        std::size_t rows_, cols_;
        bool *field_ = nullptr;
};

}

#endif  // MAZE_MODEL_CAVE_GENERATOR_H
