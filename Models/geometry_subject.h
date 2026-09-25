#ifndef MODESL_GEOMETRY_SUBJECT_H
#define MODESL_GEOMETRY_SUBJECT_H

#include "geometry.h"
#include "geometry_observer.h"

namespace s21 {

/**
 * @brief Интерфейс представителя наблюдаемой модели
 */
class GeometrySubject {
 public:
  virtual ~GeometrySubject();

  /**
   * @brief Attach Регистрация нового наблюдателя
   * @param observer - наблюдатель
   */
  virtual void Attach(GeometryObserver *observer) = 0;

  /**
   * @brief Detach Исключить указанного наблюдателя
   * @param observer - наблюдатель
   */
  virtual void Detach(GeometryObserver *observer) = 0;

  /**
   * @brief Update Уведомление всех наблюдателей
   * @param message - состояние модели
   */
  virtual void Update(void *message) = 0;

 protected:
  std::vector<GeometryObserver *> observers_;
};

/**
 * @brief OpenGL реализации представителя наблюдаемой модели
 */
class GeometryGLSubject : public GeometrySubject {
 public:
  GeometryGLSubject(Geometry *geometry);
  ~GeometryGLSubject();
  void Attach(GeometryObserver *observer) override;
  void Detach(GeometryObserver *observer) override;
  void Update(void *message) override;

 private:
  Geometry *geometry_;
};

}  // namespace s21

#endif  // MODESL_GEOMETRY_SUBJECT_H
