#ifndef SFGRAPHING_SFPLOT_H
#define SFGRAPHING_SFPLOT_H

#include "PlotDataSet.h"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <sstream>

namespace csrc
{
    class SFPlot : public sf::Drawable
    {
    private:
        sf::Vector2f _origin;
        sf::Vector2f _dimension;

        float _margin;

        std::vector<PlotDataSet*> _plotDataSets;

        sf::Font* _font;

        sf::Color _axesColor;
        sf::Vector2f _xCoordBounds;
        sf::Vector2f _yCoordBounds;
        sf::Vector2f _CoordSteps;

        /*
         * SFML Drawables
         */
        //Axis lines
        sf::VertexArray _axesVertexArray;
        sf::VertexArray _axesIndicatorVertexArray;

        //data lines, all text elements
        std::vector<sf::VertexArray> _dataSetsVertexArrays;
        std::vector<sf::Text> _textElementArray;

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        sf::Vector2f CoordToWindowPosition(sf::Vector2f);

    public:
        std::string ToString(double d, int precision);

        SFPlot(sf::Vector2f position, sf::Vector2f dimension, float margin, sf::Font* font);

        void SetupAxes();

        void SetupAxes(float xmin, float xmax, float ymin, float ymax, float xstep, float ystep, sf::Color axesColor);

        void AddDataSet(PlotDataSet* set);

        void GenerateVertices();

        void ClearVertices();
    };
}

#endif //SFGRAPHING_SFPLOT_H
