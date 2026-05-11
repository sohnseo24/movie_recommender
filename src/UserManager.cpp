#include "User.h"
#include "UserManager.h"
#include <iostream>
#include <fstream>   // ifstream 사용을 위해
#include <sstream>   // stringstream 사용을 위해
#include <string>    // string, stoi, stod 사용을 위해

// 5번: 사용자 추가
void UserManager::addUser(const User& user) {
    users.push_back(user);
}

// 6번: 전체 출력
void UserManager::printAllUsers() const {
    if (users.empty()) {
        std::cout << "등록된 사용자가 없습니다." << std::endl;
        return;
    }
    for (const auto& u : users) {
        u.display(); 
    }
}

// 반복문을 이용한 사용자 이름 검색
User* UserManager::findByName(const std::string& name) {
    // 벡터를 처음부터 끝까지 돌면서 이름을 비교
    for (size_t i = 0; i < users.size(); i++) {
        if (users[i].getName() == name) {
            return &users[i]; // 찾으면 해당 사용자의 주소 즉 포인터 반환
        }
    }
    return nullptr; // 끝까지 못 찾으면 없다는 뜻으로 nullptr 반환
}

//CSV를 위한 loadUser추가
void UserManager::loadUsers(const std::string& filename) { //CSV로딩을 위해 새로 추가
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: " << filename << " 열 수 없습니다" << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // 헤더 스킵

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;

        std::getline(ss, token, ','); int id = std::stoi(token);
        std::getline(ss, token, ','); std::string name = token;
        std::getline(ss, token, ','); int age = std::stoi(token);


        //읽어온 데이터를 바로 users벡터에 추가
        users.push_back(User(id, name, age)); 
    }
    std::cout << "[알림] " << filename << " 데이터를 성공적으로 불러왔습니다." << std::endl;
}
void UserManager::saveUsers(const std::string& filename) const {
    std::ofstream file(filename); // 파일 열기

    if (!file.is_open()) {
        std::cerr << "Error: " << filename << " 저장 실패" << std::endl;
        return;
    }

    // 1. 헤더 작성
    file << "id,name,age" << std::endl;

    // 2. 데이터 작성
    for (const auto& m : users) {
        file << m.getId() << "," 
             << m.getName() << "," 
             << m.getAge() << std::endl; 
    }

    file.close();
    std::cout << "[알림] " << filename << " 저장 완료: " << users.size() << "건" << std::endl;
}

//9번: 전체 사용자를 한 명씩 비교하려면 전체 리스트를 받아올 수 있어야 한다.
const std::vector<User>& UserManager::getAllUsers() const {
    return users;
}