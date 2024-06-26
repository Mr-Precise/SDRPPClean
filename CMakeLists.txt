cmake_minimum_required(VERSION 3.13)
project(sdrpp)

# Compatibility Options
option(OPT_OVERRIDE_STD_FILESYSTEM "Use a local version of std::filesystem on systems that don't have it yet" OFF)

# Sources
option(OPT_BUILD_AIRSPY_SOURCE "Build Airspy Source Module (Dependencies: libairspy)" ON)
option(OPT_BUILD_AIRSPYHF_SOURCE "Build Airspy HF+ Source Module (Dependencies: libairspyhf)" ON)
option(OPT_BUILD_MIRISDR_SOURCE "Build MiriSDR Source Module (Dependencies: libmirisdr v4 and higher)" OFF)
option(OPT_BUILD_AUDIO_SOURCE "Build Audio Source Module (Dependencies: rtaudio)" ON)
option(OPT_BUILD_BLADERF_SOURCE "Build BladeRF Source Module (Dependencies: libbladeRF)" OFF)
option(OPT_BUILD_FILE_SOURCE "Wav file source" ON)
option(OPT_BUILD_HACKRF_SOURCE "Build HackRF Source Module (Dependencies: libhackrf)" ON)
option(OPT_BUILD_HERMES_SOURCE "Build Hermes Source Module (no dependencies required)" ON)
option(OPT_BUILD_LIMESDR_SOURCE "Build LimeSDR Source Module (Dependencies: liblimesuite)" OFF)
option(OPT_BUILD_NETWORK_SOURCE "Build Network Source Module (no dependencies required)" ON)
option(OPT_BUILD_PERSEUS_SOURCE "Build Perseus Source Module (Dependencies: libperseus-sdr)" OFF)
option(OPT_BUILD_PLUTOSDR_SOURCE "Build PlutoSDR Source Module (Dependencies: libiio, libad9361)" ON)
option(OPT_BUILD_RFSPACE_SOURCE "Build RFspace Source Module (no dependencies required)" ON)
option(OPT_BUILD_RTL_SDR_SOURCE "Build RTL-SDR Source Module (Dependencies: librtlsdr)" ON)
option(OPT_BUILD_RTL_TCP_SOURCE "Build RTL-TCP Source Module (no dependencies required)" ON)
option(OPT_BUILD_SDRPP_SERVER_SOURCE "Build SDR++ Server Source Module (no dependencies required)" ON)
option(OPT_BUILD_SOAPY_SOURCE "Build SoapySDR Source Module (Dependencies: soapysdr)" OFF)
# option(OPT_BUILD_SPECTRAN_SOURCE "Build Spectran Source Module (Dependencies: Aaronia RTSA Suite)" OFF)
option(OPT_BUILD_SPECTRAN_HTTP_SOURCE "Build Spectran HTTP Source Module (no dependencies required)" ON)
option(OPT_BUILD_SPYSERVER_SOURCE "Build SpyServer Source Module (no dependencies required)" ON)
option(OPT_BUILD_USRP_SOURCE "Build USRP Source Module (libuhd)" OFF)

# Sinks
option(OPT_BUILD_AUDIO_SINK "Build Audio Sink Module (Dependencies: rtaudio)" ON)
option(OPT_BUILD_NETWORK_SINK "Build Audio Sink Module (no dependencies required)" ON)
option(OPT_BUILD_NEW_PORTAUDIO_SINK "Build the new PortAudio Sink Module (Dependencies: portaudio)" OFF)
option(OPT_BUILD_PORTAUDIO_SINK "Build PortAudio Sink Module (Dependencies: portaudio)" OFF)

# Decoders
option(OPT_BUILD_ATV_DECODER "Build ATV decoder (no dependencies required)" OFF)
# option(OPT_BUILD_FALCON9_DECODER "Build the falcon9 live decoder (Dependencies: ffplay)" OFF)
# option(OPT_BUILD_KG_SSTV_DECODER "Build the KG SSTV (KG-STV) decoder module (no dependencies required)" OFF)
option(OPT_BUILD_M17_DECODER "Build the M17 decoder module (Dependencies: codec2)" OFF)
option(OPT_BUILD_METEOR_DEMODULATOR "Build the meteor demodulator module (no dependencies required)" ON)
option(OPT_BUILD_PAGER_DECODER "Build the pager decoder module (no dependencies required)" ON)
option(OPT_BUILD_RADIO "Main audio modulation decoder (AM, FM, SSB, etc...)" ON)
# option(OPT_BUILD_WEATHER_SAT_DECODER "Build the HRPT decoder module (no dependencies required)" OFF)

