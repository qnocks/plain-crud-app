#include <iostream>

#include "service/registry/Registry.h"
#include "util/Utils.h"

void mainLoop();
void saveSystemTime();

int main() {

    saveSystemTime();
    mainLoop();

    return 0;
}

void saveSystemTime() {

    // Сохранение даты и времени запуска приложения
    std::fstream file("startup-info.txt", std::ios::app);

    time_t     now = time(0);
    struct tm  tm{};
    char       buf[80];
    tm = *localtime(&now);
    strftime(buf, sizeof(buf),"%d-%m-%Y %X", &tm);

    file << buf << '\n';
}

void mainLoop() {
    system("clear");

    Registry registry;
    int input  = 99;

    while (input != 0 || !Utils::isStreamValid()) {

        std::cout << "*************************" << std::endl;
        std::cout << "Меню" << std::endl;
        std::cout << "1. Список докторов" << std::endl;
        std::cout << "2. Список пациентов" << std::endl;
        std::cout << "3. Список талонов" << std::endl;
        std::cout << "4. Добавить доктора" << std::endl;
        std::cout << "5. Добавить пациета" << std::endl;
        std::cout << "6. Добавить талон" << std::endl;
        std::cout << "7. Удалить доктора" << std::endl;
        std::cout << "8. Удалить пациета" << std::endl;
        std::cout << "9. Удалить талон" << std::endl;
        std::cout << "10. Удалить всех докторов" << std::endl;
        std::cout << "11. Удалить всех пациентов" << std::endl;
        std::cout << "12. Удалить все талоны" << std::endl;
        std::cout << "13. Обновить доктора" << std::endl;
        std::cout << "14. Обновить пациета" << std::endl;
        std::cout << "15. Обновить талон" << std::endl;
        std::cout << "0. Выйти" << std::endl;
        std::cout << "*************************" << std::endl;

        std::cin >> input;
        if (!Utils::isStreamValid()) input = 99;
        switch (input) {
            case 1: {
                system("clear");
                registry.getDoctors();
                break;
            }
            case 2: {
                system("clear");
                registry.getPatients();
                break;
            }
            case 3: {
                system("clear");
                registry.getAppointments();
                break;
            }
            case 4:
                system("clear");
                registry.addDoctor();
                break;
            case 5:
                system("clear");
                registry.addPatient();
                break;
            case 6:
                system("clear");
                registry.addAppointment();
                break;
            case 7:
                system("clear");
                registry.deleteDoctor();
                break;
            case 8:
                system("clear");
                registry.deletePatient();
                break;
            case 9:
                system("clear");
                registry.deleteAppointment();
                break;
            case 10:
                system("clear");
                registry.clearDoctors();
                break;
            case 11:
                system("clear");
                registry.clearPatients();
                break;
            case 12:
                system("clear");
                registry.clearAppointments();
                break;
            case 13:
                system("clear");
                registry.updateDoctor();
                break;
            case 14:
                system("clear");
                registry.updatePatient();
                break;
            case 15:
                system("clear");
                registry.updateAppointment();
                break;
            case 0:
                system("clear");
                return;
            default: {
                system("clear");
                std::cout << "Ошибка ввода. Допустимы числа от 0 до 12." << std::endl;
            }
        }
    }
}

