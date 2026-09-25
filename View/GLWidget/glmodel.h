#ifndef GLWIDGET_GLMODEL_H
#define GLWIDGET_GLMODEL_H

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

#include <QFile>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QPixmap>
#include <QSettings>
#include <QTimer>
#include <iostream>

#include "geometry_observer.h"
#include "glmodel_projection.h"

namespace s21 {
namespace UI {
/**
 * @brief Класс представляющий логику отрисовки сцены
 */
class glModel : public QOpenGLWidget, public s21::GeometryGLStateObserver {
 public:
  const void* v;
  const void* f;
  unsigned int v_count, f_count;

  int edges_type;
  int vertice_type;
  float edges_r, edges_g, edges_b, edges_width;
  float vertice_r, vertice_g, vertice_b, vertice_size;
  float backgr_r, backgr_g, backgr_b;

  float xRot, yRot, zRot, xcopyRot, ycopyRot;
  double xPos, yPos, zPos, scale, xR, yR, zR;

  explicit glModel(QWidget* parent = 0);
  ~glModel();
  /**
   * @brief Очистка параметров модели
   */
  void paramsClearing();

  /**
   * @brief Инициализация GL модели
   */
  void initializeGL() override;
  /**
   * @brief Задание размера окна просмотра модели
   * @param w - ширина окна просмотра
   * @param w - высота окна просмотра
   */
  void resizeGL(int w, int h) override;
  /**
   * @brief Отрисовка модели
   */
  void paintGL() override;

  /**
   * @brief Наблюдатель за состоянием модели.
   */
  void Update(s21::GeometryGLState* state) override;

  /**
   * @brief Установка стратегии перспективы на ortho
   */
  void SetOrthoProjection() {
    context->SetStrategy(new s21::UI::OrthoProjection());
  }

  /**
   * @brief Установка стратегии перспективы на frustrum
   */
  void SetFrustrumProjection() {
    context->SetStrategy(new s21::UI::FrustrumProjection());
  }

  /**
   * @brief Применение перспективы
   */
  void glApplyProjection() { context->ExecuteStrategy(); }

 private:
  QPoint mousePos;
  void mousePressEvent(QMouseEvent*) override;
  void mouseMoveEvent(QMouseEvent*) override;
  void mouseReleaseEvent(QMouseEvent*) override;
  QSettings* settings;
  s21::UI::Context* context =
      new s21::UI::Context(new s21::UI::OrthoProjection());
};
}  // namespace UI

}  // namespace s21
#endif  // GLWIDGET_GLMODEL_H
