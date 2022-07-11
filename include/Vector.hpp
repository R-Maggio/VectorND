#pragma once

#include <iostream>
#include <cmath> // sqrt
#include <iomanip> // std::setprecision

// TODO: periodicDiff static ?
// TODO: periodicDiff: add parameter precise which boundary is periodic
// TODO: add scalar adition to Vector
// TODO: add %= for consistency
// TODO: add inline functions where possible
// TODO: init with variadic template arguments: Vector<double, 3>(1, 2, 3) 

namespace VectorND {

/**
 * @brief 2D vector class
 * 
 * @tparam T the type of the elements
 * @tparam N the number of elements
 */
template <typename T, size_t N>
class Vector
{
private:
    std::array<T, N> data;
public:
    // aliases
    using iterator = T*;
    using const_iterator = const T*;

    // size of the vector (for convenience)
    static constexpr size_t size = N;
    //**----------
    Vector(): data{} {}
    //TODO: remove copy constructor
    Vector(const Vector& v): data{v.data} {}
    
    Vector(const std::array<T, N>& data): data{data} {}
    //**----------
    // iterators
    inline iterator begin() noexcept { return data.data(); }
    inline const_iterator cbegin() const noexcept { return data.data(); }
    inline iterator end() noexcept { return data.data() + N; }
    inline const_iterator cend() const noexcept { return data.data() + N; }
    //**----------

    /**
     * @brief Operator for the casting to one vector to another
     * 
     */
    template <typename U>
    operator Vector<U, N>() const {
        Vector<U, N> result;
        for (size_t i = 0; i < N; ++i) {
            result[i] = static_cast<U>(data[i]);
        }
        return result;
    }

    /**
     * @brief element access operator  (write)
     * 
     * @param i the index of the element
     */
    inline T& operator[](size_t i) {
        return data[i];
    }

    /**
     * @brief element access operator (read)
     * 
     * @param i the index of the element
     */
    inline T operator[](size_t i) const {
        return data[i];
    }

    /**
     * @brief element access (read) with bounds checking
     * 
     * @param i the index of the element
     */
    inline T at(size_t i) const {
        return data.at(i);
    }

    /**
     * @brief sum of 2 vectors and returns a new vector
     * 
     * @param otherVector 
     * @return Vector
     */
    Vector operator+(const Vector& otherVector) const;

    /**
     * @brief substraction
     * 
     * @param otherVector 
     * @return Vector 
     */
    Vector operator-(const Vector& otherVector) const;

    /**
     * @brief unary minus operator
     * 
     * @return Vector 
     */
    Vector operator-() const;

    /**
     * @brief add a vector to the current vector
     * 
     * @param otherVector 
     * @return Vector& 
     */ 
    Vector& operator+=(const Vector& otherVector);

    /**
     * @brief -= operator overloading
     * 
     * @param otherVector 
     * @return Vector& 
     */
    Vector& operator-=(const Vector& otherVector);

    /**
     * @brief return dot product
     * 
     * @param otherVector 
     * @return Vector 
     */
    T dot(const Vector& otherVector) const;

    /**
     * @brief return result of multiplying a vector by a scalar
     * 
     * @param scalar 
     * @return Vector 
     */
    Vector operator*(T scalar) const;

    /**
     * @brief return result of multiplying a scalar by a vecor
     * 
     * @param vector 
     * @param scalar 
     * @return Vector 
     */
    friend Vector operator*(T scalar, const Vector& vector) {
        Vector<T, N> result;
        for (size_t i = 0; i < N; i++) {
            result.data[i] = scalar * vector.data[i];
        }
        return result;
    }

    /**
     * @brief element by element product
     * 
     * @param otherVector 
     * @return Vector
     */
    Vector operator*(const Vector& otherVector) const;

    /**
     * @brief element by element division
     * 
     * @param otherVector 
     * @return Vector
     */
    Vector operator/(const Vector& otherVector) const;

    /**
     * @brief *= operator overlading. multiply by scalar
     * 
     * @param scalar
     * @return Vector& 
     */
    Vector& operator*=(T scalar);

    /**
     * @brief *= operator overlading. multiply by vector
     * 
     * @param vector
     * @return Vector& 
     */
    Vector& operator*=(const Vector& vector);

    /**
     * @brief return result of dividing a vector by a scalar
     * 
     * @param scalar 
     * @return Vector 
     */
    Vector operator/(T scalar) const;

    /**
     * @brief return result of dividing a scalar by a vecor
     * 
     * @param vector 
     * @param scalar 
     * @return Vector 
     */
    friend Vector operator/(T scalar, const Vector& vector) {
            Vector<T, N> result;
        for (size_t i = 0; i < N; i++) {
            result.data[i] = scalar / vector.data[i];
        }
        return result;
    }

    /**
     * @brief /= operator overlading. divide by scalar
     * 
     * @param scalar
     * @return Vector& 
     */
    Vector& operator/=(T scalar);

    /**
     * @brief /= operator overlading. divide by vector
     * 
     * @param vector
     * @return Vector& 
     */
    Vector& operator/=(const Vector& vector);

