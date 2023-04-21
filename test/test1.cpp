#include <gtest/gtest.h>

#include <U_ptr.hpp>

TEST(U_ptrTest, Constructor) {
    U_ptr<int> ptr;
    EXPECT_FALSE(ptr);
}

TEST(U_ptrTest, ConstructorWithPtr) {
    U_ptr<int> ptr(new int(42));
    EXPECT_EQ(*ptr, 42);
}

TEST(U_ptrTest, ConstructorWithNullptr) {
    U_ptr<int> ptr(nullptr);
    EXPECT_FALSE(ptr);
}

TEST(U_ptrTest, MoveConstructor) {
    U_ptr<int> ptr1(new int(42));
    U_ptr<int> ptr2(std::move(ptr1));
    EXPECT_FALSE(ptr1);
    EXPECT_EQ(*ptr2, 42);
}

TEST(U_ptrTest, MoveAssignmentOperator) {
    U_ptr<int> ptr1(new int(42));
    U_ptr<int> ptr2(new int(100));
    ptr2 = std::move(ptr1);
    EXPECT_FALSE(ptr1);
    EXPECT_EQ(*ptr2, 42);
}

TEST(U_ptrTest, DereferenceOperator) {
    U_ptr<int> ptr(new int(42));
    EXPECT_EQ(*ptr, 42);
}

TEST(U_ptrTest, ArrowOperator) {
    struct Foo {
        int value;
        Foo(int value) : value(value) {
        }
    };
    U_ptr<Foo> ptr(new Foo(42));
    EXPECT_EQ(ptr->value, 42);
}

TEST(U_ptrTest, OperatorBool) {
    U_ptr<int> ptr;
    EXPECT_FALSE(ptr);
    ptr.reset(new int(42));
    EXPECT_TRUE(ptr);
}

TEST(U_ptrTest, Release) {
    int* raw_ptr = new int(42);
    U_ptr<int> ptr(raw_ptr);
    int* released_ptr = ptr.release();
    EXPECT_EQ(raw_ptr, released_ptr);
    delete released_ptr;
}

TEST(U_ptrTest, Reset) {
    U_ptr<int> ptr(new int(42));
    ptr.reset(new int(100));
    EXPECT_EQ(*ptr, 100);
}

TEST(U_ptrTest, Swap) {
    U_ptr<int> ptr1(new int(42));
    U_ptr<int> ptr2(new int(100));
    ptr1.swap(ptr2);
    EXPECT_EQ(*ptr1, 100);
    EXPECT_EQ(*ptr2, 42);
}

TEST(U_ptrTest, Get) {
    int* raw_ptr = new int(42);
    U_ptr<int> ptr(raw_ptr);
    EXPECT_EQ(ptr.get(), raw_ptr);
}

TEST(U_ptrTest, CopyConstructorIsDeleted) {
    EXPECT_TRUE(std::is_copy_constructible<U_ptr<int>>::value == false);
}

TEST(U_ptrTest, CopyAssignmentOperatorIsDeleted) {
    EXPECT_TRUE(std::is_copy_assignable<U_ptr<int>>::value == false);
}
//----------------------------------

TEST(U_ptrArrayTest, DefaultConstruction) {
    U_ptr<int[]> up;
    EXPECT_FALSE(up);
    EXPECT_EQ(nullptr, up.get());
}

TEST(U_ptrArrayTest, ConstructWithNullptr) {
    U_ptr<int[]> up(nullptr);
    EXPECT_FALSE(up);
    EXPECT_EQ(nullptr, up.get());
}

TEST(U_ptrArrayTest, ConstructWithPointer) {
    int* arr = new int[5];
    U_ptr<int[]> up(arr);
    EXPECT_TRUE(up);
    EXPECT_EQ(arr, up.get());
}

TEST(U_ptrArrayTest, Release) {
    int* arr = new int[5];
    U_ptr<int[]> up(arr);
    int* released_arr = up.release();
    EXPECT_EQ(arr, released_arr);
    EXPECT_FALSE(up);
    EXPECT_EQ(nullptr, up.get());
    delete[] released_arr;
}

TEST(U_ptrArrayTest, Reset) {
    int* arr1 = new int[5];
    int* arr2 = new int[3];
    U_ptr<int[]> up(arr1);
    up.reset(arr2);
    EXPECT_TRUE(up);
    EXPECT_EQ(arr2, up.get());
}

TEST(U_ptrArrayTest, ResetWithNullptr) {
    U_ptr<int[]> up(new int[5]);
    up.reset(nullptr);
    EXPECT_FALSE(up);
    EXPECT_EQ(nullptr, up.get());
}

TEST(U_ptrArrayTest, SwapArray) {
    const int kSize = 3;
    U_ptr<int[]> ptr1(new int[kSize]{1, 2, 3});
    U_ptr<int[]> ptr2(new int[kSize]{4, 5, 6});

    ptr1.swap(ptr2);

    EXPECT_EQ(4, ptr1[0]);
    EXPECT_EQ(5, ptr1[1]);
    EXPECT_EQ(6, ptr1[2]);
    EXPECT_EQ(1, ptr2[0]);
    EXPECT_EQ(2, ptr2[1]);
    EXPECT_EQ(3, ptr2[2]);
}

TEST(U_ptrArrayTest, ArrowOperator) {
    class MyClass {
      public:
        int x;
    };
    U_ptr<MyClass[]> up(new MyClass[3]);
    up->x = 42;
    ASSERT_EQ(42, up->x);
}

TEST(U_ptrArrayTest, SubscriptOperator) {
    U_ptr<int[]> up(new int[5]);
    up[0] = 10;
    up[1] = 20;
    EXPECT_EQ(10, up[0]);
    EXPECT_EQ(20, up[1]);
}

TEST(U_ptrArrayTest, DereferenceOperator) {
    U_ptr<int[]> up(new int[5]);
    *up = 10;
    EXPECT_EQ(10, *up);
}

TEST(U_ptrArrayTest, CopyConstructorIsDeleted) {
    EXPECT_TRUE(std::is_copy_constructible<U_ptr<int[]>>::value == false);
}

TEST(U_ptrArrayTest, CopyAssignmentOperatorIsDeleted) {
    EXPECT_TRUE(std::is_copy_assignable<U_ptr<int[]>>::value == false);
}

TEST(U_ptrMakeUptrTest, MakeUptrTest) {
    U_ptr<int> p = make_uptr<int>(10);

    ASSERT_NE(nullptr, p.get());

    ASSERT_EQ(10, *p);
}

TEST(U_ptrMakeUptrTest, MakeUptrArrTest) {
    U_ptr<int[]> p = make_uptr<int[]>(10);

    ASSERT_NE(nullptr, p.get());

    for (int i = 0; i < 10; i++) {
        ASSERT_EQ(0, p[i]);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
