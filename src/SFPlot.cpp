#include "SFGraphing/SFPlot.h"

using namespace csrc;

void SFPlot::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(_axesVertexArray, states);
    target.draw(_axesIndicatorVertexArray, states);
    for (size_t i = 0; i < _dataSetsVertexArrays.size(); i++)
    {
        target.draw(_dataSetsVertexArrays[i], states);
    }
    for (size_t i = 0; i < _textElementArray.size(); i++)
    {
        target.draw(_textElementArray[i], states);
    }
}

sf::Vector2f SFPlot::CoordToWindowPosition(const sf::Vector2f& coords)
{
    sf::Vector2f windowPosition;

    float xAxisLength = _dimension.x - 2.f * _margin;
    float xAxisMax = _xCoordBounds.y;

    float yAxisLength = _dimension.y - 2.f * _margin;
    float yAxisMax = _yCoordBounds.y;

    windowPosition.x = _origin.x + (_margin + xAxisLength * (coords.x / xAxisMax));
    windowPosition.y = _origin.y + (_dimension.y - _margin - yAxisLength * (coords.y / yAxisMax));

    return windowPosition;
}

std::string SFPlot::ToString(const double& d, const size_t& precision)
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(precision) << d;
    std::string s = stream.str();
    return s;
}

SFPlot::SFPlot(const sf::Vector2f& position, const sf::Vector2f& dimension, const float& margin, const sf::Font& font, const std::string& xLabel,
               const std::string& yLabel)
    : _origin(position), _dimension(dimension), _margin(margin), _font(font), _xAxisLabel(xLabel), _yAxisLabel(yLabel)
{
}

void SFPlot::SetupAxes()
{
    //Auto deducing stepsize and boundaries
    float xmin = INFINITY;
    float ymin = INFINITY;

    for (const auto& dataset : _plotDataSets)
    {
        std::vector<float> setXAxis = dataset.GetXValues();
        std::vector<float> setYAxis = dataset.GetYValues();

        float setMinX = *std::min_element(setXAxis.begin(), setXAxis.end());
        float setMinY = *std::min_element(setYAxis.begin(), setYAxis.end());

        if (setMinX < xmin)
        {
            xmin = setMinX;
        }
        if (setMinY < ymin)
        {
            ymin = setMinY;
        }
    }

    float xmax = -INFINITY;
    float ymax = -INFINITY;

    for (const auto& dataset : _plotDataSets)
    {
        std::vector<float> setXAxis = dataset.GetXValues();
        std::vector<float> setYAxis = dataset.GetYValues();

        float setMaxX = *std::max_element(setXAxis.begin(), setXAxis.end());
        float setMaxY = *std::max_element(setYAxis.begin(), setYAxis.end());

        if (setMaxX > xmax)
        {
            xmax = setMaxX;
        }
        if (setMaxY > ymax)
        {
            ymax = setMaxY;
        }
    }

    _xCoordBounds.x = xmin;
    _xCoordBounds.y = xmax;

    _yCoordBounds.x = ymin;
    _yCoordBounds.y = ymax;

    _CoordSteps.x = (xmax - xmin) / 10;
    _CoordSteps.y = (ymax - ymin) / 10;

    _axesColor = sf::Color::White;
}

void SFPlot::SetupAxes(const float& xmin, const float& xmax, const float& ymin, const float& ymax, const float& xstep, const float& ystep, const sf::Color& axesColor)
{
    _xCoordBounds.x = xmin;
    _xCoordBounds.y = xmax;

    _yCoordBounds.x = ymin;
    _yCoordBounds.y = ymax;

    _CoordSteps.x = xstep;
    _CoordSteps.y = ystep;

    _axesColor = axesColor;
}

void SFPlot::AddDataSet(const PlotDataSet& data_set)
{
    _plotDataSets.push_back(data_set);
}

