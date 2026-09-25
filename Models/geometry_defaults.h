#ifndef GEOMETRYDEFAULTS_H
#define GEOMETRYDEFAULTS_H

#include "geometry.h"

namespace s21 {

/**
 * @brief Набор примеров
 */
class GeometryDefaults {
 public:
  /**
   * @brief Модель куба
   * @return
   */
  static Geometry Cube();

  /**
   * @brief Модель утки
   * @return
   */
  static Geometry Duck();
};

}  // namespace s21

#endif  // GEOMETRYDEFAULTS_H
