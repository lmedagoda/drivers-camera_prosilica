SET(module_name ${PROJECT_NAME})
SET(TestViewer TestViewer)

add_library(${PROJECT_NAME} SHARED CamGigEProsilica.cpp)
target_link_libraries(${PROJECT_NAME} librt.so libPvAPI.a libcamera_interface.so libpthread.so)
install(TARGETS ${PROJECT_NAME} 
			RUNTIME DESTINATION bin
			LIBRARY DESTINATION lib)

# test programs 
add_executable(${TestViewer} TestViewer.cpp)   
target_link_libraries(${TestViewer} libcamera_prosilica_gige.so libcv.so libhighgui.so)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/build/bin/ DESTINATION ${PROJECT_SOURCE_DIR}/test
	FILES_MATCHING PATTERN "Test*")

