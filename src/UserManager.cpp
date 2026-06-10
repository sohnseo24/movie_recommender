#include "User.h"
#include "UserManager.h"
#include <iostream>
#include <fstream>   
#include <sstream>   
#include <string>    

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
User& UserManager::findByName(const std::string& name) {
    // 벡터를 처음부터 끝까지 돌면서 이름을 비교
    for (User& u : users) {

        if (u.getName() == name) {
            return u; //포인터 기호(&) 빼고 참조자 그대로 반환
        }
    }

    //nullptr 대신 명시적 예외 발생
    throw std::out_of_range("Error: '" + name + "' 해당 이름을 가진 사용자를 찾을 수 없습니다.");

}

//CSV를 위한 loadUser추가
void UserManager::loadFromFile(const std::string& filename) { 
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("치명적 오류: 사용자 데이터 파일('" + filename + "')을 열 수 없습니다.");
    }

    std::string line;
    std::getline(file, line); // 헤더 스킵
    int lineNum = 1;

    while (std::getline(file, line)) {
        lineNum++;
        try{
        std::stringstream ss(line);
        std::string token;

        std::getline(ss, token, ','); int id = std::stoi(token);
        std::getline(ss, token, ','); std::string name = token;
        std::getline(ss, token, ','); int age = std::stoi(token);


        //읽어온 데이터를 바로 users벡터에 추가
        users.push_back(User(id, name, age)); 
        }catch(const std::exception& e) {
            std::cerr << "[CSV 데이터 손상] 사용자 매니저 " << lineNum << "번 줄 건너뜀 (원인: " << e.what() << ")" << std::endl;
        }
    }
    std::cout << "[알림] " << filename << " 데이터를 성공적으로 불러왔습니다." << std::endl;
}
void UserManager::saveToFile(const std::string& filename) const {
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

int UserManager::size() const { //벡터의 크기 반환하는 함수 추가
    return users.size();
}