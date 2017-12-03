///Users/nikita/Library/Mobile Documents/com~apple~CloudDocs/ФИВТ/1 курс/АиСД — проекты/Deque/Deque/main.cpp
//  main.cpp
//  Deque
//
//  Created by Никита on 27.11.2017.
//  Copyright © 2017 Никита. All rights reserved.
//

#include <iostream>
#include <gtest/gtest.h>
#include "deque.h"


class SimpleDequeTest : public ::testing::Test {
protected:
    void SetUp()
    {
        deq.clear();
    }
    void TearDown()
    {
        deq.clear();
    }
    Deque<int> deq;
};

TEST_F(SimpleDequeTest, simplePushing) {
    deq.push_back(1);
    ASSERT_EQ(deq.front(), 1);
}

TEST_F(SimpleDequeTest, simplePoping) {
    deq.push_back(1);
    deq.push_front(2);
    deq.push_back(3);
    deq.pop_back();
    ASSERT_EQ(deq.front(), 2);
    ASSERT_EQ(deq.back(), 1);
}

TEST_F(SimpleDequeTest, Clearing) {
    deq.push_back(1);
    deq.push_front(2);
    deq.push_back(3);
    deq.pop_back();
    deq.pop_back();
    deq.pop_back();
    ASSERT_EQ(deq.size(), 0);
    ASSERT_EQ(deq.empty(), true);
}

TEST_F(SimpleDequeTest, GettingElements) {
    deq.push_back(1);
    deq.push_front(2);
    deq.push_back(3);
    deq.push_front(4);
    deq.push_back(5);
    deq.push_front(6);
    ASSERT_EQ(deq.front(), 6);
    ASSERT_EQ(deq.back(), 5);
    ASSERT_EQ(deq.size(), 6);
    ASSERT_EQ(deq.empty(), false);
    ASSERT_EQ(deq[0], 6);
    ASSERT_EQ(deq[1], 4);
    ASSERT_EQ(deq[2], 2);
    ASSERT_EQ(deq[3], 1);
    ASSERT_EQ(deq[4], 3);
    ASSERT_EQ(deq[5], 5);
}
TEST_F(SimpleDequeTest, simpleEq) {
    deq.push_back(1);
    deq[0] = 2;
    ASSERT_EQ(deq[0], 2);
}

TEST_F(SimpleDequeTest, Balancing) {
    deq.push_back(1);
    deq.push_front(2);
    deq.push_back(3);
    deq.push_front(4);
    deq.push_back(5);
    deq.push_front(6);
    ASSERT_EQ(deq.front(), 6);
    ASSERT_EQ(deq.back(), 5);
    deq.pop_front();
    ASSERT_EQ(deq.front(), 4);
    ASSERT_EQ(deq.back(), 5);
    deq.pop_front();
    ASSERT_EQ(deq.front(), 2);
    ASSERT_EQ(deq.back(), 5);
    deq.pop_front();
    ASSERT_EQ(deq.front(), 1);
    ASSERT_EQ(deq.back(), 5);
    deq.pop_back();
    ASSERT_EQ(deq.front(), 1);
    ASSERT_EQ(deq.back(), 3);
    deq.pop_back();
    ASSERT_EQ(deq.front(), 1);
    ASSERT_EQ(deq.back(), 1);
    deq.pop_front();
    ASSERT_EQ(deq.size(), 0);
    ASSERT_EQ(deq.empty(), true);
    deq.push_front(0);
    ASSERT_EQ(deq.back(), 0);
    ASSERT_EQ(deq.front(), 0);
    deq.pop_back();
    ASSERT_EQ(deq.size(), 0);
    ASSERT_EQ(deq.empty(), true);
}

