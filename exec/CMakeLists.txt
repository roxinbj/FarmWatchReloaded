
#about this project
#———————

project(exec)

set(Boost_USE_STATIC_LIBS        ON) # only find static libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package(Boost 1.67.0 COMPONENTS date_time filesystem system )
if(Boost_FOUND)
  message("Boost found")
  include_directories(${Boost_INCLUDE_DIRS})
endif()


find_package(OpenCV REQUIRED ) 

include_directories(${CMAKE_SOURCE_DIR}/libsrc)


add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/main.cpp)

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} libsrc)
#target_link_libraries(${PROJECT_NAME} libsrc)

#create binaries
#—————
#add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/main.cpp)
#target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} libsrc)

#link
#———

#configure install
#———
install( TARGETS ${PROJECT_NAME}
	  RUNTIME DESTINATION bin
         LIBRARY DESTINATION lib
	  ARCHIVE DESTINATION lib/static  )