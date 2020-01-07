mkdir build
cd build
conan install .. --build=missing
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
cd ..
