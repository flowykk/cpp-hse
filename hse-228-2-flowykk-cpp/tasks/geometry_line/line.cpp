#include "line.h"

#include "cmath"
#include "segment.h"

geometry::Line::Line() {
    start_ = Point();
    end_ = Point();
}

int64_t geometry::Line::GetA() const {
    return start_.GetY() - end_.GetY();
}

int64_t geometry::Line::GetB() const {
    return end_.GetX() - start_.GetX();
}

int64_t geometry::Line::GetC() const {
    return start_.GetX() * end_.GetY() - end_.GetX() * start_.GetY();
}

geometry::Line::Line(geometry::Point start, geometry::Point end) : start_(start), end_(end) {
}

double geometry::Line::Distance(geometry::Point point) const {
    return std::abs(static_cast<double>(GetA() * point.GetX() + GetB() * point.GetY() + GetC()) /
                    (std::sqrt(std::pow(GetA(), 2) + std::pow(GetB(), 2))));
}

geometry::Line& geometry::Line::Move(const geometry::Vector& vector) {
    start_.Move(vector);
    end_.Move(vector);
    return *this;
}

bool geometry::Line::ContainsPoint(const geometry::Point& point) const {
    return GetA() * point.GetX() + GetB() * point.GetY() + GetC() == 0;
}

bool geometry::Line::CrossesSegment(const geometry::Segment& segment) const {
    Point a = start_;
    Point b = end_;
    Point c = segment.GetStart();
    Point d = segment.GetEnd();
    Vector ab = b - a;
    Vector ac = c - a;
    Vector ad = d - a;
    int64_t acab = VectorMult(ab, ac);
    int64_t abad = VectorMult(ab, ad);
    return (acab * abad <= 0);
}

geometry::Line* geometry::Line::Clone() const {
    Line* clone = new Line;
    clone->start_ = start_;
    clone->end_ = end_;
    return clone;
}
