#include "geometry_controller.h"

s21::GeometryControllerInterface::~GeometryControllerInterface() {}

s21::GeometryController::GeometryController(s21::Geometry* geometry)
    : geometry_(geometry), subject_(new GeometryGLSubject(geometry)) {}

s21::GeometryController::~GeometryController() { delete subject_; }

void s21::GeometryController::LoadGeometry(std::string filename) {
  std::ifstream ins(filename, std::ios::in);
  try {
    geometry_->Load(ins);
    subject_->Update(geometry_);
  } catch (...) {
    // ...
  }
  ins.close();
}

void s21::GeometryController::ObserveGeometry(GeometryObserver* observer) {
  subject_->Attach(observer);
}

const s21::GeometryGLState& s21::GeometryController::GetGeometryGLState()
    const {
  return geometry_->GetGLState();
}

void s21::GeometryController::Scale(double k) { geometry_->Scale(k); }

void s21::GeometryController::Rotate(double yaw, double pitch, double roll) {
  geometry_->Rotate(yaw, pitch, roll);
}

void s21::GeometryController::Move(double dx, double dy, double dz) {
  geometry_->Translate(dx, dy, dz);
}

void s21::GeometryController::Rotate_X(double yaw) { Rotate(yaw, 0, 0); }

void s21::GeometryController::Rotate_Y(double pitch) { Rotate(0, pitch, 0); }

void s21::GeometryController::Rotate_Z(double roll) { Rotate(0, 0, roll); }

void s21::GeometryController::Move_X(double dx) { Move(dx, 0, 0); }

void s21::GeometryController::Move_Y(double dy) { Move(0, dy, 0); }

void s21::GeometryController::Move_Z(double dz) { Move(0, 0, dz); }
