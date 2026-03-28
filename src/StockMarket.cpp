#include "../include/StockMarket.h"
#include "../include/Colors.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void StockMarket::visit(Player &player)
{
    // static 변수를 사용하여 거래소를 나갔다 들어와도 가격이 유지되게 함
    static int slimePrice = 100;   // 우량주
    static int goblinPrice = 300;  // 테마주
    static int dragonPrice = 1000; // 작전주 (하이리스크)

    bool inMarket = true;
    while (inMarket)
    {
        system("cls");
        cout << YELLOW << "\n=== [ 고블린 증권 거래소 (Goblin Stock Exchange) ] ===" << RESET << endl;
        cout << "고블린 브로커: 키히힉! 자본주의의 맛을 보러 왔나? 매수와 매도는 타이밍이라구!" << endl;
        cout << "\n[ 내 지갑 ]: " << YELLOW << player.gold << " G" << RESET << endl;

        // 내 포트폴리오 출력
        cout << CYAN << "\n[ 내 주식 잔고 및 현재가 ]" << RESET << endl;
        cout << "1. 슬라임 운수 (우량주)  : " << player.slimeShares << " 주 (현재가: " << slimePrice << " G)" << endl;
        cout << "2. 고블린 제약 (테마주)  : " << player.goblinShares << " 주 (현재가: " << goblinPrice << " G)" << endl;
        cout << "3. 드래곤 항공 (작전주)  : " << player.dragonShares << " 주 (현재가: " << dragonPrice << " G)" << endl;

        cout << "\n1. 주식 매수 (Buy)" << endl;
        cout << "2. 주식 매도 (Sell)" << endl;
        cout << "3. 시장 다음 날로 넘기기 (Turn Next Day - 가격 변동!)" << endl;
        cout << "4. 거래소 나서기\n선택: ";

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            cout << "\n매수할 종목 번호(1~3)와 수량을 띄어쓰기로 입력 (예: 1 10): ";
            int stockChoice, amount;
            cin >> stockChoice >> amount;
            if (amount <= 0)
                continue;

            int price = (stockChoice == 1) ? slimePrice : (stockChoice == 2) ? goblinPrice
                                                      : (stockChoice == 3)   ? dragonPrice
                                                                             : 0;
            if (price == 0)
            {
                cout << RED << "잘못된 종목입니다." << RESET << endl;
                continue;
            }

            int totalCost = price * amount;
            if (player.gold >= totalCost)
            {
                player.gold -= totalCost;
                if (stockChoice == 1)
                    player.slimeShares += amount;
                else if (stockChoice == 2)
                    player.goblinShares += amount;
                else if (stockChoice == 3)
                    player.dragonShares += amount;
                cout << GREEN << amount << "주 매수 체결 완료! (-" << totalCost << " G)" << RESET << endl;
            }
            else
            {
                cout << RED << "골드가 부족합니다! (필요: " << totalCost << " G)" << RESET << endl;
            }
        }
        else if (choice == 2)
        {
            cout << "\n매도할 종목 번호(1~3)와 수량을 띄어쓰기로 입력 (예: 1 10): ";
            int stockChoice, amount;
            cin >> stockChoice >> amount;
            if (amount <= 0)
                continue;

            int currentShares = (stockChoice == 1) ? player.slimeShares : (stockChoice == 2) ? player.goblinShares
                                                                      : (stockChoice == 3)   ? player.dragonShares
                                                                                             : 0;

            if (currentShares >= amount)
            {
                int price = (stockChoice == 1) ? slimePrice : (stockChoice == 2) ? goblinPrice
                                                          : (stockChoice == 3)   ? dragonPrice
                                                                                 : 0;
                int totalGain = price * amount;

                if (stockChoice == 1)
                    player.slimeShares -= amount;
                else if (stockChoice == 2)
                    player.goblinShares -= amount;
                else if (stockChoice == 3)
                    player.dragonShares -= amount;

                player.gold += totalGain;
                cout << GREEN << amount << "주 매도 체결 완료! (+" << totalGain << " G)" << RESET << endl;
            }
            else
            {
                cout << RED << "보유 주식이 부족합니다!" << RESET << endl;
            }
        }
        else if (choice == 3)
        {
            cout << CYAN << "\n하루가 지났습니다... 시장 가격이 요동칩니다!" << RESET << endl;

            // 1. 슬라임 운수: -10% ~ +15% (안정적)
            float slimeVar = 1.0f + ((rand() % 26 - 10) / 100.0f);
            slimePrice = (int)(slimePrice * slimeVar);
            if (slimePrice < 10)
                slimePrice = 10;

            // 2. 고블린 제약: -30% ~ +40% (변동성 큼)
            float goblinVar = 1.0f + ((rand() % 71 - 30) / 100.0f);
            goblinPrice = (int)(goblinPrice * goblinVar);
            if (goblinPrice < 10)
                goblinPrice = 10;

            // 3. 드래곤 항공: -80% ~ +200% (뉴스 이벤트 기반 하이리스크)
            int dragonEvent = rand() % 100;
            if (dragonEvent < 20)
            {
                cout << MAGENTA << "[뉴스] 드래곤 항공 여객기 추락! 주가 폭락!!!" << RESET << endl;
                dragonPrice = (int)(dragonPrice * 0.2f);
            }
            else if (dragonEvent > 80)
            {
                cout << YELLOW << "[뉴스] 드래곤 항공, 마왕성 항로 독점 계약! 상한가!!!" << RESET << endl;
                dragonPrice = (int)(dragonPrice * 2.5f);
            }
            else
            {
                float dragonVar = 1.0f + ((rand() % 41 - 20) / 100.0f);
                dragonPrice = (int)(dragonPrice * dragonVar);
            }
            if (dragonPrice < 10)
                dragonPrice = 10;
        }
        else if (choice == 4)
        {
            cout << "브로커: 시장은 언제나 열려있다구! 껄껄!" << endl;
            inMarket = false;
        }
        else
        {
            cout << RED << "잘못된 입력입니다." << RESET << endl;
        }

        if (inMarket)
        {
            cout << "\n엔터를 누르면 계속합니다...";
            cin.ignore();
            cin.get();
        }
    }
}