//
//  cave_reader.h
//
//
//  Created by Антон Ёлшин on 02.01.2024.
//  Changed by Антон Ёлшин on 14.03.2024.
//

#ifndef MLP_MLP_MLP_DATASET_READER_H
#define MLP_MLP_MLP_DATASET_READER_H

#include <vector>
#include <set>
#include <tuple>

#include "geometry_elements.h"
#include "geometry.h"
#include "cave.h"
#include "maze.h"

namespace s21::model::converter {

/// @brief Интерфейс. Метод конвертации из объекта типа TIn в объект TOut.
/// @tparam TIn 
/// @tparam TOut 
template<typename TOut, typename TIn>
class ConverterMethodInterface
{
public:
    /// @brief 
    virtual TOut Convert(const TIn& obj) const = 0;
};

class GeometryConverter : 
    public ConverterMethodInterface<Geometry, CaveData>,
    public ConverterMethodInterface<Geometry, MazeData> {
public:
    Geometry Convert(const CaveData& obj) const {
        std::vector<s21::Vertex> verteces;
        std::vector<s21::Facet> facets;

        facets.push_back(Facet { std::vector<unsigned int>{ 1, 2, 2, 4, 4, 3, 3, 1 } });
        verteces.push_back(Vertex { (double)0, (double)0, .0 });
        verteces.push_back(Vertex { (double)0, (double)obj.Cols(), .0 });
        verteces.push_back(Vertex { (double)obj.Rows(), (double)0, .0 });
        verteces.push_back(Vertex { (double)obj.Rows(), (double)obj.Cols(), .0 });

        for (size_t row = 0; row < obj.Rows(); row++)
        {
            for (size_t col = 0; col < obj.Cols(); col++)
            {
                if (!obj.at(row, col)) {
                    unsigned int no = (unsigned int) verteces.size() + 1;
                    facets.push_back(Facet { std::vector<unsigned int>{ no, no + 1, no + 2, no + 3 } });
                    verteces.push_back(Vertex { (double)row, (double)col, .0 });
                    verteces.push_back(Vertex { (double)row, (double)col + 1, .0 });
                    verteces.push_back(Vertex { (double)row + 1, (double)col, .0 });
                    verteces.push_back(Vertex { (double)row + 1, (double)col + 1, .0 });
                }
            }
        }
        return s21::Geometry(verteces, facets);
    }

    Geometry Convert(const MazeData& obj) const {
        std::vector<s21::Vertex> verteces;
        std::vector<s21::Facet> facets;

        facets.push_back(Facet { std::vector<unsigned int>{ 1, 2, 2, 4, 4, 3, 3, 1 } });
        verteces.push_back(Vertex { (double)0, (double)0, .0 });
        verteces.push_back(Vertex { (double)0, (double)obj.Cols(), .0 });
        verteces.push_back(Vertex { (double)obj.Rows(), (double)0, .0 });
        verteces.push_back(Vertex { (double)obj.Rows(), (double)obj.Cols(), .0 });

        unsigned int facet_no = verteces.size();
        for (size_t row = 0; row < obj.Rows(); row++)
        {
            for (size_t col = 0; col < obj.Cols(); col++)
            {
                if (obj.at(row, col, MazeData::MazeDataAccessor::RightWall)) {
                    facets.push_back(Facet { std::vector<unsigned int>{
                        (unsigned int)facet_no + 1, (unsigned int)facet_no + 2 }
                    });
                    verteces.push_back(Vertex { (double)row, (double)col + 1, .0 });
                    verteces.push_back(Vertex { (double)row + 1, (double)col + 1, .0 });
                    facet_no += 2;
                }
                if (obj.at(row, col, MazeData::MazeDataAccessor::BottomWall)) {
                    facets.push_back(Facet { std::vector<unsigned int>{
                        (unsigned int)facet_no + 1, (unsigned int)facet_no + 2 }
                    }); verteces.push_back(Vertex { (double)row + 1, (double)col, .0 });
                    verteces.push_back(Vertex { (double)row + 1, (double)col + 1, .0 });
                    facet_no += 2;
                }
            }
        }
        return s21::Geometry(verteces, facets);
    }
};

}

#endif  // MLP_MLP_MLP_DATASET_READER_H
