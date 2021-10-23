#include "SFGraphing/PlotDataSet.h"

using namespace csrc;

PlotDataSet::PlotDataSet()
{
    _color = sf::Color::White;
    _label = "Unlabeled";
    _pType = PlottingType::POINTS;
}

PlotDataSet::PlotDataSet(const sf::Color& color, const std::string& label, const PlottingType& type)
    : _color(color), _label(label), _pType(type)
{
}

PlotDataSet::PlotDataSet(const std::vector<float>& xValues, const std::vector<float>& yValues, const sf::Color& color, const std::string& label,
                         const PlottingType& type)
    : _xValues(xValues), _yValues(yValues), _color(color), _label(label), _pType(type)
{
    if (_xValues.size() != _yValues.size())
    {
        std::cerr << "Incompatible data sizes" << std::endl;
        exit(1);
    }
}

sf::Vector2f PlotDataSet::GetDataValue(const size_t& i) const
{
    return sf::Vector2f{_xValues[i], _yValues[i]};
}

void PlotDataSet::SetDataValue(const size_t& i, const sf::Vector2f& valuePair)
{
    _xValues[i] = valuePair.x;
    _yValues[i] = valuePair.y;
}

sf::Color PlotDataSet::GetColor() const
{
    return _color;
}

void PlotDataSet::SetColor(const sf::Color& color)
{
    _color = color;
}

std::string PlotDataSet::GetLabel() const
{
    return _label;
}

void PlotDataSet::SetLabel(const std::string& label)
{
    _label = label;
}

PlottingType PlotDataSet::GetPlottingType() const
{
    return _pType;
}

void PlotDataSet::SetPlottingType(const PlottingType& type)
{
    _pType = type;
}

size_t PlotDataSet::GetDataLength() const
{
    return _xValues.size();
}

std::vector<float> PlotDataSet::GetXValues() const
{
    return _xValues;
}

std::vector<float> PlotDataSet::GetYValues() const
{
    return _yValues;
}

void PlotDataSet::PushPair(const sf::Vector2f& pair)
{
    _xValues.push_back(pair.x);
    _yValues.push_back(pair.y);
}

void PlotDataSet::PopFront(const size_t n)
{
    size_t erase_count = std::min(n, _xValues.size());

    if (erase_count != 0)
    {
        _xValues.erase(_xValues.begin(), _xValues.begin() + erase_count);
        _yValues.erase(_yValues.begin(), _yValues.begin() + erase_count);
    }
}
