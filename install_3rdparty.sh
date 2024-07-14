#!/bin/bash

rm -rf 3rdparty_vcpkg/
vcpkg install --triplet=x64-windows-static-md --x-install-root=3rdparty_vcpkg