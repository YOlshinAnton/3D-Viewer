#ifndef MODELS_GEOMETRY_ELEMENTS_H
#define MODELS_GEOMETRY_ELEMENTS_H

#include <vector>

namespace s21 {

/**
 * @brief Представление вершины модели
 */
class Vertex {
 public:
  double x, y, z;
};

/**
 * @brief Представление грани модели
 */
class Facet {
 public:
  /**
   * @brief vertices - набор вершин состовляющих грань
   */
  std::vector<unsigned int> vertices;
};

}  // namespace s21

#endif  // MODELS_GEOMETRY_ELEMENTS_H
