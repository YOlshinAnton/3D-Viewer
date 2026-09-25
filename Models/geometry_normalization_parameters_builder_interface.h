#ifndef MODELS_GEOMETRY_NORMALIZATION_PARAMETERS_BUILDER_INTERFACE_H
#define MODELS_GEOMETRY_NORMALIZATION_PARAMETERS_BUILDER_INTERFACE_H

namespace s21 {

/**
 * @brief Интерфейс строителя параметров нормализации модели
 */
class GeometryNormalizationParametersBuilderInterface {
 public:
  virtual double GetFigureMaxX() const = 0;
  virtual double GetFigureMinX() const = 0;
  virtual double GetFigureMaxY() const = 0;
  virtual double GetFigureMinY() const = 0;
  virtual double GetFigureMaxZ() const = 0;
  virtual double GetFigureMinZ() const = 0;
  virtual double GetFigureMaxComponent() const = 0;
  virtual double GetFigureMinComponent() const = 0;
  virtual double GetFigureScale() const = 0;
};

}  // namespace s21
#endif  // MODELS_GEOMETRY_NORMALIZATION_PARAMETERS_BUILDER_INTERFACE_H
