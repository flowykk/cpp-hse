#include "circle.h"

#include "segment.h"
#include "vector.h"

geometry::Circle::Circle() {
    centre_ = Point();
    radius_ = 0;
}

geometry::Circle::Circle(geometry::Point centre, int64_t radius) : centre_(centre), radius_(radius) {
}

geometry::Circle& geometry::Circle::Move(const geometry::Vector& vector) {
    centre_.Move(vector);
    return *this;
}

bool geometry::Circle::ContainsPoint(const geometry::Point& point) const {
    Vector vector = point - centre_;
    return Length(vector) <= static_cast<double>(radius_);
}

bool geometry::Circle::CrossesSegment(const geometry::Segment& segment) const {
    if (segment.Distance(centre_) <= static_cast<double>(radius_)) {
        Vector v1 = segment.GetStart() - centre_;
        Vector v2 = segment.GetEnd() - centre_;
        if (Length(v1) >= static_cast<double>(radius_) || Length(v2) >= static_cast<double>(radius_)) {
            return true;
        }
    }
    return false;
}

geometry::Circle* geometry::Circle::Clone() const {
    Circle* clone = new Circle;
    clone->centre_ = centre_;
    clone->radius_ = radius_;
    return clone;
}

int64_t geometry::Circle::GetRadius() const {
    return radius_;
}

geometry::Point geometry::Circle::GetCenter() const {
    return centre_;
}
