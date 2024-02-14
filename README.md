# SDR++ Clean bloat-free SDR software

#### This is a really clean **Fork** of SDR++
* **Bugs from this fork should be reported** [**here**](https://github.com/Mr-Precise/SDRPPClean/issues), not to the original author.
* Upstream url: [Mr-Precise/SDRPlusPlus](https://github.com/Mr-Precise/SDRPlusPlus)  
* SDR++ original author: [**AlexandreRouma/SDRPlusPlus**](https://github.com/AlexandreRouma/SDRPlusPlus)
* 
* MinGW compatible / build without garbage from Microsoft
* CMake only
* Improved CMake install logic and more readable code
* Possible backward incompatibility (different paths/names)
* Implemented linux portable build

SDR++ is a cross-platform and open source SDR software with the aim of being bloat free and simple to use.

### Dependencies
soon  
build-essential pkg-config git cmake make fftw3  
dev packages libvolk libzstd libhackrf rtl-sdr etc...

### Configure
soon  
cmake will accept some options, e.g.
* `-DUSE_LINUX_PORTABLE=ON`, Linux portable build
* `-DCMAKE_INSTALL_PREFIX=/usr` default install prefix on ubuntu/debian.  
`cmake -L ..` or see [CMakeLists.txt](https://github.com/Mr-Precise/SDRPPClean/blob/main/CMakeLists.txt)

### Build & Install
soon

```sh
git clone --recursive https://github.com/Mr-Precise/SDRPPClean
cd SDRPPClean && mkdir build && cd build
cmake -G "Unix Makefiles" ..
cmake --build . --config Release
```
MinGW toolchain
```sh
cmake -G "Unix Makefiles" .. -DCMAKE_TOOLCHAIN_FILE=Your-CrossCompiling-Toolchain-file.cmake
```

## Used libraries & projects
* [SoapySDR (PothosWare)](https://github.com/pothosware/SoapySDR)
* [Dear ImGui (ocornut)](https://github.com/ocornut/imgui)
* [json (nlohmann)](https://github.com/nlohmann/json)
* [portaudio](http://www.portaudio.com/)
* [rtaudio](https://www.music.mcgill.ca/~gary/rtaudio)
* [Portable File Dialogs](https://github.com/samhocevar/portable-file-dialogs)
* [sdrpp-mirisdr-source (cropinghigh)](https://github.com/cropinghigh/sdrpp-mirisdr-source)
* [volk](https://github.com/gnuradio/volk)
* [glfw](https://github.com/glfw/glfw)
* [rtl-sdr](https://github.com/Mr-Precise/rtl-sdr)
* [hackrf](https://github.com/greatscottgadgets/hackrf)
* [Airspy](https://github.com/airspy/airspyone_host)
* [Airspy HF+](https://github.com/airspy/airspyhf)
* [libmirisdr-5 (ericek111)](https://github.com/ericek111/libmirisdr-5)
* [bladeRF](https://github.com/Nuand/bladeRF)
* [libad9361-iio](https://github.com/analogdevicesinc/libad9361-iio)
