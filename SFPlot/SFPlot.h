//
// Created by jerrit on 23.03.20.
//

#ifndef SFPLOT_SFPLOT_H
#define SFPLOT_SFPLOT_H

#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <iostream>
#include "DataSet.h"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

namespace csrc {

    enum PlotType{
        Points,
        Line,
        Bars,
        Undefined
    };

    class SFPlot {
    private:
        std::vector<DataSet> DataSets;
        std::vector<double> xAxis;

        std::string xLabel;
        std::string yLabel;

        double margin;
        sf::Font *font;

        double xMax;
        double xMin;
        double yMax;
        double yMin;

        double xAxisLen;
        double yAxisLen;

        int xLow;
        int xHigh;
        int xStepSize;

        int yLow;
        int yHigh;
        int yStepSize;

        sf::Vector2u windowDim;
        bool windowDimOverriden;

        sf::VertexArray xAxisArray;
        sf::VertexArray yAxisArray;

        sf::Text xLabelText;
        sf::Text yLabelText;

        sf::VertexArray xnumArray;
        sf::VertexArray ynumArray;

        std::vector<sf::Text> xnumLabelArray;
        std::vector<sf::Text> ynumLabelArray;

        std::vector<sf::VertexArray> datasetsPlotPoints;

        sf::Vector2f CoordToWindowLocation(double x, double y, sf::RenderWindow *window);

    public:
        SFPlot(std::vector<double> x, std::string xl, std::string yl, double margin,
               sf::Font *f);

        void setup(sf::RenderWindow *window, PlotType type);

        double distSq(sf::Vector2f a, sf::Vector2f b);

        void setxAxis(std::vector<double> axis);

        void setFont(sf::Font *font);

        void setMargin(double margin);

        void clearDatasets();

        void overrideWindowSize(int x, int y);

        void plot(DataSet set);

        void setLabels(std::string x, std::string y);

        std::string ToString(double d, int precision);

        void RenderTo(sf::RenderWindow* window);
    };
}

#endif //SFPLOT_SFPLOT_H