# Misc
option(OPT_BUILD_FREQUENCY_MANAGER "Build the Frequency Manager module" ON)
option(OPT_BUILD_IQ_EXPORTER "Build the IQ Exporter module" ON)
option(OPT_BUILD_RECORDER "Audio and baseband recorder" ON)
option(OPT_BUILD_RIGCTL_CLIENT "Rigctl client to make SDR++ act as a panadapter" ON)
option(OPT_BUILD_RIGCTL_SERVER "Rigctl backend for controlling SDR++ with software like gpredict" ON)
option(OPT_BUILD_SCANNER "Frequency scanner" ON)
option(OPT_BUILD_SCHEDULER "Build the scheduler" OFF)

# Other options
option(USE_INTERNAL_LIBCORRECT "Use an internal version of libcorrect" ON)
option(USE_BUNDLE_DEFAULTS "Set the default resource and module directories to the right ones for a MacOS .app" OFF)
option(USE_LINUX_PORTABLE "Set the resource and module directories for a Linux portable build" OFF)

# Module cmake path
set(SDRPP_MODULE_CMAKE "${CMAKE_SOURCE_DIR}/cmake/sdrpp_module.cmake")

# Root source folder
set(SDRPP_CORE_ROOT "${CMAKE_SOURCE_DIR}/core/src/")

# Compiler flags
# NEED fix
if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    # Debug Flags
    if(MSVC)
        set(SDRPP_COMPILER_FLAGS /std:c++17 /EHsc)
        set(SDRPP_GUI_COMPILER_FLAGS ${SDRPP_COMPILER_FLAGS})
    elseif(MINGW)
        set(SDRPP_COMPILER_FLAGS -g -Og -std=c++17 -Wl,--export-all-symbols)
        set(SDRPP_GUI_COMPILER_FLAGS ${SDRPP_COMPILER_FLAGS} -mwindows)
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(SDRPP_COMPILER_FLAGS -g -Og -std=c++17 -Wno-unused-command-line-argument -undefined dynamic_lookup)
        set(SDRPP_GUI_COMPILER_FLAGS ${SDRPP_COMPILER_FLAGS})
    else()
        set(SDRPP_COMPILER_FLAGS -g -Og -std=c++17)
        set(SDRPP_GUI_COMPILER_FLAGS ${SDRPP_COMPILER_FLAGS})
    endif()
else()
    # Normal Flags
    if (MSVC)
        set(SDRPP_COMPILER_FLAGS /O2 /Ob2 /std:c++17 /EHsc)
        set(SDRPP_GUI_COMPILER_FLAGS ${SDRPP_COMPILER_FLAGS})
    elseif(MINGW)
        set(SDRPP_COMPILER_FLAGS -O3 -std=c++17 -Wl,--export-all-symbols)
        set(SDRPP_GUI_COMPILER_FLAGS ${SDRPP_COMPILER_FLAGS} -mwindows)
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(SDRPP_COMPILER_FLAGS -O3 -std=c++17 -Wno-unused-command-line-argument -undefined dynamic_lookup)
    else()
        set(SDRPP_COMPILER_FLAGS -O3 -std=c++17)
        set(SDRPP_GUI_COMPILER_FLAGS ${SDRPP_COMPILER_FLAGS})
    endif()
endif()
set(SDRPP_MODULE_COMPILER_FLAGS ${SDRPP_COMPILER_FLAGS})


# Set a default install prefix
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        set(CMAKE_INSTALL_PREFIX "/usr/local" CACHE PATH "..." FORCE)
    else()
        set(CMAKE_INSTALL_PREFIX "/usr" CACHE PATH "..." FORCE)
    endif()
endif()

# Create directory for MinGW build
if((${CMAKE_SYSTEM_NAME} MATCHES "Linux" AND USE_LINUX_PORTABLE) OR MINGW)
    set(BUILD_OUTPUT_DIR ${CMAKE_BINARY_DIR}/SDRRlusPlus-build-${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR})
    file(MAKE_DIRECTORY ${BUILD_OUTPUT_DIR}/modules/)
endif()

# Core of SDR++
add_subdirectory("core")

# Source modules
if(OPT_BUILD_AIRSPY_SOURCE)
    add_subdirectory("source_modules/airspy_source")
endif(OPT_BUILD_AIRSPY_SOURCE)

if(OPT_BUILD_AIRSPYHF_SOURCE)
    add_subdirectory("source_modules/airspyhf_source")
endif(OPT_BUILD_AIRSPYHF_SOURCE)

if(OPT_BUILD_MIRISDR_SOURCE)
    add_subdirectory("source_modules/mirisdr_source")
endif(OPT_BUILD_MIRISDR_SOURCE)

