#ifndef VIEW_MAINWINDOW_H
#define VIEW_MAINWINDOW_H

#include <qgifimage.h>

#include <QMainWindow>

#include "geometry_controller_interface.h"
#include "glmodel.h"

QT_BEGIN_NAMESPACE
using namespace s21::UI;
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {
namespace UI {
/**
 * @brief Логика интерфейса главного окна
 */
class MainWindow : public QMainWindow, public GeometryGLStateObserver {
  Q_OBJECT

 public:
  /**
   * @brief Инициализация главного окна
   */
  MainWindow(s21::GeometryControllerInterface *ctrl);
  ~MainWindow();

  /**
   * @brief Обсервер состояния модели. Обновляет отображаемые параметры модели
   */
  void Update(GeometryGLState *modelState);

 private slots:
  /**
   * @brief Загрузка модели
   */
  void Load();

  /**
   * @brief Смена цвета фона
   */
  void BgColorChange();
  /**
   * @brief Смена цвета границ
   */
  void EdgesColorChange();
  /**
   * @brief Смена цвета вершин
   */
  void VertexesColorChange();

  /**
   * @brief Смена толщины линии границ
   * @param argument - ширина линии
   */
  void EdgesWidthChange(double argument);
  /**
   * @brief Смена типа линии границ (сплошная/штриховая)
   * @param index - параметр линии
   */
  void EdgesTypeChange(int index);
  /**
   * @brief Смена величины точек
   * @param argument - размер точки
   */
  void VertexesSizeChange(double argument);
  /**
   * @brief Смена типа точек (круглая/квадратная)
   * @param index - параметр точки
   */
  void VertexesTypeChange(int index);

  /**
   * @brief Функция движения слайдера перемещения по оси X
   * @param position - величина перемещения
   */
  void SliderMoveXMoved(int position);
  /**
   * @brief Функция опускания слайдера перемещения по оси X
   */
  void SliderMoveXReleased();
  /**
   * @brief Функция движения слайдера перемещения по оси Y
   * @param position - величина перемещения
   */
  void SliderMoveYMoved(int position);
  /**
   * @brief Функция опускания слайдера перемещения по оси Y
   */
  void SliderMoveYReleased();
  /**
   * @brief Функция движения слайдера перемещения по оси Z
   * @param position - величина перемещения
   */
  void SliderMoveZMoved(int position);
  /**
   * @brief Функция опускания слайдера перемещения по оси Z
   */
  void SliderMoveZReleased();

  /**
   * @brief Функция движения слайдера вращения по оси X
   * @param position - величина вращения
   */
  void SliderRotXMoved(int position);
  /**
   * @brief Функция опускания слайдера вращения по оси X
   */
  void SliderRotXReleased();
  /**
   * @brief Функция движения слайдера вращения по оси Y
   * @param position - величина вращения
   */
  void SliderRotYMoved(int position);
  /**
   * @brief Функция опускания слайдера вращения по оси Y
   */
  void SliderRotYReleased();
  /**
   * @brief Функция движения слайдера вращения по оси Z
   * @param position - величина вращения
   */
  void SliderRotZMoved(int position);
  /**
   * @brief Функция опускания слайдера вращения по оси Z
   */
  void SliderRotZReleased();

  /**
   * @brief Функция движения слайдера масштабирования
   * @param position - коэффициент масштабирования
   */
  void SliderScaleMoved(int position);
  /**
   * @brief Функция опускания слайдера масштабирования
   */
  void SliderScaleReleased();

  /**
   * @brief Смена проекции на параллельную
   */
  void OrthoPerspectiveButtonClicked();
  /**
   * @brief Смена проекции на прямую
   */
  void FrustrumPerspectiveButtonClicked();

  /**
   * @brief Скриншот модели
   */
  void ScreenshotButtonClicked();
  /**
   * @brief Запись gif
   */
  void GifButtonClicked();
  void gifRecord();
  void gifStop();
  void gifTime();

  /**
   * @brief Перемещение по оси X
   */
  void MoveXValue();
  /**
   * @brief Перемещение по оси Y
   */
  void MoveYValue();
  /**
   * @brief Перемещение по оси Z
   */
  void MoveZValue();

  /**
   * @brief Вращение по оси X
   */
  void RotXValue();
  /**
   * @brief Вращение по оси Y
   */
  void RotYValue();
  /**
   * @brief Вращение по оси Z
   */
  void RotZValue();

  /**
   * @brief Масштабирование модели
   */
  void ScaleValue();

 private:
  s21::GeometryControllerInterface *controller;
  Ui::MainWindow *ui;
  QImage *frame;
  int frame_num;
  QTimer *gifTimer;
  QTimer *gifTimerStop;
  QGifImage *gifOut;
  bool gifStart = 0;
};
}  // namespace UI
}  // namespace s21

#endif  // VIEW_MAINWINDOW_H
