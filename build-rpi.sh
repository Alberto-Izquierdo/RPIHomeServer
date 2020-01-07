mkdir build
cd build
conan install .. --build=missing --profile ../rpi_profile
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=../Toolchain-RaspberryPi.cmake
make -j$(nproc)
cd ..
