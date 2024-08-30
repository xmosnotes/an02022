cmake_minimum_required(VERSION 3.21)
include($ENV{XMOS_CMAKE_PATH}/xcommon.cmake)
project(app)

set(APP_HW_TARGET       example.xn)

set(XMOS_SANDBOX_DIR    ${CMAKE_CURRENT_LIST_DIR}/../..)

XMOS_REGISTER_APP()
