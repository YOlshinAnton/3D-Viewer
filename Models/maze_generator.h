//
//  maze_generator.h
//
//
//  Created by Angelena Piece on 19 February 2024
//

#ifndef MAZE_MODEL_MAZE_GENERATOR_H
#define MAZE_MODEL_MAZE_GENERATOR_H

#include <iostream>
#include <vector>
#include <cstddef>

#include "random_generator.h"
#include "cell_friends_interface.h"
#include "maze.h"
#include "maze_console_view.h"

namespace s21::model::generator {

    class CellFriends : public CellFriendsInterface {
        public:
            CellFriends() {}
            CellFriends(std::size_t rows, std::size_t cols) {
                initialize(rows, cols);
            }
            ~CellFriends() {
               utilize();
            }
            void Reset(std::size_t rows, std::size_t cols) {
                utilize();
                initialize(rows, cols);
            }

            std::size_t Rows() const {
                return rows_;
            }

            std::size_t Cols() const {
                return cols_;
            }

            std::size_t Number(std::size_t row, std::size_t col) const {
                return at(row, col);
            }

            bool HasFriends(std::size_t row, std::size_t col) const {
                return at(row, col) != 0;
            }

            bool IsFriends(std::size_t row1, std::size_t col1, std::size_t row2, std::size_t col2) const {
                return at(row1, col1) == at(row2, col2);
            }

            virtual void Alone(std::size_t row, std::size_t col) {
                at(row, col) = 0;
            }

            void MakeLeader(std::size_t row, std::size_t col) {
                at(row, col) = counter_++;
            }

            void MakeFriends(std::size_t row1, std::size_t col1, std::size_t row2, std::size_t col2) {
                if (!HasFriends(row1, col1)) {
                    MakeLeader(row1, col1);
                }
                at(row2,col2) = at(row1, col1);
            }

            void MakeAllFriends(std::size_t row1, std::size_t col1, std::size_t row2, std::size_t col2) {
                std::vector<std::pair<std::size_t, std::size_t>> friends2 = GetFriends(row2, col2);
                std::vector<std::pair<std::size_t, std::size_t>>::const_iterator friend2 = friends2.cbegin();
                while(friend2 != friends2.cend()) {
                    MakeFriends(row1, col1, std::get<0>(*friend2), std::get<1>(*friend2));
                    friend2++;
                }
            }

            std::vector<std::pair<std::size_t, std::size_t>> GetFriends(std::size_t row, std::size_t col) const {
                std::vector<std::pair<std::size_t, std::size_t>> friends(0);
                if (HasFriends(row, col)) {
                    for (size_t col_ = 0; col_ < cols_; col_++)
                    {
                        if (IsFriends(row, col, row, col_)) {
                            friends.push_back(std::make_pair(row, col_));
                        }
                    }
                }
                return friends;
            }

        private:
            void initialize(std::size_t rows, std::size_t cols) {
                counter_ = 1;
                rows_ = rows;
                cols_ = cols;
                cells_ = new std::size_t[rows_ * cols_]();
            }
            void utilize() {
                if (cells_ != nullptr) {
                    delete cells_;
                    cells_ = nullptr;
                }
            }
            std::size_t at(std::size_t row, std::size_t col) const {
                if (rows_ <= row || cols_ <= col) {
                    throw std::out_of_range("CellFriends::at(...) const: out of range");
                }
                return cells_[row * cols_ + col];
            }
            std::size_t& at(std::size_t row, std::size_t col) {
                if (rows_ <= row || cols_ <= col) {
                    throw std::out_of_range("&CellFriends::at(...): out of range");
                }
                return cells_[row * cols_ + col];
            }

        private:
            std::size_t counter_ = 1;
            std::size_t rows_ = 0;
            std::size_t cols_ = 0;
            std::size_t *cells_ = nullptr;
    };

    class MazeGenerator {
        public:
            MazeGenerator(std::size_t rows, std::size_t cols) {
               initialize(rows, cols); 
            }
            ~MazeGenerator() {
               utilize(); 
            }

