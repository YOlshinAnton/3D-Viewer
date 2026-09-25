#ifndef CONTROLLERS_GEOMETRY_CONTROLLER_INTERFACE_H
#define CONTROLLERS_GEOMETRY_CONTROLLER_INTERFACE_H

#include <string>

#include "geometry_glstate.h"
#include "geometry_observer.h"

namespace s21 {

/**
 * @brief Интерфейс контроллера GeometryController.
 */
class GeometryControllerInterface {
 public:
  virtual ~GeometryControllerInterface();
  /**
   * @brief Выполнить загрузку модели
   * @param filename - путь к файлу модели формата OBJ
   */
  virtual void LoadGeometry(std::string filename) = 0;

  /**
   * @brief Зарегистрировать обсервера модели
   * @param observer - объект зависимый от изменений модели
   */
  virtual void ObserveGeometry(GeometryObserver* observer) = 0;

  /**
   * @brief Получить состояние модели в формате OpenGL
   * @return Состояни модели в формате GL
   */
  virtual const GeometryGLState& GetGeometryGLState() const = 0;

  /**
   * @brief Масштабировать модель
   * @param k - коэффициент масштабирования
   */
  virtual void Scale(double k) = 0;

  /**
   * @brief Вращение модели по заданым осям
   * @param yaw - угол вращения по оси X
   * @param pitch - угол вращения по сои Y
   * @param roll - угол вращения по оси Z
   */
  virtual void Rotate(double yaw, double pitch, double roll) = 0;

  /**
   * @brief Вращение модели по оси X
   * @param yaw - угол вращения
   */
  virtual void Rotate_X(double yaw) = 0;

  /**
   * @brief Вращение модели по оси Y
   * @param pitch - угол вращения
   */
  virtual void Rotate_Y(double pitch) = 0;

  /**
   * @brief Вращение модели по оси Z
   * @param roll - угол вращения
   */
  virtual void Rotate_Z(double roll) = 0;

  /**
   * @brief Перемещение модели в напралении заданных осей
   * @param dx - величина сдвига по оси X
   * @param dy - величина сдвига по оси Y
   * @param dz - величина сдвига по оси Z
   */
  virtual void Move(double dx, double dy, double dz) = 0;

  /**
   * @brief Перемещение модели в направлении оси X
   * @param dx - величина сдвига
   */
  virtual void Move_X(double dx) = 0;

  /**
   * @brief Перемещение модели в направлении оси Y
   * @param dy - величина сдвига
   */
  virtual void Move_Y(double dy) = 0;

  /**
   * @brief Перемещение модели в направлении оси Z
   * @param dz - величина сдвига
   */
  virtual void Move_Z(double dz) = 0;
};

}  // namespace s21

#endif  // CONTROLLERS_GEOMETRY_CONTROLLER_INTERFACE_H
