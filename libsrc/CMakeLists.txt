project(libsrc)


find_package( OpenCV REQUIRED )
message (“Libs directory: “ ${PROJECT_SOURCE_DIR})
set(HEADERS lib_imageDatatypes.hpp lib_dataImporter.hpp lib_imageOperations.hpp) 
set(SOURCES lib_imageDatatypes.cpp lib_dataImporter.cpp)
add_library(libsrc SHARED ${HEADERS} ${SOURCES} )
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})


#link
#———

#configure install
#———
install( TARGETS ${PROJECT_NAME}
	  RUNTIME DESTINATION bin
         LIBRARY DESTINATION lib
	  ARCHIVE DESTINATION lib/static  )
