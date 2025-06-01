#include "circular_list.h"
#include <gtest/gtest.h>
#include <algorithm>
#include <vector>
#include <string>

using namespace my;

TEST(CircularListTest, DefaultConstructor) {
    circular_list<int> list;
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);
}

TEST(CircularListTest, PushBack) {
    circular_list<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);
}

TEST(CircularListTest, PushFront) {
    circular_list<int> list;
    list.push_front(3);
    list.push_front(2);
    list.push_front(1);
    
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);
}

TEST(CircularListTest, PopBack) {
    circular_list<int> list = {1, 2, 3};
    list.pop_back();
    
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.back(), 2);
}

TEST(CircularListTest, PopFront) {
    circular_list<int> list = {1, 2, 3};
    list.pop_front();
    
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 2);
}

TEST(CircularListTest, Iterator) {
    circular_list<int> list = {1, 2, 3};
    std::vector<int> result;
    
    for (auto it = list.begin(); it != list.end(); ++it) {
        result.push_back(*it);
    }
    
    EXPECT_EQ(result, std::vector<int>({1, 2, 3}));
}

TEST(CircularListTest, ConstIterator) {
    const circular_list<int> list = {1, 2, 3};
    std::vector<int> result;
    
    for (auto it = list.begin(); it != list.end(); ++it) {
        result.push_back(*it);
    }
    
    EXPECT_EQ(result, std::vector<int>({1, 2, 3}));
}

TEST(CircularListTest, ReverseIterator) {
    circular_list<int> list = {1, 2, 3};
    std::vector<int> result;
    
    for (auto it = list.rbegin(); it != list.rend(); ++it) {
        result.push_back(*it);
    }
    
    EXPECT_EQ(result, std::vector<int>({3, 2, 1}));
}

TEST(CircularListTest, Insert) {
    circular_list<int> list = {1, 3};
    auto it = list.begin();
    ++it;
    list.insert(it, 2);
    
    std::vector<int> result(list.begin(), list.end());
    EXPECT_EQ(result, std::vector<int>({1, 2, 3}));
}

TEST(CircularListTest, Erase) {
    circular_list<int> list = {1, 2, 3};
    auto it = list.begin();
    ++it;
    list.erase(it);
    
    std::vector<int> result(list.begin(), list.end());
    EXPECT_EQ(result, std::vector<int>({1, 3}));
}

TEST(CircularListTest, Clear) {
    circular_list<int> list = {1, 2, 3};
    ASSERT_EQ(list.size(), 3);
    
    list.clear();
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);
}

TEST(CircularListTest, CopyConstructor) {
    circular_list<int> list1 = {1, 2, 3};
    circular_list<int> list2(list1);
    
    EXPECT_EQ(list1.size(), list2.size());
    EXPECT_TRUE(std::equal(list1.begin(), list1.end(), list2.begin()));
}

TEST(CircularListTest, MoveConstructor) {
    circular_list<int> list1 = {1, 2, 3};
    circular_list<int> list2(std::move(list1));
    
    EXPECT_EQ(list2.size(), 3);
    EXPECT_TRUE(list1.empty());
}

TEST(CircularListTest, AssignmentOperator) {
    circular_list<int> list1 = {1, 2, 3};
    circular_list<int> list2;
    list2 = list1;
    
    EXPECT_EQ(list1.size(), list2.size());
    EXPECT_TRUE(std::equal(list1.begin(), list1.end(), list2.begin()));
}

TEST(CircularListTest, MoveAssignmentOperator) {
    circular_list<int> list1 = {1, 2, 3};
    circular_list<int> list2;
    list2 = std::move(list1);
    
    EXPECT_EQ(list2.size(), 3);
    EXPECT_TRUE(list1.empty());
}

TEST(CircularListTest, InitializerList) {
    circular_list<int> list = {1, 2, 3, 4, 5};
    EXPECT_EQ(list.size(), 5);
    EXPECT_EQ(*list.begin(), 1);
    EXPECT_EQ(*(--list.end()), 5);
}

TEST(CircularListTest, RangeInsert) {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    circular_list<int> list;
    for (auto num : vec) {
        list.push_back(num);
    }
    EXPECT_EQ(list.size(), 5);
    EXPECT_TRUE(std::equal(list.begin(), list.end(), vec.begin()));
}

TEST(CircularListTest, Resize) {
    circular_list<int> list = {1, 2, 3};
    list.resize(5);
    EXPECT_EQ(list.size(), 5);
    
    list.resize(2);
    EXPECT_EQ(list.size(), 2);
}

TEST(CircularListTest, Swap) {
    circular_list<int> list1 = {1, 2, 3};
    circular_list<int> list2 = {4, 5, 6};
    
    list1.swap(list2);
    EXPECT_EQ(list1.size(), 3);
    EXPECT_EQ(*list1.begin(), 4);
    EXPECT_EQ(list2.size(), 3);
    EXPECT_EQ(*list2.begin(), 1);
}

TEST(CircularListTest, Emplace) {
    circular_list<std::string> list;
    list.emplace_back("test");
    EXPECT_EQ(*list.begin(), "test");
}

TEST(CircularListTest, Remove) {
    circular_list<int> list = {1, 2, 2, 3, 2};
    list.remove(2);
    EXPECT_EQ(list.size(), 2);
}

TEST(CircularListTest, Reverse) {
    circular_list<int> list = {1, 2, 3};
    list.reverse();
    std::vector<int> result(list.begin(), list.end());
    EXPECT_EQ(result, std::vector<int>({3, 2, 1}));
}

TEST(CircularListTest, Unique) {
    circular_list<int> list = {1, 1, 2, 3, 3, 3};
    list.unique();
    std::vector<int> result(list.begin(), list.end());
    EXPECT_EQ(result, std::vector<int>({1, 2, 3}));
}

TEST(CircularListTest, Sort) {
    circular_list<int> list = {3, 1, 4, 2};
    list.sort();
    std::vector<int> result(list.begin(), list.end());
    EXPECT_EQ(result, std::vector<int>({1, 2, 3, 4}));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
