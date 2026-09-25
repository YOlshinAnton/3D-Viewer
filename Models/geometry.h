#ifndef MODELS_GEOMETRY_H
#define MODELS_GEOMETRY_H

#include <cmath>
#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <vector>

#include "geometry_elements.h"
#include "geometry_glstate.h"
#include "geometry_normalization_parameters.h"
#include "geometry_normalization_parameters_builder.h"

namespace s21 {

/**
 * @brief MVC Модель. Представляет Wavefront 3D модель и предоставлятет
 * трансформации над моделью
 */
class Geometry {
 public:
  /**
   * @brief Конструктор по умолчанию. Не осуществляет инициализации модели
   */
  Geometry();

  /**
   * @brief Конструктор инициализирующий модель заданным состоянием
   * @param vertices - набор вершин модели
   * @param facets - набор граней
   */
  Geometry(std::vector<Vertex> &vertices, std::vector<Facet> &facets);

  /**
   * @brief Конструктор инициализирующий модель из потока
   * @param is - поток для чтения модели
   */
  Geometry(std::istream &is);

  /**
   * @brief Загрузка модели из указанного потока
   * @param is - поток для чтения
   */
  void Load(std::istream &is);

  /**
   * @brief Запись модели в поток
   * @param os - поток для записи
   */
  void Save(std::ostream &os);

  /**
   * @brief Нормализовать размеры и положение модели
   */
  void Normalize();

  /**
   * @brief Масштабировать модель
   * @param k - коэффициент масштабирования
   */
  void Scale(double k);

  /**
   * @brief Вращени модели по заданым осям
   * @param yaw - угол вращения по оси X
   * @param pitch - угол вращения по оси Y
   * @param roll - угол вращения по оси Z
   */
  void Rotate(double yaw, double pitch, double roll);

  /**
   * @brief Перемещение модели в направлении указанных осей
   * @param dx - величина сдвига по оси X
   * @param dy - величина сдвига по оси Y
   * @param dz - величина сдвига по оси Z
   */
  void Translate(double dx, double dy, double dz);

  /**
   * @brief Состояние модели в формате OpenGL
   * @return состояние модели (указатель на набор вершин и указатель на набор
   * ребер)
   */
  const GeometryGLState &GetGLState() const;

 private:
  void init();

 private:
  s21::GeometryNormalizationParameters params_;
  std::vector<Vertex> vertices_;
  std::vector<Facet> facets_;
  // GL
  s21::GeometryGLState glState_;
  std::vector<unsigned int> facetLoops_;
};

}  // namespace s21

#endif  // MODELS_GEOMETRY_H
