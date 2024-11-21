#include "tmatrix.h"


#include <gtest.h>


template <typename T>
class TestTDynamicVector : public ::testing::Test
{
public:
	TDynamicVector<T>* vector;
	TDynamicVector<T>* vector_0;
	TDynamicVector<T>* vector_1;
	TDynamicVector<T>* vector_2;
	TDynamicVector<T>* vector_3;
	TDynamicVector<T>* vector_4;
	T* arr_1;
	T* arr_2;
	T* arr_3;
	T* arr_4;
	
	void SetUp()
	{

		arr_1 = new T[5]{ 1, 0, 1, 0, 1 };
		vector_1 = new TDynamicVector<T>(arr_1, 5);

		arr_2 = new T[5]{ 2, 1, 2, 1, 2 };
		vector_2 = new TDynamicVector<T>(arr_2, 5);

		arr_3 = new T[4]{ 1, 2, 3, 4 };
		vector_3 = new TDynamicVector<T>(arr_3, 4);

		arr_4 = new T[5]{ 3, 1, 3, 1, 3 };
		vector_4 = new TDynamicVector<T>(arr_4, 5);

		vector = new TDynamicVector<T>(*vector_1);

		
	}
	
	void TearDown()
	{
		delete vector;
		delete vector_1;
		delete vector_2;
		delete vector_3;
		delete vector_4;
		delete[] arr_1;
		arr_1 = nullptr;
		delete[] arr_2;
		arr_2 = nullptr;
		delete[] arr_3;
		arr_3 = nullptr;
		delete[] arr_4;
		arr_4 = nullptr;
	}

	void CreateDinamicVector(std::size_t size = 5)
	{
		vector = new TDynamicVector<T>(size);
		vector_0 = new TDynamicVector<T>(*vector);
	}
};

typedef ::testing::Types<int, float, double> VectorTypes;
TYPED_TEST_CASE(TestTDynamicVector, VectorTypes);


TYPED_TEST(TestTDynamicVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(this->CreateDinamicVector(1));
}

TYPED_TEST(TestTDynamicVector, cant_create_too_large_vector)
{
	ASSERT_ANY_THROW(this->CreateDinamicVector(MAX_VECTOR_SIZE + 1));
}

TYPED_TEST(TestTDynamicVector, throws_when_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(this->CreateDinamicVector(-1));
}

TYPED_TEST(TestTDynamicVector, can_create_copied_vector)
{
	ASSERT_NO_THROW(this->CreateDinamicVector());
}

TYPED_TEST(TestTDynamicVector, copied_vector_is_equal_to_source_one)
{
	EXPECT_EQ((*(this->vector)), (*(this->vector_1)));
}

TYPED_TEST(TestTDynamicVector, copied_vector_has_its_own_memory)
{
	EXPECT_NE((this->vector), (this->vector_1));
}

TYPED_TEST(TestTDynamicVector, can_get_size)
{
	EXPECT_EQ(5, (this->vector->size()));
}

TYPED_TEST(TestTDynamicVector, can_set_and_get_element)
{
	this->vector[0][0] = 1;
	EXPECT_EQ((this->vector[0][0]), 1);
}

TYPED_TEST(TestTDynamicVector, throws_when_set_element_with_negative_index)
{
	ASSERT_ANY_THROW(this->vector->at(-1) = 1);
}

TYPED_TEST(TestTDynamicVector, throws_when_set_element_with_too_large_index)
{
	ASSERT_ANY_THROW(this->vector->at(10));
}

TYPED_TEST(TestTDynamicVector, can_assign_vector_to_itself)
{
	*(this->vector) = *(this->vector);
	EXPECT_EQ((*(this->vector)), (*(this->vector)));
}

TYPED_TEST(TestTDynamicVector, can_assign_vectors_of_equal_size)
{
	*(this->vector) = *(this->vector_2);
	EXPECT_EQ(*(this->vector), *(this->vector_2));
}

TYPED_TEST(TestTDynamicVector, assign_operator_change_vector_size)
{
	*(this->vector) = *(this->vector_3);
	EXPECT_EQ(this->vector->size(), this->vector_3->size());
}

TYPED_TEST(TestTDynamicVector, can_assign_vectors_of_different_size)
{
	*(this->vector) = *(this->vector_3);
	EXPECT_EQ(this->vector->size(), this->vector_3->size());
	EXPECT_EQ(*(this->vector), *(this->vector_3));
}

TYPED_TEST(TestTDynamicVector, compare_equal_vectors_return_true)
{
	EXPECT_EQ(*(this->vector) == *(this->vector_1), true);
}

TYPED_TEST(TestTDynamicVector, compare_vector_with_itself_return_true)
{
	EXPECT_EQ(*(this->vector) == *(this->vector), true);
}

TYPED_TEST(TestTDynamicVector, vectors_with_different_size_are_not_equal)
{
	EXPECT_EQ(*(this->vector) == *(this->vector_3), false);
}

TYPED_TEST(TestTDynamicVector, can_add_scalar_to_vector)
{
	*(this->vector) = *(this->vector) + 1;
	EXPECT_EQ(*(this->vector), *(this->vector_2));
}

TYPED_TEST(TestTDynamicVector, can_subtract_scalar_from_vector)
{
	*(this->vector_2) = *(this->vector_2) - 1;
	EXPECT_EQ(*(this->vector_1), *(this->vector_2));
}

TYPED_TEST(TestTDynamicVector, can_multiply_scalar_by_vector)
{
	EXPECT_EQ(*(this->vector) * 1, *(this->vector));
}

TYPED_TEST(TestTDynamicVector, can_add_vectors_with_equal_size)
{
	EXPECT_EQ(*(this->vector_1) + *(this->vector_2), *(this->vector_4));
}

TYPED_TEST(TestTDynamicVector, cant_add_vectors_with_not_equal_size)
{
	ASSERT_ANY_THROW(*(this->vector_1) + *(this->vector_3));
}

TYPED_TEST(TestTDynamicVector, can_subtract_vectors_with_equal_size)
{
	EXPECT_EQ(*(this->vector_4) - *(this->vector_1), *(this->vector_2));
}

TYPED_TEST(TestTDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	ASSERT_ANY_THROW(*(this->vector_1) - *(this->vector_3));
}

TYPED_TEST(TestTDynamicVector, can_multiply_vectors_with_equal_size)
{
	EXPECT_EQ(6, *(this->vector_1) * *(this->vector_2));

}

TYPED_TEST(TestTDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	ASSERT_ANY_THROW(*(this->vector_1) * *(this->vector_3));
}
