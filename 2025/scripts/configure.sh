export CC=gcc-10
export CXX=g++-10
export SOURCE_PATH="${SOURCE_PATH:-"$( cd "$(dirname "$0")" ; pwd -P )"/..}"
export BUILD_PATH="${SOURCE_PATH}/build"

cmake -S"${SOURCE_PATH}" -B"${BUILD_PATH}" \
-DCMAKE_BUILD_TYPE=Release

cmake --build "${BUILD_PATH}"