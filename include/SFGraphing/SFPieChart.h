#pragma once
/**
 * @file Piechart file
 *
 * @author Jerrit Gläsker
 * @date 22.05.202
 *
 * @license MIT-License
 */
#include "PieChartDataSet.h"
#include <cmath>
#include <iomanip>
#include <sstream>

namespace csrc
{
class SFPieChart : public sf::Drawable
{
private:
    sf::Font _font;
    PieChartDataSet _dataset;

    sf::Vector2f _position;
    float _radius;

    std::vector<sf::VertexArray> _pieSegments;
    std::vector<sf::Text> _textElements;

    /**
     * SFML Function override
     * @param target sf::RenderTarget
     * @param states sf::RenderStates
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:

    /**
     * Standard constructor
     * @param dataset  The pie chart data to be used
     * @param position position of the pies center
     * @param radius   radius of piechart
     * @param font     sf::Font reference
     */
    SFPieChart(const PieChartDataSet& dataset, const sf::Vector2f& position, const float& radius, const sf::Font& font);

    /**
     * Creates a string representation of a double with 'precision' number of digits after comma
     * @param  d         double to convert
     * @param  precision number of digits after comma
     * @return           String representation
     */
    std::string ToString(const double& d, const size_t& precision = 2);

    /**
     * Function for generating SFML VertexArrays
     */
    void GenerateVertices();

    /**
     * Function for clearing SFML VertexArrays
     */
    void ClearVertices();
};
}
