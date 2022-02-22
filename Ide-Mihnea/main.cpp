#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <map>
#include <string>
#include <random>
#include <chrono>
#include <functional>
#include <fstream>
#include "IDE.h"

using namespace std;



int main() {
  sf::Vector2i resolution(900, 900);
  sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y), "Vim");
  sf::View camera;
  camera.setSize(sf::Vector2f(1, 1) * 1.0f);
  camera.setCenter(camera.getSize() / 2.0f);
  window.setView(camera);

  IDE ide(window, resolution);

  sf::Clock frameClock;
  
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      else {
        ide.handleEvent(event);
      }
    }

    ide.update();

    float dt = frameClock.restart().asSeconds();

    window.clear();
    window.draw(ide);

    window.display();

  }

  return 0;
}