#ifndef MPO_1_POLYCLINIC_H
#define MPO_1_POLYCLINIC_H

#include <list>
#include <algorithm>

#include "../../domain/doctor/Doctor.h"
#include "../../domain/patient/Patient.h"
#include "../../domain/appointment/Appointment.h"

class Polyclinic {
private:

    int64_t doctorId = 0;
    int64_t patientId = 0;
    int64_t appointmentsId = 0;

    std::list<Doctor> doctors;
    std::list<Patient> patients;
    std::list<Appointment> appointments;
public:
    const std::list<Doctor> &getDoctors() const;
    const std::list<Patient> &getPatients() const;
    const std::list<Appointment> &getAppointments() const;

    const Doctor &getDoctorById(int64_t id) const;
    const Patient &getPatientById(int64_t id) const;
    const Appointment &getAppointmentById(int64_t id) const;

    void addDoctor(Doctor d);
    void addPatient(Patient p);
    void addAppointment(Appointment a);

    void clearDoctors();
    void clearPatients();
    void clearAppointments();

    void deleteDoctor(int64_t id);
    void deletePatient(int64_t id);
    void deleteAppointment(int64_t id);

    void updateDoctor(const Doctor &d);
    void updatePatient(const Patient &p);
    void updateAppointment(const Appointment &a);

private:
    template<typename T>
    typename std::list<T>::const_iterator constIteratorById(std::list<T>, int64_t id) const;

};

#endif //MPO_1_POLYCLINIC_H
