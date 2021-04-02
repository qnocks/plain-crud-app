#include <iostream>
#include "Registry.h"
#include "../../util/Utils.h"

Registry::Registry() {
    doctorsFile = std::fstream("doctors.txt");
    patientsFile = std::fstream("patients.txt");
    appointmentsFile = std::fstream("appointments.txt");

    std::string doctor;
    while (std::getline(doctorsFile, doctor)) {
        polyclinic.addDoctor(mapDoctor(doctor));
    }

    std::string patient;
    while (std::getline(patientsFile, patient)) {
        polyclinic.addPatient(mapPatient(patient));
    }

    std::string appointment;
    while (std::getline(appointmentsFile, appointment)) {
        polyclinic.addAppointment(mapAppointment(appointment));
    }

    doctorsFile.close();
    patientsFile.close();
    appointmentsFile.close();
}

Doctor Registry::mapDoctor(std::string &strToParse) {
    auto parsedDoctor = Utils::split(strToParse, "; ");
    return Doctor(
            std::stoi(parsedDoctor[0]),
            parsedDoctor[1],
            parsedDoctor[2],
            std::stoi(parsedDoctor[3]),
            parsedDoctor[4]);
}

Patient Registry::mapPatient(std::string &strToParse) {
    auto parsedPatient = Utils::split(strToParse, "; ");
    return Patient(
            std::stoi(parsedPatient[0]),
            parsedPatient[1],
            parsedPatient[2],
            parsedPatient[3]);
}


Appointment Registry::mapAppointment(std::string &strToParse) {
    auto parsedAppointment = Utils::split(strToParse, "; ");

    parsedAppointment[1]
        .append("; " + parsedAppointment[2])
        .append("; " + parsedAppointment[3])
        .append("; " + parsedAppointment[4])
        .append("; " + parsedAppointment[5]);

    parsedAppointment[6]
        .append("; " + parsedAppointment[7])
        .append("; " + parsedAppointment[8])
        .append("; " + parsedAppointment[9]);

    return Appointment(
            std::stoi(parsedAppointment[0]),
            mapDoctor(parsedAppointment[1]),
            mapPatient(parsedAppointment[6]),
            parsedAppointment[10],
            parsedAppointment[11]);
}

Registry::~Registry() {
}

void Registry::getDoctors() {
    std::cout << "Доктора:" << std::endl;
    for (const auto &d : polyclinic.getDoctors()) std::cout << d << std::endl;
    std::cout << std::endl;
}

void Registry::getPatients() {
    std::cout << "Пациенты:" << std::endl;
    for (const auto &p : polyclinic.getPatients()) std::cout << p << std::endl;
    std::cout << std::endl;
}

void Registry::getAppointments() {
    std::cout << "Талоны:" << std::endl;
    for (const auto &a : polyclinic.getAppointments()) std::cout << a << std::endl;
    std::cout << std::endl;
}

Doctor Registry::getDoctorById(int64_t id) {
    return polyclinic.getDoctorById(id);
}

Patient Registry::getPatientById(int64_t id) {
    return polyclinic.getPatientById(id);
}

Appointment Registry::getAppointmentById(int64_t id) {
    return polyclinic.getAppointmentById(id);
}

