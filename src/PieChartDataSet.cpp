#include "SFGraphing/PieChartDataSet.h"

using namespace csrc;

PieChartDataSet::PieChartDataSet()
{
    _representation = Representation::ABSOLUTE;
}

PieChartDataSet::PieChartDataSet(std::vector<float> values, std::vector<std::string> labels,
                                 Representation representation, std::vector<sf::Color> color)
{
    if (values.size() != color.size()) {
        std::cerr << "Invalid data set input" << std::endl;
        exit(1);
    }

    _values = values;
    _labels = labels;
    _representation = representation;
    _colors = color;
}

float PieChartDataSet::GetValue(int i)
{
    return _values[i];
}

sf::Color PieChartDataSet::GetColor(int i)
{
    return _colors[i];
}

int PieChartDataSet::GetLength()
{
    return _values.size();
}

std::string PieChartDataSet::GetLabel(int i)
{
    return _labels[i];
}

Representation PieChartDataSet::GetRepresentation()
{
    return _representation;
}

void PieChartDataSet::SetValue(int i, float value)
{
    _values[i] = value;
}
