#pragma once
/**
 * @file Plot file
 *
 * @author Jerrit Gläsker
 * @date 22.05.202
 *
 * @license MIT-License
 */
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

    std::vector<PlotDataSet> _plotDataSets;

    sf::Font _font;

    std::string _xAxisLabel;
    std::string _yAxisLabel;

    sf::Color _axesColor;
    sf::Vector2f _xCoordBounds;
    sf::Vector2f _yCoordBounds;
    sf::Vector2f _CoordSteps;

    sf::VertexArray _axesVertexArray;
    sf::VertexArray _axesIndicatorVertexArray;

    //data lines, all text elements
    std::vector<sf::VertexArray> _dataSetsVertexArrays;
    std::vector<sf::Text> _textElementArray;

    /**
     * SFML Function override
     * @param target sf::RenderTarget
     * @param states sf::RenderStates
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    /**
     * Function for converting between plot coordinates and window coordinates
     * @param  loc The position to convert
     * @return              Converted Position
     */
    sf::Vector2f CoordToWindowPosition(const sf::Vector2f& loc);

public:

    /**
     * Creates a string representation of a double with 'precision' number of digits after comma
     * @param  d         double to convert
     * @param  precision number of digits after comma
     * @return           String representation
     */
    std::string ToString(const double& d, const size_t& precision = 2);

    /**
     * Constructor using essential values
     * @param position  top left position of plot
     * @param dimension width and height of plot
     * @param margin    distance of axes from the borders of the plot
     * @param font      sf::Font reference
     * @param xLabel    label of x-axis
     * @param yLabel    label of y-axis
     */
    SFPlot(const sf::Vector2f& position, const sf::Vector2f& dimension, const float& margin, const sf::Font& font, const std::string& xLabel,
           const std::string& yLabel);

    /**
     * Function for automatically deducing axes labeling
     */
    void SetupAxes();

    /**
     * Function for setting axes labeling manually
     * @param xmin      lower x bound
     * @param xmax      higher x bound
     * @param ymin      lower y bound
     * @param ymax      higher y bound
     * @param xstep     x step size
     * @param ystep     y step size
     * @param axesColor color of axes
     */
    void SetupAxes(const float& xmin, const float& xmax, const float& ymin, const float& ymax, const float& xstep, const float& ystep, const sf::Color& axesColor);

    /**
     * Function for adding a dataset to the plot
     * @param set the set to be added
     */
    void AddDataSet(const PlotDataSet& data_set);

    /**
     * Generate SFML VertexArrays from Datasets
     */
    void GenerateVertices();

    /**
     * Clear SFML VertexArrays
     */
    void ClearVertices();
};
}
