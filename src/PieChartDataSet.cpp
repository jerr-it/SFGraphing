#include "SFGraphing/PieChartDataSet.h"

using namespace csrc;

PieChartDataSet::PieChartDataSet()
    : _representation(Representation::ABSOLUTE)
{
}

PieChartDataSet::PieChartDataSet(const std::vector<float>& values, const std::vector<std::string>& labels,
                                 const Representation& representation, const std::vector<sf::Color>& color)
    : _values(values), _labels(labels), _representation(representation), _colors(color)
{
    if (values.size() != color.size())
    {
        std::cerr << "Invalid data set input" << std::endl;
        exit(1);
    }
}

float PieChartDataSet::GetValue(const size_t& i) const
{
    return _values[i];
}

sf::Color PieChartDataSet::GetColor(const size_t& i) const
{
    return _colors[i];
}

size_t PieChartDataSet::GetLength() const
{
    return _values.size();
}

std::string PieChartDataSet::GetLabel(const size_t& i) const
{
    return _labels[i];
}

Representation PieChartDataSet::GetRepresentation() const
{
    return _representation;
}

void PieChartDataSet::SetValue(const size_t& i, const float& value)
{
    _values[i] = value;
}
