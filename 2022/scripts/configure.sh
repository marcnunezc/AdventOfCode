export SOURCE_PATH="${SOURCE_PATH:-"$( cd "$(dirname "$0")" ; pwd -P )"/..}"
export BUILD_PATH="${SOURCE_PATH}/build"

cmake -H"${SOURCE_PATH}" -B"${BUILD_PATH}/${KRATOS_BUILD_TYPE}" \
-DCMAKE_BUILD_TYPE=Debug

cmake --build "${BUILD_PATH}"