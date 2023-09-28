#include "polygon.h"

#include "line.h"
#include "point.h"
#include "segment.h"
#include "vector.h"

geometry::Ray::Ray() {
    start_ = Point();
    end_ = Point();
}

geometry::Ray::Ray(geometry::Point first, geometry::Point second) : start_(first), end_(second) {
}

geometry::Ray& geometry::Ray::Move(const geometry::Vector& vector) {
    start_.Move(vector);
    end_.Move(vector);
    return *this;
}

bool geometry::Ray::ContainsPoint(const geometry::Point& point) const {
    auto line = Line(start_, end_);
    if (line.ContainsPoint(point)) {
        if (start_.GetX() < end_.GetX()) {
            return point.GetX() >= start_.GetX();
        } else if (start_.GetX() > end_.GetX()) {
            return point.GetX() <= start_.GetX();
        } else {
            if (start_.GetY() > end_.GetY()) {
                return point.GetY() <= start_.GetY();
            } else if (start_.GetY() < end_.GetY()) {
                return point.GetY() >= start_.GetY();
            } else {
                return point.GetY() == start_.GetY();
            }
        }
    }
    return false;
}

bool geometry::Ray::CrossesSegment(const geometry::Segment& segment) const {
    auto line = Line(start_, end_);
    if (!line.CrossesSegment(segment)) {
        return false;
    }

    Vector to_start = segment.GetStart() - start_;
    Vector to_end = segment.GetStart() - end_;
    Vector vector = segment.GetEnd() - segment.GetStart();
    int64_t pr1 = VectorMult(vector, to_start);
    int64_t pr2 = VectorMult(vector, to_end);
    if (pr1 * pr2 < 0) {
        return true;
    } else if ((pr1 == 0 && pr2 != 0) || (pr2 == 0 && pr1 != 0)) {
        return true;
    } else if (pr1 == 0) {
        return this->ContainsPoint(segment.GetStart()) || this->ContainsPoint(segment.GetEnd());
    }

    if (this->ContainsPoint(segment.GetStart())) {
        return true;
    } else {
        double cos_to_start = static_cast<double>(ScalarMult(to_start, vector)) / (Length(to_start) * Length(vector));
        double cos_to_end = static_cast<double>(ScalarMult(to_end, vector)) / (Length(to_end) * Length(vector));
        return cos_to_end > cos_to_start;
    }
}

geometry::Ray* geometry::Ray::Clone() const {
    Ray* clone = new Ray;
    clone->start_ = start_;
    clone->end_ = end_;
    return clone;
}

geometry::Point geometry::Ray::GetStart() const {
    return start_;
}

geometry::Point geometry::Ray::GetEnd() const {
    return end_;
}

geometry::Polygon::Polygon() {
    num_points_ = 0;
}

geometry::Polygon::Polygon(std::vector<Point> points) : points_(points), num_points_(points_.size()) {
}

geometry::Polygon& geometry::Polygon::Move(const geometry::Vector& vector) {
    for (auto& i : points_) {
        i.Move(vector);
    }
    return *this;
}

bool geometry::Polygon::ContainsPoint(const geometry::Point& point) const {
    for (int i = 0; i < num_points_; ++i) {
        if (point.ContainsPoint(points_[i])) {
            return true;
        }
    }

    Ray r = Ray(Point(static_cast<int64_t>(std::rand()), static_cast<int64_t>(std::rand())), point);

    int count_crosses = 0;
    Segment seg = Segment(points_[num_points_ - 1], points_[0]);
    if (r.CrossesSegment(seg)) {
        ++count_crosses;
    }
    if (seg.ContainsPoint(point)) {
        return true;
    }
    for (int i = 0; i < num_points_ - 1; ++i) {
        seg = Segment(points_[i], points_[i + 1]);
        if (r.CrossesSegment(seg)) {
            ++count_crosses;
        }
        if (seg.ContainsPoint(point)) {
            return true;
        }
    }

    return count_crosses % 2;
}

bool geometry::Polygon::CrossesSegment(const geometry::Segment& segment) const {
    Segment seg = Segment(points_[0], points_[num_points_ - 1]);
    if (seg.CrossesSegment(segment)) {
        return true;
    }
    for (int i = 0; i < num_points_ - 1; ++i) {
        seg = Segment(points_[i], points_[i + 1]);
        if (seg.CrossesSegment(segment)) {
            return true;
        }
    }
    return false;
}

geometry::Polygon* geometry::Polygon::Clone() const {
    Polygon* clone = new Polygon;
    clone->points_ = points_;
    clone->num_points_ = points_.size();
    return clone;
}
