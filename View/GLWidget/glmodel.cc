#include "glmodel.h"

#include <QCoreApplication>
#include <iostream>

s21::UI::glModel::glModel(QWidget* parent) : QOpenGLWidget(parent) {
  v = NULL;
  f = NULL;

  paramsClearing();

  if (!(QFile::exists(QCoreApplication::applicationDirPath() +
                      "settings.ini"))) {
    settings =
        new QSettings(QCoreApplication::applicationDirPath() + "settings.ini",
                      QSettings::IniFormat, this);
    settings->beginGroup("Settings");
    settings->setValue("proj_type", 0);
    settings->setValue("edges_type", 1);
    settings->setValue("vertice_type", 1);
    settings->setValue("edges_r", 1.0);
    settings->setValue("edges_g", 1.0);
    settings->setValue("edges_b", 1.0);
    settings->setValue("edges_width", 2.0);
    settings->setValue("vertice_r", 0.0);
    settings->setValue("vertice_g", 0.9);
    settings->setValue("vertice_b", 0.0);
    settings->setValue("vertice_size", 8.0);
    settings->setValue("backgr_r", 0);
    settings->setValue("backgr_g", 0);
    settings->setValue("backgr_b", 0);
    settings->endGroup();
  }

  settings =
      new QSettings(QCoreApplication::applicationDirPath() + "settings.ini",
                    QSettings::IniFormat, this);
  settings->beginGroup("Settings");
  edges_type = settings->value("edges_type").toInt();
  vertice_type = settings->value("vertice_type").toInt();
  edges_r = settings->value("edges_r").toFloat();
  edges_g = settings->value("edges_g").toFloat();
  edges_b = settings->value("edges_b").toFloat();
  edges_width = settings->value("edges_width").toFloat();
  backgr_r = settings->value("backgr_r").toFloat();
  backgr_g = settings->value("backgr_g").toFloat();
  backgr_b = settings->value("backgr_b").toFloat();
  vertice_r = settings->value("vertice_r").toFloat();
  vertice_g = settings->value("vertice_g").toFloat();
  vertice_b = settings->value("vertice_b").toFloat();
  vertice_size = settings->value("vertice_size").toFloat();

  settings->endGroup();
}

s21::UI::glModel::~glModel() {
  settings->beginGroup("Settings");

  settings->setValue("edges_type", edges_type);
  settings->setValue("vertice_type", vertice_type);
  settings->setValue("edges_r", edges_r);
  settings->setValue("edges_g", edges_g);
  settings->setValue("edges_b", edges_b);
  settings->setValue("edges_width", edges_width);
  settings->setValue("vertice_r", vertice_r);
  settings->setValue("vertice_g", vertice_g);
  settings->setValue("vertice_b", vertice_b);
  settings->setValue("vertice_size", vertice_size);
  settings->setValue("backgr_r", backgr_r);
  settings->setValue("backgr_g", backgr_g);
  settings->setValue("backgr_b", backgr_b);

  settings->endGroup();
}

void s21::UI::glModel::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);
  glMatrixMode(GL_PROJECTION);
  glLineStipple(1, 0x0F0F);
}

void s21::UI::glModel::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void s21::UI::glModel::paintGL() {
  glClearColor(backgr_r, backgr_g, backgr_b, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  if (v) {
    glApplyProjection();
    glTranslated(0, 0, 0);
    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);
    glRotatef(zRot, 0, 0, 1);
    glVertexPointer(3, GL_DOUBLE, 0, v);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3d(vertice_r, vertice_g, vertice_b);
    glPointSize(vertice_size);
    if (vertice_type == 1) glEnable(GL_POINT_SMOOTH);
    if (vertice_type) glDrawArrays(GL_POINTS, 0, v_count);
    if (vertice_type == 1) glDisable(GL_POINT_SMOOTH);
    glColor3d(edges_r, edges_g, edges_b);
    glLineWidth(edges_width);
    if (edges_type) glEnable(GL_LINE_STIPPLE);
    if (f) glDrawElements(GL_LINES, f_count, GL_UNSIGNED_INT, f);
    if (edges_type) glDisable(GL_LINE_STIPPLE);
    glDisableClientState(GL_VERTEX_ARRAY);
  }
}

void s21::UI::glModel::Update(s21::GeometryGLState* state) {
  v = state->Vertices;
  v_count = state->VertexCount;
  f = state->FacetElements;
  f_count = state->FacetElementCount;
  update();
}

void s21::UI::glModel::mousePressEvent(QMouseEvent* m) { mousePos = m->pos(); }

void s21::UI::glModel::mouseMoveEvent(QMouseEvent* m) {
  xRot = 1 / M_PI * (m->pos().y() - mousePos.y()) + xcopyRot;
  yRot = 1 / M_PI * (m->pos().x() - mousePos.x()) + ycopyRot;
  update();
}

void s21::UI::glModel::mouseReleaseEvent(QMouseEvent* m) {
  xcopyRot = (float)m->pos().x();
  xcopyRot = xRot;
  ycopyRot = yRot;
}

void s21::UI::glModel::paramsClearing() {
  xcopyRot = ycopyRot = 0;
  xRot = yRot = zRot = 0;
  xPos = yPos = zPos = scale = xR = yR = zR = 0;
}
