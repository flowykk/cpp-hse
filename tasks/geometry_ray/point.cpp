#include "point.h"

#include "segment.h"
#include "vector.h"

int64_t geometry::Point::GetX() const {
    return x_coord_;
}

int64_t geometry::Point::GetY() const {
    return y_coord_;
}

void geometry::Point::SetX(int64_t x) {
    x_coord_ = x;
}
void geometry::Point::SetY(int64_t y) {
    y_coord_ = y;
}

geometry::Point& geometry::Point::Move(const geometry::Vector& vector) {
    x_coord_ += vector.GetX();
    y_coord_ += vector.GetY();
    return *this;
}

bool geometry::Point::ContainsPoint(const geometry::Point& point) const {
    return (x_coord_ == point.x_coord_ && y_coord_ == point.y_coord_);
}

bool geometry::Point::CrossesSegment(const geometry::Segment& segment) const {
    int64_t x1 = segment.GetStart().x_coord_;
    int64_t y1 = segment.GetStart().y_coord_;
    int64_t x2 = segment.GetEnd().x_coord_;
    int64_t y2 = segment.GetEnd().y_coord_;
    int64_t x = x_coord_;
    int64_t y = y_coord_;
    if ((y1 - y2) * x + (x2 - x1) * y + (x1 * y2 - x2 * y1) == 0) {
        if (std::min(x1, x2) <= x && std::max(x1, x2) >= x && std::min(y1, y2) <= y && std::max(y1, y2) >= y) {
            return true;
        }
    }
    return false;
}

geometry::Point* geometry::Point::Clone() const {
    Point* clone = new Point;
    clone->SetX(x_coord_);
    clone->SetY(y_coord_);
    return clone;
}

geometry::Point::Point(int64_t x, int64_t y) : x_coord_(x), y_coord_(y) {
}

geometry::Vector geometry::Point::operator-(geometry::Point other) const {
    return Vector(x_coord_ - other.x_coord_, y_coord_ - other.y_coord_);
}
