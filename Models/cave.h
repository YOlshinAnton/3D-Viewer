//
//  caver.h
//
//
//  Created by Angelena Piece on 14 March 2024
//

#ifndef MAZE_MODEL_CAVE_H
#define MAZE_MODEL_CAVE_H

#include <stdexcept>

namespace s21::model {

class CaveData {
public:
    CaveData(std::size_t rows, std::size_t cols, const bool * const data) 
        : rows_(rows), cols_(cols), data_(data) {}

    std::size_t Rows() const { return rows_; }
    std::size_t Cols() const { return cols_; }

    bool at(std::size_t row, std::size_t col) const {
        if (rows_ <= row || cols_ <= col) {
            throw std::out_of_range("");
        }
        return data_[row * cols_ + col];
    }

private:
    std::size_t rows_, cols_;
    const bool * const data_;
};

}

#endif  // MAZE_MODEL_CAVE_H