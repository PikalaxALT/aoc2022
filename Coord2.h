#ifndef AOC2022_COORD2_H
#define AOC2022_COORD2_H

#include <algorithm>

namespace aoc2022 {
    template<typename T>
    struct Coord2 {
        T x;
        T y;

        bool operator==(const Coord2 &rhs) const {
            return x == rhs.x && y == rhs.y;
        }

        friend Coord2 operator+(Coord2 lhs, const Coord2 &rhs) {
            return {lhs.x + rhs.x, lhs.y + rhs.y};
        }

        friend Coord2 operator-(Coord2 lhs, const Coord2 &rhs) {
            return {lhs.x - rhs.x, lhs.y - rhs.y};
        }

        Coord2 &operator+=(const Coord2 &rhs) {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }
        
        Coord2 operator-() const {
            return {-x, -y};
        }
        
        friend std::ostream& operator<<(std::ostream& strm, const Coord2& self) {
            strm << "{" << self.x << ", " << self.y << "}";
            return strm;
        }
        
        bool operator!=(const Coord2& rhs) const {
            return x != rhs.x || y != rhs.y;
        }
        
        bool operator<(const Coord2& rhs) const {
            if (x == rhs.x) {
                return y < rhs.y;
            }
            return x < rhs.x;
        }

        template <typename Scalar>
        Coord2 operator/(const Scalar& rhs) const {
            return {
                x / rhs,
                y / rhs
            };
        }

        template <typename Scalar>
        Coord2 operator*(const Scalar& rhs) const {
            return {
                x * rhs,
                y * rhs
            };
        }
        
        T l1dist(const Coord2& rhs) const {
            return std::abs(rhs.x - x) + std::abs(rhs.y - y);
        }
    };

    using CoordI2 = Coord2<int>;
}

template<typename T> struct std::hash<aoc2022::Coord2<T>> {
    unsigned long long operator()(const aoc2022::Coord2<T>& obj) const {
        std::hash<T> int_hasher {};
        unsigned long long xhash = int_hasher(obj.x), yhash = int_hasher(obj.y);
        return (xhash << 1) ^ yhash;
    }
};

#endif //AOC2022_COORD2_H