void SFPlot::GenerateVertices()
{
    this->ClearVertices();
    const auto characterSize = static_cast<unsigned int>(_margin * 0.35);

    /*
     * Calculating axes themselves
     */
    _axesVertexArray.setPrimitiveType(sf::LineStrip);
    //Topleft
    _axesVertexArray.append(sf::Vertex(CoordToWindowPosition(sf::Vector2f(0, _yCoordBounds.y)), _axesColor));
    //Origin
    _axesVertexArray.append(sf::Vertex(CoordToWindowPosition(sf::Vector2f(0, 0)), _axesColor));
    //BottomRight
    _axesVertexArray.append(sf::Vertex(CoordToWindowPosition(sf::Vector2f(_xCoordBounds.y, 0)), _axesColor));

    /*
     * Axis Labels
     */
    sf::Text xaxislabel;
    xaxislabel.setFont(_font);
    xaxislabel.setCharacterSize(characterSize);
    xaxislabel.setFillColor(_axesColor);
    xaxislabel.setString(_xAxisLabel);

    xaxislabel.setPosition(CoordToWindowPosition(sf::Vector2f(_xCoordBounds.y, 0)) + sf::Vector2f(_margin * 0.3f, 0));

    xaxislabel.rotate(-90);

    _textElementArray.push_back(xaxislabel);

    //------
    sf::Text yaxislabel;
    yaxislabel.setFont(_font);
    yaxislabel.setCharacterSize(characterSize);
    yaxislabel.setFillColor(_axesColor);
    yaxislabel.setString(_yAxisLabel);

    yaxislabel.setPosition(_origin.x, _origin.y);

    _textElementArray.push_back(yaxislabel);

    /*
     * Calulating axes indicators and adding text
     */
    _axesIndicatorVertexArray.setPrimitiveType(sf::PrimitiveType::Lines);
    //x axis
    for (float x = _xCoordBounds.x; x <= _xCoordBounds.y; x += _CoordSteps.x)
    {
        //indicator
        sf::Vector2f windowPosition = CoordToWindowPosition(sf::Vector2f(x, 0));

        _axesIndicatorVertexArray.append(sf::Vertex(windowPosition, _axesColor));
        _axesIndicatorVertexArray.append(
            sf::Vertex(sf::Vector2f(windowPosition.x, windowPosition.y + (_margin * 0.25f)), _axesColor));

        //text
        sf::Text indicatorText;
        indicatorText.setCharacterSize(characterSize);
        indicatorText.setFont(_font);
        indicatorText.setString(ToString(x, 2));
        indicatorText.setFillColor(_axesColor);

        sf::FloatRect tDimension = indicatorText.getLocalBounds();
        indicatorText.setOrigin(tDimension.left + tDimension.width / 2, tDimension.top + tDimension.height / 2);

        indicatorText.setPosition(windowPosition.x, windowPosition.y + (_margin * 0.5f));

        _textElementArray.push_back(indicatorText);
    }

    //y axis
    for (float y = _yCoordBounds.x; y <= _yCoordBounds.y; y += _CoordSteps.y)
    {
        //indicator
        sf::Vector2f windowPosition = CoordToWindowPosition(sf::Vector2f(0, y));

        _axesIndicatorVertexArray.append(sf::Vertex(windowPosition, _axesColor));
        _axesIndicatorVertexArray.append(
            sf::Vertex(sf::Vector2f(windowPosition.x - (_margin * 0.25f), windowPosition.y), _axesColor));

        //text
        sf::Text indicatorText;
        indicatorText.setCharacterSize(characterSize);
        indicatorText.setFont(_font);
        indicatorText.setString(ToString(y, 2));
        indicatorText.setFillColor(_axesColor);

        indicatorText.setPosition(windowPosition.x - (_margin * 0.25f), windowPosition.y - 5);
        sf::FloatRect tDimension = indicatorText.getLocalBounds();
        indicatorText.move(-tDimension.width - 2, -tDimension.height / 2);

        _textElementArray.push_back(indicatorText);
    }

    /*
     * Calculate graphs
     */

    sf::Vector2f legendPos = sf::Vector2f(_origin + sf::Vector2f(_dimension.x - 5, 0));
    for (const auto& dataset : _plotDataSets)
    {
        //Generate legend
        sf::Text segmentLegend;
        segmentLegend.setPosition(legendPos);
        segmentLegend.setFont(_font);
        segmentLegend.setCharacterSize(static_cast<unsigned int>(_margin * 0.6));
        segmentLegend.setString(dataset.GetLabel());
        segmentLegend.setFillColor(dataset.GetColor());

        sf::FloatRect dim = segmentLegend.getLocalBounds();
        segmentLegend.move(-dim.width, 0);

        legendPos -= sf::Vector2f(dim.width + 5, 0);

        _textElementArray.push_back(segmentLegend);

        //Generate actual data lines
        sf::VertexArray graph;
        PlottingType type = dataset.GetPlottingType();

        sf::Color col = dataset.GetColor();

        if (type == PlottingType::POINTS)
        {
            graph.setPrimitiveType(sf::PrimitiveType::Quads);

            for (size_t i = 0; i < dataset.GetDataLength(); i++)
            {
                sf::Vector2f windowPosition = CoordToWindowPosition(dataset.GetDataValue(i));

                graph.append(sf::Vertex(sf::Vector2f(windowPosition.x - 2, windowPosition.y - 2), col));
                graph.append(sf::Vertex(sf::Vector2f(windowPosition.x + 2, windowPosition.y - 2), col));
                graph.append(sf::Vertex(sf::Vector2f(windowPosition.x + 2, windowPosition.y + 2), col));
                graph.append(sf::Vertex(sf::Vector2f(windowPosition.x - 2, windowPosition.y + 2), col));
            }
        }
        else if (type == PlottingType::LINE)
        {
            graph.setPrimitiveType(sf::PrimitiveType::LinesStrip);

            for (size_t i = 0; i < dataset.GetDataLength(); i++)
            {
                sf::Vector2f windowPosition = CoordToWindowPosition(dataset.GetDataValue(i));

                graph.append(sf::Vertex(windowPosition, col));
            }
        }
        else if (type == PlottingType::BARS)
        {
            graph.setPrimitiveType(sf::PrimitiveType::Quads);

            for (size_t i = 0; i < dataset.GetDataLength(); i++)
            {
                //Generate bars
                sf::Vector2f dataValue = dataset.GetDataValue(i);
                sf::Vector2f windowPosition = CoordToWindowPosition(dataValue);
                sf::Vector2f zeroWindowPosition = CoordToWindowPosition(sf::Vector2f(dataValue.x, 0));

                graph.append(sf::Vertex(sf::Vector2f(windowPosition.x - 2, windowPosition.y), col));
                graph.append(sf::Vertex(sf::Vector2f(windowPosition.x + 2, windowPosition.y), col));

                graph.append(sf::Vertex(sf::Vector2f(zeroWindowPosition.x + 2, zeroWindowPosition.y), col));
                graph.append(sf::Vertex(sf::Vector2f(zeroWindowPosition.x - 2, zeroWindowPosition.y), col));
            }
        }
        else
        {
            //Should never happen
            exit(1);
        }

        _dataSetsVertexArrays.push_back(graph);
    }
}

void SFPlot::ClearVertices()
{
    _axesVertexArray.clear();
    _axesIndicatorVertexArray.clear();
    _dataSetsVertexArrays.clear();
    _textElementArray.clear();
}
