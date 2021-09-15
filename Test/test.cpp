#include "pch.h"
#include "RaytraceFunctions/Util/vec3.h"
#include <iostream>

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(VectorTests, VecAdd) {
	vec3 a = vec3(3, -2, 5);
	vec3 b = vec3(-2, 3, 1);
	vec3 res = vec3(1, 1, 6);
	ASSERT_TRUE((a+b).equal(res));
}

TEST(VectorTests, VecSubtract) {
	vec3 a = vec3(3, -2, 5);
	vec3 b = vec3(-2, 3, 1);
	vec3 res = vec3(5, -5, 4);
	ASSERT_TRUE((a-b).equal(res));
}

TEST(VectorTests, VecMultVec) {
	vec3 a = vec3(1, 2, 3);
	vec3 b = vec3(-2, 3, 1);
	vec3 res = vec3(-2, 6, 3);
	ASSERT_TRUE((a*b).equal(res));
}

TEST(VectorTests, VecMultScal) {
	vec3 a = vec3(1, -2, 3);
	double b = 2;
	vec3 res = vec3(2, -4, 6);
	ASSERT_TRUE((a*b).equal(res));
}

TEST(VectorTests, VecMultFrac) {
	vec3 a = vec3(1, -2, 3);
	double b = 0.5;
	vec3 res = vec3(0.5, -1, 1.5);
	ASSERT_TRUE((a*b).equal(res));
}

TEST(VectorTests, VecDivVec) {
	vec3 a = vec3(1, 2, 3);
	vec3 b = vec3(-2, 2, 1);
	vec3 res = vec3(-0.5, 1, 3);
	ASSERT_TRUE((a/b).equal(res));
}

TEST(VectorTests, VecDivScal) {
	vec3 a = vec3(1, -2, 3);
	double b = 2;
	vec3 res = vec3(0.5, -1, 1.5);

	ASSERT_TRUE((a/b).equal(res));
}

TEST(VectorTests, VecDivFrac) {
	vec3 a = vec3(1, -2, 3);
	double b = 0.5;
	vec3 res = vec3(2, -4, 6);
	ASSERT_TRUE((a/b).equal(res));
}
