#ifndef MODELS_GEOMETRY_GLSTATE_H
#define MODELS_GEOMETRY_GLSTATE_H

namespace s21 {

/**
 * @brief Представление состояния модели в формате OpenGL
 */
class GeometryGLState {
 public:
  const double* Vertices;
  int VertexCount;
  int FacetCount;
  const unsigned* FacetElements;
  int FacetElementCount;
};

}  // namespace s21

#endif  // MODELS_GEOMETRY_GLSTATE_H
