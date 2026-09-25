//
//  maze_generator.h
//
//
//  Created by Angelena Piece on 19 February 2024
//

#ifndef MAZE_MODEL_CELL_FRIENDS_INTERFACE_H
#define MAZE_MODEL_CELL_FRIENDS_INTERFACE_H

#include <iostream>
#include <vector>
#include <cstddef>    

namespace s21::model {

class CellFriendsInterface {
    public:
        virtual void Reset(std::size_t rows, std::size_t cols) = 0;
        virtual std::size_t Number(std::size_t row, std::size_t col) const = 0;
        virtual bool HasFriends(std::size_t row, std::size_t col) const = 0;
        virtual bool IsFriends(std::size_t row1, std::size_t col1, std::size_t row2, std::size_t col2) const = 0;
        virtual void Alone(std::size_t row, std::size_t col) = 0;
        virtual void MakeLeader(std::size_t row, std::size_t col) = 0;
        virtual void MakeFriends(std::size_t row1, std::size_t col1, std::size_t row2, std::size_t col2) = 0;
        virtual void MakeAllFriends(std::size_t row1, std::size_t col1, std::size_t row2, std::size_t col2) = 0;
        virtual std::vector<std::pair<std::size_t, std::size_t>> GetFriends(std::size_t row, std::size_t col) const = 0;
};

}

#endif  // MAZE_MODEL_CELL_FRIENDS_INTERFACE_H 
