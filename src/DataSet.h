//
// Created by jerrit on 27.03.20.
//

#ifndef SFPLOT_DATASET_H
#define SFPLOT_DATASET_H

#include <vector>
#include <SFML/Graphics/Color.hpp>

class DataSet {
public:
    std::vector <double> data;
    sf::Color color;

    DataSet(std::vector<double> _data, sf::Color _color);
};


#endif //SFPLOT_DATASET_H
