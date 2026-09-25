#include "geometry_subject.h"

#include "geometry_observer.h"

void s21::GeometryGLStateObserver::Update(void *message) {
  Update(reinterpret_cast<GeometryGLState *>(message));
}

s21::GeometrySubject::~GeometrySubject() {}

s21::GeometryGLSubject::GeometryGLSubject(s21::Geometry *geometry)
    : geometry_(geometry) {}

s21::GeometryGLSubject::~GeometryGLSubject() {}

void s21::GeometryGLSubject::Attach(s21::GeometryObserver *observer) {
  observers_.push_back(observer);
  GeometryGLState state = geometry_->GetGLState();
  observer->Update(&state);
}

void s21::GeometryGLSubject::Detach(s21::GeometryObserver *observer) {
  observers_.erase(std::find(observers_.begin(), observers_.end(), observer));
}

void s21::GeometryGLSubject::Update(void *message) {
  geometry_ = reinterpret_cast<Geometry *>(message);
  GeometryGLState state = geometry_->GetGLState();
  for (GeometryObserver *observer : observers_) {
    observer->Update(&state);
  }
}
