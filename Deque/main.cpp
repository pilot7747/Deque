//  main.cpp
//  Deque
//
//  Created by Nikita Pavlichenko on 27.11.2017.
//  Copyright © 2017 Nikita Pavlichenko. All rights reserved.
//

#include <iostream>
#include <gtest/gtest.h>
#include <string>
#include <chrono>
#include <deque>
#include <cstdio>
#include <ctime>
#include <fstream>
#include "deque.h"

double getTime(void func(Deque<int>&, size_t), Deque<int> &deq, size_t size)
{
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    func(deq, size);
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    return time_span.count();
}



void stressPushing(Deque<int> &deq, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        if (rand() % 2 == 0)
            deq.push_back(rand());
        else
            deq.push_front(rand());
    }
}

void stressPoping(Deque<int> &deq, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        if (rand() % 2 == 0)
            deq.pop_back();
        else
            deq.pop_front();
    }
}

void stressPopingOneHalf(Deque<int> &deq, size_t size) {
    size_t i = 0;
    for (; i < size / 2; ++i) {
        deq.pop_back();
    }
    for (; i < size; ++i) {
        deq.pop_front();
    }
}

void stressRandomAccess(Deque<int> &deq, size_t size) {
    int tmp;
    for (size_t i = 0; i < size; ++i) {
        tmp = deq[rand() % size];
        Deque<int>::const_iterator it = deq.cbegin();
        it += rand() % size;
        tmp = *it;
    }
}

class SimpleDequeTest : public ::testing::Test {
protected:
    void SetUp() {
        deq.clear();
    }
    void TearDown() {
        deq.clear();
    }
    Deque<int> deq;
};

class stressTests : public ::testing::Test {
protected:
    void SetUp() {
        deq.clear();
    }
    void TearDown() {
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

TEST_F(SimpleDequeTest, simpleIteration) {
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
    
    std::vector<int> vec;
    std::vector<int> ansVec(3);
    ansVec[0] = 1;
    ansVec[1] = 2;
    ansVec[2] = 3;
    for (it = deq.begin(); it != deq.end(); ++it) {
        vec.push_back(*it);
    }
    ASSERT_EQ(vec, ansVec);
    
    vec.clear();
    for (Deque<int>::const_iterator cit = deq.cbegin(); cit != deq.cend(); ++cit) {
        vec.push_back(*cit);
    }
    ASSERT_EQ(vec, ansVec);
    
    vec.clear();
    ansVec.clear();
    ansVec.resize(3);
    ansVec[0] = 3;
    ansVec[1] = 2;
    ansVec[2] = 1;
    for (Deque<int>::reverse_iterator rit = deq.rbegin(); rit != deq.rend(); ++rit) {
        vec.push_back(*rit);
    }
    ASSERT_EQ(vec, ansVec);
    
    vec.clear();
    for (Deque<int>::const_reverse_iterator rit = deq.crbegin(); rit != deq.crend(); ++rit) {
        vec.push_back(*rit);
    }
    ASSERT_EQ(vec, ansVec);
}

TEST_F(SimpleDequeTest, constDeque) {
    
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
TEST_F(SimpleDequeTest, dequePointer) {
    struct testStruc {
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

TEST_F(SimpleDequeTest, equations) {
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

TEST_F(stressTests, pushing) {
    double time = getTime(stressPushing, deq, 1000000);
    ASSERT_LE(time, 1);
}
TEST_F(stressTests, poping) {
    stressPushing(deq, 1000000);
    double time = getTime(stressPoping, deq, 1000000);
    ASSERT_LE(time, 1);
}
TEST_F(stressTests, popingAhalf) {
    stressPushing(deq, 1000000);
    double time = getTime(stressPopingOneHalf, deq, 1000000);
    ASSERT_LE(time, 1);
}

TEST_F(stressTests, randomAccess) {
    stressPushing(deq, 1000000);
    double time = getTime(stressRandomAccess, deq, 1000000);
    ASSERT_LE(time, 1);
}

class stlDeqEq : public ::testing::Test {
protected:
    void SetUp() {
        deq.clear();
    }
    void TearDown() {
        deq.clear();
    }
    Deque<int> deq;
};

TEST_F(stlDeqEq, verySimpleSort) {
    deq.push_back(4);
    deq.push_back(3);
    deq.push_back(2);
    deq.push_back(1);
    deq.push_front(5);
    std::sort(deq.begin(), deq.end());
    ASSERT_EQ(deq[0], 1);
    ASSERT_EQ(deq[1], 2);
    ASSERT_EQ(deq[2], 3);
    ASSERT_EQ(deq[3], 4);
    ASSERT_EQ(deq[4], 5);
}

TEST_F(stlDeqEq, sortAndReverseSize1000) {
    
    //------GENERATING-----
    /*std::ofstream of("sortSize1000.txt");
    for (int i = 0; i < 1000; ++i)
    {
        if (rand() % 2 == 0)
            of << rand() << " f" << std::endl;
        else
            of << rand() << " b" << std::endl;
    }
    of.close();*/
    
    std::ifstream in("sortSize1000.txt");
    std::deque<int> stdDeq;
    for (int i = 0; i < 1000; ++i)
    {
        int num;
        std::string command;
        in >> num >> command;
        if (command == "f")
        {
            deq.push_front(num);
            stdDeq.push_front(num);
        }
        else
        {
            deq.push_back(num);
            stdDeq.push_back(num);
        }
    }
    in.close();
    std::sort(deq.begin(), deq.end());
    std::sort(stdDeq.begin(), stdDeq.end());
    for (int i = 0; i < 1000; ++i) {
        ASSERT_EQ(deq[i], stdDeq[i]);
    }
    std::reverse(deq.begin(), deq.end());
    std::reverse(stdDeq.begin(), stdDeq.end());
    for (int i = 0; i < 1000; ++i) {
        ASSERT_EQ(deq[i], stdDeq[i]);
    }
}

TEST_F(stlDeqEq, sortAndReverseConsecutiveNumbersSize1000) {
    
    //------GENERATING-----
    /*std::ofstream of("sortSize1000.txt");
     for (int i = 0; i < 1000; ++i)
     {
     if (rand() % 2 == 0)
     of << i << " f" << std::endl;
     else
     of << i << " b" << std::endl;
     }
     of.close();*/
    
    std::ifstream in("sortSize1000.txt");
    std::deque<int> stdDeq;
    for (int i = 0; i < 1000; ++i)
    {
        int num;
        std::string command;
        in >> num >> command;
        if (command == "f")
        {
            deq.push_front(num);
            stdDeq.push_front(num);
        }
        else
        {
            deq.push_back(num);
            stdDeq.push_back(num);
        }
    }
    in.close();
    std::sort(deq.begin(), deq.end());
    std::sort(stdDeq.begin(), stdDeq.end());
    Deque<int>::reverse_iterator deqIt = deq.rbegin();
    std::deque<int>::reverse_iterator stdDeqIt = stdDeq.rbegin();
    for (; deqIt != deq.rend(); ++deqIt) {
        ASSERT_EQ(*deqIt, *stdDeqIt);
        ++stdDeqIt;
    }
    std::reverse(deq.begin(), deq.end());
    std::reverse(stdDeq.begin(), stdDeq.end());
    for (int i = 0; i < 1000; ++i) {
        ASSERT_EQ(deq[i], stdDeq[i]);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
