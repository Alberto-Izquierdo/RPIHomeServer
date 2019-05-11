mkdir build
cd build && conan install .. --build=missing --profile ../rpi_profile && cmake .. -DCMAKE_TOOLCHAIN_FILE=../Toolchain-RaspberryPi.cmake && make -j$(nproc)
