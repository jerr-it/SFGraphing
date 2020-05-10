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

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    public:
        SFPieChart(PieChartDataSet* dataset, sf::Vector2f position, float radius, sf::Font* font);

        std::string ToString(double d, int precision);

        void GenerateVertices();

        void ClearVertices();
    };
}

#endif //GRAPHING_SFPIECHART_H
