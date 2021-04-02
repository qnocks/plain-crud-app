//
// Created by qnocks on 3/25/21.
//

#include <regex>
#include "Appointment.h"


Appointment::Appointment(const Doctor &doctor, const Patient &patient, const std::string &date, const std::string &time)
        : doctor(doctor), patient(patient) {
    setDate(date);
    setTime(time);
}

Appointment::Appointment(int64_t id, const Doctor &doctor, const Patient &patient, const std::string &date,
                         const std::string &time) : doctor(doctor), patient(patient) {
    setId(id);
    setDate(date);
    setTime(time);
}

Appointment::Appointment(const Appointment &a) : doctor(a.doctor), patient(a.patient) {
    setId(a.id);
    setDate(a.date);
    setTime(a.time);
}

Appointment &Appointment::operator=(const Appointment &a) {
    if (this == &a)
        return *this;

    setDate(a.date);
    setTime(a.time);

    return *this;
}

const int64_t &Appointment::getId() const {
    return id;
}

void Appointment::setId(const int64_t &id) {
    Appointment::id = id;
}

const Doctor &Appointment::getDoctor() const {
    return doctor;
}

void Appointment::setDoctor(const Doctor &doctor) {
    Appointment::doctor = doctor;
}

const Patient &Appointment::getPatient() const {
    return patient;
}

void Appointment::setPatient(const Patient &patient) {
    Appointment::patient = patient;
}

const std::string &Appointment::getDate() const {
    return date;
}

void Appointment::setDate(const std::string &date) {

    std::regex pattern(R"((0[1-9]|[12][0-9]|3[01])[.](0[1-9]|1[012])[.](19|20)\d\d)");

    if (!std::regex_match(date, pattern))
        throw std::domain_error("Дата талона должна быть в формате ДД.ММ.ГГГГ [" + date + "]");

    Appointment::date = date;
}

const std::string &Appointment::getTime() const {
    return time;
}

void Appointment::setTime(const std::string &time) {

    const std::regex pattern("([01]?[0-9]|2[0-3]):[0-5][0-9]");

    if (!std::regex_match(time, pattern))
        throw std::domain_error("Время талона должно быть в формате ЧЧ:ММ [" + time + "]");

    auto hoursAndMinutesAppointment = Utils::split(time, ":"); // 14:22
    auto hoursAppointment = hoursAndMinutesAppointment[0]; // 14
    auto minutesAppointment = hoursAndMinutesAppointment[1]; // 22

    int hoursAppointmentInt = std::stoi(hoursAppointment);
    int minutesAppointmentInt = std::stoi(minutesAppointment);


    auto startAndEnd = Utils::split(doctor.getSchedule(), "-");
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

    if (!(hoursAppointmentInt > hoursStartInt && hoursAppointmentInt < hoursEndInt ||
            hoursAppointmentInt == hoursStartInt && minutesAppointmentInt >= minutesStartInt ||
            hoursAppointmentInt == hoursEndInt && minutesAppointmentInt < minutesEndInt)) {
        throw std::domain_error("Время талона должно попадать в интервал расписания доктора  [" + time + ", "+ doctor.getSchedule() + "]");
    }

    Appointment::time = time;
}

std::ostream &operator<<(std::ostream &os, const Appointment &appointment) {
    os << appointment.id << "; " << appointment.doctor << "; " << appointment.patient
       << "; " << appointment.date << "; " << appointment.time;
    return os;

}



