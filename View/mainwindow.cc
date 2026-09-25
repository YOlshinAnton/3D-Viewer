#include "mainwindow.h"

#include <QColor>
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QMovie>
#include <QtMath>

#include "ui_mainwindow.h"

#define S21_DEFAULT_ROTATION_STEP 0.1
#define S21_DEFAULT_SCALE_STEP 0.1

s21::UI::MainWindow::MainWindow(s21::GeometryControllerInterface *ctrl)
    : controller(ctrl), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // загрузка
  connect(ui->load, &QPushButton::clicked, this, &s21::UI::MainWindow::Load);

  // цвета
  connect(ui->backgr_color, &QPushButton::clicked, this,
          &s21::UI::MainWindow::BgColorChange);
  connect(ui->edges_color, &QPushButton::clicked, this,
          &s21::UI::MainWindow::EdgesColorChange);
  connect(ui->vertices_color, &QPushButton::clicked, this,
          &s21::UI::MainWindow::VertexesColorChange);

  // параметры вершин и линий
  connect(ui->edges_size, &QDoubleSpinBox::valueChanged, this,
          &s21::UI::MainWindow::EdgesWidthChange);
  connect(ui->edges_type, &QComboBox::currentIndexChanged, this,
          &s21::UI::MainWindow::EdgesTypeChange);
  connect(ui->vertices_size, &QDoubleSpinBox::valueChanged, this,
          &s21::UI::MainWindow::VertexesSizeChange);
  connect(ui->vertices_type, &QComboBox::currentIndexChanged, this,
          &s21::UI::MainWindow::VertexesTypeChange);

  // слайдеры перемещений
  connect(ui->moveX_slider, &QSlider::sliderMoved, this,
          &s21::UI::MainWindow::SliderMoveXMoved);
  connect(ui->moveX_slider, &QSlider::sliderReleased, this,
          &s21::UI::MainWindow::SliderMoveXReleased);
  connect(ui->moveY_slider, &QSlider::sliderMoved, this,
          &s21::UI::MainWindow::SliderMoveYMoved);
  connect(ui->moveY_slider, &QSlider::sliderReleased, this,
          &s21::UI::MainWindow::SliderMoveYReleased);
  connect(ui->moveZ_slider, &QSlider::sliderMoved, this,
          &s21::UI::MainWindow::SliderMoveZMoved);
  connect(ui->moveZ_slider, &QSlider::sliderReleased, this,
          &s21::UI::MainWindow::SliderMoveZReleased);

  // слайдеры вращений
  connect(ui->rotateX_slider, &QSlider::sliderMoved, this,
          &s21::UI::MainWindow::SliderRotXMoved);
  connect(ui->rotateX_slider, &QSlider::sliderReleased, this,
          &s21::UI::MainWindow::SliderRotXReleased);
  connect(ui->rotateY_slider, &QSlider::sliderMoved, this,
          &s21::UI::MainWindow::SliderRotYMoved);
  connect(ui->rotateY_slider, &QSlider::sliderReleased, this,
          &s21::UI::MainWindow::SliderRotYReleased);
  connect(ui->rotateZ_slider, &QSlider::sliderMoved, this,
          &s21::UI::MainWindow::SliderRotZMoved);
  connect(ui->rotateZ_slider, &QSlider::sliderReleased, this,
          &s21::UI::MainWindow::SliderRotZReleased);

  // слайдер масштабирования
  connect(ui->scale_slider, &QSlider::sliderMoved, this,
          &s21::UI::MainWindow::SliderScaleMoved);
  connect(ui->scale_slider, &QSlider::sliderReleased, this,
          &s21::UI::MainWindow::SliderScaleReleased);

  // кнопки перспективы
  connect(ui->ortho_proj, &QPushButton::clicked, this,
          &s21::UI::MainWindow::OrthoPerspectiveButtonClicked);
  connect(ui->frustrum_proj, &QPushButton::clicked, this,
          &s21::UI::MainWindow::FrustrumPerspectiveButtonClicked);

  // кнопки изображений и гифки
  connect(ui->screenshot_button, &QPushButton::clicked, this,
          &s21::UI::MainWindow::ScreenshotButtonClicked);
  connect(ui->gif_button, &QPushButton::clicked, this,
          &s21::UI::MainWindow::GifButtonClicked);

  // Поля ввода
  connect(ui->x_value, &QDoubleSpinBox::valueChanged, this,
          &s21::UI::MainWindow::MoveXValue);
  connect(ui->y_value, &QDoubleSpinBox::valueChanged, this,
          &s21::UI::MainWindow::MoveYValue);
  connect(ui->z_value, &QDoubleSpinBox::valueChanged, this,
          &s21::UI::MainWindow::MoveZValue);

  connect(ui->xrot_value, &QDoubleSpinBox::valueChanged, this,
          &s21::UI::MainWindow::RotXValue);
  connect(ui->yrot_value, &QDoubleSpinBox::valueChanged, this,
          &s21::UI::MainWindow::RotYValue);
  connect(ui->zrot_value, &QDoubleSpinBox::valueChanged, this,
          &s21::UI::MainWindow::RotZValue);

  connect(ui->scale_value, &QDoubleSpinBox::valueChanged, this,
          &s21::UI::MainWindow::ScaleValue);

  ui->edges_type->setCurrentIndex(ui->widget_model->edges_type);
  ui->edges_size->setValue(ui->widget_model->edges_width);
  ui->vertices_type->setCurrentIndex(ui->widget_model->vertice_type);
  ui->vertices_size->setValue(ui->widget_model->vertice_size);

  if (ui->vertices_type->currentIndex() == 0)
    ui->vertices_size->setEnabled(false);
  ui->ortho_proj->setChecked(true);

  controller->ObserveGeometry(this);
  controller->ObserveGeometry(ui->widget_model);

  gifTimer = new QTimer();
  connect(gifTimer, SIGNAL(timeout()), this, SLOT(gifTime()));
}

