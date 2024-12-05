# internal project
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/test)

# Local Lib ############################################################################################################

########################################################################################################################
# set: she_test
set(_she_test "${CMAKE_CURRENT_SOURCE_DIR}/third_party/she_test-1.0.0")
set(she_test_include_dir "${_she_test}/include")
set(she_test_lib_dir "${_she_test}/lib")
set(she_test_link_libs she_test)
# import she_test
include_directories(${she_test_include_dir})
link_directories(${she_test_lib_dir})
list(APPEND test_link_dependency ${she_test_link_libs})
########################################################################################################################

########################################################################################################################
# set ffmpeg_wrapper
set(_ffmpeg_wrapper_path "${CMAKE_CURRENT_SOURCE_DIR}/third_party/ffmpeg_wrapper-1.0.0")
set(ffmpeg_wrapper_include_dir "${_ffmpeg_wrapper_path}/include")
set(ffmpeg_wrapper_lib_dir "${_ffmpeg_wrapper_path}/lib")
set(ffmpeg_wrapper_link_libs ffmpeg_wrapper)
# import ffmpeg_wrapper
include_directories(${ffmpeg_wrapper_include_dir})
link_directories(${ffmpeg_wrapper_lib_dir})
list(APPEND src_link_dependency ${ffmpeg_wrapper_link_libs})
########################################################################################################################

########################################################################################################################
# set portaudio
set(_portaudio_path "${CMAKE_CURRENT_SOURCE_DIR}/third_party/portaudio-v19.7.0")
set(portaudio_include_dir "${_portaudio_path}/include")
set(portaudio_lib_dir "${_portaudio_path}/lib")
set(portaudio_link_libs portaudio)
# import portaudio
include_directories(${portaudio_include_dir})
link_directories(${portaudio_lib_dir})
list(APPEND src_link_dependency ${portaudio_link_libs})
########################################################################################################################

########################################################################################################################
# set spdlog
set(_spdlog_path "${CMAKE_CURRENT_SOURCE_DIR}/third_party/spdlog-v1.10.0")
set(spdlog_include_dir "${_spdlog_path}/include")
# import portaudio
include_directories(${spdlog_include_dir})
########################################################################################################################

# Non-local Lib ########################################################################################################

########################################################################################################################
# set ffmpeg
set(FFMPEG_ROOT_DIR "/usr/local" CACHE STRING "default path")
set(_ffmpeg_path ${FFMPEG_ROOT_DIR})
set(ffmpeg_include_dir "${_ffmpeg_path}/include")
set(ffmpeg_lib_dir "${_ffmpeg_path}/lib")
set(ffmpeg_link_libs avcodec avdevice avfilter avformat avutil postproc swresample swscale)
# import ffmpeg
include_directories(${ffmpeg_include_dir})
link_directories(${ffmpeg_lib_dir})
list(APPEND src_link_dependency ${ffmpeg_link_libs})
########################################################################################################################

########################################################################################################################
# set sqlite3
set(SQLITE3_ROOT_DIR "/usr/local" CACHE STRING "default path")
set(_sqlite3_path ${SQLITE3_ROOT_DIR})
set(sqlite3_include_dir "${_sqlite3_path}/include")
set(sqlite3_lib_dir "${_sqlite3_path}/lib")
set(sqlite3_link_libs sqlite3)
# import sqlite3
include_directories(${sqlite3_include_dir})
link_directories(${sqlite3_lib_dir})
list(APPEND src_link_dependency ${sqlite3_link_libs})
########################################################################################################################

########################################################################################################################
# set sqlite_orm
set(SQLITE_ORM_ROOT_DIR "/usr/local" CACHE STRING "default path")
set(_sqlite_orm_path ${SQLITE_ORM_ROOT_DIR})
set(sqlite_orm_include_dir "${_sqlite_orm_path}/include")
# import sqlite3
include_directories(${sqlite_orm_include_dir})
########################################################################################################################

########################################################################################################################
# set qt5
set(QT5_ROOT_DIR "/usr/local" CACHE STRING "default path")
set(_qt5_path ${QT5_ROOT_DIR})
set(CMAKE_PREFIX_PATH ${_qt5_path})
set(CMAKE_AUTOMOC ON)
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
set(qt5_include_dir "${_qt5_path}/include")
set(qt5_lib_dir "${_qt5_path}/lib")
set(qt5_link_libs Qt5::Core Qt5::Widgets)
# import qt5
include_directories(${qt5_include_dir})
link_directories(${qt5_lib_dir})
list(APPEND src_link_dependency ${qt5_link_libs})
########################################################################################################################
