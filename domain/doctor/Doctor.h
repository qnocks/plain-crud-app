//
// Created by qnocks on 3/25/21.
//

#ifndef MPO_1_DOCTOR_H
#define MPO_1_DOCTOR_H


#include <cstdint>
#include <string>
#include <ostream>

#include "../../util/Utils.h"


class Doctor {
private:
    int64_t id;
    std::string fullName;
    std::string specialty;
    int officeNumber;
    std::string schedule;
public:
    Doctor();
    Doctor(const std::string &fullName, const std::string &specialty, int officeNumber, const std::string &schedule);

    Doctor(int64_t id, const std::string &fullName, const std::string &specialty, int officeNumber,
           const std::string &schedule);

    Doctor(const Doctor &d);
    Doctor & operator=(const Doctor &d);

    int64_t getId() const;
    void setId(int64_t id);

    const std::string &getFullName() const;
    void setFullName(const std::string &fullName);

    const std::string &getSpecialty() const;
    void setSpecialty(const std::string &specialty);

    int getOfficeNumber() const;
    void setOfficeNumber(int officeNumber);

    const std::string &getSchedule() const;
    void setSchedule(const std::string &schedule);

    friend std::ostream &operator<<(std::ostream &os, const Doctor &doctor);
};


#endif //MPO_1_DOCTOR_H
