cmake . build -DCMAKE_GENERATOR_PLATFORM=x64 -DCMAKE_GENERATOR="Visual Studio 16 2019" -DEVENT__DISABLE_OPENSSL=ON -DEVENT__DISABLE_MBEDTLS=ON -DEVENT__MSVC_STATIC_RUNTIME=ON -DCMAKE_BUILD_TYPE=Release -DEVENT__LIBRARY_TYPE=SHARED