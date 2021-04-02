#include <regex>
#include "Patient.h"

Patient::Patient() = default;

Patient::Patient(const std::string &fullName, const std::string &birthDate, const std::string &address) {
    setFullName(fullName);
    setBirthDate(birthDate);
    setAddress(address);
}


Patient::Patient(int64_t id, const std::string &fullName, const std::string &birthDate, const std::string &address) {
    setId(id);
    setFullName(fullName);
    setBirthDate(birthDate);
    setAddress(address);
}

Patient::Patient(const Patient &p) {
    setId(p.id);
    setFullName(p.fullName);
    setBirthDate(p.birthDate);
    setAddress(p.address);
}

Patient &Patient::operator=(const Patient &p) {
    if (this == &p)
        return *this;

    setFullName(p.fullName);
    setBirthDate(p.birthDate);
    setAddress(p.address);

    return *this;
}

const int64_t &Patient::getId() const {
    return id;
}

void Patient::setId(const int64_t &id) {
    if (id < 0)
        throw std::domain_error("Id пациента не может быть меньше нуля [id = " + std::to_string(id) + "]");
    Patient::id = id;
}

const std::string &Patient::getFullName() const {
    return fullName;
}

void Patient::setFullName(const std::string &fullName) {
    if (fullName.empty() || fullName.length() < 3 || fullName.length() > 100)
        throw std::domain_error("Имя пациента не может быть путыми, меньше 3 символов и превышать 100 "
                                "[" + fullName + "]");
    Patient::fullName = fullName;
}

const std::string &Patient::getBirthDate() const {
    return birthDate;
}

void Patient::setBirthDate(const std::string &birthDate) {

    std::regex pattern(R"((0[1-9]|[12][0-9]|3[01])[.](0[1-9]|1[012])[.](19|20)\d\d)");

    if (!std::regex_match(birthDate, pattern))
        throw std::domain_error("Дата рождения должна быть в формате ДД.ММ.ГГГГ [" + birthDate + "]");

    Patient::birthDate = birthDate;
}

const std::string &Patient::getAddress() const {
    return address;
}

void Patient::setAddress(const std::string &address) {
    if (address.empty() || address.length() > 100 || address.length() < 3)
        throw std::domain_error("Адрес пациента не может быть путым, меньше 3 символов и превышать 100 "
                                "[" + address + "]");
    Patient::address = address;
}

std::ostream &operator<<(std::ostream &os, const Patient &patient) {
    os << patient.id << "; " << patient.fullName << "; " << patient.birthDate
       << "; " << patient.address;
    return os;
}



