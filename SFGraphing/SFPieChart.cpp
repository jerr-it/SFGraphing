#include "SFPieChart.h"

using namespace csrc;

void SFPieChart::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (int i = 0; i < _pieSegments.size(); i++)
    {
        target.draw(_pieSegments[i], states);
    }

    for (int i = 0; i < _textElements.size(); i++)
    {
        target.draw(_textElements[i], states);
    }
}

SFPieChart::SFPieChart(PieChartDataSet* dataset, sf::Vector2f position, float radius, sf::Font* font)
{
    _font = font;
    _dataset = dataset;
    _position = position;
    _radius = radius;
}

std::string SFPieChart::ToString(double d, int precision)
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(precision) << d;
    std::string s = stream.str();
    return s;
}

void SFPieChart::GenerateVertices()
{
    float totalSegmentsValue = 0;
    for (int i = 0; i < _dataset->GetLength(); i++)
    {
        totalSegmentsValue += _dataset->GetValue(i);
    }

    float segmentBaseAngle = -M_PI / 2;
    float angleStep = 2 * M_PI / 360;

    float charSize = _radius * 0.15;
    sf::Vector2f legendBasePosition = sf::Vector2f(_position.x + _radius + 10, _position.y);
    legendBasePosition.y -= (_dataset->GetLength() / 2) * charSize;

    for (int i = 0; i < _dataset->GetLength(); i++)
    {
        /*
         * Pie Segment
         */
        sf::VertexArray segment;
        segment.setPrimitiveType(sf::PrimitiveType::TriangleFan);

        //Middle point
        segment.append(sf::Vertex(_position, _dataset->GetColor(i)));

        float segmentAngle = (_dataset->GetValue(i) / totalSegmentsValue) * 2 * M_PI;

        for (float theta = segmentBaseAngle; theta < segmentBaseAngle + segmentAngle + angleStep; theta += angleStep)
        {
            float xPos = _position.x + _radius * cos(theta);
            float yPos = _position.y + _radius * sin(theta);

            segment.append(sf::Vertex(sf::Vector2f(xPos, yPos), _dataset->GetColor(i)));
        }

        _pieSegments.push_back(segment);
        segmentBaseAngle += segmentAngle;

        /*
         * Pie Legend
         */
        sf::Text text;
        text.setFont(*_font);
        std::string label;
        if (_dataset->GetRepresentation() == Representation::ABSOLUTE)
        {
            label = ToString(_dataset->GetValue(i), 2) + " - " + _dataset->GetLabel(i);
        } else
        {
            label = ToString(_dataset->GetValue(i) / totalSegmentsValue, 3) + " - " + _dataset->GetLabel(i);
        }
        text.setString(label);

        text.setFillColor(_dataset->GetColor(i));
        text.setPosition(legendBasePosition);
        text.setCharacterSize(charSize);

        sf::FloatRect fr = text.getLocalBounds();
        text.move(0, i * fr.height * 1.2);

        _textElements.push_back(text);
    }
}

void SFPieChart::ClearVertices()
{
    _pieSegments.clear();
    _textElements.clear();
}
