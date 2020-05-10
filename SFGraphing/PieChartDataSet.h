#ifndef GRAPHING_PIECHARTDATASET_H
#define GRAPHING_PIECHARTDATASET_H

#include "SFML/Graphics.hpp"
#include <iostream>

namespace csrc
{
    enum Representation
    {
        RELATIVE,
        ABSOLUTE
    };

    class PieChartDataSet
    {
    private:
        std::vector<float> _values;
        std::vector<std::string> _labels;
        Representation _representation;
        std::vector<sf::Color> _colors;
    public:
        PieChartDataSet();

        PieChartDataSet(std::vector<float> values, std::vector<std::string> labels, Representation representation,
                        std::vector<sf::Color> colors);

        int GetLength();

        float GetValue(int i);

        std::string GetLabel(int i);

        sf::Color GetColor(int i);

        Representation GetRepresentation();

        void SetValue(int i, float value);
    };
}

#endif //GRAPHING_PIECHARTDATASET_H
