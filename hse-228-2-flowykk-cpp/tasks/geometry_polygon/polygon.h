#pragma once
#include <iostream>
#include <vector>

#include "point.h"
#include "vector.h"

namespace geometry {
class Ray : public IShape {
private:
    Point start_;
    Point end_;

public:
    Ray();

    Ray(Point first, Point second);

    Ray& Move(const Vector& vector) override;

    bool ContainsPoint(const Point& point) const override;

    bool CrossesSegment(const Segment& segment) const override;

    Ray* Clone() const override;

    Point GetStart() const;

    Point GetEnd() const;
};
}  // namespace geometry

namespace geometry {
class Polygon : public IShape {
private:
    std::vector<Point> points_;
    size_t num_points_;

public:
    Polygon();

    explicit Polygon(std::vector<Point> points);

    Polygon& Move(const Vector& vector) override;

    bool ContainsPoint(const Point& point) const override;

    bool CrossesSegment(const Segment& segment) const override;

    Polygon* Clone() const override;

    std::vector<Point> GetPoints() const {
        return points_;
    }
};
}  // namespace geometry
