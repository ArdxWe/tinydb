include(FetchContent) FetchContent_Declare(
    googletest
#Specify the commit you depend on and update it regularly.
        URL https
    :  // github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
    )
#For Windows : Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        FetchContent_MakeAvailable(googletest)

#Now simply link against gtest or gtest_main as needed.Eg
            add_executable(put put_test.cpp)
                target_link_libraries(put gtest_main tinydb)
                    add_test(NAME put_test COMMAND put)

                        include_directories(../ src)