s21::UI::MainWindow::~MainWindow() { delete ui; }

void s21::UI::MainWindow::Update(s21::GeometryGLState *modelState) {
  ui->fileinfo->setText(
      "Vertices: " + QString::number(modelState->VertexCount) + "\n" +
      "Facets: " + QString::number(modelState->FacetCount));
}

void s21::UI::MainWindow::Load() {
  QString filename = QFileDialog::getOpenFileName(
      this, tr("Open Object File"), "../../", "Obj files (*.obj)");
  std::string filename_model = filename.toStdString();
  controller->LoadGeometry(filename_model);
  s21::GeometryGLState modelState = controller->GetGeometryGLState();
  ui->fileinfo->setText(
      "Model: " +
      filename.last(filename.length() - filename.lastIndexOf("/") - 1) + "\n" +
      "Vertices: " + QString::number(modelState.VertexCount) + "\n" +
      "Facets: " + QString::number(modelState.FacetCount));
}

void s21::UI::MainWindow::BgColorChange() {
  QColor backgr_rgb =
      QColorDialog::getColor(Qt::white, this, "Pick background color");
  if (backgr_rgb.isValid()) {
    backgr_rgb.getRgbF(&(ui->widget_model->backgr_r),
                       &(ui->widget_model->backgr_g),
                       &(ui->widget_model->backgr_b));
    ui->widget_model->update();
  }
}

void s21::UI::MainWindow::EdgesColorChange() {
  QColor facet_rgb =
      QColorDialog::getColor(Qt::black, this, "Pick facets color");
  if (facet_rgb.isValid()) {
    facet_rgb.getRgbF(&(ui->widget_model->edges_r),
                      &(ui->widget_model->edges_g),
                      &(ui->widget_model->edges_b));
    ui->widget_model->update();
  }
}

