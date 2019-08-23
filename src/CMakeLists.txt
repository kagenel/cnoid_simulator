####
## settings for OpenRTM
##

# pkg_check_modules
include(FindPkgConfig)
include(CheckIncludeFiles)

####
## Find OpenRTM
##
pkg_check_modules(OPENRTM REQUIRED openrtm-aist)

add_definitions(${OPENRTM_DEFINITIONS})
include_directories(${OPENRTM_INCLUDE_DIRS})
link_directories(${OPENRTM_LIBRARY_DIRS})

####
## BodyIoRTC
##
pkg_check_modules(CHOREONOID REQUIRED choreonoid-body-plugin)

include_directories(${CHOREONOID_INCLUDE_DIRS})
link_directories(${CHOREONOID_LIBRARY_DIRS})

####
## SRC
##
set(COMP_NAME "SampleIoRTC")

add_library(${COMP_NAME} SHARED sampleRTC.cpp sampleIoRTC.cpp)
target_link_libraries(${COMP_NAME} ${CHOREONOID_LIBRARIES} ${OPENRTM_LIBRARIES})

####
## 名前変更
##
set_target_properties(${COMP_NAME} PROPERTIES PREFIX "")                  # プリフィックス
set_target_properties(${COMP_NAME} PROPERTIES OUTPUT_NAME ${COMP_NAME})   # 出力名
set_target_properties(${COMP_NAME} PROPERTIES SUFFIX ".so")               # サフィックス