    /**
     * @brief element by element remainder operation on each element
     * 
     * @param otherVector
     * @return Vector 
     */
    Vector mod(const Vector& otherVector) const;

    //***
    /**
     * @brief apply the true modulo operation on each element
     * 
     * @param scalar 
     * @return Vector 
     */
    Vector mod(T scalar) const;

    /**
     * @brief return the euclidean norm of a vector (static function)
     * 
     * @return double 
     */
    static double norm(const Vector& vector);

    /**
     * @brief return the euclidean norm of a vector
     * 
     * @param vector 
     * @return double 
     */
    double norm() const;

    /**
     * @brief return the absolute squared norm of a vector (static function)
     * 
     * @param vector 
     * @return double
     */
    static double squaredNorm(const Vector& vector);

    /**
     * @brief return the absolute squared norm of a vector
     * 
     * @return double 
     */
    double squaredNorm() const;

    /**
     * @brief return the euclidean distance between 2 vectors a and b (static function)
     * 
     * @param a 
     * @param b 
     * @return double 
     */
    static double dist(const Vector& a, const Vector& b);

    /**
     * @brief return the euclidean distance between 2 vectors
     * 
     * @param otherVector
     * @return double 
     */
    double dist(const Vector& otherVector) const;

    /**
     * @brief return the squared distance between 2 vectors a and b (static function)
     * 
     * @param a 
     * @param b 
     * @return double 
     */
    static double squaredDist(const Vector& a, const Vector& b);

    /**
     * @brief return the squared distance between 2 vectors
     * 
     * @param otherVector
     * @return double 
     */
    double squaredDist(const Vector& otherVector) const;
    
    /**
     * @brief compute v1 - v2 ("vectorial distance" distance) with periodic boundaries
     * 
     * @param otherVector 
     * @return Vector 
     */
    Vector periodicDiff(const Vector& otherVector, const Vector& domainSize) const;

    /**
     * @brief reverse the order of the elements: {x,y} => {y,x}
     * 
     * @return Vector 
     */
    Vector reverse() const;

    /**
     * @brief equality operator
     * 
     * @param otherVector
     * @return true if the vectors are equal
     * @return false if the vectors are not equal
     */
    inline bool operator==(const Vector& otherVector) const;

    /**
     * @brief inequality operator
     * 
     * @param otherVector
     * @return true if the vectors are not equal
     * @return false if the vectors are equal
    */
    inline bool operator!=(const Vector& otherVector) const;


