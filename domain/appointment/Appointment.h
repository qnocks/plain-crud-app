#ifndef MPO_1_APPOINTMENT_H
#define MPO_1_APPOINTMENT_H


#include <stdint-gcc.h>
#include <string>
#include <ostream>
#include "../doctor/Doctor.h"
#include "../patient/Patient.h"

class Appointment {
private:
    int64_t id;
    Doctor doctor;
    Patient patient;
    std::string date;
    std::string time;

public:
    Appointment(const Doctor &doctor, const Patient &patient, const std::string &date, const std::string &time);

    Appointment(int64_t id, const Doctor &doctor, const Patient &patient, const std::string &date,
                const std::string &time);

    Appointment(const Appointment &a);
    Appointment & operator=(const Appointment &d);

    const int64_t &getId() const;
    void setId(const int64_t &id);

    const Doctor &getDoctor() const;
    void setDoctor(const Doctor &doctor);

    const Patient &getPatient() const;
    void setPatient(const Patient &patient);

    const std::string &getDate() const;
    void setDate(const std::string &date);

    const std::string &getTime() const;
    void setTime(const std::string &time);

    friend std::ostream &operator<<(std::ostream &os, const Appointment &appointment);
};


#endif //MPO_1_APPOINTMENT_H
