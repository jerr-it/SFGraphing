#include <iostream>
#include "SFPlot/SFPlot.h"

using namespace csrc;

int main() {
        sf::Font font;
        //https://www.1001fonts.com/rm-typerighter-medium-font.html
        font.loadFromFile("tmedium.ttf");

        std::vector<double> xax = {10, 20, 30, 40, 50, 60, 70, 80, 90};

        std::vector<double> data1 = {50, 25, 17.5, 9, 4, 2, 1, 1, 1};
        DataSet set1(data1, sf::Color(156, 0, 0), "Red Graph");

        std::vector<double> data2 = {56, 12, 46, 77, 41, 4, 6, 54, 10};
        DataSet set2(data2, sf::Color(0, 156, 0), "Green Graph");

        std::vector<double> data3 = {56, 12, 13, 55, 26, 4, 6, 54, 43};
        DataSet set3(data3, sf::Color(0, 0, 150), "Blue Graph");

        std::vector<double> data4 = {50, 25, 12, 10, 9, 8, 6, 54, 43};
        DataSet set4(data4, sf::Color(150, 150, 0), "Some Graph");

        SFPlot plotter(xax, "X Label", "Y Label", 50, &font);
        plotter.plot(set1);
        plotter.plot(set2);
        plotter.plot(set3);
        plotter.plot(set4);

        sf::ContextSettings settings;
        settings.antialiasingLevel = 4;

        sf::RenderWindow window(sf::VideoMode(800, 600), "Plot Test",sf::Style::Default, settings);

        plotter.setup(&window, PlotType::Points);

        sf::Vector2 windowDim = window.getSize();
        sf::Texture texture;
        texture.create(windowDim.x, windowDim.y);
        sf::Image screenshot;

        while(window.isOpen()) {
                sf::Event event;
                if(window.pollEvent(event)) {
                        if(event.type == sf::Event::Closed) {
                                window.close();
                        }
                }

                if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                {
                        texture.update(window);
                        screenshot = texture.copyToImage();
                        screenshot.saveToFile("screenshot.png");
                }

                window.clear(sf::Color(50, 50, 50));
                plotter.RenderTo(&window);
                window.display();
        }

        return 0;
}
