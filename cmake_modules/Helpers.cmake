function(congifure_prebuilt_lib test_locations url filename dest)
    message(STATUS "Setting up a prebuilt library ...")
    foreach(ONE_PATH ${test_locations})
        if( NOT EXISTS ${ONE_PATH} )
            set(DO_DL 1)
            break()
        endif()
    endforeach()

    if(DEFINED DO_DL)
        file(GLOB file_list_pbl
            LIST_DIRECTORIES true 
            ${dest}/*
        )

        message(STATUS "Cleaning destination ${dest} except CMakeLists")

        list(REMOVE_ITEM file_list_pbl "${dest}/CMakeLists.txt")
        list(LENGTH file_list_pbl lib_dir_list_size)

        if(NOT lib_dir_list_size EQUAL 0)
            foreach(TO_REMOVE ${file_list_pbl})
                file(REMOVE_RECURSE "${TO_REMOVE}")
            endforeach()
        endif()
    
        message(STATUS "Downloading prebuilt libraries from ${url} ...")

        file(DOWNLOAD ${url} ${dest}/${filename} STATUS DL_RESULT)
        list(GET DL_RESULT 0 DL_RESULT_CODE)
    
        if(NOT DL_RESULT_CODE EQUAL 0)
            message(FATAL_ERROR "Failed downloading! Error: ${DL_RESULT}.")
        endif()
    
        message(STATUS "Extracting file ${dest}/${filename} ...")

        file(ARCHIVE_EXTRACT INPUT "${dest}/${filename}"
            DESTINATION "${dest}"
        )

        message(STATUS "Removing file ${dest}/${filename} ...")
        file(REMOVE_RECURSE "${dest}/${filename}")
    else()
        message(STATUS "Prebuilt libraries already downloaded.")
        file(REMOVE_RECURSE "${dest}/${filename}")
    endif()
endfunction()