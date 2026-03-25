#pragma once
#include <string>

class User {
private:
    int         id;       // 사용자 ID
    std::string name;     // 이름
    std::string email;    // 이메일

public:
    User();
    User(int id, const std::string& name, const std::string& email);

    int getId() const;
    std::string getName() const;
    std::string getEmail() const;

    void display() const;
    // TODO: 생성자, getter, display()
    // Movie 클래스를 참고하여 작성
};
