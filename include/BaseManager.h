#pragma once
#include <string>

class BaseManager {
public:
    //virtual 소멸자: 상속 구조에서 메모리 누수를 방지하기 위해 필수
    virtual ~BaseManager() {}

    //순수 가상 함수 (= 0): 구현부 없이 선언만 하며, 자식이 반드시 구현하도록 강제
    virtual void loadFromFile(const std::string& filename) = 0;
    virtual void saveToFile(const std::string& filename) const = 0;
    virtual int size() const = 0;
};