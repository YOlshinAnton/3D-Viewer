#include "geometry.h"

static inline void addVerticesVertex(std::vector<s21::Vertex> &vertices,
                                     s21::Vertex &&v) {
  for (int i = 0; i < vertices.size(); ++i) {
    vertices[i].x += v.x;
    vertices[i].y += v.y;
    vertices[i].z += v.z;
  }
}

static inline void mltVerticesNumber(std::vector<s21::Vertex> &vertices,
                                     double n) {
  for (int i = 0; i < vertices.size(); ++i) {
    vertices[i].x *= n;
    vertices[i].y *= n;
    vertices[i].z *= n;
  }
}

static inline void mltVerticesMatrix(std::vector<s21::Vertex> &vertices,
                                     double (*m)[3]) {
  double x, y, z;
  for (int i = 0; i < vertices.size(); ++i) {
    x = m[0][0] * vertices[i].x + m[0][1] * vertices[i].y +
        m[0][2] * vertices[i].z;
    y = m[1][0] * vertices[i].x + m[1][1] * vertices[i].y +
        m[1][2] * vertices[i].z;
    z = m[2][0] * vertices[i].x + m[2][1] * vertices[i].y +
        m[2][2] * vertices[i].z;
    vertices[i].x = x;
    vertices[i].y = y;
    vertices[i].z = z;
  }
}

static inline void rotateYaw(std::vector<s21::Vertex> &vertices, double yaw) {
  double cos_yaw = cos(yaw), sin_yaw = sin(yaw);
  double r[3][3]{};
  r[0][0] = 1;
  r[1][1] = cos_yaw;
  r[1][2] = sin_yaw;
  r[2][1] = -sin_yaw;
  r[2][2] = cos_yaw;
  mltVerticesMatrix(vertices, r);
}

static inline void rotatePitch(std::vector<s21::Vertex> &vertices,
                               double pitch) {
  double cos_pitch = cos(pitch), sin_pitch = sin(pitch);
  double r[3][3]{};
  r[0][0] = cos_pitch;
  r[0][2] = sin_pitch;
  r[1][1] = 1;
  r[2][0] = -sin_pitch;
  r[2][2] = cos_pitch;
  mltVerticesMatrix(vertices, r);
}

static inline void rotateRoll(std::vector<s21::Vertex> &vertices, double roll) {
  double cos_roll = cos(roll), sin_roll = sin(roll);
  double r[3][3]{};
  r[0][0] = cos_roll;
  r[0][1] = -sin_roll;
  r[1][0] = sin_roll;
  r[1][1] = cos_roll;
  r[2][2] = 1;
  mltVerticesMatrix(vertices, r);
}

static inline void normalizeSize(std::vector<s21::Vertex> &vertices,
                                 s21::GeometryNormalizationParameters &params) {
  double normalization_coefficient =
      1 / ((params.FigureMaxComponent - params.FigureMinComponent) *
           params.FigureScale);
  mltVerticesNumber(vertices, normalization_coefficient);
  params = s21::GeometryNormalizationParametersBuilder()
               .FigureSize(vertices)
               ->Build();
}

static inline double nearestToCenterPoint(double a, double b) {
  // a < b
  return b < 0 || 0 <= a ? a : -1 * a <= b ? a : b;
}

static inline void normalizePosition(
    std::vector<s21::Vertex> &vertices,
    s21::GeometryNormalizationParameters &params) {
  // move to center
  double x_middle = (params.FigureMaxX - params.FigureMaxX) / 2 +
                    nearestToCenterPoint(params.FigureMaxX, params.FigureMaxX);
  double y_middle = (params.FigureMaxY - params.FigureMinY) / 2 +
                    nearestToCenterPoint(params.FigureMinY, params.FigureMaxY);
  double z_middle = (params.FigureMaxZ - params.FigureMinZ) / 2 +
                    nearestToCenterPoint(params.FigureMinZ, params.FigureMaxZ);
  addVerticesVertex(vertices, {-x_middle, -y_middle, -z_middle});
  params = s21::GeometryNormalizationParametersBuilder()
               .FigureSize(vertices)
               ->Build();
}

