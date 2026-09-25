//
//  maze.h
//
//
//  Created by Angelena Piece on 14 March 2024
//

#ifndef MAZE_MODEL_MAZE_H
#define MAZE_MODEL_MAZE_H

#include <stdexcept>

namespace s21::model {

class MazeData {
public:
    enum MazeDataAccessor { RightWall, BottomWall };
    
    MazeData(std::size_t rows, std::size_t cols, const bool * const rightWalls, const bool * const bottomWalls) 
        : rows_(rows), cols_(cols), rightWalls_(rightWalls), bottomWalls_(bottomWalls) {}

    std::size_t Rows() const { return rows_; }
    std::size_t Cols() const { return cols_; }

    bool at(std::size_t row, std::size_t col, MazeDataAccessor accessor) const {
        switch (accessor)
        {
        case MazeDataAccessor::RightWall:  return at(row, col, rightWalls_);
        case MazeDataAccessor::BottomWall: return at(row, col, bottomWalls_);
        }
    }

    bool at(std::size_t row, std::size_t col, const bool * const data) const {
        if (rows_ <= row || cols_ <= col) {
            throw std::out_of_range("");
        }
        return data[row * cols_ + col];
    }

private:
    std::size_t rows_, cols_;
    const bool * const rightWalls_;
    const bool * const bottomWalls_;
};

}

#endif  // MAZE_MODEL_MAZE_H
