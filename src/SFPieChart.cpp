#include "SFGraphing/SFPieChart.h"

using namespace csrc;

void SFPieChart::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (size_t i = 0; i < _pieSegments.size(); i++)
    {
        target.draw(_pieSegments[i], states);
    }

    for (size_t i = 0; i < _textElements.size(); i++)
    {
        target.draw(_textElements[i], states);
    }
}

SFPieChart::SFPieChart(const PieChartDataSet& dataset, const sf::Vector2f& position, const float& radius, const sf::Font& font)
    : _font(font), _dataset(dataset), _position(position), _radius(radius)
{
}

std::string SFPieChart::ToString(const double& d, const size_t& precision)
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(precision) << d;
    std::string s = stream.str();
    return s;
}

void SFPieChart::GenerateVertices()
{
    this->ClearVertices();
    float totalSegmentsValue = 0.f;
    for (size_t i = 0; i < _dataset.GetLength(); i++)
    {
        totalSegmentsValue += _dataset.GetValue(i);
    }

    float segmentBaseAngle = static_cast<float>(-M_PI / 2);
    float angleStep = static_cast<float>(2 * M_PI / 360);

    float charSize = _radius * 0.15f;
    sf::Vector2f legendBasePosition = sf::Vector2f(_position.x + _radius + 10, _position.y);
    legendBasePosition.y -= (_dataset.GetLength() / 2) * charSize;

    for (size_t i = 0; i < _dataset.GetLength(); i++)
    {
        /*
         * Pie Segment
         */
        sf::VertexArray segment;
        segment.setPrimitiveType(sf::PrimitiveType::TriangleFan);

        //Middle point
        segment.append(sf::Vertex(_position, _dataset.GetColor(i)));

        float segmentAngle = (_dataset.GetValue(i) / totalSegmentsValue) * static_cast<float>(2 * M_PI);

        for (float theta = segmentBaseAngle; theta < segmentBaseAngle + segmentAngle + angleStep; theta += angleStep)
        {
            float xPos = _position.x + _radius * cos(theta);
            float yPos = _position.y + _radius * sin(theta);

            segment.append(sf::Vertex(sf::Vector2f(xPos, yPos), _dataset.GetColor(i)));
        }

        _pieSegments.push_back(segment);
        segmentBaseAngle += segmentAngle;

        /*
         * Pie Legend
         */
        sf::Text text;
        text.setFont(_font);
        std::string label;
        if (_dataset.GetRepresentation() == Representation::ABSOLUTE)
        {
            label = ToString(_dataset.GetValue(i), 2) + " - " + _dataset.GetLabel(i);
        }
        else
        {
            label = ToString(_dataset.GetValue(i) / totalSegmentsValue, 3) + " - " + _dataset.GetLabel(i);
        }
        text.setString(label);

        text.setFillColor(_dataset.GetColor(i));
        text.setPosition(legendBasePosition);
        text.setCharacterSize(static_cast<unsigned int>(charSize));

        sf::FloatRect fr = text.getLocalBounds();
        text.move(0, i * fr.height * 1.2f);

        _textElements.push_back(text);
    }
}

void SFPieChart::ClearVertices()
{
    _pieSegments.clear();
    _textElements.clear();
}
