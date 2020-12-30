/**
 * @file Plot data file
 *
 * @author Jerrit Gläsker
 * @date 22.05.202
 *
 * @license MIT-License
 */


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

    /**
     * Create empty data
     */
    PlotDataSet();

    /**
     * Constructor for empty data, but initializing other properties
     * @param color dataset color
     * @param label dataset label
     * @param type dataset type
     */
    PlotDataSet(const sf::Color& color, const std::string& label, const PlottingType& type);

    /**
     * Dataset constructor
     * @param xValues vector of doubles, representing x axis
     * @param yValues vector of doubles, representing y axis
     * @param color   color of the bars/points/line
     * @param label   data label
     * @param type    bars/points/line
     */
    PlotDataSet(const std::vector<float>& xValues, const std::vector<float>& yValues, const sf::Color& color, const std::string& label,
                const PlottingType& type);

    /**
     * _xValues Getter
     * @return _xValues
     */
    std::vector<float> GetXValues();

    /**
     * _yValues Getter
     * @return _yValues
     */
    std::vector<float> GetYValues();

    /**
     * Get element count (_xValues ad _yValues always the same size)
     * @return _xValues.size()
     */
    int GetDataLength();

    /**
     * Get a specific value
     * @param  i index
     * @return   value pair at i
     */
    sf::Vector2f GetDataValue(int i);

    /**
     * Setter for a certain value, by index
     * @param i         index
     * @param valuePair new x and y values
     */
    void SetDataValue(int i, sf::Vector2f valuePair);

    /**
     * _color Getter
     * @return _color
     */
    sf::Color GetColor();

    /**
     * _color Setter
     * @param color _color
     */
    void SetColor(sf::Color color);

    /**
     * _label Getter
     * @return _label
     */
    std::string GetLabel();

    /**
     * _label Setter
     * @param lab new _label
     */
    void SetLabel(std::string lab);

    /**
     * _plotType Getter
     * @return _plotType
     */
    PlottingType GetPlottingType();

    /**
     * _plotType Setter
     * @param type new _plotType
     */
    void SetPlottingType(PlottingType type);

    /**
     * Function for adding a pair of values to the dataset
     * @param pair the pair to be added
     */
    void PushPair(sf::Vector2f pair);
};
}

#endif //SFGRAPHING_PLOTDATASET_H
