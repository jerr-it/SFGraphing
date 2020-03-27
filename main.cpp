#include <iostream>
#include "SFPlot.h"

using namespace csrc;

int main() {
        std::cout << "Hello, World!" << std::endl;

        sf::Font font;
        font.loadFromFile("Roboto-Regular.ttf");

        std::vector<double> xax = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

        std::vector<double> data1 = {0, 50, 25, 17.5, 9, 4, 2, 1, 1, 1, 1};
        DataSet set1(data1, sf::Color::Red);

        std::vector<double> data2 = {34, 56, 12, 46, 77, 41, 4, 6, 54, 10, 11};
        DataSet set2(data2, sf::Color::Green);

        SFPlot plotter(xax, "X Axo", "Y Axo", 50, &font);
        plotter.plot(set1);
        plotter.plot(set2);

        sf::ContextSettings settings;
        settings.antialiasingLevel = 4;

        sf::RenderWindow window(sf::VideoMode(800, 600), "Plot Test",sf::Style::Default, settings);

        plotter.setup(&window, PlotType::Line);

        while(window.isOpen()) {
                sf::Event event;
                if(window.pollEvent(event)) {
                        if(event.type == sf::Event::Closed) {
                                window.close();
                        }
                }
                window.clear();
                plotter.RenderTo(&window);
                window.display();
        }

        return 0;
}
