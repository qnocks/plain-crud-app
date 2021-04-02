#ifndef MPO_1_PATIENT_H
#define MPO_1_PATIENT_H


#include <stdint-gcc.h>
#include <string>
#include <ostream>

class Patient {
private:
    int64_t id;
    std::string fullName;
    std::string birthDate;
    std::string address;
public:
    Patient();
    Patient(const std::string &fullName, const std::string &birthDate, const std::string &address);
    Patient(int64_t id, const std::string &fullName, const std::string &birthDate, const std::string &address);

    Patient(const Patient &p);

    Patient & operator=(const Patient &p);

    const int64_t &getId() const;
    void setId(const int64_t &id);

    const std::string &getFullName() const;
    void setFullName(const std::string &fullName);

    const std::string &getBirthDate() const;
    void setBirthDate(const std::string &birthDate);

    const std::string &getAddress() const;
    void setAddress(const std::string &address);

    friend std::ostream &operator<<(std::ostream &os, const Patient &patient);
};


#endif //MPO_1_PATIENT_H