if(OPT_BUILD_AUDIO_SOURCE)
    add_subdirectory("source_modules/audio_source")
endif(OPT_BUILD_AUDIO_SOURCE)

if(OPT_BUILD_BLADERF_SOURCE)
    add_subdirectory("source_modules/bladerf_source")
endif(OPT_BUILD_BLADERF_SOURCE)

if(OPT_BUILD_FILE_SOURCE)
    add_subdirectory("source_modules/file_source")
endif(OPT_BUILD_FILE_SOURCE)

if(OPT_BUILD_HACKRF_SOURCE)
    add_subdirectory("source_modules/hackrf_source")
endif(OPT_BUILD_HACKRF_SOURCE)

if(OPT_BUILD_HERMES_SOURCE)
    add_subdirectory("source_modules/hermes_source")
endif(OPT_BUILD_HERMES_SOURCE)

if(OPT_BUILD_LIMESDR_SOURCE)
    add_subdirectory("source_modules/limesdr_source")
endif(OPT_BUILD_LIMESDR_SOURCE)

if (OPT_BUILD_NETWORK_SOURCE)
    add_subdirectory("source_modules/network_source")
endif (OPT_BUILD_NETWORK_SOURCE)

if(OPT_BUILD_PERSEUS_SOURCE)
    add_subdirectory("source_modules/perseus_source")
endif(OPT_BUILD_PERSEUS_SOURCE)

if(OPT_BUILD_PLUTOSDR_SOURCE)
    add_subdirectory("source_modules/plutosdr_source")
endif(OPT_BUILD_PLUTOSDR_SOURCE)

if(OPT_BUILD_RFSPACE_SOURCE)
    add_subdirectory("source_modules/rfspace_source")
endif(OPT_BUILD_RFSPACE_SOURCE)

if(OPT_BUILD_RTL_SDR_SOURCE)
    add_subdirectory("source_modules/rtl_sdr_source")
endif(OPT_BUILD_RTL_SDR_SOURCE)

if(OPT_BUILD_RTL_TCP_SOURCE)
    add_subdirectory("source_modules/rtl_tcp_source")
endif(OPT_BUILD_RTL_TCP_SOURCE)

if(OPT_BUILD_SDRPP_SERVER_SOURCE)
    add_subdirectory("source_modules/sdrpp_server_source")
endif(OPT_BUILD_SDRPP_SERVER_SOURCE)

if(OPT_BUILD_SDRPLAY_SOURCE)
    add_subdirectory("source_modules/sdrplay_source")
endif(OPT_BUILD_SDRPLAY_SOURCE)

if(OPT_BUILD_SOAPY_SOURCE)
    add_subdirectory("source_modules/soapy_source")
endif(OPT_BUILD_SOAPY_SOURCE)

if(OPT_BUILD_SPECTRAN_SOURCE)
    add_subdirectory("source_modules/spectran_source")
endif(OPT_BUILD_SPECTRAN_SOURCE)

if(OPT_BUILD_SPECTRAN_HTTP_SOURCE)
    add_subdirectory("source_modules/spectran_http_source")
endif(OPT_BUILD_SPECTRAN_HTTP_SOURCE)

if(OPT_BUILD_SPYSERVER_SOURCE)
    add_subdirectory("source_modules/spyserver_source")
endif(OPT_BUILD_SPYSERVER_SOURCE)

if(OPT_BUILD_USRP_SOURCE)
    add_subdirectory("source_modules/usrp_source")
endif(OPT_BUILD_USRP_SOURCE)


# Sink modules
if(OPT_BUILD_AUDIO_SINK)
    add_subdirectory("sink_modules/audio_sink")
endif(OPT_BUILD_AUDIO_SINK)

if(OPT_BUILD_PORTAUDIO_SINK)
    add_subdirectory("sink_modules/portaudio_sink")
endif(OPT_BUILD_PORTAUDIO_SINK)

if(OPT_BUILD_NETWORK_SINK)
    add_subdirectory("sink_modules/network_sink")
endif(OPT_BUILD_NETWORK_SINK)

if(OPT_BUILD_NEW_PORTAUDIO_SINK)
    add_subdirectory("sink_modules/new_portaudio_sink")
endif(OPT_BUILD_NEW_PORTAUDIO_SINK)


# Decoders
if(OPT_BUILD_ATV_DECODER)
    add_subdirectory("decoder_modules/atv_decoder")
endif(OPT_BUILD_ATV_DECODER)

if(OPT_BUILD_FALCON9_DECODER)
    add_subdirectory("decoder_modules/falcon9_decoder")
endif(OPT_BUILD_FALCON9_DECODER)

