#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>
#include <cmath>

template<class T>
concept Arithmetic = std::is_arithmetic_v<T>;

template<Arithmetic T>
struct Vertex {
    Vertex(const T x_in = 0.0f, const T y_in = 0.0f) : x(x_in), y(y_in) {}
    Vertex operator+(const Vertex& v_in) const {
        return {x + v_in.x, y + v_in.y};
    }
    Vertex operator-(const Vertex& v_in) const {
        return {x - v_in.x, y - v_in.y};
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
    virtual ~Vertex() = default;
public:
    T x;
    T y;
};

template<Arithmetic T>
class Shape {
    protected:
        virtual ~Shape() = default;
    public:
        virtual Vertex<T> GetCenter() const = 0;
        virtual double GetArea() const = 0;

};
template<Arithmetic T>
class Polygon : public Shape<T> {
    protected:
        void SortVerticesClockwise() {
            Vertex<T> center = this->GetCenter();

            std::sort(vertices.begin(), vertices.end(), [center](const Vertex<T>& a, const Vertex<T>& b) {
                const T angleA = std::atan2(a.y - center.y, a.x - center.x);
                const T angleB = std::atan2(b.y - center.y, b.x - center.x);
                return angleA > angleB;
            });
        }
        Polygon(std::string name_in, std::vector<Vertex<T>> vertices_in) : name(std::move(name_in)), vertices(std::move(vertices_in)) {
            }
        ~Polygon() override = default;
    public:
        virtual std::string GetName() const { return name; }
        virtual std::vector<Vertex<T>> GetVertices() const { return vertices; }

        friend std::ostream& operator<<(std::ostream& os, const Polygon& obj){
            os << obj.GetName() << ": " << " { ";
            for (auto& v : obj.vertices) {
                os << v;
            }
            os << "}";

            return os;
        }

        void SetVertices(const std::vector<Vertex<T>>& vertices_in) {
            vertices = vertices_in;
            SortVerticesClockwise();
        }

        bool operator==(const Polygon& other) const{
            return vertices == other.vertices;
        }


    protected:
        std::string name;
        std::vector<Vertex<T>> vertices;
};
template<Arithmetic T>
class Triangle : public Polygon<T> {
    public:
        explicit Triangle(const std::vector<Vertex<T>>& vertices_in) : Polygon<T>("Triangle", vertices_in) {
            assert(vertices_in.size() == 3);
            this->SortVerticesClockwise();
        }

        Vertex<T> GetCenter() const override{
            std::vector<Vertex<T>> const vert = this->GetVertices();
            T const Cent_x = (vert[0].x + vert[1].x + vert[2].x) / 3.0f;
            T const Cent_y = (vert[0].y + vert[1].y + vert[2].y) / 3.0f;

            return Vertex{Cent_x, Cent_y};
        }

        double GetArea() const override
        {
            auto const verts = this->GetVertices();

            double const area = 0.5 * std::fabs((verts[0].x - verts[2].x) * (verts[1].y - verts[2].y)
                - (verts[1].x - verts[2].x) * (verts[0].y - verts[2].y));

            return area;
        }
        friend std::istream& operator>>(std::istream& is, Triangle& obj){
            std::vector<Vertex<T>> verts(3);
            is >> verts[0] >> verts[1] >> verts[2];
            obj.SetVertices(verts);
            return is;
        }
};
template<Arithmetic T>
class Square : public Polygon<T> {
    public:
        explicit Square(const std::vector<Vertex<T>>& vertex_in) : Polygon<T>("Square", vertex_in) {
            assert(vertex_in.size() == 4);
            this->SortVerticesClockwise();
        }
        Vertex<T> GetCenter() const override{
            auto const vert = this->GetVertices();
            T const Cent_x = (vert[0].x + vert[1].x + vert[2].x + vert[3].x) / 4.0f;
            T const Cent_y = (vert[0].y + vert[1].y + vert[2].y + vert[3].y) / 4.0f;

            return Vertex{Cent_x, Cent_y};
        }
        double GetArea() const override{
            auto const vert = this->GetVertices();
            double side = std::sqrt(std::pow(vert[1].x - vert[0].x, 2) + std::pow(vert[1].y - vert[0].y, 2));
            return side * side;
        }
        friend std::istream& operator>>(std::istream& is, Square& obj){
            std::vector<Vertex<T>> verts(4);
            is >> verts[0] >> verts[1] >> verts[2] >> verts[3];
            obj.SetVertices(verts);
            return is;
        }
};
template<Arithmetic T>
class Rectangle : public Polygon<T> {
    public:
        explicit Rectangle(const std::vector<Vertex<T>>& vertices_in) : Polygon<T>("Rectangle", vertices_in) {
            assert(vertices_in.size() == 4);
            this->SortVerticesClockwise();
        }
        Vertex<T> GetCenter() const override{
            auto const vert = this->GetVertices();
            T const Cent_x = (vert[0].x + vert[1].x + vert[2].x + vert[3].x) / 4.0f;
            T const Cent_y = (vert[0].y + vert[1].y + vert[2].y + vert[3].y) / 4.0f;

            return Vertex{Cent_x, Cent_y};
        }
        double GetArea() const override{
            auto const vert = this->GetVertices();;
            double width = std::sqrt(std::pow(vert[1].x - vert[0].x, 2) + std::pow(vert[1].y - vert[0].y, 2));
            double height = std::sqrt(std::pow(vert[2].x - vert[1].x, 2) + std::pow(vert[2].y - vert[1].y, 2));
            return width * height;
        }
        friend std::istream& operator>>(std::istream& is, Rectangle& obj){
            std::vector<Vertex<T>> verts(4);
            is >> verts[0] >> verts[1] >> verts[2] >> verts[3];
            obj.SetVertices(verts);
            return is;
        }
};
