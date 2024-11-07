#include "Shapes.h"

std::ostream& operator<<(std::ostream& os, const Polygon& shape)
{
    os << shape.GetName() << ": " << " { ";
    for (auto& v : shape.vertices) {
        os << v;
    }
    os << "}";

    return os;
}

std::istream& operator>>(std::istream& is, Triangle& obj) {
    std::vector<Vertex> verts(3);
    is >> verts[0] >> verts[1] >> verts[2];
    obj.SetVertices(verts);
    return is;
}

std::istream& operator>>(std::istream& is, Square& obj) {
    std::vector<Vertex> verts(4);
    is >> verts[0] >> verts[1] >> verts[2] >> verts[3];
    obj.SetVertices(verts);
    return is;
}

std::istream& operator>>(std::istream& is, Rectangle& obj) {
    std::vector<Vertex> verts(4);
    is >> verts[0] >> verts[1] >> verts[2] >> verts[3];
    obj.SetVertices(verts);
    return is;
}

bool Polygon::operator==(const Polygon& other) const {
    return vertices == other.vertices;
}


Vertex Triangle::GetCenter() const {
    auto const vert = GetVertices();
    float const Cent_x = (vert[0].x + vert[1].x + vert[2].x) / 3.0f;
    float const Cent_y = (vert[0].y + vert[1].y + vert[2].y) / 3.0f;

    return Vertex{Cent_x, Cent_y};
}

double Triangle::GetArea() const
{
    auto const verts = GetVertices();

    double const area = 0.5 * std::fabs((verts[0].x - verts[2].x) * (verts[1].y - verts[2].y)
        - (verts[1].x - verts[2].x) * (verts[0].y - verts[2].y));

    return area;
}

Vertex Square::GetCenter() const {
    auto const vert = GetVertices();
    float const Cent_x = (vert[0].x + vert[1].x + vert[2].x + vert[3].x) / 4.0f;
    float const Cent_y = (vert[0].y + vert[1].y + vert[2].y + vert[3].y) / 4.0f;

    return Vertex{Cent_x, Cent_y};
}

double Square::GetArea() const {
    auto const vert = GetVertices();
    float const side = std::sqrt(std::pow(vert[1].x - vert[0].x, 2) + std::pow(vert[1].y - vert[0].y, 2));
    return side * side;
}

double Rectangle::GetArea() const {
    auto const vert = GetVertices();
    float const width = std::sqrt(std::pow(vert[1].x - vert[0].x, 2) + std::pow(vert[1].y - vert[0].y, 2));
    float const height = std::sqrt(std::pow(vert[2].x - vert[1].x, 2) + std::pow(vert[2].y - vert[1].y, 2));
    return width * height;
}

Vertex Rectangle::GetCenter() const {
    auto const vert = GetVertices();
    float const Cent_x = (vert[0].x + vert[1].x + vert[2].x + vert[3].x) / 4.0f;
    float const Cent_y = (vert[0].y + vert[1].y + vert[2].y + vert[3].y) / 4.0f;

    return Vertex{Cent_x, Cent_y};
}