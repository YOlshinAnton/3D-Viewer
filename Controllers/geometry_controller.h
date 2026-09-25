#ifndef CONTROLLERS_GEOMETRY_CONTROLLER_H
#define CONTROLLERS_GEOMETRY_CONTROLLER_H

#include <fstream>
#include <iostream>

#include "geometry.h"
#include "geometry_controller_interface.h"
#include "geometry_defaults.h"
#include "geometry_observer.h"
#include "geometry_subject.h"

namespace s21 {

/**
 * @brief MVC Контроллер. Отвечает за манипуляции над моделью и предоставляет
 * логику наблюдения за состояним модели
 */
class GeometryController : public GeometryControllerInterface {
 public:
  GeometryController(Geometry *geometry);
  ~GeometryController();

  void LoadGeometry(std::string filename);

  void ObserveGeometry(GeometryObserver *observer);
  const GeometryGLState &GetGeometryGLState() const;

  void Scale(double k);

  void Rotate(double yaw, double pitch, double roll);
  inline void Rotate_X(double yaw);
  inline void Rotate_Y(double pitch);
  inline void Rotate_Z(double roll);

  void Move(double dx, double dy, double dz);
  inline void Move_X(double dx);
  inline void Move_Y(double dy);
  inline void Move_Z(double dz);

 private:
  Geometry *geometry_;
  GeometryGLSubject *subject_;
};

}  // namespace s21

#endif  // CONTROLLERS_GEOMETRY_CONTROLLER_H
