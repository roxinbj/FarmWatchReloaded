
#about this project
#———————

project(exec)

find_package( OpenCV REQUIRED )
include_directories(${CMAKE_SOURCE_DIR}/libsrc)
#target_include_directories(exec PRIVATE ${PROJECT_SOURCE_DIR}../libsrc)
#set public headers and sources


#create binaries
#—————
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/main.cpp)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} libsrc)

#link
#———

#configure install
#———
install( TARGETS ${PROJECT_NAME}
	  RUNTIME DESTINATION bin
         LIBRARY DESTINATION lib
	  ARCHIVE DESTINATION lib/static  )