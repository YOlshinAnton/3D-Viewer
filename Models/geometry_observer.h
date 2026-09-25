#ifndef MODELS_GEOMETRY_OBSERVER_H
#define MODELS_GEOMETRY_OBSERVER_H

#include "geometry_glstate.h"

namespace s21 {

/**
 * @brief Интерфейс наблюдателя состояния 3D модели
 */
class GeometryObserver {
 public:
  /**
   * @brief Update Обновить состояние обсервера
   * @param message - сообщение об изменении состояния
   */
  virtual void Update(void* message) = 0;
};

/**
 * @brief Интерфейс наблюдателя OpenGL состояния 3D модели
 */
class GeometryGLStateObserver : public GeometryObserver {
 public:
  /**
   * @brief Update Обновить состояние обсервера
   * @param message - сообщение об изменении состояния
   */
  void Update(void* message) override;

  /**
   * @brief Update Обновить состояние обсервера
   * @param state - состояние модели в формате OpenGL
   */
  virtual void Update(GeometryGLState* state) = 0;
};

}  // namespace s21

#endif  // MODELS_GEOMETRY_OBSERVER_H
