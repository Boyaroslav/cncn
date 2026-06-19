cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project("lcnovel")

set(PROJECT_ROOT ${CMAKE_SOURCE_DIR}/../../..)

# ============================================
# Пути
# ============================================
set(JNI_LIBS_DIR ${CMAKE_SOURCE_DIR}/../src/main/jniLibs/${ANDROID_ABI})
set(SDL2_INCLUDE_DIR ${PROJECT_ROOT}/build/_deps/sdl2-src/include)
set(SDL2_IMAGE_INCLUDE_DIR ${PROJECT_ROOT}/build/_deps/sdl2_image-src/include)
set(SDL2_TTF_INCLUDE_DIR ${PROJECT_ROOT}/build/_deps/sdl2_ttf-src/)
set(SDL2_MIXER_INCLUDE_DIR ${PROJECT_ROOT}/build/_deps/sdl2_mixer-src/include)
set(LUA_ROOT ${CMAKE_SOURCE_DIR}/../../../lua)

message(STATUS "SDL2_INCLUDE_DIR: ${SDL2_INCLUDE_DIR}")

# ============================================
# Собираем Lua из исходников (СТАТИЧЕСКИ)
# ============================================
if(EXISTS ${LUA_ROOT}/lapi.c)
    message(STATUS "✅ Building Lua from sources: ${LUA_ROOT}")
    
    add_library(lua STATIC
        ${LUA_ROOT}/lapi.c
        ${LUA_ROOT}/lauxlib.c
        ${LUA_ROOT}/lbaselib.c
        ${LUA_ROOT}/lcode.c
        ${LUA_ROOT}/ldebug.c
        ${LUA_ROOT}/ldo.c
        ${LUA_ROOT}/ldump.c
        ${LUA_ROOT}/lfunc.c
        ${LUA_ROOT}/lgc.c
        ${LUA_ROOT}/linit.c
        ${LUA_ROOT}/liolib.c
        ${LUA_ROOT}/llex.c
        ${LUA_ROOT}/lmathlib.c
        ${LUA_ROOT}/lmem.c
        ${LUA_ROOT}/lcorolib.c      # <-- ADD: fixes luaopen_coroutine
        ${LUA_ROOT}/lctype.c        # <-- ADD: fixes luai_ctype_
        ${LUA_ROOT}/ldblib.c  
        ${LUA_ROOT}/loadlib.c
        ${LUA_ROOT}/lobject.c
        ${LUA_ROOT}/lopcodes.c
        ${LUA_ROOT}/loslib.c
        ${LUA_ROOT}/lparser.c
        ${LUA_ROOT}/lstate.c
        ${LUA_ROOT}/lstring.c
        ${LUA_ROOT}/lstrlib.c
        ${LUA_ROOT}/ltable.c
        ${LUA_ROOT}/ltablib.c
        ${LUA_ROOT}/ltm.c
        ${LUA_ROOT}/lundump.c
        ${LUA_ROOT}/lutf8lib.c
        ${LUA_ROOT}/lvm.c
        ${LUA_ROOT}/lzio.c
    )
    
    target_include_directories(lua PUBLIC ${LUA_ROOT})
    target_compile_definitions(lua PRIVATE
        LUA_USE_LINUX
        LUA_COMPAT_5_2
        LUA_COMPAT_5_3
        LUA_USE_DLOPEN=0
    )
        target_compile_options(lua PRIVATE 
        -w
        -fno-stack-protector
    )
    set(LUA_LIBRARY lua)
    
    message(STATUS "✅ Lua will be built as STATIC library")
else()
    message(WARNING "❌ Lua sources not found at ${LUA_ROOT}/src! Trying prebuilt library...")
    
    # Если исходников нет, ищем готовую библиотеку
    find_library(LUA_LIBRARY
        NAMES lua lua54 lua53
        PATHS ${JNI_LIBS_DIR}
        NO_DEFAULT_PATH
    )
    
    if(NOT LUA_LIBRARY)
        message(FATAL_ERROR "❌ Lua not found! Please check path: ${LUA_ROOT}/src")
    endif()
endif()

# ============================================
# Библиотеки из jniLibs
# ============================================
set(SDL2_LIBRARY ${JNI_LIBS_DIR}/libSDL2.so)
set(SDL2_TTF_LIBRARY ${JNI_LIBS_DIR}/libSDL2_ttf.so)
set(SDL2_MIXER_LIBRARY ${JNI_LIBS_DIR}/libSDL2_mixer.so)
set(SDL2_IMAGE_LIBRARY ${JNI_LIBS_DIR}/libSDL2_image.so)

# ============================================
# Ваша библиотека
# ============================================
add_library(lcnovel SHARED
    ${CMAKE_SOURCE_DIR}../../../../main.cpp
)

# ============================================
# Линковка
# ============================================
target_link_libraries(lcnovel
    ${SDL2_LIBRARY}
    ${SDL2_TTF_LIBRARY}
    ${SDL2_MIXER_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
    ${LUA_LIBRARY}              # Статическая Lua из исходников
    android                     # Android API
    OpenSLES
    log
    z                           # Сжатие (нужно Lua и PNG)
    m                           # Математика


)

# ============================================
# Заголовки (include)
# ============================================
target_include_directories(lcnovel PRIVATE
    ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIR} 
    ${SDL2_TTF_INCLUDE_DIR}
    ${SDL2_MIXER_INCLUDE_DIR}
    ${LUA_ROOT}           # Заголовки Lua (lua.h, luaconf.h)
    ${LUA_ROOT}        # Альтернативный путь для заголовков
    src/main/cpp
    ${PROJECT_ROOT}              # Для main.cpp и других хедеров
)

target_compile_options(lcnovel PRIVATE
    -Wall
    -Wextra
    -fPIC
)

# ============================================
# Для отладки
# ============================================
message(STATUS "========================================")
message(STATUS "ANDROID_ABI: ${ANDROID_ABI}")
message(STATUS "SDL2: ${SDL2_LIBRARY}")
message(STATUS "SDL2_ttf: ${SDL2_TTF_LIBRARY}")
message(STATUS "SDL2_mixer: ${SDL2_MIXER_LIBRARY}")
message(STATUS "SDL2_image: ${SDL2_IMAGE_LIBRARY}")
message(STATUS "Lua: ${LUA_LIBRARY}")
message(STATUS "Lua root: ${LUA_ROOT}")
message(STATUS "========================================")