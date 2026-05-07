#include "User.h"
#include <iostream>

User::User()
    : id(0), name(""), email("") {}

User::User(int id, const std::string& name, const std::string& email)
    : id(id), name(name), email(email) {}

int         User::getId()    const { return id; }
std::string User::getName()  const { return name; }
std::string User::getEmail() const { return email; }

// 이름 비교 연산자 구현
bool User::operator==(const std::string& userName) const {
    return this->name == userName;
}

// 출력 연산자 구현
std::ostream& operator<<(std::ostream& os, const User& u) {
    os << "ID: " << u.id << " | Name: " << u.name << " | Email: " << u.email;
    return os;
}

void User::display() const {
    std::cout << *this << std::endl;
}
