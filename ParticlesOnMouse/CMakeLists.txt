add_executable(ParticlesOnMouse main.cpp
        game.cpp
        game.h
        particle.cpp
        particle.h
)

target_link_libraries(ParticlesOnMouse PUBLIC SFML::Graphics)