//
//  maze.h
//
//
//  Created by Angelena Piece on 23 February 2024
//

#ifndef MAZE_MODEL_MAZE_CONSOLE_VIEW_H
#define MAZE_MODEL_MAZE_CONSOLE_VIEW_H

#include <iostream>
#include <string>

#include "view_interface.h"
#include "cell_friends_interface.h"

namespace s21::model {

class MazeConsoleView : ViewInterface {
    public:
        MazeConsoleView(const CellFriendsInterface *cells, const bool * const rightWalls, const bool * const bottomWalls, std::size_t rows, std::size_t cols, std::size_t scale = 2, bool cellGroups = false) : 
            cells_(cells), rightWalls_(rightWalls), bottomWalls_(bottomWalls), rows_(rows), cols_(cols) {
                if (scale < 1) {
                    throw std::out_of_range("scale be equal or gteater than 1");
                }
                cellGroups_ = cellGroups;
                vcfactor = scale;
                hcfactor = 3 * scale;
                std::cout << rows_ << ' ' << cols_ <<std::endl;
            }

        void Render() const {
            framehline();
            for (size_t row = 0; row < rows_; row++)
            {
                line(row);
            }
            framehline();
        }
    private:
        std::string hwall(bool frame = false) const {
            if (frame) {
                return std::string(hcfactor + 1, wch_);
            }
            return std::string(hcfactor, wch_);
        }
        std::string vwall() const {
            return std::string(1, wch_);
        }
        std::string nowall() const {
            return std::string(1, fch_);
        }
        std::string hcell() const {
            return std::string(hcfactor, fch_);
        }
        std::string hcell(std::size_t row, std::size_t col) const {
            std::string number = std::to_string(cells_->Number(row, col));
            std::string cell_space;
            std::size_t pre_space = (hcfactor - number.size()) / 2;
            std::size_t pst_space = (hcfactor - number.size()) % 2 == 1 ? pre_space + 1 : pre_space;

            cell_space = std::string(pre_space, fch_) + number + std::string(pst_space, fch_);
            
            if (hcfactor != cell_space.size()) {
                return hcell();
            }
            return cell_space;
        }
        void framehline() const {
            std::cout << vwall();
            for (size_t col = 0; col < cols_; col++)
            {
                std::cout << hwall(true);   
            }
            std::cout << std::endl;
        }

        void line(std::size_t row) const {
            for (size_t sect = 0; sect < vcfactor; sect++)
            {
                std::cout << vwall();
                for (size_t col = 0; col < cols_; col++)
                {
                    if (cellGroups_ && sect == vcfactor / 2) {
                        std::cout << hcell(row, col);
                    } else {
                       std::cout << hcell(); 
                    }
                    if (at(rightWalls_, row, col) || col + 1 == cols_) {
                        std::cout << vwall();
                    } else {
                        std::cout << nowall();
                    }
                }
                std::cout << std::endl;
            }
            if (row + 1 != rows_) {
                    std::cout << vwall(); 
                    for (size_t col = 0; col < cols_; col++)
                    {
                        if (at(bottomWalls_, row, col)) {
                            std::cout << hwall(true);
                        } else {
                            std::cout << hcell();
                            std::cout << vwall();
                        }
                    }
                    std::cout << std::endl;
                }
        }
    private:
        bool at(const bool * const walls, std::size_t row, std::size_t col) const {
            if (rows_ <= row || cols_ <= col) {
                throw std::out_of_range("Maze::at(...) const");
            }
            return walls[row * cols_ + col];
        }

    private:
        bool cellGroups_ = false;
        char wch_ = '#';
        char fch_ = ' ';
        std::size_t hcfactor = 3;
        std::size_t vcfactor = 1;

        std::size_t rows_ = 0, cols_ = 0;
        const bool * const rightWalls_;
        const bool * const bottomWalls_;
        const CellFriendsInterface *cells_;
};

}

#endif  // MAZE_MODEL_MAZE_CONSOLE_VIEW_H