void s21::UI::MainWindow::VertexesColorChange() {
  QColor vertice_rgb =
      QColorDialog::getColor(Qt::red, this, "Pick vertices color");
  if (vertice_rgb.isValid()) {
    vertice_rgb.getRgbF(&(ui->widget_model->vertice_r),
                        &(ui->widget_model->vertice_g),
                        &(ui->widget_model->vertice_b));
    ui->widget_model->update();
  }
}

void s21::UI::MainWindow::EdgesWidthChange(double argument) {
  ui->widget_model->edges_width = argument;
  ui->widget_model->update();
}

void s21::UI::MainWindow::EdgesTypeChange(int index) {
  ui->widget_model->edges_type = index;
  ui->widget_model->update();
}

void s21::UI::MainWindow::VertexesSizeChange(double argument) {
  ui->widget_model->vertice_size = argument;
  ui->widget_model->update();
}

void s21::UI::MainWindow::VertexesTypeChange(int index) {
  ui->widget_model->vertice_type = index;
  if (index) {
    ui->vertices_size->setEnabled(true);
  } else {
    ui->vertices_size->setEnabled(false);
  }
  ui->widget_model->update();
}

void s21::UI::MainWindow::SliderMoveYMoved(int position) {
  controller->Move_Y(((double)position - ui->widget_model->yPos) / 100);
  ui->widget_model->update();
  ui->widget_model->yPos = position;
}

void s21::UI::MainWindow::SliderMoveYReleased() {
  ui->widget_model->yPos = 0;
  ui->moveY_slider->setValue(0);
}

void s21::UI::MainWindow::SliderMoveXMoved(int position) {
  controller->Move_X(((double)position - ui->widget_model->xPos) / 100);
  ui->widget_model->update();
  ui->widget_model->xPos = (double)position;
}

void s21::UI::MainWindow::SliderMoveXReleased() {
  ui->widget_model->xPos = 0;
  ui->moveX_slider->setValue(0);
}

void s21::UI::MainWindow::SliderMoveZMoved(int position) {
  controller->Move_Z(((double)position - ui->widget_model->zPos) / 100);
  ui->widget_model->update();
  ui->widget_model->zPos = (double)position;
}

void s21::UI::MainWindow::SliderMoveZReleased() {
  ui->widget_model->zPos = 0;
  ui->moveZ_slider->setValue(0);
}

void s21::UI::MainWindow::SliderScaleMoved(int position) {
  if ((double)position - ui->widget_model->scale > 0)
    controller->Scale(1 + S21_DEFAULT_SCALE_STEP);
  else
    controller->Scale(1 - S21_DEFAULT_SCALE_STEP);
  ui->widget_model->update();
  ui->widget_model->scale = (double)position;
}

void s21::UI::MainWindow::SliderScaleReleased() {
  ui->widget_model->scale = 0;
  ui->scale_slider->setValue(0);
}

void s21::UI::MainWindow::SliderRotXMoved(int position) {
  if ((double)position - ui->widget_model->xR > 0)
    controller->Rotate_X(S21_DEFAULT_ROTATION_STEP);
  else
    controller->Rotate_X(-S21_DEFAULT_ROTATION_STEP);
  ui->widget_model->update();
  ui->widget_model->xR = (double)position;
}

void s21::UI::MainWindow::SliderRotXReleased() {
  ui->widget_model->xR = 0;
  ui->rotateX_slider->setValue(0);
}

void s21::UI::MainWindow::SliderRotYMoved(int position) {
  if ((double)position - ui->widget_model->yR > 0)
    controller->Rotate_Y(S21_DEFAULT_ROTATION_STEP);
  else
    controller->Rotate_Y(-S21_DEFAULT_ROTATION_STEP);
  ui->widget_model->update();
  ui->widget_model->yR = (double)position;
}

void s21::UI::MainWindow::SliderRotYReleased() {
  ui->widget_model->yR = 0;
  ui->rotateY_slider->setValue(0);
}

