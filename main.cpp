#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <optional>
#include "Player.h"
#include "Slime.h"
#include "Colors.h"

using namespace std;

int main() {
    system("chcp 65001");
    srand(time(0)); 

    Player player; 
    Slime slime(player.level); 

    // 1. 2D 그래픽 창 세팅 (800 x 600)
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 600)), "Slime Hunter 2D");

    // 2. 슬라임 이미지 불러오기
    sf::Texture slimeTex;
    if (!slimeTex.loadFromFile("slime.png")) {
        cout << RED << "❌ slime.png 파일을 찾을 수 없습니다!" << RESET << endl;
        return -1;
    }
    sf::Sprite slimeSprite(slimeTex);
    slimeSprite.setScale(sf::Vector2f(0.2f, 0.2f)); // 크기 조절 (테스트때 맞춘 비율로 수정 가능)
    slimeSprite.setPosition(sf::Vector2f(500.f, 250.f)); // 화면 오른쪽에 배치

    // 3. 플레이어 임시 그래픽 (파란색 네모)
    sf::RectangleShape playerShape(sf::Vector2f(100.f, 150.f));
    playerShape.setFillColor(sf::Color::Blue);
    playerShape.setPosition(sf::Vector2f(150.f, 250.f)); // 화면 왼쪽에 배치

    // 4. 게임 시작 안내
    cout << CYAN << "=== 2D 슬라임 헌터에 오신 것을 환영합니다! ===" << RESET << endl;
    cout << "🎮 조작법: [스페이스바]를 눌러 슬라임을 공격하세요!" << endl;
    cout << "🚪 종료: [ESC] 키를 누르거나 창의 X 버튼을 누르세요.\n" << endl;

    // 5. 실시간 게임 루프
    while (window.isOpen() && player.hp > 0) {
        // 이벤트 처리 (키보드 입력, 창 닫기 등)
        while (std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            
            // 키보드가 눌렸을 때의 이벤트 처리 (SFML 3.x 방식)
            if (const auto* keyPress = event->getIf<sf::Event::KeyPressed>()) {
                // 스페이스바를 누르면 전투 실행!
                if (keyPress->code == sf::Keyboard::Key::Space) {
                    if (slime.hp > 0) {
                        cout << "\n------------------------------------" << endl;
                        int damage = player.attack(); 
                        slime.takeDamage(damage);

                        if (slime.hp > 0) {
                            int slimeDamage = slime.attack(); 
                            player.takeDamage(slimeDamage); 
                        } else {
                            cout << YELLOW << "\n🎉 슬라임을 물리쳤습니다!" << RESET << endl;
                            player.gainExp(50);
                            
                            // 새 슬라임 소환!
                            slime = Slime(player.level); 
                            cout << RED << "🚨 야생의 새로운 슬라임이 나타났다!" << RESET << endl;
                        }
                        
                        // 체력 상태 출력
                        cout << GREEN << "[내 HP: " << player.hp << "/" << player.maxHp << "] " << RESET;
                        cout << RED << "[적 HP: " << slime.hp << "]" << RESET << endl;
                    }
                } 
                // ESC를 누르면 창 닫기
                else if (keyPress->code == sf::Keyboard::Key::Escape) {
                    window.close();
                }
            }
        }

        // 6. 화면 그리기 (렌더링)
        window.clear(sf::Color(30, 30, 30)); // 짙은 회색 배경으로 지우기
        window.draw(playerShape);            // 플레이어 그리기
        window.draw(slimeSprite);            // 슬라임 그리기
        window.display();                    // 모니터에 출력
    }

    if (player.hp <= 0) cout << RED << "\n💀 플레이어가 쓰러졌습니다... Game Over." << RESET << endl;
    
    return 0;
}