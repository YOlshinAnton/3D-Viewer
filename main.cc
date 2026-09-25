#include <QApplication>

#include <fstream>

#include "maze.h"
#include "maze_generator.h"
#include "cave_generator.h"

#include "geometry.h"
#include "geometry_converter.h"
#include "geometry_controller.h"
#include "geometry_defaults.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

//  s21::model::generator::CaveGenerator generator(50,50,4,3,1);
//  generator.Generate();
//  s21::model::CaveData cave = generator.Get();
//  s21::model::converter::GeometryConverter converter;
//  s21::Geometry geometry = converter.Convert(cave);

  s21::model::generator::MazeGenerator generator(25,25);
  generator.Generate();
  s21::model::MazeData maze = generator.Get();
  s21::model::converter::GeometryConverter converter;
  s21::Geometry geometry = converter.Convert(maze);

  geometry.Translate(0, 1, 0);
  geometry.Scale(3);
//  s21::Geometry geometry = s21::GeometryDefaults::Cube();
  s21::GeometryController controller(&geometry);
  s21::UI::MainWindow w(&controller);
  w.show();
  return a.exec();
}