void s21::UI::MainWindow::SliderRotZMoved(int position) {
  if ((double)position - ui->widget_model->zR > 0)
    controller->Rotate_Z(S21_DEFAULT_ROTATION_STEP);
  else
    controller->Rotate_Z(-S21_DEFAULT_ROTATION_STEP);
  ui->widget_model->update();
  ui->widget_model->zR = (double)position;
}

void s21::UI::MainWindow::SliderRotZReleased() {
  ui->widget_model->zR = 0;
  ui->rotateZ_slider->setValue(0);
}

void s21::UI::MainWindow::OrthoPerspectiveButtonClicked() {
  ui->widget_model->SetOrthoProjection();
  ui->widget_model->update();
}

void s21::UI::MainWindow::FrustrumPerspectiveButtonClicked() {
  ui->widget_model->SetFrustrumProjection();
  ui->widget_model->update();
}

void s21::UI::MainWindow::ScreenshotButtonClicked() {
  QImage screen = ui->widget_model->grabFramebuffer();
  QString defaultName = "image";
  QString defaultPath = QDir::homePath() + "/Desktop";
  QStringList mimeTypeFilters({"image/jpeg", "image/bmp"});
  QFileDialog saveDialog(this, tr("Save as"), defaultName, defaultPath);
  saveDialog.setAcceptMode(QFileDialog::AcceptSave);
  saveDialog.setDirectory(defaultPath);
  saveDialog.setFileMode(QFileDialog::AnyFile);
  saveDialog.setMimeTypeFilters(mimeTypeFilters);
  if (saveDialog.exec() == QDialog::Accepted) {
    const QString fname = saveDialog.selectedFiles().constFirst();
    if (!screen.save(fname)) {
      QMessageBox::warning(this, tr("Error"),
                           tr("Imposible to save image in \"%1\".")
                               .arg(QDir::toNativeSeparators(fname)));
    }
  }
}

void MainWindow::GifButtonClicked() {
  if (!gifStart) {
    gifStart = 1;
    ui->gif_button->setText("SAVE");
    gifRecord();
  } else {
    ui->gif_button->setText("gif");
    gifStart = 0;
    gifTimer->stop();
    gifStop();
  }
}

void MainWindow::gifRecord() {
  gifOut = new QGifImage();
  gifTimer->start(100);
}

void MainWindow::gifTime() {
  QImage frame = ui->widget_model->grabFramebuffer();
  frame = frame.scaled(640, 480, Qt::IgnoreAspectRatio);
  gifOut->addFrame(frame, 100);
}

void MainWindow::gifStop() {
  gifStart = 0;
  QString safeGIF = QFileDialog::getSaveFileName(this, "Сохранить как...",
                                                 QDir::homePath() + "/Desktop",
                                                 "GIF Files (*.gif)");
  if (!safeGIF.isNull()) gifOut->save(safeGIF);
  gifOut->~QGifImage();
}

void s21::UI::MainWindow::MoveXValue() {
  controller->Move_X(ui->x_value->value());
  ui->widget_model->update();
}

void s21::UI::MainWindow::MoveYValue() {
  controller->Move_Y(ui->y_value->value());
  ui->widget_model->update();
}

void s21::UI::MainWindow::MoveZValue() {
  controller->Move_Z(ui->z_value->value());
  ui->widget_model->update();
}

void s21::UI::MainWindow::RotXValue() {
  controller->Rotate_X(ui->xrot_value->value());
  ui->widget_model->update();
}

void s21::UI::MainWindow::RotYValue() {
  controller->Rotate_Y(ui->yrot_value->value());
  ui->widget_model->update();
}

void s21::UI::MainWindow::RotZValue() {
  controller->Rotate_Z(ui->zrot_value->value());
  ui->widget_model->update();
}

void s21::UI::MainWindow::ScaleValue() {
  controller->Scale(ui->scale_value->value());
  ui->widget_model->update();
}