TEST_F(SimpleDequeTest, simpleIteration)
{
    deq.push_back(1);
    deq.push_back(2);
    deq.push_back(3);
    Deque<int>::iterator it = deq.begin();
    ASSERT_EQ(*it, 1);
    it += 1;
    ASSERT_EQ(*it, 2);
    it += 1;
    ASSERT_EQ(*it, 3);
    
    it = deq.begin();
    ASSERT_EQ(*it, 1);
    ++it;
    ASSERT_EQ(*it, 2);
    ++it;
    ASSERT_EQ(*it, 3);
    
    it = deq.end();
    --it;
    ASSERT_EQ(*it, 3);
    --it;
    ASSERT_EQ(*it, 2);
    --it;
    ASSERT_EQ(*it, 1);
    
    it = deq.begin();
    ASSERT_EQ(it[0], 1);
    ASSERT_EQ(it[1], 2);
    ASSERT_EQ(it[2], 3);
    it++;
    ASSERT_EQ(it[0], 2);
    ASSERT_EQ(it[1], 3);
    it++;
    ASSERT_EQ(it[0], 3);
    
    it = deq.begin() + 1;
    ASSERT_EQ(it[0], 2);
    
    it = deq.end() - 1;
    ASSERT_EQ(it[0], 3);
    
    ASSERT_EQ(deq.end() - deq.begin(), 3);
    /*it--;
    ASSERT_EQ(it[0], 3);*/
    
    std::vector<int> vec;
    std::vector<int> ansVec(3);
    ansVec[0] = 1;
    ansVec[1] = 2;
    ansVec[2] = 3;
    for (it = deq.begin(); it != deq.end(); ++it)
    {
        vec.push_back(*it);
    }
    ASSERT_EQ(vec, ansVec);
    
    vec.clear();
    for (Deque<int>::const_iterator cit = deq.cbegin(); cit != deq.cend(); ++cit)
    {
        vec.push_back(*cit);
    }
    ASSERT_EQ(vec, ansVec);
    
    vec.clear();
    ansVec.clear();
    ansVec.resize(3);
    ansVec[0] = 3;
    ansVec[1] = 2;
    ansVec[2] = 1;
    for (Deque<int>::reverse_iterator rit = deq.rbegin(); rit != deq.rend(); ++rit)
    {
        vec.push_back(*rit);
    }
    ASSERT_EQ(vec, ansVec);
    
    vec.clear();
    for (Deque<int>::const_reverse_iterator rit = deq.crbegin(); rit != deq.crend(); ++rit)
    {
        vec.push_back(*rit);
    }
    ASSERT_EQ(vec, ansVec);
}

TEST_F(SimpleDequeTest, constDeque)
{
    
    Deque<int> deq;
    deq.push_back(1);
    deq.push_back(2);
    deq.push_back(3);
    const Deque<int> constDeq(deq);
    Deque<int>::const_iterator it = constDeq.begin();
    ASSERT_EQ(*it, 1);
    ASSERT_EQ(constDeq.front(), 1);
    ASSERT_EQ(constDeq.back(), 3);
}
TEST_F(SimpleDequeTest, dequePointer)
{
    struct testStruc
    {
        int x = 0;
        int y = 0;
    };
    Deque<testStruc> deq;
    testStruc a, b, c;
    a.x = 10;
    a.y = 10;
    b.x = 5;
    b.y = 5;
    c.x = 1;
    c.y = 1;
    deq.push_back(a);
    deq.push_back(b);
    deq.push_back(c);
    Deque<testStruc>::iterator it = deq.begin();
    ASSERT_EQ(it->x, 10);
}

TEST_F(SimpleDequeTest, equations)
{
    Deque<int> deq;
    deq.push_back(2);
    deq.push_front(1);
    deq.push_back(3);
    Deque<int>::iterator first = deq.begin();
    Deque<int>::iterator second = deq.begin() + 1;
    Deque<int>::iterator third = deq.end() - 1;
    ASSERT_TRUE(third > second);
    ASSERT_FALSE(third > third);
    ASSERT_FALSE(first > third);
    
    ASSERT_TRUE(third >= third);
    ASSERT_FALSE(first >= third);
    ASSERT_TRUE(third >= second);
    
    ASSERT_TRUE(third <= third);
    ASSERT_TRUE(second <= third);
    ASSERT_FALSE(third <= first);
    
    ASSERT_TRUE(second < third);
    ASSERT_FALSE(second < second);
    ASSERT_FALSE(third < first);
    
    ASSERT_FALSE(second != second);
    ASSERT_TRUE(second == second);
    
    ASSERT_EQ(*first, 1);
    ASSERT_EQ(*second, 2);
    ASSERT_EQ(*third, 3);
    
    third -= 2;
    ASSERT_EQ(*third, 1);
    ASSERT_TRUE(third == deq.begin());
}

int main(int argc, char **argv) {
    /*Deque<int> deq;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::string command;
        int num;
        std::cin >> command;
        if (command == "push_back")
        {
            std::cin >> num;
            deq.push_back(num);
        }
        if (command == "push_front")
        {
            std::cin >> num;
            deq.push_front(num);
        }
        if (command == "pop_back")
        {
            deq.pop_back();
        }
        if (command == "pop_front")
        {
            deq.pop_front();
        }
        if (command == "size")
        {
            std::cout << deq.size() << std::endl;
        }
        if (command == "empty")
        {
            std::cout << deq.empty() << std::endl;
        }
        if (command == "front")
        {
            std::cout << deq.front() << std::endl;
        }
        if (command == "back")
        {
            std::cout << deq.back() << std::endl;
        }
        if (command == "[]")
        {
            std::cin >> num;
            std::cout << deq[num] << std::endl;
        }
    }*/
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
