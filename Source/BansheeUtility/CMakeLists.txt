# Includes
set(BansheeUtility_INC "Include" "Include/ThirdParty" "../../Dependencies/include")

if(WIN32)
	set(BansheeUtility_INC ${BansheeUtility_INC} "Include/Win32")
endif()

include_directories(${BansheeUtility_INC})	
	
# Sources
set(BansheeUtility_SRC_FOLDERS "Source/*.cpp" "Source/ThirdParty/*.cpp")

if(WIN32)
	set(BansheeUtility_SRC_FOLDERS ${BansheeUtility_SRC_FOLDERS} "Source/Win32/*.cpp")
endif()

foreach(includeFolder ${BansheeUtility_INC})
	set(BansheeUtility_SRC_FOLDERS ${BansheeUtility_SRC_FOLDERS} "${includeFolder}/*.h")
endforeach()

file(GLOB BansheeUtility_SRC ${BansheeUtility_SRC_FOLDERS})

# Configure file
#configure_file (
#  "BsBuildConfig.h.in"
#  "Generated/BsBuildConfig.h"
#)

#include_directories ("${CMAKE_CURRENT_BINARY_DIR}/Generated")

# Target
add_library(BansheeUtility SHARED ${BansheeUtility_SRC})

# Defines
target_compile_definitions(BansheeUtility PUBLIC -DBS_UTILITY_EXPORTS)

# Libraries
if(WIN32)
target_link_libraries(BansheeUtility 
	DbgHelp
	IPHLPAPI
	Rpcrt4
	)
else()
	# TODO_OTHER_PLATFORMS_GO_HERE
endif()