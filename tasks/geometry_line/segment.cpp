#include "segment.h"

#include "vector.h"

geometry::Segment::Segment(Point start, Point end) {
    start_ = start;
    end_ = end;
}

geometry::Segment::Segment() {
    start_ = Point();
    end_ = Point();
}

geometry::Point geometry::Segment::GetStart() const {
    return start_;
}

geometry::Point geometry::Segment::GetEnd() const {
    return end_;
}

geometry::Segment& geometry::Segment::Move(const geometry::Vector& vector) {
    start_.Move(vector);
    end_.Move(vector);
    return *this;
}

bool geometry::Segment::ContainsPoint(const geometry::Point& point) const {
    return point.CrossesSegment(*this);
}

bool geometry::Segment::CrossesSegment(const geometry::Segment& segment) const {
    Point a = Point(start_);
    Point b = Point(end_);
    Point c = Point(segment.start_);
    Point d = Point(segment.end_);
    Vector ab = b - a;
    Vector ac = c - a;
    Vector ad = d - a;
    int64_t acab = VectorMult(ab, ac);
    int64_t abad = VectorMult(ab, ad);
    if (acab * abad > 0) {
        return false;
    }
    Vector dc = d - c;
    Vector db = d - b;
    int64_t dadc = VectorMult(dc, ad);
    int64_t dbdc = VectorMult(dc, db);
    if (dadc * dbdc > 0) {
        return false;
    }
    return true;
}

geometry::Segment* geometry::Segment::Clone() const {
    Segment* clone = new Segment;
    clone->start_ = start_;
    clone->end_ = end_;
    return clone;
}
