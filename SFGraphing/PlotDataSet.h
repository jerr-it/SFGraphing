#ifndef SFGRAPHING_PLOTDATASET_H
#define SFGRAPHING_PLOTDATASET_H

#include <vector>
#include <string>
#include <iostream>
#include "SFML/Graphics.hpp"


namespace csrc
{
    enum PlottingType
    {
        POINTS,
        LINE,
        BARS
    };

    class PlotDataSet
    {
    private:
        std::vector<float> _yValues;
        std::vector<float> _xValues;
        sf::Color _color;
        std::string _label;
        PlottingType _pType;
    public:
        PlotDataSet();

        PlotDataSet(std::vector<float> xValues, std::vector<float> yValues, sf::Color color, std::string label,
                    PlottingType type);

        std::vector<float> GetXValues();

        std::vector<float> GetYValues();

        int GetDataLength();

        sf::Vector2f GetDataValue(int);

        void SetDataValue(int i, sf::Vector2f valuePair);

        sf::Color GetColor();

        void SetColor(sf::Color);

        std::string GetLabel();

        void SetLabel(std::string);

        PlottingType GetPlottingType();

        void SetPlottingType(PlottingType type);
    };
}

#endif //SFGRAPHING_PLOTDATASET_H
