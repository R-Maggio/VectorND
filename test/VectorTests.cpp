#include "Vector.hpp"
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include <cmath>

using namespace VectorND;

TEST(VectorTests, constructor) {
    Vector<double, 3> vf1;
    EXPECT_DOUBLE_EQ(0.0, vf1[0]);
    EXPECT_DOUBLE_EQ(0.0, vf1[1]);
    EXPECT_DOUBLE_EQ(0.0, vf1[2]);

    Vector<double, 3> vf2{{1., 2.0, 3.0}};

    // test integer constructor
    Vector<int, 3> vi1{{1, 2, 3}};
    EXPECT_EQ(1, vi1[0]);
    EXPECT_EQ(2, vi1[1]);
    EXPECT_EQ(3, vi1[2]);

    // test static casting int to double
    Vector<int, 3> vi3{{1, 2, 3}};
    Vector<double, 3> vf3 = static_cast<Vector<double, 3>>(vi3);
    EXPECT_EQ(vf3, (Vector<double, 3>{{1., 2., 3.}}));
    // test static casting double to int
    Vector<double, 3> vf4{{1.1, 2.0, 3.0}};
    Vector<int, 3> vi4 = static_cast<Vector<int, 3>>(vf4);
    EXPECT_EQ(vi4, (Vector<int, 3>{{1, 2, 3}}));
}

TEST(VectorTests, testEquality) {
    Vector<double, 3> vf1({1.0, 2.0, 4.0});
    Vector<double, 3> vf2({1.0, 2.0, 3.0});
    Vector<double, 3> vf3(vf2);
    Vector<double, 4> vf4({1.0, 2.0, 4.0, 5.0});

    // test equality
    EXPECT_EQ(vf3, vf2);
    // not equal
    EXPECT_NE(vf1, vf2);

    // test with int
    Vector<int, 3> vi1({1, 2, 4});
    Vector<int, 3> vi2({1, 2, 3});
    Vector<int, 3> vi3(vi2);
    Vector<int, 4> vi4({1, 2, 4, 5});

    // test equality
    EXPECT_EQ(vi3, vi2);
    // not equal
    EXPECT_NE(vi1, vi2);

    // test access
    EXPECT_EQ(vf1[0], 1.0);
    EXPECT_EQ(vf1[1], 2.0);
    EXPECT_EQ(vf1[2], 4.0);
    EXPECT_EQ(vi1[0], 1);
    EXPECT_EQ(vi1[1], 2);
    EXPECT_EQ(vi1[2], 4);

    // change the value of the vector
    vf2[2] = 4.0;
    // test equality
    EXPECT_EQ(vf1, vf2);        

    // test at
    EXPECT_EQ(vf1.at(0), 1.0);
    EXPECT_EQ(vf1.at(1), 2.0);
    EXPECT_EQ(vi1.at(0), 1);
    EXPECT_EQ(vi1.at(1), 2);
}

TEST(VectorTests, additionSubtraction) {
    // test vector addition
    Vector<double, 3> vf1({1.0, 2.0, 4.0});
    Vector<double, 3> vf2({1.0, 2.0, 3.0});
    auto vf3 = vf1 + vf2;
    Vector<double, 3> vf4({2.0, 4.0, 7.0});
    EXPECT_EQ(vf3, vf4);
    // intergers
    Vector<int, 3> vi1({1, 2, 4});
    Vector<int, 3> vi2({-1, -2, -4});
    auto vi3 = vi1 + vi2;
    Vector<int, 3> vi4({0, 0, 0});
    EXPECT_EQ(vi3, vi4);

    // test subtraction
    // be careful with numerical errors
    auto vf5 = vf3 - vf2;
    auto vf6 = vf3 - vf1;
    EXPECT_EQ(vf5, vf1);
    EXPECT_EQ(vf6, vf2);
    // intergers
    auto vi5 = vi3 - vi2;
    auto vi6 = vi3 - vi1;
    EXPECT_EQ(vi5, vi1);
    EXPECT_EQ(vi6, vi2);
    // test +=
    vf1 += vf2;
    EXPECT_EQ(vf1, vf4);
    vi1 += vi2;
    EXPECT_EQ(vi1, vi4);
    // test -=
    vf1 -= vf2;
    EXPECT_EQ(vf1, ( Vector<double, 3>({1.0, 2.0, 4.0}) ) );
    vi1 -= vi2;
    EXPECT_EQ(vi1, (Vector<int, 3>({1, 2, 4})) );
}

