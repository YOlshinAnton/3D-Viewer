#include "geometry_normalization_parameters.h"

s21::GeometryNormalizationParameters::GeometryNormalizationParameters() {}

s21::GeometryNormalizationParameters::GeometryNormalizationParameters(
    s21::GeometryNormalizationParametersBuilderInterface* builder) {
  FigureMaxX = builder->GetFigureMaxX();
  FigureMaxX = builder->GetFigureMinX();
  FigureMaxY = builder->GetFigureMaxY();
  FigureMinY = builder->GetFigureMinY();
  FigureMaxZ = builder->GetFigureMaxZ();
  FigureMinZ = builder->GetFigureMinZ();
  FigureMaxComponent = builder->GetFigureMaxComponent();
  FigureMinComponent = builder->GetFigureMinComponent();
  FigureScale = builder->GetFigureScale();
}
