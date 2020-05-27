#include "PlotDataSet.h"

using namespace csrc;

PlotDataSet::PlotDataSet()
{
    _color = sf::Color::White;
    _label = "Unlabeled";
    _pType = PlottingType::POINTS;
}

PlotDataSet::PlotDataSet(sf::Color color, std::string label, PlottingType type)
{
    _color = color;
    _label = label;
    _pType = type;
}

PlotDataSet::PlotDataSet(std::vector<float> xValues, std::vector<float> yValues, sf::Color color, std::string label,
                         PlottingType type)
{
    if (xValues.size() != yValues.size())
    {
        std::cerr << "Incompatible data sizes" << std::endl;
        exit(1);
    }

    _xValues = xValues;
    _yValues = yValues;

    _color = color;
    _label = label;
    _pType = type;
}

sf::Vector2f PlotDataSet::GetDataValue(int i)
{
    return sf::Vector2f{_xValues[i], _yValues[i]};
}

void PlotDataSet::SetDataValue(int i, sf::Vector2f valuePair)
{
    _xValues[i] = valuePair.x;
    _yValues[i] = valuePair.y;
}

sf::Color PlotDataSet::GetColor()
{
    return _color;
}

void PlotDataSet::SetColor(sf::Color color)
{
    _color = color;
}

std::string PlotDataSet::GetLabel()
{
    return _label;
}

void PlotDataSet::SetLabel(std::string label)
{
    _label = label;
}

PlottingType PlotDataSet::GetPlottingType()
{
    return _pType;
}

void PlotDataSet::SetPlottingType(PlottingType type)
{
    _pType = type;
}

int PlotDataSet::GetDataLength()
{
    return _xValues.size();
}

std::vector<float> PlotDataSet::GetXValues()
{
    return _xValues;
}

std::vector<float> PlotDataSet::GetYValues()
{
    return _yValues;
}

void PlotDataSet::PushPair(sf::Vector2f pair)
{
    _xValues.push_back(pair.x);
    _yValues.push_back(pair.y);
}
