#ifndef GLWIDGET_GLMODEL_PROJECTION_H_
#define GLWIDGET_GLMODEL_PROJECTION_H_

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

#include <QOpenGLWidget>

namespace s21 {
namespace UI {
/**
 * @brief Паттерн стратегии
 */
class ProjectionStrategy {
 public:
  virtual ~ProjectionStrategy() {}
  /**
   * @brief Выполнение стратегии
   */
  virtual void Execute() = 0;
};

/**
 * @brief Инициализация конкретной стратегии (frustrum)
 */
class FrustrumProjection : public ProjectionStrategy {
 public:
  void Execute() override {
    glFrustum(-1, 1, -1, 1, 1, 40);
    glTranslated(0, 0, -3);
  }
};

/**
 * @brief Инициализация конкретной стратегии (ortho)
 */
class OrthoProjection : public ProjectionStrategy {
 public:
  void Execute() override {
    glOrtho(-4, 4, -4, 4, 4, 40);
    glTranslated(0, 0, -12);
  }
};

/**
 * @brief Класс контекста, на основе которого выбирается стратегия
 */
class Context {
 public:
  /**
   * @brief Контекст инициализируется только на основе стратегии
   */
  Context(ProjectionStrategy* strategy) : strategy_(strategy) {}

  /**
   * @brief Инициализация стратегии
   * @param strategy - стратегия
   */
  void SetStrategy(ProjectionStrategy* strategy) {
    delete strategy_;
    strategy_ = strategy;
  }

  /**
   * @brief Выполнение стратегии
   */
  void ExecuteStrategy() { strategy_->Execute(); }

 private:
  ProjectionStrategy* strategy_;
};
}  // namespace UI

}  // namespace s21

#endif  // GLWIDGET_GLMODEL_PROJECTION_H_
