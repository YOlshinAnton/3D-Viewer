//
//  maze.h
//
//
//  Created by Angelena Piece on 24 February 2024
//

#ifndef MAZE_MODEL_VIEW_INTERFACE_H
#define MAZE_MODEL_VIEW_INTERFACE_H

namespace s21::model {

class ViewInterface {
    public:
        virtual void Render() const = 0;
};

}

#endif  // MAZE_MODEL_VIEW_INTERFACE_H