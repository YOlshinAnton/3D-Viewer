#ifndef MODELS_GEOMETRY_NORMALIZATION_PARAMETERS_H
#define MODELS_GEOMETRY_NORMALIZATION_PARAMETERS_H

#include "geometry_normalization_parameters_builder_interface.h"

namespace s21 {

/**
 * @brief Набор параметров нормализации модели
 */
class GeometryNormalizationParameters {
 public:
  GeometryNormalizationParameters();
  GeometryNormalizationParameters(
      GeometryNormalizationParametersBuilderInterface *builder);

  double FigureMaxX;
  double FigureMinX;
  double FigureMaxY;
  double FigureMinY;
  double FigureMaxZ;
  double FigureMinZ;
  double FigureMaxComponent;
  double FigureMinComponent;
  double FigureScale = 1.0;
};

}  // namespace s21

#endif  // MODELS_GEOMETRY_NORMALIZATION_PARAMETERS_H