if(OPT_BUILD_KG_SSTV_DECODER)
    add_subdirectory("decoder_modules/kg_sstv_decoder")
endif(OPT_BUILD_KG_SSTV_DECODER)

if(OPT_BUILD_M17_DECODER)
    add_subdirectory("decoder_modules/m17_decoder")
endif(OPT_BUILD_M17_DECODER)

if(OPT_BUILD_METEOR_DEMODULATOR)
    add_subdirectory("decoder_modules/meteor_demodulator")
endif(OPT_BUILD_METEOR_DEMODULATOR)

if(OPT_BUILD_PAGER_DECODER)
    add_subdirectory("decoder_modules/pager_decoder")
endif(OPT_BUILD_PAGER_DECODER)

if(OPT_BUILD_RADIO)
    add_subdirectory("decoder_modules/radio")
endif(OPT_BUILD_RADIO)

if(OPT_BUILD_WEATHER_SAT_DECODER)
    add_subdirectory("decoder_modules/weather_sat_decoder")
endif(OPT_BUILD_WEATHER_SAT_DECODER)

# Misc
if(OPT_BUILD_FREQUENCY_MANAGER)
    add_subdirectory("misc_modules/frequency_manager")
endif(OPT_BUILD_FREQUENCY_MANAGER)

if(OPT_BUILD_IQ_EXPORTER)
    add_subdirectory("misc_modules/iq_exporter")
endif(OPT_BUILD_IQ_EXPORTER)

if(OPT_BUILD_RECORDER)
    add_subdirectory("misc_modules/recorder")
endif(OPT_BUILD_RECORDER)

if(OPT_BUILD_RIGCTL_CLIENT)
    add_subdirectory("misc_modules/rigctl_client")
endif(OPT_BUILD_RIGCTL_CLIENT)

if(OPT_BUILD_RIGCTL_SERVER)
    add_subdirectory("misc_modules/rigctl_server")
endif(OPT_BUILD_RIGCTL_SERVER)

if(OPT_BUILD_SCANNER)
    add_subdirectory("misc_modules/scanner")
endif(OPT_BUILD_SCANNER)

if(OPT_BUILD_SCHEDULER)
    add_subdirectory("misc_modules/scheduler")
endif(OPT_BUILD_SCHEDULER)

# create main SDR++
if(MSVC OR MINGW)
    add_executable(sdrpp "src/main.cpp" "resources/win32/resources.rc")
else()
    add_executable(sdrpp "src/main.cpp")
endif()

target_link_libraries(sdrpp PRIVATE sdrpp_core)

# Compiler arguments
target_compile_options(sdrpp PRIVATE ${SDRPP_GUI_COMPILER_FLAGS})

# Copy sdrpp gui binary to build dir
if((${CMAKE_SYSTEM_NAME} MATCHES "Linux" AND USE_LINUX_PORTABLE) OR MINGW)
    add_custom_target(copy_sdrpp ALL
        COMMAND ${CMAKE_COMMAND} -E copy
            "$<TARGET_FILE_DIR:sdrpp>/sdrpp${CMAKE_EXECUTABLE_SUFFIX}"
            "${BUILD_OUTPUT_DIR}"
    )
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
    target_link_libraries(sdrpp PUBLIC pthread)
endif()

# Create module cmake file
configure_file(${CMAKE_SOURCE_DIR}/cmake/sdrpp_module.cmake ${CMAKE_CURRENT_BINARY_DIR}/sdrpp_module.cmake @ONLY)

# Install directives
install(TARGETS sdrpp DESTINATION bin)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/resources/res/bandplans DESTINATION share/sdrpp)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/resources/res/colormaps DESTINATION share/sdrpp)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/resources/res/fonts DESTINATION share/sdrpp)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/resources/res/icons DESTINATION share/sdrpp)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/resources/res/themes DESTINATION share/sdrpp)
configure_file(${CMAKE_SOURCE_DIR}/resources/sdrpp.desktop ${CMAKE_CURRENT_BINARY_DIR}/sdrpp.desktop @ONLY)

if((${CMAKE_SYSTEM_NAME} MATCHES "Linux" AND USE_LINUX_PORTABLE) OR MINGW)
    file(GLOB resources
        "${CMAKE_SOURCE_DIR}/resources/res/*"
    )
    file(COPY ${resources} DESTINATION ${BUILD_OUTPUT_DIR}/res/)
endif()


if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/sdrpp.desktop DESTINATION share/applications)
endif()

# Create uninstall target
configure_file(${CMAKE_SOURCE_DIR}/cmake/cmake_uninstall.cmake ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake @ONLY)
add_custom_target(uninstall ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
