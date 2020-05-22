/**
 * @file Piechart data file
 *
 * @author Jerrit Gläsker
 * @date 22.05.202
 *
 * @license MIT-License
 */

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
    std::vector <float> _values;
    std::vector <std::string> _labels;
    Representation _representation;
    std::vector <sf::Color> _colors;
public:

    /**
     * Create empty data
     */
    PieChartDataSet();

    /**
     * Create specific data
     * values, labels and colors have to be the same size
     * @param values         sizes of the pie segments
     * @param labels         labels of each segment
     * @param representation relative/absolute
     * @param colors         colors of segments
     */
    PieChartDataSet(std::vector <float> values, std::vector <std::string> labels, Representation representation,
                    std::vector <sf::Color> colors);

    /**
     * Get Segment Count
     * @return segment count
     */
    int GetLength();

    /**
     * Get size of specific segment
     * @param  i index
     * @return   segment i
     */
    float GetValue(int i);

    /**
     * Get label of segment i
     * @param  i index
     * @return   label of segment i
     */
    std::string GetLabel(int i);

    /**
     * Get color of segment i
     * @param  i index
     * @return   color of segment i
     */
    sf::Color GetColor(int i);

    /**
     * Get piechart representation
     * @return _representation
     */
    Representation GetRepresentation();

    /**
     * Set a segments value
     * @param i     index
     * @param value new value
     */
    void SetValue(int i, float value);
};
}

#endif //GRAPHING_PIECHARTDATASET_H
