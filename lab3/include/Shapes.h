#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <assert.h>
#include <algorithm>
#include <cmath>


struct Vertex {
    Vertex(float x_in = 0.0f, float y_in = 0.0f) : x(x_in), y(y_in) {}
    Vertex operator+(const Vertex& v_in) const {
        return Vertex(x + v_in.x, y + v_in.y);
    }
    Vertex operator-(const Vertex& v_in) const {
        return Vertex(x - v_in.x, y - v_in.y);
    }
    Vertex& operator+=(const Vertex& rhs) {
        x += rhs.x;
        y += rhs.y;

        return *this;
    }
    Vertex& operator-=(const Vertex& rhs) {
        x -= rhs.x;
        y -= rhs.y;

        return *this;
    }
    bool operator==(const Vertex& rhs) const {
        return x == rhs.x && y == rhs.y;
    }
    bool operator!=(const Vertex& rhs) const {
        return !(*this == rhs);
    }
    friend std::ostream& operator<<(std::ostream& os, const Vertex& vertex) {
        os << "(" << vertex.x << " ," << vertex.y << ")";
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Vertex& vertex) {
        is >> vertex.x >> vertex.y;
        return is;
    }
public:
    float x;
    float y;
};

class Shape {
    public:
        virtual Vertex GetCenter() const = 0;
        virtual double GetArea() const = 0;

};

class Polygon : public Shape {
    protected:
        void SortVerticesClockwise() {
        Vertex center = GetCenter();

        std::sort(vertices.begin(), vertices.end(), [center](const Vertex& a, const Vertex& b) {
            float angleA = std::atan2(a.y - center.y, a.x - center.x);
            float angleB = std::atan2(b.y - center.y, b.x - center.x);
            return angleA > angleB;
        });
    }
        Polygon(const std::string& name_in, const std::vector<Vertex>& vertices_in) : name(name_in), vertices(vertices_in) {
        }
    public:
        virtual inline std::string GetName() const { return name; }
        virtual inline std::vector<Vertex> GetVertices() const { return vertices; }

        friend std::ostream& operator<<(std::ostream& os, const Polygon& obj);

        inline void SetVertices(const std::vector<Vertex>& vertices_in) {
            vertices = vertices_in;
            SortVerticesClockwise();
        }

        bool operator==(const Polygon& other) const;


    protected:
        std::string name;
        std::vector<Vertex> vertices;
};

class Triangle : public Polygon {
    public:
        Triangle(const std::vector<Vertex>& vertices_in) : Polygon("Triangle", vertices_in) {
            assert(vertices_in.size() == 3);
            SortVerticesClockwise();
        }
        Vertex GetCenter() const override;
        double GetArea() const override;
        friend std::istream& operator>>(std::istream& is, Triangle& obj);
};

class Square : public Polygon {
    public:
        Square(const std::vector<Vertex>& vertex_in) : Polygon("Square", vertex_in) {
            assert(vertex_in.size() == 4);
            SortVerticesClockwise();
        }
        Vertex GetCenter() const override;
        double GetArea() const override;
        friend std::istream& operator>>(std::istream& is, Square& obj);
};

class Rectangle : public Polygon {
    public:
        Rectangle(const std::vector<Vertex>& vertices_in) : Polygon("Rectangle", vertices_in) {
            assert(vertices_in.size() == 4);
            SortVerticesClockwise();
        }
        Vertex GetCenter() const override;
        double GetArea() const override;
        friend std::istream& operator>>(std::istream& is, Rectangle& obj);
};