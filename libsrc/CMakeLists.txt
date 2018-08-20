project(libsrc)



message (“Libs directory: “ ${PROJECT_SOURCE_DIR})
set(HEADERS lib_imageDatatypes.hpp lib_dataImporter.hpp) 
set(SOURCES lib_imageDatatypes.cpp lib_dataImporter.cpp)
add_library(libsrc SHARED ${HEADERS} ${SOURCES} )

#link
#———

#configure install
#———
install( TARGETS ${PROJECT_NAME}
	  RUNTIME DESTINATION bin
         LIBRARY DESTINATION lib
	  ARCHIVE DESTINATION lib/static  )
