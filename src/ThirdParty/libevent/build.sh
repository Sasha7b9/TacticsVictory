#!/usr/bin/env bash
cmake . -Bbuild -G "CodeBlocks - Unix Makefiles"  -DEVENT__DISABLE_OPENSSL=ON -DEVENT__DISABLE_MBEDTLS=ON -DCMAKE_BUILD_TYPE=Release -DEVENT__LIBRARY_TYPE=STATIC
cd build
make -j$(nproc)
make
cd ..

