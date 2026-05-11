#pragma once
#include <string>
#include <iostream>

class User {
private:
    int         id;
    int         age;
    std::string name;
    std::string email;

public:
    User();
    User(int id, const std::string& name, const std::string& email);
    User(int id, const std::string& name , int age);

    // Getter들
    int         getId()    const;
    int         getAge()   const;
    std::string getName()  const;
    std::string getEmail() const;

    //이름으로 검색하기 위한 연산자
    bool operator==(const std::string& userName) const;

    //출력을 위한 연산자 오버로딩
    friend std::ostream& operator<<(std::ostream& os, const User& u);

    void display() const;
};
