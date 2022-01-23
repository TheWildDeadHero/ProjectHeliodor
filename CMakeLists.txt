cmake_minimum_required(VERSION 3.10)

# Set the project name and version.
#
# Change this for new projects.
project(PokemonAGPC VERSION 0.0.1)

# Specify language standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

target_include_directories(PokemonAGPC PUBLIC
                            ${CMAKE_SOURCE_DIR}/CoreEngine/Display/Inc
                            ${CMAKE_SOURCE_DIR}/CoreEngine/Input/Inc
                            ${CMAKE_SOURCE_DIR}/CoreEngine/Logic/Inc
                            ${CMAKE_SOURCE_DIR}/CoreEngine/ScriptingEngine/Inc
                            ${CMAKE_SOURCE_DIR}/CoreEngine/Sound/Inc
                            ${CMAKE_SOURCE_DIR}/Game/Inc
)

target_sources(PokemonAGPC PUBLIC
                ${CMAKE_SOURCE_DIR}/CoreEngine/Display/Src
                ${CMAKE_SOURCE_DIR}/CoreEngine/Input/Src
                ${CMAKE_SOURCE_DIR}/CoreEngine/Logic/Src
                ${CMAKE_SOURCE_DIR}/CoreEngine/ScriptingEngine/Src
                ${CMAKE_SOURCE_DIR}/CoreEngine/Sound/Src
                ${CMAKE_SOURCE_DIR}/Game/Src
)