void Registry::addDoctor() {

    try {
        std::string fullName;
        std::string specialty;
        int officeNumber;
        std::string schedule;

        std::cout << "Введите: имя доктора, специальность, номер кабинета, расписание: " << std::endl;
        std::cin.clear(); std::cin.sync(); std::cin.ignore();
        std::getline(std::cin, fullName);
        std::cin >> specialty >> officeNumber >> schedule;

        if (!Utils::isStreamValid())
            std::cout << "Некорректный ввод. Повторите снова" << std::endl;
        else {
            Doctor doctor(fullName, specialty, officeNumber, schedule);
            polyclinic.addDoctor(Doctor(fullName, specialty, officeNumber, schedule));
            flushDoctorsToFile();
        }

    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void Registry::addPatient() {

    try {
        std::string fullName;
        std::string birthDate;
        std::string address;

        std::cout << "Введите: имя пациента, дату рождения, адрес: " << std::endl;
        std::cin.clear(); std::cin.sync(); std::cin.ignore();
        std::getline(std::cin, fullName);
        std::cin >> birthDate;
        std::cin.clear(); std::cin.sync(); std::cin.ignore();
        std::getline(std::cin, address);

        if (!Utils::isStreamValid())
            std::cout << "Некорректный ввод. Повторите снова" << std::endl;
        else {
            polyclinic.addPatient(Patient(fullName, birthDate, address));
            flushPatientsToFile();
        }

    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void Registry::addAppointment() {

    getDoctors();
    getPatients();

    try {
        int64_t doctorId;
        int64_t patientId;
        std::string date;
        std::string time;

        std::cout << "Введите: id доктора, к которому берется талон, id пациента, дату, время талона: " << std::endl;
        std::cin >> doctorId >> patientId >> date >> time;
        if (!Utils::isStreamValid())
            std::cout << "Некорректный ввод. Повторите снова" << std::endl;
        else {
            polyclinic.addAppointment(Appointment(getDoctorById(doctorId), getPatientById(patientId), date, time));
            flushAppointmentsToFile();
        }

    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }

}

void Registry::clearDoctors() {
    polyclinic.clearDoctors();
    flushDoctorsToFile();
    std::cout << "Данные очищены." << std::endl;
}

void Registry::clearPatients() {
    polyclinic.clearPatients();
    flushPatientsToFile();
    std::cout << "Данные очищены." << std::endl;
}

void Registry::clearAppointments() {
    polyclinic.clearAppointments();
    flushAppointmentsToFile();
    std::cout << "Данные очищены." << std::endl;
}

void Registry::deleteDoctor() {

    getDoctors();

    int64_t id;
    std::cout << "Введите id доктора, чтобы удалить его: ";
    std::cin >> id;

    if (!Utils::isStreamValid())
        std::cout << "Некорректный ввод. Повторите снова" << std::endl;
    else {
        polyclinic.deleteDoctor(id);
        flushDoctorsToFile();
    }
}

void Registry::deletePatient() {

    getPatients();

    int64_t id;
    std::cout << "Введите id пациента, чтобы удалить его: ";
    std::cin >> id;

    if (!Utils::isStreamValid())
        std::cout << "Некорректный ввод. Повторите снова" << std::endl;
    else {
        polyclinic.deletePatient(id);
        flushPatientsToFile();
    }
}

void Registry::deleteAppointment() {

    getAppointments();

    int64_t id;
    std::cout << "Введите id талона, чтобы удалить его: ";
    std::cin >> id;

    if (!Utils::isStreamValid())
        std::cout << "Некорректный ввод. Повторите снова" << std::endl;
    else {
        polyclinic.deleteAppointment(id);
        flushAppointmentsToFile();
    }
}

void Registry::updateDoctor() {

    getDoctors();

    try {
        int64_t id;
        std::cout << "Введите id доктора, чтобы обновить его: ";
        std::cin >> id;

        std::string fullName;
        std::string specialty;
        int officeNumber;
        std::string schedule;

        std::cout << "Введите: имя доктора, специальность, номер кабинета, график приема:" << std::endl;

        std::cin.clear(); std::cin.sync(); std::cin.ignore();
        std::getline(std::cin, fullName);
        std::cin >> specialty >> officeNumber >> schedule;

        if (!Utils::isStreamValid())
            std::cout << "Некорректный ввод. Повторите снова" << std::endl;
        else {
            polyclinic.updateDoctor(Doctor(id, fullName, specialty, officeNumber, schedule));
            flushDoctorsToFile();
        }

    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void Registry::updatePatient() {

    getPatients();

    try {
        int64_t id;
        std::cout << "Введите id пациента, чтобы обновить его: ";
        std::cin >> id;

        std::string fullName;
        std::string birthDate;
        std::string address;

        std::cout << "Введите: имя пациента, дату рождения, адрес: " << std::endl;
        std::cin.clear(); std::cin.sync(); std::cin.ignore();
        std::getline(std::cin, fullName);
        std::cin >> birthDate;
        std::cin.clear(); std::cin.sync(); std::cin.ignore();
        std::getline(std::cin, address);

        if (!Utils::isStreamValid())
            std::cout << "Некорректный ввод. Повторите снова" << std::endl;
        else {
            polyclinic.updatePatient(Patient(id, fullName, birthDate, address));
            flushPatientsToFile();
        }

    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void Registry::updateAppointment() {

    getDoctors();
    getPatients();
    std::cout << std::endl;
    getAppointments();

    try {
        int64_t id;
        std::cout << "Введите id талона, чтобы обновить его: ";
        std::cin >> id;

        int64_t doctorId;
        int64_t patientId;
        std::string date;
        std::string time;

        std::cout << "Введите: id доктора, к которому берется талон, id пациента, дату, время талона: " << std::endl;
        std::cin >> doctorId >> patientId >> date >> time;

        if (!Utils::isStreamValid())
            std::cout << "Некорректный ввод. Повторите снова" << std::endl;
        else {
            polyclinic.updateAppointment(Appointment(getDoctorById(doctorId), getPatientById(patientId), date, time));
            flushAppointmentsToFile();
        }

    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void Registry::flushDoctorsToFile() {

    std::ofstream newDoctorsFile("doctors.txt");

    auto doctors = polyclinic.getDoctors();

    if (doctors.empty()) {
        newDoctorsFile << "";
        newDoctorsFile.close();
        return;
    } else {
        doctors.sort([](const Doctor &d1, const Doctor &d2){return d1.getFullName() < d2.getFullName();});
        for (const auto &d : doctors) {
            newDoctorsFile << d << '\n';
        }
        newDoctorsFile.close();
    }

}

void Registry::flushPatientsToFile() {

    std::ofstream  newPatientsFile("patients.txt");

    auto patients = polyclinic.getPatients();
    if (patients.empty()) {
        newPatientsFile << "";
        newPatientsFile.close();
    } else {
        patients.sort([](const Patient &p1, const Patient &p2){return p1.getFullName() < p2.getFullName();});
        for (const auto &p : patients)
            newPatientsFile << p << '\n';
        newPatientsFile.close();
    }
}

void Registry::flushAppointmentsToFile() {

    std::ofstream newAppointmentsFile("appointments.txt");

    auto appointments = polyclinic.getAppointments();
    if (appointments.empty()) {
        newAppointmentsFile << "";
        newAppointmentsFile.close();
    } else {
        appointments.sort([](const Appointment &a1, const Appointment &a2){return a1.getId() < a2.getId();});
        for (const auto &a : appointments)
            newAppointmentsFile << a << '\n';
        newAppointmentsFile.close();
    }
}

