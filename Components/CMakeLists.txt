# Include Doodle component


set(COMPONENTS_SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/Components.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/ComponentsManager.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/ComponentCreator.cpp
    ${DOODLE_SOURCES} # Add Doodle sources
    PARENT_SCOPE
)