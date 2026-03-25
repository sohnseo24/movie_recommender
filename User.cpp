#include "User.h"
#include <iostream>

// 기본 생성자
User::User()
    : id(0), name(""), email("") {}

// 3인자 생성자
User::User(int id, const std::string& name, const std::string& email)
    :id(id), name(name), email(email){}

int         User::getId()           const { return id; }
std::string User::getName()         const { return name; }
std::string User::getEmail()        const { return email;}

void User::display() const {           // 중복 제거 — 하나만 유지
    std::cout << "Id: "<< id << std::endl
    << "Name: " << name << std::endl
    << "Email: " << email << std::endl;
}
