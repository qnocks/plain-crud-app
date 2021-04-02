cmake_minimum_required(VERSION 3.17)
project(mpo_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(mpo_1 main.cpp dao/polyclinic/Polyclinic.cpp dao/polyclinic/Polyclinic.h service/registry/Registry.cpp service/registry/Registry.h domain/doctor/Doctor.cpp domain/doctor/Doctor.h domain/patient/Patient.cpp domain/patient/Patient.h domain/appointment/Appointment.cpp domain/appointment/Appointment.h util/Utils.h)