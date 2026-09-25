//
//  cave_console_view.h
//  Maze
//
//  Created by Angelena Piece on 24 February 2024
//

#ifndef MAZE_MODEL_CAVE_CONSOLE_VIEW_H
#define MAZE_MODEL_CAVE_CONSOLE_VIEW_H

#include <iostream>
#include <string>

#include "view_interface.h"

namespace s21::model {

class CaveConsoleView : ViewInterface {
public:
    CaveConsoleView(const bool * const field, std::size_t rows, std::size_t cols, std::size_t height = 1) :
        field_(field), rows_(rows), cols_(cols), height_(height) {}

    void Render() const {
        for (size_t row = 0; row < rows_; row++)
        {
            line(row);
        }
    }

    private:
        std::string hdsect() const {
            return std::string(height_ * scale_, dcell_);
        }
        std::string hasect() const {
            return std::string(height_ * scale_, acell_);
        }
        void line(std::size_t row) const {
            for (size_t sect = 0; sect < height_; sect++)
            {
                for (size_t col = 0; col < cols_; col++)
                {
                    if (at(row, col)) {
                        std::cout << hdsect();
                    } else {
                        std::cout << hasect();
                    }
                }
                std::cout << std::endl;
            }
        }
        bool at(std::size_t row, std::size_t col) const {
            if (rows_ <= row || cols_ <= col) {
                throw std::out_of_range("Cave::at(...) const");
            }
            return field_[row * cols_ + col];
        }

    private:
        const char dcell_ = '.';
        const char acell_ = '#';
        std::size_t height_ = 1;
        std::size_t scale_ = 2;
        std::size_t rows_, cols_;
        const bool * const field_;
};


}

#endif  // MAZE_MODEL_CAVE_CONSOLE_VIEW_H