#pragma once
/**
 * @file Piechart data file
 *
 * @author Jerrit Gläsker
 * @date 22.05.202
 *
 * @license MIT-License
 */
#include "SFML/Graphics.hpp"
#include <iostream>

namespace csrc
{
enum class Representation
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
    PieChartDataSet(const std::vector<float>& values, const std::vector<std::string>& labels, const Representation& representation,
                    const std::vector<sf::Color>& colors);

    /**
     * Get Segment Count
     * @return segment count
     */
    size_t GetLength() const;

    /**
     * Get size of specific segment
     * @param  i index
     * @return   segment i
     */
    float GetValue(const size_t& i) const;

    /**
     * Get label of segment i
     * @param  i index
     * @return   label of segment i
     */
    std::string GetLabel(const size_t& i) const;

    /**
     * Get color of segment i
     * @param  i index
     * @return   color of segment i
     */
    sf::Color GetColor(const size_t& i) const;

    /**
     * Get piechart representation
     * @return _representation
     */
    Representation GetRepresentation() const;

    /**
     * Set a segments value
     * @param i     index
     * @param value new value
     */
    void SetValue(const size_t& i, const float& value);
};
}