            void Generate(std::size_t rows = 0, std::size_t cols = 0) {
                if (rows != 0 && cols != 0) {
                    reset(rows, cols);
                } else {
                    clear();
                }
                auto generator = s21::model::utils::generator::RandomNumberGenerator((int)0, (int)1);
                
                // 1. (DONE) Create the first row. No cells will be members of any set
                for (size_t row = 0; row < rows_; row++)
                {
                    // 2. Join any cells not members of a set to their own unique set
                    for (size_t col = 0; col < cols_; col++)
                    {                        
                        if (!cells_.HasFriends(row, col)) {
                            cells_.MakeLeader(row, col);
                        }
                    }

                    // 3. Create right-walls, moving from left to right:
                    // Randomly decide to add a wall or not
                    //      If the current cell and the cell to the right are members of the same set, always create a wall between them. (This prevents loops)
                    //      If you decide not to add a wall, union the sets to which the current cell and the cell to the right are members.
                    for (size_t col = 0; col < cols_ - 1; col++)
                    {              
                        bool rightWall = (bool)generator.NextInteger();
                        if (rightWall || cells_.IsFriends(row, col, row, col + 1)) {
                            setRigthWall(row, col);
                        } else {
                            cells_.MakeAllFriends(row, col, row, col + 1);
                        }
                    }

                    // 4. bottom walls
                    // Create bottom-walls, moving from left to right:
                    //     Randomly decide to add a wall or not. Make sure that each set has at least one cell without a bottom-wall (This prevents isolations)
                    //     If a cell is the only member of its set without a bottom-wall, do not create a bottom-wall
                    for (size_t col = 0; col < cols_; col++)
                    {
                        bool bottomWall = (bool)generator.NextInteger();
                        if (bottomWall && !isolatedCellGroup(row, col)) {
                            setBottomWall(row, col);
                        }
                    }

                    // 5. Decide to keep adding rows, or stop and complete the maze
                    // A. If you decide to add another row:
                    //      Output the current row
                    //      Remove all right walls
                    //      Remove cells with a bottom-wall from their set
                    //      Remove all bottom walls
                    //      Continue from Step 2
                    if (row + 1 < rows_) {
                        for (size_t col = 0; col < cols_; col++)
                        {
                            cells_.MakeFriends(row, col, row + 1, col);
                            if (hasBottomWall(row, col)) {
                                cells_.Alone(row + 1, col);
                            }
                        }
                    } else {
                        break;
                    }
                }
                // 5B. If you decide to complete the maze
                //      Add a bottom wall to every cell
                //      Moving from left to right:
                //          If the current cell and the cell to the right are members of a different set:
                //              Remove the right wall
                //              Union the sets to which the current cell and cell to the right are members.
                //              Output the final row
                for (size_t col = 0; col < cols_; col++)
                {
                    setBottomWall(rows_ - 1, col);
                    if (col + 1 < cols_ && !cells_.IsFriends(rows_ - 1, col, rows_ - 1, col + 1)) {
                        removeRightWall(rows_ - 1, col);
                        cells_.MakeAllFriends(rows_ - 1, col, rows_ - 1, col + 1);
                    }
                }
            }

            MazeData Get() const {
                return MazeData(rows_, cols_, rightWalls_, bottomWalls_);
            }

            void Preview() {
                MazeConsoleView view(&cells_, rightWalls_, bottomWalls_, rows_, cols_, 3, true);
                view.Render();
            }

        private:
            void initialize(std::size_t rows, std::size_t cols) {
                rows_ = rows;
                cols_ = cols;
                cells_.Reset(rows_, cols_);
                rightWalls_ = new bool[rows_ * cols_];
                bottomWalls_ = new bool[rows_ * cols_];
            }
            void utilize() {
                if (rightWalls_ != nullptr) {
                    delete rightWalls_;
                    rightWalls_ = nullptr;
                }
                if (bottomWalls_ != nullptr) {
                    delete bottomWalls_;
                    bottomWalls_ = nullptr;
                }
                cells_.~CellFriends();
            }

            void reset(std::size_t rows, std::size_t cols) {
                utilize();
                initialize(rows, cols);
            }
            void clear() {
                for (size_t row = 0; row < rows_; row++)
                {
                    for (size_t col = 0; col < cols_; col++)
                    {
                        removeRightWall(row, col);
                        removeBottomWall(row, col);
                    }
                }
            }
            bool at(bool *walls, std::size_t row, std::size_t col) const {
                if (rows_ <= row || cols_ <= col) {
                    throw std::out_of_range("Maze::at(...) const");
                }
                return walls[row * cols_ + col];
            }
            bool& at(bool *walls, std::size_t row, std::size_t col) {
                if (rows_ <= row || cols_ <= col) {
                    throw std::out_of_range("&Maze::at(...)");
                }
                return walls[row * cols_ + col];
            }
            bool hasRightWall(std::size_t row, std::size_t col) const {
                return at(rightWalls_, row, col);
            }
            bool hasBottomWall(std::size_t row, std::size_t col) const {
                return at(bottomWalls_, row, col);
            }
            void setRigthWall(std::size_t row, std::size_t col) {
                at(rightWalls_, row, col) = true;
            }
            void setBottomWall(std::size_t row, std::size_t col) {
                at(bottomWalls_, row, col) = true;
            }
            void removeRightWall(std::size_t row, std::size_t col) {
                at(rightWalls_, row, col) = false;
            }
            void removeBottomWall(std::size_t row, std::size_t col) {
                at(bottomWalls_, row, col) = false;
            }

            bool isolatedCellGroup(std::size_t row, std::size_t col) const {
                auto friends = cells_.GetFriends(row, col);
                std::size_t bottomWallCount = 0;
                if (friends.size() > 1) {
                    for (auto & cellFriend : friends) {
                        if (hasBottomWall(std::get<0>(cellFriend), std::get<1>(cellFriend))) {
                            bottomWallCount++;
                        }
                    }
                }
                return friends.size() == 1 || friends.size() - bottomWallCount == 1;
            }

        private:
            CellFriends cells_;
            std::size_t rows_, cols_;
            bool *rightWalls_ = nullptr;
            bool *bottomWalls_ = nullptr;
    };
}

#endif  // MAZE_MODEL_MAZE_GENERATOR_H