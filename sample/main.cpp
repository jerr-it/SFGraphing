#include <iostream>

#include "SFGraphing/SFPlot.h"
#include "SFGraphing/SFPieChart.h"

using namespace csrc;

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(1600, 800), "SF-Graphing", sf::Style::Default, settings);

    sf::Font font;
    font.loadFromFile("JetBrainsMono-Regular.ttf");

    /*
     * Plot
     */
    std::vector<float> xAxis = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<float> yAxis = {1, 2, 3, 4, 5, 6, 5, 6, 7, 8};

    PlotDataSet set1(xAxis, yAxis, sf::Color::Green, "Green Data", PlottingType::LINE);

    std::vector<float> xAxis2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<float> yAxis2 = {1, 1, 1, 2, 4, 6, 6, 8, 9, 10};

    PlotDataSet set2(xAxis2, yAxis2, sf::Color::Cyan, "Cyan Data", PlottingType::BARS);


    /*
     * Pie Chart
     */
    std::vector<float> values = {100, 230, 150, 100};
    std::vector<sf::Color> colors = {sf::Color::Blue, sf::Color::Red, sf::Color::Magenta, sf::Color::Cyan};
    std::vector<std::string> labels = {"A", "B", "C", "D"};
    PieChartDataSet pSet(values, labels, Representation::RELATIVE, colors);

    while (window.isOpen())
    {
        SFPlot plot(sf::Vector2f(800, 0), sf::Vector2f(800, 800), 60, font, "X Axis", "Y Axis");
        plot.AddDataSet(set1);
        plot.AddDataSet(set2);
        //x-minimum, x-maximum, y-minimum, y-maximum, x-step-size, y-step-size, Color of axes
        plot.SetupAxes(0, 10, 0, 10, 1, 1, sf::Color::White);
        plot.GenerateVertices();

        SFPieChart pChart(pSet, sf::Vector2f(250, 400), 200, font);
        pChart.GenerateVertices();

        sf::Event event;
        if (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear(sf::Color(30, 30, 30));

        /*
         * Update Plot in Real-Time
         */
        plot.ClearVertices();

        set1.SetDataValue(0, set1.GetDataValue(0) + sf::Vector2f(0, 0.001));

        //Calling without parameters makes the Plot auto-deduce the size of the plot
        plot.SetupAxes();
        plot.GenerateVertices();

        window.draw(plot);
        /*
         * ----------------------------------
         * Update Pie Chart in Real-Time
         */
        pChart.ClearVertices();

        pSet.SetValue(0, pSet.GetValue(0) + 0.003);

        pChart.GenerateVertices();
        window.draw(pChart);
        /*
         * ----------------------------------
         */

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            sf::Vector2u wSize = window.getSize();
            sf::Texture texture;
            texture.create(wSize.x, wSize.y);
            texture.update(window);
            sf::Image screenshot = texture.copyToImage();
            screenshot.saveToFile("screenshot.png");
        }

        window.display();
    }

    return 0;
}
