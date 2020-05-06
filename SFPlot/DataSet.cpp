//
// Created by jerrit on 27.03.20.
//

#include "DataSet.h"

DataSet::DataSet(std::vector<double> _data, sf::Color _color, std::string lbl){
    data = _data;
    color = _color;
    label = lbl;
}