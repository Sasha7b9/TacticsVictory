#!/usr/bin/env bash

cmake .. -DEVENT__DISABLE_OPENSSL=ON -DEVENT__DISABLE_MBEDTLS=ON
make -j$(nproc)