TEST(VectorTests, multiplication) {
    // test vector multiplication
    Vector<double, 3> vf1({1.0, 2.0, 4.0});
    Vector<double, 3> vf2({1.0, 2.0, 3.0});
    auto vf3 = vf1 * vf2;
    Vector<double, 3> vf4({1.0, 4.0, 12.0});
    EXPECT_EQ(vf3, vf4);

    // test scalar multiplication
    auto vf5 = vf1 * 2.0;
    auto vf6 = 2.0 * vf1;
    EXPECT_EQ(vf5, vf6);
    EXPECT_EQ(vf5, (Vector<double, 3>({2.0, 4.0, 8.0})));
    // intergers
    Vector<int, 3> vi1({1, 2, 4});
    auto vi2 = vi1 * 2;
    EXPECT_EQ(vi2, (Vector<int, 3>({2, 4, 8})));
    // test scalar multiplication
    auto vi3 = vi1 * 2;
    auto vi4 = 2 * vi1;
    EXPECT_EQ(vi3, vi4);
    EXPECT_EQ(vi3, (Vector<int, 3>({2, 4, 8})));
    // test *=
    vf1 *= 2.0;
    EXPECT_EQ(vf1, (Vector<double, 3>({2.0, 4.0, 8.0})));
    vi1 *= 3;
    EXPECT_EQ(vi1, (Vector<int, 3>({3, 6, 12})));
    // test *= with vectors
    vf1 *= Vector<double, 3>({3.0, 1.0, 2.0});
    EXPECT_EQ(vf1, (Vector<double, 3>({6.0, 4.0, 16.0})));
    vi1 *= Vector<int, 3>({2, 3, 4});
    EXPECT_EQ(vi1, (Vector<int, 3>({6, 18, 48})));
}

TEST(VectorTests, division) {
    // test vector division
    // intergers
    Vector<int, 3> vi1({1, 2, 4});
    Vector<int, 3> vi2({2, 4, 8});
    auto vi3 = vi2 / vi1;
    Vector<int, 3> vi4({2, 2, 2});
    EXPECT_EQ(vi3, vi4);
    // scalar
    auto vi5 = vi2 / 2;
    auto vi6 = 8 / Vector<int, 4>({2, 4, 8, 9});
    EXPECT_EQ(vi5, vi1);
    EXPECT_EQ(vi6, (Vector<int, 4>({4, 2, 1, 0})));
    // /=
    auto vi7 = Vector<int, 5>({2, 4, 8, 9, 10});
    vi2 /= 2;
    vi7 /= 3;
    EXPECT_EQ(vi1, vi2);
    EXPECT_EQ(vi7, (Vector<int, 5>({0, 1, 2, 3, 3})));
    // vect
    auto vi8 = Vector<int, 5>({2, 4, 8, 9, 10});
    vi8 /= Vector<int, 5>({1, 2, 3, 4, 5});
    EXPECT_EQ(vi8, (Vector<int, 5>({2, 2, 2, 2, 2})));

    // same with doubles
    Vector<double, 3> vf1({1.0, 2.0, 4.0});
    Vector<double, 3> vf2({2.0, 4.0, 8.0});
    auto vf3 = vf2 / vf1;
    Vector<double, 3> vf4({2.0, 2.0, 2.0});
    EXPECT_EQ(vf3, vf4);
    // scalar
    auto vf5 = vf2 / 2.0;
    auto vf6 = 8.0 / Vector<double, 4>({2.0, 4.0, 8.0, 9.0});
    EXPECT_EQ(vf5, vf1);
    EXPECT_EQ(vf6, (Vector<double, 4>({8./2.0, 8./4.0, 8./8.0, 8./9.0})));
    // /=
    auto vf7 = Vector<double, 5>({2.0, 4.0, 8.0, 9.0, 10.0});
    vf2 /= 2.0;
    vf7 /= 3.0;
    EXPECT_EQ(vf2, (Vector<double, 3>({2./2.0, 4./2.0, 8./2.0})));
    EXPECT_EQ(vf7, (Vector<double, 5>({2./3.0, 4./3.0, 8./3.0, 9./3.0, 10./3.0})));
    // vect
    auto vf8 = Vector<double, 5>({2.0, 4.0, 8.0, 9.0, 10.0});
    vf8 /= Vector<double, 5>({1.0, 2.0, 3.0, 4.0, 5.0});
    EXPECT_EQ(vf8, (Vector<double, 5>({2./1.0, 4./2.0, 8./3.0, 9./4.0, 10./5.0})));

}

