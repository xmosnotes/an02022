cmake_minimum_required(VERSION 3.21)
include($ENV{XMOS_CMAKE_PATH}/xcommon.cmake)
project(app_an02021)

set(APP_HW_TARGET       secondary-pll.xn)
#set(APP_HW_TARGET       system-pll.xn)

set(APP_COMPILER_FLAGS          -O2
                                -g
                                -mcmodel=large)

#set(APP_INCLUDES        src/
#                        ../../lib_src/lib_src/src/asrc_task/)

set(XMOS_SANDBOX_DIR    ${CMAKE_CURRENT_LIST_DIR}/../..)

XMOS_REGISTER_APP()
