#include <cmath>

namespace geometry {
class Vector {
private:
    int64_t x_coord_;
    int64_t y_coord_;

public:
    Vector() {
        x_coord_ = 0;
        y_coord_ = 0;
    }

    Vector(int64_t x, int64_t y) : x_coord_(x), y_coord_(y) {
    }

    int64_t GetX() const {
        return x_coord_;
    }

    int64_t GetY() const {
        return y_coord_;
    }

    Vector operator+(const Vector& other) const {
        Vector temp;
        temp.x_coord_ = this->x_coord_ + other.x_coord_;
        temp.y_coord_ = this->y_coord_ + other.y_coord_;
        return temp;
    }

    Vector operator-(const Vector& other) const {
        Vector temp;
        temp.x_coord_ = this->x_coord_ - other.x_coord_;
        temp.y_coord_ = this->y_coord_ - other.y_coord_;
        return temp;
    }

    Vector operator+() const {
        auto temp = *this;
        return temp;
    }

    Vector operator-() const {
        auto temp = *this;
        temp.y_coord_ *= -1;
        temp.x_coord_ *= -1;
        return temp;
    }

    Vector operator*(int64_t number) const {
        Vector temp;
        temp.x_coord_ = number * this->x_coord_;
        temp.y_coord_ = number * this->y_coord_;
        return temp;
    }

    Vector operator/(int64_t number) const {
        Vector temp;
        temp.x_coord_ = this->x_coord_ / number;
        temp.y_coord_ = this->y_coord_ / number;
        return temp;
    }

    Vector& operator+=(const Vector& other) {
        this->x_coord_ += other.x_coord_;
        this->y_coord_ += other.y_coord_;
        return *this;
    }

    Vector& operator-=(const Vector& other) {
        this->x_coord_ -= other.x_coord_;
        this->y_coord_ -= other.y_coord_;
        return *this;
    }

    Vector& operator*=(int64_t number) {
        this->x_coord_ *= number;
        this->y_coord_ *= number;
        return *this;
    }

    Vector& operator/=(int64_t number) {
        this->x_coord_ /= number;
        this->y_coord_ /= number;
        return *this;
    }

    bool operator==(const Vector& other) const {
        return (this->x_coord_ == other.x_coord_ && this->y_coord_ == other.y_coord_);
    }

    friend int64_t ScalarMult(const Vector& first, const Vector& second) {
        return first.x_coord_ * second.x_coord_ + first.y_coord_ * second.y_coord_;
    }

    friend int64_t VectorMult(const Vector& first, const Vector& second) {
        return first.x_coord_ * second.y_coord_ - first.y_coord_ * second.x_coord_;
    }

    friend double Length(Vector vector) {
        double x = static_cast<double>(vector.x_coord_);
        double y = static_cast<double>(vector.y_coord_);
        return sqrt(x * x + y * y);
    }
};
}  // namespace geometry
