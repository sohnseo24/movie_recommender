#pragma once
#include <string>
#include <iostream>

class User {
private:
    int         id;
    std::string name;
    std::string email;

public:
    User();
    User(int id, const std::string& name, const std::string& email);

    // Getter들
    int         getId()    const;
    std::string getName()  const;
    std::string getEmail() const;

    // [추가] 이름으로 검색하기 위한 연산자 (find_if 등에서 활용)
    bool operator==(const std::string& userName) const;

    // [추가] 출력을 위한 연산자 오버로딩
    friend std::ostream& operator<<(std::ostream& os, const User& u);

    void display() const;
};