TEST(VectorTests, dot) {
    // test vector dot product
    Vector<double, 3> vf1({1.0, 2.0, 4.0});
    Vector<double, 3> vf2({3., 4., 5.});
    auto rdot1 = vf1.dot(vf2);
    EXPECT_DOUBLE_EQ(rdot1, 31.0);
    // intergers
    Vector<int, 3> vi1({1, 2, 4});
    Vector<int, 3> vi2({-2, 4, 8});
    auto rdot2 = vi1.dot(vi2);
    EXPECT_EQ(rdot2, 38);
}

TEST(VectorTests, modulo) {
    // test vector modulo operator
    Vector<double, 5> vf1({-17.0, 2.0, 3.0, -3.0, 5.0});
    Vector<double, 5> vf2({5.0, 2.0, 2.0, 2.0, 3.0});
    auto vf3 = vf1.mod(vf2);
    EXPECT_EQ(vf3, (Vector<double, 5>({3.0, 0.0, 1.0, 1.0, 2.0})));
    // test mod scalar
    Vector<double, 5> vf4({-17.0, 2.0, 3.0, -3.0, 5.0});
    auto vf5 = vf4.mod(2.0);
    EXPECT_EQ(vf5, (Vector<double, 5>({1.0, 0.0, 1.0, 1.0, 1.0})));
    // test modulo with intergers
    Vector<int, 5> vi1({-17, 2, 3, -3, 5});
    Vector<int, 5> vi2({5, 2, 2, 2, 3});
    auto vi3 = vi1.mod(vi2);
    EXPECT_EQ(vi3, (Vector<int, 5>({3, 0, 1, 1, 2})));
    // test mod scalar with intergers
    Vector<int, 5> vi4({-17, 2, 3, -3, 5});
    auto vi5 = vi4.mod(2);
    EXPECT_EQ(vi5, (Vector<int, 5>({1, 0, 1, 1, 1})));
}

TEST(VectorTests, norm) {
    // test vector norm
    Vector<double, 5> vf1{{1., 2., 3., 4., 5.}};
    Vector<int, 5> vi1{{1, 2, 3, 4, 5}};
    double n1 = std::sqrt(1 + 4 + 9 + 16 + 25);
    EXPECT_DOUBLE_EQ(n1, vi1.norm());
    EXPECT_DOUBLE_EQ(n1, vf1.norm());
    EXPECT_DOUBLE_EQ(n1, (Vector<double, 5>::norm(vi1)));
    EXPECT_DOUBLE_EQ(n1, (Vector<int, 5>::norm(vf1)));

    // test squaredNorm
    double squared1 = 1 + 4 + 9 + 16 + 25;
    EXPECT_DOUBLE_EQ(squared1, vi1.squaredNorm());
    EXPECT_DOUBLE_EQ(squared1, vf1.squaredNorm());
    EXPECT_DOUBLE_EQ(squared1, (Vector<double, 5>::squaredNorm(vi1)));
    EXPECT_DOUBLE_EQ(squared1, (Vector<int, 5>::squaredNorm(vf1)));

    // test dist
    auto vf2 = -vf1;
    auto vf3 = -2. * vf1;
    auto vi2 = -vi1;
    auto vi3 = -2 * vi1;
    EXPECT_DOUBLE_EQ(vf2.dist(vf3), n1);
    EXPECT_DOUBLE_EQ(vf2.squaredDist(vf3), squared1);
    EXPECT_DOUBLE_EQ(vi2.dist(vi3), n1);
    EXPECT_DOUBLE_EQ(vi2.squaredDist(vi3), squared1);
}

