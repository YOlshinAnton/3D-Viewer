#ifndef MODELS_GEOMETRY_NORMALIZATION_PARAMETERS_BUILDER_H
#define MODELS_GEOMETRY_NORMALIZATION_PARAMETERS_BUILDER_H

#include "geometry_elements.h"
#include "geometry_normalization_parameters.h"
#include "geometry_normalization_parameters_builder_interface.h"

#define S21_FIGURE_DEFAULT_SCALE 1.0

namespace s21 {

/**
 * @brief Паттерн строитель параметров нормализации модели.
 */
class GeometryNormalizationParametersBuilder
    : public GeometryNormalizationParametersBuilderInterface {
  using self = GeometryNormalizationParametersBuilder;

 public:
  GeometryNormalizationParametersBuilder();

  /**
   * @brief Build Инициализация параметров масштабирования
   * @return
   */
  GeometryNormalizationParameters Build();

  /**
   * @brief Определить размеры модели по заданному набору ее вершин
   * @param vertices - набор вершин модели
   * @param scale - коэффициент масштабирования модели
   * @return
   */
  self* FigureSize(const std::vector<Vertex>& vertices,
                   double scale = S21_FIGURE_DEFAULT_SCALE);

  /**
   * @brief Задать масштаб модели
   * @param scale - коэффициент масштабирования модели
   * @return
   */
  self* FigureScale(double scale);

  double GetFigureMaxX() const;
  double GetFigureMinX() const;
  double GetFigureMaxY() const;
  double GetFigureMinY() const;
  double GetFigureMaxZ() const;
  double GetFigureMinZ() const;
  double GetFigureScale() const;
  double GetFigureMaxComponent() const;
  double GetFigureMinComponent() const;

 private:
  double figureMaxX_, figureMinX_;
  double figureMaxY_, figureMinY_;
  double figureMaxZ_, figureMinZ_;
  double figureMaxComponent_, figureMinComponent_;
  double figureScale_ = S21_FIGURE_DEFAULT_SCALE;
};

}  // namespace s21

#undef S21_DEFAULT_SCALE

#endif  // MODELS_GEOMETRY_NORMALIZATION_PARAMETERS_BUILDER_H