static inline void normalizeAngle(std::vector<s21::Vertex> &vertices) {
  //    rotateYaw(vertices, 3.141592 / 3);
  //    RotatePitch(vertices, 3.141592 / 12);
    rotateRoll(vertices, -3.141592/2);
}

void s21::Geometry::init() {
  Normalize();

  // GL
  for (const s21::Facet &f : facets_) {
    for (int i = 0; i < f.vertices.size(); ++i) {
      facetLoops_.push_back(f.vertices[i] - 1);
      facetLoops_.push_back(f.vertices[(i + 1) % f.vertices.size()] - 1);
    }
  }

  glState_ = GeometryGLState{reinterpret_cast<double *>(vertices_.data()),
                             (int)vertices_.size(), (int)facets_.size(),
                             reinterpret_cast<unsigned *>(facetLoops_.data()),
                             (int)facetLoops_.size()};
}

s21::Geometry::Geometry() {}

s21::Geometry::Geometry(std::vector<s21::Vertex> &vertices,
                        std::vector<s21::Facet> &facets) {
  vertices_ = vertices;
  facets_ = facets;
  init();
}

s21::Geometry::Geometry(std::istream &is) : Geometry() { Load(is); }

void s21::Geometry::Load(std::istream &is) {
  vertices_.clear();
  facets_.clear();
  facetLoops_.clear();
  glState_ = {};

  // parse
  std::string line;
  while (getline(is, line)) {
    // parse vertices
    if (line.substr(0, 2) == "v ") {
      s21::Vertex v;
      std::istringstream ss(line.substr(2));
      ss >> v.x >> v.y >> v.z;
      vertices_.push_back(v);
    }
    // parse facets
    else if (line.substr(0, 2) == "f ") {
      s21::Facet f;
      std::istringstream ss(line.substr(2));
      while (!ss.eof()) {
        unsigned int fvi;
        std::string facet_vertex;
        ss >> facet_vertex;
        if (facet_vertex == "") {
          break;
        }
        std::istringstream fs(facet_vertex);
        fs >> fvi;
        f.vertices.push_back(fvi);
      }
      facets_.push_back(f);
    }
  }

  init();
}

void s21::Geometry::Save(std::ostream &os) {
  os << std::setprecision(16);
  for (std::size_t i = 0; i < vertices_.size(); i++)
  {
    os << "v " << vertices_[i].x << ' ' << vertices_[i].y << ' ' << vertices_[i].z << std::endl;
  }

  for (std::size_t i = 0; i < facets_.size(); i++)
  {
    os << "f ";
    for (std::size_t j = 0; j < facets_[i].vertices.size() - 1; j++)
    {
      os << facets_[i].vertices[j] << ' ';
    }
    os << facets_[i].vertices[facets_[i].vertices.size() - 1] << std::endl;
  }
}

void s21::Geometry::Normalize() {
  params_ = GeometryNormalizationParametersBuilder()
                .FigureSize(vertices_)
                ->FigureScale(0.5)
                ->Build();
  normalizeSize(vertices_, params_);
  normalizePosition(vertices_, params_);
  normalizeAngle(vertices_);
}

void s21::Geometry::Scale(double k) { mltVerticesNumber(vertices_, k); }

void s21::Geometry::Rotate(double yaw, double pitch, double roll) {
  if (yaw != 0) {
    rotateYaw(vertices_, yaw);
  }
  if (pitch != 0) {
    rotatePitch(vertices_, pitch);
  }
  if (roll != 0) {
    rotateRoll(vertices_, roll);
  }
}

void s21::Geometry::Translate(double dx, double dy, double dz) {
  addVerticesVertex(vertices_, {dx, dy, dz});
}

const s21::GeometryGLState &s21::Geometry::GetGLState() const {
  return glState_;
}
