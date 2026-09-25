#include "geometry_normalization_parameters_builder.h"

s21::GeometryNormalizationParametersBuilder::
    GeometryNormalizationParametersBuilder() {}

s21::GeometryNormalizationParameters
s21::GeometryNormalizationParametersBuilder::Build() {
  return GeometryNormalizationParameters(this);
}

s21::GeometryNormalizationParametersBuilder*
s21::GeometryNormalizationParametersBuilder::FigureSize(
    const std::vector<s21::Vertex>& vertices, double scale) {
  auto compX = [](const auto a, const auto b) { return a.x < b.x; };
  auto maxXVertex = std::max_element(vertices.begin(), vertices.end(), compX);
  auto minXVertex = std::min_element(vertices.begin(), vertices.end(), compX);

  auto compY = [](const auto a, const auto b) { return a.y < b.y; };
  auto maxYVertex = std::max_element(vertices.begin(), vertices.end(), compY);
  auto minYVertex = std::min_element(vertices.begin(), vertices.end(), compY);

  auto compZ = [](const auto a, const auto b) { return a.z < b.z; };
  auto maxZVertex = std::max_element(vertices.begin(), vertices.end(), compZ);
  auto minZVertex = std::min_element(vertices.begin(), vertices.end(), compZ);
  figureMaxX_ = maxXVertex->x;
  figureMinX_ = minXVertex->x;
  figureMaxY_ = maxYVertex->y;
  figureMinY_ = minYVertex->y;
  figureMaxZ_ = maxZVertex->z;
  figureMinZ_ = minZVertex->z;
  figureMaxComponent_ = std::max({figureMaxX_, figureMaxY_, figureMaxZ_});
  figureMinComponent_ = std::min({figureMinX_, figureMinY_, figureMinZ_});
  figureScale_ = scale;
  return this;
}

s21::GeometryNormalizationParametersBuilder*
s21::GeometryNormalizationParametersBuilder::FigureScale(double scale) {
  figureScale_ = scale;
  return this;
}

double s21::GeometryNormalizationParametersBuilder::GetFigureMaxX() const {
  return figureMaxX_;
}

double s21::GeometryNormalizationParametersBuilder::GetFigureMinX() const {
  return figureMinX_;
}

double s21::GeometryNormalizationParametersBuilder::GetFigureMaxY() const {
  return figureMaxY_;
}

double s21::GeometryNormalizationParametersBuilder::GetFigureMinY() const {
  return figureMinY_;
}

double s21::GeometryNormalizationParametersBuilder::GetFigureMaxZ() const {
  return figureMaxZ_;
}

double s21::GeometryNormalizationParametersBuilder::GetFigureMinZ() const {
  return figureMinZ_;
}

double s21::GeometryNormalizationParametersBuilder::GetFigureScale() const {
  return figureScale_;
}

double s21::GeometryNormalizationParametersBuilder::GetFigureMaxComponent()
    const {
  return figureMaxComponent_;
}

double s21::GeometryNormalizationParametersBuilder::GetFigureMinComponent()
    const {
  return figureMinComponent_;
}
