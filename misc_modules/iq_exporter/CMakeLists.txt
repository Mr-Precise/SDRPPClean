cmake_minimum_required(VERSION 3.13)
project(iq_exporter)

file(GLOB SRC "src/*.cpp")

include(${SDRPP_MODULE_CMAKE})