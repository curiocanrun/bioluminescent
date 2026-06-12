#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <cstdlib>

struct Particle {
    float x, y, baseY;
    float phase;
    float pulseSpeed;
    float size;
};

int main() {
    const unsigned int WIDTH = 1000;
    const unsigned int HEIGHT = 800;
    
    // SFML 3.0 fix: VideoMode now takes an sf::Vector2u
    sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "Bioluminescent Waves");
    window.setFramerateLimit(60);

    int numParticles = 8000;
    // SFML 3.0 fix: Enumerators are now strongly typed (PrimitiveType::Points)
    sf::VertexArray va(sf::PrimitiveType::Points, numParticles);
    std::vector<Particle> particles(numParticles);

    // Initialize particles clustered around a coastline curve
    for (int i = 0; i < numParticles; ++i) {
        particles[i].x = static_cast<float>(rand() % WIDTH);
        particles[i].baseY = static_cast<float>((HEIGHT / 2) + (rand() % (HEIGHT / 2))); 
        particles[i].phase = static_cast<float>(rand()) / RAND_MAX * 6.28f;
        particles[i].pulseSpeed = 0.02f + (static_cast<float>(rand()) / RAND_MAX * 0.05f);
    }

    sf::Clock clock;

    while (window.isOpen()) {
        // SFML 3.0 fix: pollEvent now returns a std::optional<sf::Event>
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            // Check if the event is a Close event
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        float time = clock.getElapsedTime().asSeconds();

        for (int i = 0; i < numParticles; ++i) {
            // 1. Move Particle
            float wave = std::sin(particles[i].x * 0.005f + time * 1.5f) * 30.0f;
            particles[i].y = particles[i].baseY + wave;
            particles[i].x += std::sin(time + particles[i].phase) * 0.2f;

            // 2. Compute Bioluminescent Glow (Cyan/Blue)
            float alphaSine = std::sin(time * particles[i].pulseSpeed * 50.0f + particles[i].phase);
            int brightness = static_cast<int>((alphaSine + 1.0f) * 0.5f * 200.0f) + 55;

            // Update vertex array data sent directly to GPU
            va[i].position = sf::Vector2f(particles[i].x, particles[i].y);
            va[i].color = sf::Color(0, static_cast<std::uint8_t>(brightness * 0.7f), static_cast<std::uint8_t>(brightness), static_cast<std::uint8_t>(brightness)); 
        }

        window.clear(sf::Color(2, 4, 12)); // Near black ocean blue
        window.draw(va);
        window.display();
    }
    return 0;
}
