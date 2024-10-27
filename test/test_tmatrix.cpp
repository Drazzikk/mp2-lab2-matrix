#include "tmatrix.h"


#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
    TDynamicMatrix<int> matrix1(10);
    matrix1[0][0] = 10;
    TDynamicMatrix<int> matrix2(matrix1);

    EXPECT_EQ(matrix1, matrix2);
    
}


TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
    TDynamicMatrix<int> matrix1(10);
    TDynamicMatrix<int> matrix2(matrix1);

    EXPECT_NE(&matrix1, &matrix2);

}

TEST(TDynamicMatrix, can_get_size)
{
    TDynamicMatrix<int> matrix(10);
    EXPECT_EQ(matrix.size(), 10);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
    TDynamicMatrix<int> matrix(10);
    int* arr = new int[10] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    TDynamicVector<int> vector(arr, 10);
    delete[] arr;

    matrix[5] = vector;

    EXPECT_EQ(vector, matrix[5]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
    TDynamicMatrix<int> matrix(10);
    int* arr = new int[10] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    TDynamicVector<int> vector(arr, 10);
    delete[] arr;

    ASSERT_ANY_THROW(matrix.at(-1) = vector);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
    TDynamicMatrix<int> matrix(10);
    int* arr = new int[10] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    TDynamicVector<int> vector(arr, 10);
    delete[] arr;

    ASSERT_ANY_THROW(matrix.at(10) = vector);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
    TDynamicMatrix<int> matrix1(10);
    matrix1[0][0] = 10;
    TDynamicMatrix<int> matrix2(matrix1);

    matrix1 = matrix1;

    EXPECT_EQ(matrix1, matrix2);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
    TDynamicMatrix<int> matrix1(10);
    TDynamicMatrix<int> matrix2(10);
    matrix1[0][0] = 10;

    matrix2 = matrix1;

    EXPECT_EQ(matrix1, matrix2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
    TDynamicMatrix<int> matrix1(11);
    TDynamicMatrix<int> matrix2(10);

    matrix1 = matrix2;

    EXPECT_EQ(10, matrix1.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
    TDynamicMatrix<int> matrix1(10);
    TDynamicMatrix<int> matrix2(5);
    matrix1[0][0] = 10;
    matrix2[0][0] = 15;

    matrix1 = matrix2;

    EXPECT_EQ(matrix1, matrix2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
    TDynamicMatrix<int> matrix1(10);
    TDynamicMatrix<int> matrix2(10);
    matrix1[0][0] = 5;
    matrix2[0][0] = 5;

    EXPECT_TRUE(matrix1 == matrix2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
    TDynamicMatrix<int> matrix(10);
    matrix[0][0] = 5;

    EXPECT_TRUE(matrix == matrix);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
    TDynamicMatrix<int> matrix1(10);
    TDynamicMatrix<int> matrix2(15);

    EXPECT_FALSE(matrix1 == matrix2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
    TDynamicMatrix<int> matrix1(5);
    TDynamicMatrix<int> matrix2(5);
    matrix1[0][0] = 1;
    matrix1[1][1] = 1;
    matrix2[0][0] = 1;
    matrix2[1][1] = 1;
    int* arr1 = new int[5] { 2, 0, 0, 0, 0 };
    int* arr2 = new int[5] { 0, 2, 0, 0, 0 };
    TDynamicVector<int> v1(arr1, 5);
    TDynamicVector<int> v2(arr2, 5);
    delete[] arr1;
    delete[] arr2;
    TDynamicMatrix<int> res(5);
    res[0] = v1;
    res[1] = v2;

    matrix2 = matrix1 + matrix2;

    EXPECT_EQ(matrix2, res);

}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> matrix1(10);
    TDynamicMatrix<int> matrix2(5);

    ASSERT_ANY_THROW(matrix1 + matrix2);
}


TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
    TDynamicMatrix<int> matrix1(5);
    TDynamicMatrix<int> matrix2(5);
    matrix1[0][0] = 1;
    matrix1[1][1] = 1;
    matrix2[0][0] = 1;
    matrix2[1][1] = 1;
    int* arr1 = new int[5] { 0, 0, 0, 0, 0 };
    int* arr2 = new int[5] { 0, 0, 0, 0, 0 };
    TDynamicVector<int> v1(arr1, 5);
    TDynamicVector<int> v2(arr2, 5);
    delete[] arr1;
    delete[] arr2;
    TDynamicMatrix<int> res(5);
    res[0] = v1;
    res[1] = v2;

    matrix1 = matrix1 - matrix2;

    EXPECT_EQ(res, matrix1);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    TDynamicMatrix<int> matrix1(10);
    TDynamicMatrix<int> matrix2(5);

    ASSERT_ANY_THROW(matrix1 - matrix2);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_vector_equal_size)
{
    TDynamicMatrix<int> matrix(5);
    int* arr1 = new int[5] { 1, 1, 1, 1, 1 };
    int* arr2 = new int[5] { 0, 0, 0, 0, 0 };
    TDynamicVector<int> vector1(arr1, 5);
    TDynamicVector<int> vector2(arr2, 5);
    delete[] arr1;
    delete[] arr2;
    matrix[0] = vector1;
    TDynamicVector<int> res(5);
    res[0] = 0;

    EXPECT_EQ(res, matrix * vector2);
}

TEST(TDynamicMatrix, cant_multiply_matrices_with_vector_not_equal_size)
{
    TDynamicMatrix<int> matrix(5);
    TDynamicVector<int> vector(3);

    ASSERT_ANY_THROW(matrix * vector);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)
{
    TDynamicMatrix<int> matrix1(5);
    TDynamicMatrix<int> matrix2(5);
    int* arr1 = new int[5] { 2, 2, 2, 2, 2 };
    int* arr2 = new int[5] { 1, 1, 1, 1, 1 };
    TDynamicVector<int> vector1(arr1, 5);
    TDynamicVector<int> vector2(arr2, 5);
    delete[] arr1;
    delete[] arr2;
    matrix1[0] = vector1;
    matrix2[0] = vector2;
    TDynamicMatrix<int> res(5);
    res[0] = vector2 * 2;

    EXPECT_EQ(res, matrix1 * matrix2);
}

TEST(TDynamicMatrix, cant_multiply_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> matrix1(10);
    TDynamicMatrix<int> matrix2(5);

    ASSERT_ANY_THROW(matrix1 * matrix2);
}