TEST(VectorTests, periodicDiff) {
    // test periodicDiff
    Vector<double, 2> d1{{10., 10.}};
    Vector<double, 2> vf1({1., 1.});
    Vector<double, 2> vf2({9., 9.});
    auto diff1 = vf1.periodicDiff(vf2, d1);
    EXPECT_EQ(diff1, (Vector<double, 2>({2., 2.})));
    // another test
    Vector<double, 2> vf3{{1., 4.}};
    Vector<double, 2> vf4({9., 5.});
    auto diff2 = vf3.periodicDiff(vf4, d1);
    auto diff3 = vf4.periodicDiff(vf3, d1);
    EXPECT_EQ(diff2, (Vector<double, 2>({2., -1.})));
    EXPECT_EQ(diff3, (Vector<double, 2>({-2., 1.})));

    // test periodicDiff with intergers
    Vector<int, 2> vi1({1, 1});
    Vector<int, 2> vi2({9, 9});
    auto diff4 = vi1.periodicDiff(vi2, d1);
    EXPECT_EQ(diff4, (Vector<int, 2>({2, 2})));
    // another test
    Vector<int, 2> vi3({1, 4});
    Vector<int, 2> vi4({9, 5});
    auto diff5 = vi3.periodicDiff(vi4, d1);
    auto diff6 = vi4.periodicDiff(vi3, d1);
    EXPECT_EQ(diff5, (Vector<int, 2>({2, -1})));
    EXPECT_EQ(diff6, (Vector<int, 2>({-2, 1})));
}

TEST(VectorTests, reverse) {
    // test reverse
    Vector<double, 5> vf1{{1., 2., 3., 4., 5.}};
    Vector<int, 5> vi1{{1, 2, 3, 4, 5}};
    auto vf2 = vf1.reverse();
    auto vi2 = vi1.reverse();
    EXPECT_EQ(vf2, (Vector<double, 5>({5., 4., 3., 2., 1.})));
    EXPECT_EQ(vi2, (Vector<int, 5>({5, 4, 3, 2, 1})));
}

TEST(VectorTests, equal) {
    // test equal
    Vector<double, 5> vf1{{1., 2., 3., 4., 5.}};
    auto vf2 = vf1;
    Vector<double, 5> vf3{{1., 2., 3., 5., 5.}};
    EXPECT_TRUE(vf1 == vf2);
    EXPECT_FALSE(vf1 == vf3);
    // test inequality
    EXPECT_TRUE(vf1 != vf3);
    EXPECT_FALSE(vf1 != vf2);
    // test equal with intergers
    Vector<int, 5> vi1{{1, 2, 3, 4, 5}};
    auto vi2 = vi1;
    Vector<int, 5> vi3{{1, 2, 3, 5, 5}};
    EXPECT_TRUE(vi1 == vi2);
    EXPECT_FALSE(vi1 == vi3);
    // test inequality with intergers
    EXPECT_TRUE(vi1 != vi3);
    EXPECT_FALSE(vi1 != vi2);
}

TEST(VectorTests, iterator) {
    // test iterator
    Vector<double, 5> vf1{{1., 2., 3., 4., 5.}};
    std::array<double, 5> arr = {1., 2., 3., 4., 5.};
    Vector<int, 5> vi1{{1, 2, 3, 4, 5}};
    std::array<int, 5> arr2 = {1, 2, 3, 4, 5};
    int i = 0;
    for (double& d : vf1) {
        EXPECT_DOUBLE_EQ(d, arr[i]);
        EXPECT_EQ(d, arr2[i]);
        i++;
    }
}

