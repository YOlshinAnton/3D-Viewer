//
//  main.cpp
//  Testing.s21_containers
//
//  Created by Антон Ёлшин on 28.02.2023.
//

#include <gtest/gtest.h>

#include <fstream>
#include <iostream>

#include "geometry.h"
#include "geometry_defaults.h"

bool compare_doubles(double A, double B) {
  const double EPSILON = 0.000001;
  double diff = A - B;
  return (-diff < EPSILON) && (diff < EPSILON);
}

bool compare_geometry_Vertices(s21::Geometry &g1, s21::Geometry &g2) {
  s21::GeometryGLState state1 = g1.GetGLState();
  s21::GeometryGLState state2 = g2.GetGLState();

  if (state1.VertexCount != state2.VertexCount) {
    std::cout << "vertex count !=" << std::endl;
    return false;
  }

  for (int i = 0; i < state1.VertexCount; ++i) {
    bool equal = compare_doubles(state1.Vertices[i], state2.Vertices[i]);
    if (!equal) {
      std::cout << '#' << i << " vertex " << state1.Vertices[i]
                << " != " << state2.Vertices[i] << std::endl;
      return false;
    }
  }
  return true;
}

bool compare_geometry_facetLoops(s21::Geometry &g, s21::Geometry &h) {
  s21::GeometryGLState gS = g.GetGLState();
  s21::GeometryGLState hS = h.GetGLState();

  if (gS.FacetElementCount != hS.FacetElementCount) {
    std::cout << "facet count " << gS.FacetElementCount
              << "!=" << hS.FacetElementCount << std::endl;
    return false;
  }
  return true;
}

TEST(Geometry, Load) {
  // CUBE
  s21::Geometry cubeDefault = s21::GeometryDefaults::Cube();
  std::ifstream cubeStream("../examples/cube.obj", std::ifstream::in);
  s21::Geometry cubeLoaded(cubeStream);
  cubeStream.close();
  EXPECT_EQ(true, compare_geometry_Vertices(cubeDefault, cubeLoaded));
  EXPECT_EQ(true, compare_geometry_facetLoops(cubeDefault, cubeLoaded));

  // DUCK
  cubeDefault = s21::GeometryDefaults::Duck();
  cubeStream.open("../examples/duck.obj", std::ifstream::in);
  cubeLoaded.Load(cubeStream);
  cubeStream.close();
  EXPECT_EQ(true, compare_geometry_Vertices(cubeDefault, cubeLoaded));
  EXPECT_EQ(true, compare_geometry_facetLoops(cubeDefault, cubeLoaded));
}

TEST(Geometry, XRotationByOneTurn) {
  s21::Geometry g = s21::GeometryDefaults::Cube();
  s21::Geometry gRotated = s21::GeometryDefaults::Cube();
  gRotated.Rotate(2 * 3.14159265359, 0, 0);

  EXPECT_EQ(true, compare_geometry_Vertices(g, gRotated));
}

TEST(Geometry, XandYandZRotationByHalfTurnEach) {
  s21::Geometry g = s21::GeometryDefaults::Cube();
  s21::Geometry gRotated = s21::GeometryDefaults::Cube();
  gRotated.Rotate(3.14159265359, 3.14159265359, 3.14159265359);

  EXPECT_EQ(true, compare_geometry_Vertices(g, gRotated));
}

TEST(Geometry, Translate) {
  s21::Geometry g = s21::GeometryDefaults::Cube();
  s21::Geometry gTranslated = s21::GeometryDefaults::Cube();
  gTranslated.Translate(2, 4, 6);

  s21::GeometryGLState gState = g.GetGLState();
  s21::GeometryGLState gTState = gTranslated.GetGLState();

  bool equal = true;
  for (int i = 0; i < gState.VertexCount; i += 3) {
    equal = gState.Vertices[i] + 2 == gTState.Vertices[i];
    equal = gState.Vertices[i + 1] + 4 == gTState.Vertices[i + 1];
    equal = gState.Vertices[i + 2] + 6 == gTState.Vertices[i + 2];
    if (!equal) {
      std::cout << "#" << i << std::endl;
      break;
    }
  }
  EXPECT_EQ(true, equal);
}

TEST(Geometry, ScaleTwice) {
  s21::Geometry g = s21::GeometryDefaults::Cube();
  s21::Geometry gScaled = s21::GeometryDefaults::Cube();
  gScaled.Scale(2.);

  s21::GeometryGLState gState = g.GetGLState();
  s21::GeometryGLState gScaledState = gScaled.GetGLState();

  bool equal = true;
  for (int i = 0; i < gState.VertexCount; i++) {
    equal = gState.Vertices[i] * 2 == gScaledState.Vertices[i];
    if (!equal) {
      std::cout << "#" << i << std::endl;
      break;
    }
  }
  EXPECT_EQ(true, equal);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