    /**
     * @brief overload cout to print a vector
     * 
     * @param os 
     * @param vector 
     * @return std::ostream& 
     */
    friend std::ostream& operator<<(std::ostream& os, const Vector& vector) {
        os << "[";
        for (size_t i = 0; i < N; i++) {
            os << vector.data[i];
            if (i < N - 1) {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }

    /**
     * @brief return a reference on a const std::array of the vector data
     * 
     * @return const std::array<T, N>& the data
     */
    inline const std::array<T, N>& arrayView() const { return data; }
};


//* ------------------ Implementation ------------------ *//

//sum of 2 vectors and returns a new vector

template <typename T, size_t N>
Vector<T, N> Vector<T, N>::operator+(const Vector<T, N>& otherVector) const {
    Vector<T, N> result;
    for (size_t i = 0; i < N; i++) {
        result.data[i] = data[i] + otherVector.data[i];
    }
    return result;
}

// substraction:

template <typename T, size_t N>
Vector<T, N> Vector<T, N>::operator-(const Vector<T, N>& otherVector) const {
    Vector<T, N> result;
    for (size_t i = 0; i < N; i++) {
        result.data[i] = data[i] - otherVector.data[i];
    }
    return result;
}

template <typename T, size_t N>
Vector<T, N> Vector<T, N>::operator-() const {
    Vector<T, N> result;
    for (size_t i = 0; i < N; i++) {
        result[i] = -data[i];
    }
    return result;
}

// add a vector to the current vector

template <typename T, size_t N>
Vector<T, N>& Vector<T, N>::operator+=(const Vector<T, N>& otherVector) {
    for (size_t i = 0; i < N; i++) {
        data[i] += otherVector.data[i];
    }
    return *this;
}

// -= operator overloading

template <typename T, size_t N>
Vector<T, N>& Vector<T, N>::operator-=(const Vector<T, N>& otherVector) {
    for (size_t i = 0; i < N; i++) {
        data[i] -= otherVector.data[i];
    }
    return *this; 
}

//element by element product of 2 vectors and returns a new vector

template <typename T, size_t N>
Vector<T, N> Vector<T, N>::operator*(const Vector<T, N>& otherVector) const {
    Vector<T, N> result;
    for (size_t i = 0; i < N; i++) {
        result.data[i] = data[i] * otherVector.data[i];
    }
    return result;
}

// return the dot product

template <typename T, size_t N>
T Vector<T, N>::dot(const Vector<T, N>& otherVector) const {
    T result{0};
    for (size_t i = 0; i < N; i++) {
        result += data[i] * otherVector.data[i];
    }
    return result;
}

template <typename T, size_t N>
Vector<T, N> Vector<T, N>::operator*(T scalar) const {
    Vector<T, N> result;
    for (size_t i = 0; i < N; i++) {
        result.data[i] = scalar * data[i];
    }
    return result;
}

//. *= operator overlading. multiply by scalar

template <typename T, size_t N>
Vector<T, N>& Vector<T, N>::operator*=(T scalar) {
    for (size_t i = 0; i < N; i++) {
        data[i] *= scalar;
    }
    return *this; 
}

//. *= operator overloading. multiply by a vector

template <typename T, size_t N>
Vector<T, N>& Vector<T, N>::operator*=(const Vector<T, N>& otherVector) {
    for (size_t i = 0; i < N; i++) {
        data[i] *= otherVector.data[i];
    }
    return *this; 
}

// division

//element by element division of 2 vectors and returns a new vector

template <typename T, size_t N>
Vector<T, N> Vector<T, N>::operator/(const Vector<T, N>& otherVector) const {
    Vector<T, N> result;
    for (size_t i = 0; i < N; i++) {
        result.data[i] = data[i] / otherVector.data[i];
    }
    return result;
}

template <typename T, size_t N>
Vector<T, N> Vector<T, N>::operator/(T scalar) const {
    Vector<T, N> result;
    for (size_t i = 0; i < N; i++) {
        result.data[i] = data[i] / scalar;
    }
    return result;
}

template <typename T, size_t N>
Vector<T, N>& Vector<T, N>::operator/=(T scalar) {
    for (size_t i = 0; i < N; i++) {
        data[i] /= scalar;
    }
    return *this; 
}

template <typename T, size_t N>
Vector<T, N>& Vector<T, N>::operator/=(const Vector<T, N>& otherVector) {
    for (size_t i = 0; i < N; i++) {
        data[i] /= otherVector.data[i];
    }
    return *this; 
}

// true modulo operation

template <typename T, size_t N>
Vector<T, N> Vector<T, N>::mod(const Vector<T, N>& otherVector) const {
    Vector<T, N> result;
    for (size_t i = 0; i < N; i++) {
        // cast the to T
        result.data[i] = static_cast<T>(std::fmod(std::fmod(data[i], otherVector[i]) + otherVector[i], otherVector[i]));
    }
    return result;
}

template <typename T, size_t N>
Vector<T, N> Vector<T, N>::mod(T scalar) const {
    Vector<T, N> result;
    for (size_t i = 0; i < N; i++) {
        result.data[i] = static_cast<T>(std::fmod(std::fmod(data[i], scalar) + scalar, scalar));
    }
    return result;
}

// return the euclidean norm of a vector 

template <typename T, size_t N>
double Vector<T, N>::norm() const {
    return std::sqrt(dot(*this));
}

// return the euclidean norm of a vector (static function)

template <typename T, size_t N>
double Vector<T, N>::norm(const Vector<T, N>& vector) {
    return vector.norm();
}

// return the absolute squared norm of a vector

template <typename T, size_t N>
double Vector<T, N>::squaredNorm() const {
    return dot(*this);
}

// return the absolute squared norm of a vector (static function)

template <typename T, size_t N>
double Vector<T, N>::squaredNorm(const Vector<T, N>& vector) {
    return vector.squaredNorm();
}

// return the euclidean distance between 2 vectors a and b (static function)

template <typename T, size_t N>
double Vector<T, N>::dist(const Vector<T, N>& a, const Vector<T, N>& b) {
    return Vector<T, N>::norm(a - b);
}

template <typename T, size_t N>
double Vector<T, N>::dist(const Vector<T, N>& otherVector) const {
    return Vector<T, N>::norm(*this - otherVector);
}

// return the squared distance between 2 vectors a and b (static function)

template <typename T, size_t N>
double Vector<T, N>::squaredDist(const Vector<T, N>& a, const Vector<T, N>& b) {
    return Vector<T, N>::squaredNorm(a - b);
}

template <typename T, size_t N>
double Vector<T, N>::squaredDist(const Vector<T, N>& otherVector) const {
    return Vector<T, N>::squaredNorm(*this - otherVector);
}

template <typename T, size_t N>
Vector<T, N> Vector<T, N>::periodicDiff(const Vector<T, N>& otherVector, const Vector<T, N>& domainSize) const {
    // we compute the "true" difference with periodic boundaries
    auto diff = *this - otherVector;
    for (size_t i = 0; i < N; i++) {
        if (diff[i] > domainSize[i] / 2.) {
            diff[i] -= domainSize[i];
        } else if (diff[i] < -domainSize[i] / 2.) {
            diff[i] += domainSize[i];
        }
    }
    return diff;
}

template <typename T, size_t N>
Vector<T, N> Vector<T, N>::reverse() const {
    Vector<T, N> result;
    for (size_t i = 0; i < N; i++) {
        result.data[i] = data[N - i - 1];
    }
    return result;
}

// equality operator

template <typename T, size_t N>
bool Vector<T, N>::operator==(const Vector<T, N>& otherVector) const {
    return data == otherVector.data;
}

// inequality operator

template <typename T, size_t N>
bool Vector<T, N>::operator!=(const Vector<T, N>& otherVector) const {
    return !(*this == otherVector);
}

}