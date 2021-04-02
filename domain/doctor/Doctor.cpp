#include <regex>
#include "Doctor.h"

Doctor::Doctor() = default;

Doctor::Doctor(const std::string &fullName, const std::string &specialty, int officeNumber, const std::string &schedule) {
    setFullName(fullName);
    setSpecialty(specialty);
    setOfficeNumber(officeNumber);
    setSchedule(schedule);
}


Doctor::Doctor(int64_t id, const std::string &fullName, const std::string &specialty, int officeNumber, const std::string &schedule) {
    setId(id);
    setFullName(fullName);
    setSpecialty(specialty);
    setOfficeNumber(officeNumber);
    setSchedule(schedule);
}


Doctor::Doctor(const Doctor &d) {
    setId(d.id);
    setFullName(d.fullName);
    setSpecialty(d.specialty);
    setOfficeNumber(d.officeNumber);
    setSchedule(d.schedule);
}


Doctor &Doctor::operator=(const Doctor &d) {
    if (this == &d)
        return *this;

    setFullName(d.fullName);
    setSpecialty(d.specialty);
    setOfficeNumber(d.officeNumber);
    setSchedule(d.schedule);
    return *this;
}

int64_t Doctor::getId() const {
    return id;
}

void Doctor::setId(int64_t id) {
    if (id < 0)
        throw std::domain_error("Id доктора не может быть меньше нуля [id = " + std::to_string(id) + "]");
    Doctor::id = id;
}

const std::string &Doctor::getFullName() const {
    return fullName;
}

void Doctor::setFullName(const std::string &fullName) {
    if (fullName.empty() || fullName.length() > 100 || fullName.length() < 3)
        throw std::domain_error("Имя доктора не может быть путым, меньше 3 символов и превышать 100 "
                                "[" + fullName + "]");
    Doctor::fullName = fullName;
}

const std::string &Doctor::getSpecialty() const {
    return specialty;
}

void Doctor::setSpecialty(const std::string &specialty) {
    if (specialty.empty() || specialty.length() > 50 || specialty.length() < 3)
        throw std::domain_error("Специальность доктора не может быть путой, меньше 3 и превышать 50 символов "
                                "[" + specialty + "]");
    Doctor::specialty = specialty;
}

int Doctor::getOfficeNumber() const {
    return officeNumber;
}

void Doctor::setOfficeNumber(int officeNumber) {
    if (officeNumber <= 0 || officeNumber > 1000)
        throw std::domain_error("Номер кабинета доктора должен быть больше нуля и не должен превышать значения 1000 "
                                "[" + std::to_string(officeNumber) + "]");
    Doctor::officeNumber = officeNumber;
}

const std::string &Doctor::getSchedule() const {
    return schedule;
}

void Doctor::setSchedule(const std::string &schedule) {

    const std::regex pattern("([01]?[0-9]|2[0-3]):[0-5][0-9]-([01]?[0-9]|2[0-3]):[0-5][0-9]");

    if (!std::regex_match(schedule, pattern))
        throw std::domain_error("Расписание доктора должно быть в формате ЧЧ:ММ-ЧЧ:ММ (24 часа) "
                                "[" + schedule + "]");

    // 14:11-16:22
    auto startAndEnd = Utils::split(schedule, "-");
    auto start = startAndEnd[0]; // 14:11
    auto end = startAndEnd[1];  // 16:22

    auto hoursAndMinutesStart = Utils::split(start, ":"); // 14
    auto hoursAndMinutesEnd = Utils::split(end, ":"); // 16

    auto hoursStart = hoursAndMinutesStart[0];
    auto minutesStart = hoursAndMinutesStart[1];

    auto hoursEnd = hoursAndMinutesEnd[0];
    auto minutesEnd = hoursAndMinutesEnd[1];

    int hoursStartInt = std::stoi(hoursStart);
    int minutesStartInt = std::stoi(minutesStart);
    int hoursEndInt = std::stoi(hoursEnd);
    int minutesEndInt = std::stoi(minutesEnd);

    if (hoursStartInt > hoursEndInt || ((hoursStartInt == hoursEndInt) && (minutesStartInt > minutesEndInt)))
        throw std::domain_error("Некорректно задано время [" + schedule + "]");

    Doctor::schedule = schedule;
}

std::ostream &operator<<(std::ostream &os, const Doctor &doctor) {
    os << doctor.id << "; " << doctor.fullName << "; " << doctor.specialty
       << "; " << doctor.officeNumber << "; " << doctor.schedule;
    return os;
}
