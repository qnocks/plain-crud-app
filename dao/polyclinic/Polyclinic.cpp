#include "Polyclinic.h"

const std::list<Doctor> &Polyclinic::getDoctors() const {
    return doctors;
}

const std::list<Patient> &Polyclinic::getPatients() const {
    return patients;
}

const std::list<Appointment> &Polyclinic::getAppointments() const {
    return appointments;
}

const Doctor &Polyclinic::getDoctorById(int64_t id) const {
    for (const auto &d : doctors) {
        if (d.getId() == id) {
            return d;
        }
    }
    throw std::invalid_argument("Не найден доктор с id " + std::to_string(id));
}

const Patient &Polyclinic::getPatientById(int64_t id) const {
    for (const auto &p : patients) {
        if (p.getId() == id) {
            return p;
        }
    }
    throw std::invalid_argument("Не найден пациент с id " + std::to_string(id));
}

const Appointment &Polyclinic::getAppointmentById(int64_t id) const {
    for (const auto &a : appointments) {
        if (a.getId() == id) {
            return a;
        }
    }
    throw std::invalid_argument("Не найден талон с id " + std::to_string(id));
}

void Polyclinic::addDoctor(Doctor d) {
    d.setId(doctorId++);
    doctors.push_back(d);
}

void Polyclinic::addPatient(Patient p) {
    p.setId(patientId++);
    patients.push_back(p);
}

void Polyclinic::addAppointment(Appointment a) {
    a.setId(appointmentsId++);
    appointments.push_back(a);
}

void Polyclinic::clearDoctors() {
    doctors.clear();
}

void Polyclinic::clearPatients() {
    patients.clear();
}

void Polyclinic::clearAppointments() {
    appointments.clear();
}

void Polyclinic::deleteDoctor(int64_t id) {
    doctors.remove_if([id](const Doctor &d){ return d.getId() == id; });
    appointments.remove_if([id](const Appointment &a){return a.getDoctor().getId() == id;});
}

void Polyclinic::deletePatient(int64_t id) {
    patients.remove_if([id](const Patient &p){ return p.getId() == id; });
    appointments.remove_if([id](const Appointment &a){return a.getPatient().getId() == id;});
}

void Polyclinic::deleteAppointment(int64_t id) {
    appointments.remove_if([id](const Appointment &a){ return a.getId() == id; });
}

void Polyclinic::updateDoctor(const Doctor &d) {
    bool found = false;
    for (auto &doctor : doctors) {
        if (doctor.getId() == d.getId()) {
            doctor = d;
            found = true;
        }
    }
    if (!found)
        throw std::invalid_argument("Не найден доктор с id " + std::to_string(d.getId()));
}

void Polyclinic::updatePatient(const Patient &p) {
    bool found = false;
    for (auto &patient : patients) {
        if (patient.getId() == p.getId()) {
            patient = p;
            found = true;
        }
    }
    if (!found)
        throw std::invalid_argument("Не найден пациент с id " + std::to_string(p.getId()));
}

void Polyclinic::updateAppointment(const Appointment &a) {
    bool found = false;
    for (auto &appointment : appointments) {
        if (appointment.getId() == a.getId()) {
            appointment = a;
            found = true;
        }
    }
    if (!found)
        throw std::invalid_argument("Не найден талон с id " + std::to_string(a.getId()));
}

template<typename T>
typename std::list<T>::const_iterator Polyclinic::constIteratorById(std::list<T> t, int64_t id) const {
    std::find_if(t.begin(), t.end(), [id](const T &t){ t.getId() == id; });
}

