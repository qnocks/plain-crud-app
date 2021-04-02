#ifndef MPO_1_REGISTRY_H
#define MPO_1_REGISTRY_H


#include <fstream>
#include "../../dao/polyclinic/Polyclinic.h"

class Registry {
private:
    Polyclinic polyclinic;
    std::fstream doctorsFile;
    std::fstream patientsFile;
    std::fstream appointmentsFile;
public:
    Registry();
    virtual ~Registry();

    void getDoctors();
    void getPatients();
    void getAppointments();

    Doctor getDoctorById(int64_t id);
    Patient getPatientById(int64_t id);
    Appointment getAppointmentById(int64_t id);

    // Добавление доктора
    void addDoctor();

    // Добавление пациента
    void addPatient();

    // Добавление талона
    void addAppointment();

    void clearDoctors();
    void clearPatients();
    void clearAppointments();

    void deleteDoctor();
    void deletePatient();
    void deleteAppointment();

    void updateDoctor();
    void updatePatient();
    void updateAppointment();

private:
    void flushDoctorsToFile();
    void flushPatientsToFile();
    void flushAppointmentsToFile();

    static Doctor mapDoctor(std::string &strToParse);
    static Patient mapPatient(std::string &strToParse);
    static Appointment mapAppointment(std::string &strToParse);

};


#endif //MPO_1_REGISTRY_H
