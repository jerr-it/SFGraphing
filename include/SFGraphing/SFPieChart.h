/**
 * @file Piechart file
 *
 * @author Jerrit Gläsker
 * @date 22.05.202
 *
 * @license MIT-License
 */

#ifndef GRAPHING_SFPIECHART_H
#define GRAPHING_SFPIECHART_H

#include "PieChartDataSet.h"
#include <cmath>
#include <iomanip>
#include <sstream>

namespace csrc
{
class SFPieChart : public sf::Drawable
{
private:
    sf::Font* _font;
    PieChartDataSet* _dataset;

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
    SFPieChart(PieChartDataSet* dataset, sf::Vector2f position, float radius, sf::Font* font);

    /**
     * Creates a string representation of a double with 'precision' number of digits after comma
     * @param  d         double to convert
     * @param  precision number of digits after comma
     * @return           String representation
     */
    std::string ToString(double d, int precision);

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

#endif //GRAPHING_SFPIECHART_H
