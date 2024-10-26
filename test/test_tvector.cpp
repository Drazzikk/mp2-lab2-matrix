#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	int arr[5] = { 5, 4 , 3, 2, 1 };
	TDynamicVector<int> v1(arr, 5);
	TDynamicVector<int> v2(v1);

	ASSERT_EQ(v1, v2);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v1(4), v2(4);
	TDynamicVector<int>* p1 = &v1;
	TDynamicVector<int>* p2 = &v2;
	EXPECT_NE(p1, p2);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
  TDynamicVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(5);
	ASSERT_ANY_THROW((v.at(-2) = 10));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(5);
	ASSERT_ANY_THROW(v.at(MAX_VECTOR_SIZE + 1) = 3);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(5);
	ASSERT_NO_THROW(v = v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(5);

	for (size_t i = 0; i < 5; i++) {
		v1[i] = i;
	}

	v2 = v1;

	ASSERT_EQ(v1, v2);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	int arr1[5] {5, 4, 3, 2, 1};
	TDynamicVector<int> v1(arr1, 5);
	
	int arr2[10] { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

	TDynamicVector<int> v2(arr2, 10);

	v1 = v2;

	EXPECT_EQ(v1.size(), v2.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(10);

	for (size_t i = 0; i < 5; i++) 
		v1[i] = i;
	
	v2 = v1;
	ASSERT_EQ(v1, v2);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v1(5);

	for (size_t i = 0; i < 5; i++) 
		v1[i] = i;
	

	TDynamicVector<int> v2(v1);

	ASSERT_EQ(v1 == v2, true);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v(5);

	for (size_t i = 0; i < 5; i++)
		v[i] = i;

	ASSERT_EQ(v == v, true);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(10);

	for (size_t i = 0; i < 5; i++)
		v1[i] = i;

	for (size_t i = 0; i < 10; i++)
		v1[i] = i + 20;
	

	ASSERT_EQ(v1 == v2, false);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	int arr[5]{ 10, 9, 8, 7, 6 };
	TDynamicVector<int> v1(arr, 5);

	int scalar = 1;

	TDynamicVector<int> v2(5);

	for (size_t i = 0; i < 5; i++)
		v2[i] = v1[i] + scalar;

	v1 = v1 + scalar;

	
	ASSERT_EQ(v1, v2);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	int arr[5]{ 10, 9, 8, 7, 6 };
	TDynamicVector<int> v1(arr, 5);

	int scalar = 1;

	TDynamicVector<int> v2(5);

	for (size_t i = 0; i < 5; i++)
		v2[i] = v1[i] - scalar;

	v1 = v1 - scalar;

	ASSERT_EQ(v1, v2);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	int arr[5]{ 10, 9, 8, 7, 6 };
	TDynamicVector<int> v1(arr, 5);

	int scalar = 10;

	TDynamicVector<int> v2(5);

	for (size_t i = 0; i < 5; i++)
		v2[i] = v1[i] * scalar;

	v1 = v1 * scalar;

	ASSERT_EQ(v1, v2);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	int arr1[5]{ 1, 2, 3, 4, 5 };
	int arr2[5]{ 5, 4, 3, 2, 1 };
	int arr4[5]{ 6, 6, 6, 6, 6 };
	TDynamicVector<int> v1(arr1, 5);
	TDynamicVector<int> v2(arr2, 5);
	TDynamicVector<int> v3 = v1 + v2;
	TDynamicVector<int> v4(arr4, 5);

	ASSERT_EQ(v3, v4);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(10);

	ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	int arr1[5]{ 1, 2, 3, 4, 5 };
	int arr2[5]{ 5, 4, 3, 2, 1 };
	int arr4[5]{ 4, 2, 0, -2, -4 };
	TDynamicVector<int> v1(arr1, 5);
	TDynamicVector<int> v2(arr2, 5);
	TDynamicVector<int> v3 = v2 - v1;
	TDynamicVector<int> v4(arr4, 5);

	ASSERT_EQ(v3, v4);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(10);

	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	int arr1[5]{ 1, 2, 3, 4, 5 };
	int arr2[5]{ 5, 4, 3, 2, 1 };
	int arr4[5]{ 5, 8, 9, 8, 5 };
	TDynamicVector<int> v1(arr1, 5);
	TDynamicVector<int> v2(arr2, 5);
	int a = v2 * v1;
	int b = 0;
	for (int i = 0; i < 5; i++)
		b += arr4[i];

	ASSERT_EQ(a, b);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(10);

	ASSERT_ANY_THROW(v1 * v2);
}

