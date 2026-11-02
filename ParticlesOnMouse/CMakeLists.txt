add_executable(ParticlesOnMouse main.cpp
        game.cpp
        game.h
        particle_manager.cpp
        particle_manager.h
        particle.h
)

target_link_libraries(ParticlesOnMouse PUBLIC SFML::Graphics)