TEST(VectorTests, arrayView) {
    // test arrayView
    Vector<double, 5> vf1{{1., 2., 3., 4., 5.}};
    auto arr = vf1.arrayView();
    EXPECT_EQ(arr.size(), 5);
    EXPECT_EQ(arr[0], 1.);
    EXPECT_EQ(arr[1], 2.);
    EXPECT_EQ(arr[2], 3.);
    EXPECT_EQ(arr[3], 4.);
    EXPECT_EQ(arr[4], 5.);
}

    //************ TESTS with double ************
    // auto v1 = Vector<double, 3>({1, 2, 3});
    // Vector<double, 2> vector = Vector<double, 2>(1, 2);
    // std::cout << vector << '\n';

    // std::cout << "Vector<double, 2>(vector);" << '\n';
    // std::cout << Vector<double, 2>(vector) << '\n';

    // std::cout << "vector;" << '\n';
    // std::cout << vector << '\n';

    // std::cout << "vector.set(4, 10);" << '\n';
    // vector.set(4, 10);
    // std::cout << vector << '\n';

    // std::cout << "vector = Vector<double, 2>(2, 3)" << '\n';
    // vector = Vector<double, 2>(2, 3);
    // std::cout << vector << '\n';

    // std::cout << "vector + Vector<double, 2>(1, 1)" << '\n';
    // std::cout << vector + Vector<double, 2>(1, 1) << '\n';

    // std::cout << "vector - Vector<double, 2>(1, 1)" << '\n';
    // std::cout << vector - Vector<double, 2>(1, 1) << '\n';

    // std::cout << "vector += Vector<double, 2>(1, 1);" << '\n';
    // vector += Vector<double, 2>(1, 1);
    // std::cout << vector << '\n';

    // std::cout << "vector -= Vector<double, 2>(1, 1);" << '\n';
    // vector -= Vector<double, 2>(1, 1);
    // std::cout << vector << '\n';

    // std::cout << "vector.dot(Vector<double, 2>(2, 2))" << '\n';
    // std::cout << vector.dot(Vector<double, 2>(2, 2)) << '\n';

    // std::cout << "0.5*vector" << '\n';
    // std::cout << 0.5*vector << '\n';

    // std::cout << "vector*0.5" << '\n';
    // std::cout << vector*0.5 << '\n';

    // vector *= 0.5;
    // std::cout << "vector *= 0.5" << '\n';
    // std::cout << vector << '\n';

    // std::cout << "Vector<double, 2>(-12.7, 1500.9) % 10.5" << '\n';
    // std::cout << Vector<double, 2>(-12.7, 1500.9) % 10.5 << '\n';

    // std::cout << "vector.norm()" << '\n';
    // std::cout << vector.norm() << '\n';

    // std::cout << "Vector<double, 2>::norm(vector)" << '\n';
    // std::cout << Vector<double, 2>::norm(vector) << '\n';

    // std::cout << "Vector<double, 2>::squaredNorm(vector)" << '\n';
    // std::cout << Vector<double, 2>::squaredNorm(vector) << '\n';

    // std::cout << "vector.squaredNorm()" << '\n';
    // std::cout << vector.squaredNorm() << '\n';

    // std::cout <<  "Vector<double, 2>(2, 3).PeriodicDiff(Vector<double, 2>(8, 9), Vector<double, 2>(10., 10.))" << '\n';
    // std::cout <<  Vector<double, 2>(2, 3).PeriodicDiff(Vector<double, 2>(8, 9), Vector<double, 2>(10., 10.)) << '\n';

    // std::cout <<  "Vector<double, 2>(8, 9).PeriodicDiff(Vector<double, 2>(2, 3), Vector<double, 2>(10., 10.))" << '\n';
    // std::cout <<  Vector<double, 2>(8, 9).PeriodicDiff(Vector<double, 2>(2, 3), Vector<double, 2>(10., 10.)) << '\n';

    // std::cout << "Vector<double, 2>::dist(Vector<double, 2>(1, 2), Vector<double, 2>(5, 4))" << '\n';
    // std::cout << Vector<double, 2>::dist(Vector<double, 2>(1, 2), Vector<double, 2>(5, 4)) << '\n';

    // std::cout << "Vector<double, 2>::squaredDist(Vector<double, 2>(1, 2), Vector<double, 2>(5, 4))" << '\n';
    // std::cout << Vector<double, 2>::squaredDist(Vector<double, 2>(1, 2), Vector<double, 2>(5, 4)) << '\n';
