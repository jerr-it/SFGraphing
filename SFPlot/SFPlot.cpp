//
// Created by jerrit on 23.03.20.
//

#include "SFPlot.h"

using namespace csrc;

SFPlot::SFPlot(std::vector<double> x, std::string xl, std::string yl, double m, sf::Font* f){
    xAxis = x;
    xLabel = xl;
    yLabel = yl;
    margin = m;
    font = f;
    windowDimOverriden = false;
}

std::string SFPlot::ToString(double d, int precision) {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(precision) << d;
    std::string s = stream.str();
    return s;
}

void SFPlot::setxAxis(std::vector<double> axis) {
    xAxis = axis;
}

void SFPlot::setFont(sf::Font *f) {
    font = f;
}

void SFPlot::setMargin(double _margin) {
    margin = _margin;
}

void SFPlot::plot(DataSet set) {
    if(set.data.size() != xAxis.size()){
        return;
    }
    DataSets.push_back(set);
}

void SFPlot::setLabels(std::string x, std::string y) {
    xLabel = x;
    yLabel = y;
}

void SFPlot::overrideWindowSize(int x, int y) {
    windowDim.x = x;
    windowDim.y = y;
    windowDimOverriden = true;
}

sf::Vector2f SFPlot::CoordToWindowLocation(double x, double y, sf::RenderWindow* window) {
    sf::Vector2f vec;

    vec.x = margin + xAxisLen * (x / xMax);
    vec.y = windowDim.y - margin - yAxisLen * (y / yMax);

    return vec;
}

void SFPlot::clearDatasets() {
    DataSets.clear();
    xAxisArray.clear();
    yAxisArray.clear();
    xnumArray.clear();
    ynumArray.clear();
    xnumLabelArray.clear();
    ynumLabelArray.clear();

    for(int i = 0; i < datasetsPlotPoints.size(); i++){
        datasetsPlotPoints.at(i).clear();
    }
}

void SFPlot::setup(sf::RenderWindow* window, PlotType type) {
    //Set up variables
    xMax = *std::max_element(xAxis.begin(), xAxis.end());
    xMin = *std::min_element(xAxis.begin(), xAxis.end());


    yMax = -INFINITY;
    yMin = INFINITY;
    for(int i = 0; i < DataSets.size(); i++){
        double localMax = *std::max_element(DataSets.at(i).data.begin(), DataSets.at(i).data.end());
        if(localMax > yMax){
            yMax = localMax;
        }

        double localMin = *std::min_element(DataSets.at(i).data.begin(), DataSets.at(i).data.end());
        if(localMin < yMin){
            yMin = localMin;
        }
    }

    if(!windowDimOverriden) {
        windowDim = window->getSize();
    }
    xAxisLen = windowDim.x - 2 * margin;
    yAxisLen = windowDim.y - 2 * margin;

    //Axis Lines
    xAxisArray.setPrimitiveType(sf::PrimitiveType::Lines);
    xAxisArray.resize(2);
    xAxisArray.append(sf::Vertex(sf::Vector2f(margin, windowDim.y - margin)));
    xAxisArray.append(sf::Vertex(sf::Vector2f(windowDim.x - margin, windowDim.y - margin)));

    yAxisArray.setPrimitiveType(sf::PrimitiveType::Lines);
    yAxisArray.resize(2);
    yAxisArray.append(sf::Vertex(sf::Vector2f(margin, windowDim.y - margin)));
    yAxisArray.append(sf::Vertex(sf::Vector2f(margin, margin)));

    //Axis Labels in top left and bottom right corner
    xLabelText.setString(xLabel);
    xLabelText.setCharacterSize(margin / 3);
    xLabelText.setFont(*font);
    xLabelText.setPosition(windowDim.x, windowDim.y);
    sf::FloatRect fr = xLabelText.getGlobalBounds();
    xLabelText.move(-fr.width, -fr.height * 2);

    yLabelText.setString(yLabel);
    yLabelText.setCharacterSize(margin / 3);
    yLabelText.setFont(*font);

    //Axis Numbers
    //x Axis
    //Low and High boundaries in plot coordinate system
    xLow = round(xMin);
    xHigh = round(xMax);
    //Increase between markers
    xStepSize = 2 * round(sqrt((xHigh - xLow)));

    int xsteps = (xHigh - xLow) / xStepSize;
    while(xsteps > 10){
        xStepSize *= 2;
        xsteps = (xHigh - xLow) / xStepSize;
    }

    xnumArray.setPrimitiveType(sf::PrimitiveType::Lines);
    xnumArray.resize(xAxis.size() * 2);
    for (int xlabel = xLow; xlabel <= xHigh; xlabel += xStepSize) {

        //Indicating Line
        sf::Vector2f onAxisPosition = CoordToWindowLocation(xlabel, 0, window);
        xnumArray.append(sf::Vertex(onAxisPosition));
        xnumArray.append(sf::Vertex(sf::Vector2f(onAxisPosition.x, onAxisPosition.y + 5)));

        //Label
        sf::Text text;
        text.setFont(*font);
        text.setCharacterSize(margin * 0.35);
        text.setPosition(onAxisPosition);
        text.setString(ToString(xlabel, 0));
        //Adjusting position to fit right under the Indicating Line
        sf::FloatRect fr = text.getLocalBounds();
        text.move(0, 2);
        text.rotate(45);

        xnumLabelArray.push_back(text);
    }

    //y Axis
    yLow = round(yMin);
    yHigh = round(yMax);
    yStepSize = 2 * round(sqrt((yHigh - yLow)));

    int ysteps = (yHigh - yLow) / yStepSize;
    while(ysteps > 10){
        yStepSize *= 2;
        ysteps = (yHigh - yLow) / yStepSize;
    }

    ynumArray.setPrimitiveType(sf::PrimitiveType::Lines);
    ynumArray.resize((yHigh - yLow) * 2);
    int vertexIndex = 0;
    for (int ylabel = yLow; ylabel <= yHigh; ylabel += yStepSize) {
        sf::Vector2f onAxisPosition = CoordToWindowLocation(0, ylabel, window);
        ynumArray[vertexIndex].position = onAxisPosition;
        ynumArray[vertexIndex+1].position = sf::Vector2f(onAxisPosition.x - 5, onAxisPosition.y);
        vertexIndex+=2;

        sf::Text text;
        text.setFont(*font);
        text.setCharacterSize(margin * 0.35);
        text.setPosition(onAxisPosition);
        text.setString(ToString(ylabel, 0));

        sf::FloatRect fr = text.getLocalBounds();
        text.move(-fr.width - 10, -fr.height);

        ynumLabelArray.push_back(text);
    }

    for(int di = 0; di < DataSets.size(); di++) {
        //Depending on the plot type, draw data
        sf::VertexArray plotPoints;
        if (type == PlotType::Points)
        {
            plotPoints.setPrimitiveType(sf::PrimitiveType::Quads);
            plotPoints.resize(xAxis.size() * 4);

            vertexIndex = 0;
            for (int i = 0; i < xAxis.size(); i++) {
                sf::Vector2f pos = CoordToWindowLocation(xAxis.at(i), DataSets.at(di).data.at(i), window);
                plotPoints[vertexIndex+0].position = sf::Vector2f(pos.x - 3, pos.y - 3);
                plotPoints[vertexIndex+1].position = sf::Vector2f(pos.x + 3, pos.y - 3);
                plotPoints[vertexIndex+2].position = sf::Vector2f(pos.x + 3, pos.y + 3);
                plotPoints[vertexIndex+3].position = sf::Vector2f(pos.x - 3, pos.y + 3);

                plotPoints[vertexIndex+0].color = DataSets.at(di).color;
                plotPoints[vertexIndex+1].color = DataSets.at(di).color;
                plotPoints[vertexIndex+2].color = DataSets.at(di).color;
                plotPoints[vertexIndex+3].color = DataSets.at(di).color;

                vertexIndex += 4;
            }
        } else if (type == PlotType::Line) {
            plotPoints.setPrimitiveType(sf::PrimitiveType::LineStrip);
            plotPoints.resize(xAxis.size());

            for (int i = 0; i < xAxis.size(); i++) {
                sf::Vector2f pos = CoordToWindowLocation(xAxis.at(i), DataSets.at(di).data.at(i), window);
                plotPoints[i].position = pos;
                plotPoints[i].color = DataSets.at(di).color;
            }
        } else if (type == PlotType::Bars) {
            plotPoints.setPrimitiveType(sf::PrimitiveType::Quads);
            plotPoints.resize(xAxis.size() * 4);

            float barWidth = ((float)xAxisLen / ((float)xsteps * 3 * DataSets.size())) - 5;

            vertexIndex = 0;
            for(int i = 0; i < xAxis.size(); i++){
                sf::Vector2f pos = CoordToWindowLocation(xAxis.at(i), DataSets.at(di).data.at(i), window);
                sf::Vector2f groundPos = CoordToWindowLocation(xAxis.at(i), 0, window);

                plotPoints[vertexIndex+0].position = sf::Vector2f(pos.x - barWidth / 2 - di * barWidth + ((float)DataSets.size() / 2) * (barWidth / 2), pos.y);
                plotPoints[vertexIndex+1].position = sf::Vector2f(pos.x + barWidth / 2 - di * barWidth + ((float)DataSets.size() / 2) * (barWidth / 2), pos.y);
                plotPoints[vertexIndex+2].position = sf::Vector2f(groundPos.x + barWidth / 2 - di * barWidth +  + ((float)DataSets.size() / 2) * (barWidth / 2), groundPos.y);
                plotPoints[vertexIndex+3].position = sf::Vector2f(groundPos.x - barWidth / 2 - di * barWidth +  + ((float)DataSets.size() / 2) * (barWidth / 2), groundPos.y);

                plotPoints[vertexIndex+0].color = DataSets.at(di).color;
                plotPoints[vertexIndex+1].color = DataSets.at(di).color;
                plotPoints[vertexIndex+2].color = DataSets.at(di).color;
                plotPoints[vertexIndex+3].color = DataSets.at(di).color;

                vertexIndex += 4;
            }
        } else {
            std::cout << "No valid Plottype given." << std::endl;
        }

        datasetsPlotPoints.push_back(plotPoints);
    }
}

double SFPlot::distSq(sf::Vector2f a, sf::Vector2f b){
    return ((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void SFPlot::RenderTo(sf::RenderWindow* window)
{
    //Final draw calls

    //Draw Legend
    sf::Vector2f location = sf::Vector2f(windowDim.x, 0);
    for(int i = 0; i < DataSets.size(); i++)
    {
        sf::Text label;
        label.setFont(*font);
        label.setString(DataSets.at(i).label);
        label.setCharacterSize(margin * 0.35);
        label.setFillColor(DataSets.at(i).color);
        label.setPosition(location);

        sf::FloatRect fr = label.getGlobalBounds();
        label.move(-fr.width, 0);
        location.x -= fr.width + 5;

        window->draw(label);
    }

    //Draw data
    for(int i = 0; i < datasetsPlotPoints.size(); i++){
        window->draw(datasetsPlotPoints.at(i));
    }

    //Draw x label numbers
    for(int i = 0; i < xnumLabelArray.size(); i++){
        window->draw(xnumLabelArray.at(i));
    }

    //Draw y label numbers
    for(int i = 0; i < ynumLabelArray.size(); i++){
        window->draw(ynumLabelArray.at(i));
    }

    //Draw x axis and number indicators
    window->draw(xAxisArray);
    window->draw(xnumArray);

    //Draw y axis and number indicators
    window->draw(yAxisArray);
    window->draw(ynumArray);

    //axis labels
    window->draw(xLabelText);
    window->draw(yLabelText);

    //Draw value closest to mouse
    sf::Vector2f closestDataValuePosition = sf::Vector2f(MAXFLOAT, MAXFLOAT);
    sf::Vector2f closestDataValue;
    float closestDataValueDistance = MAXFLOAT;
    for(int di = 0; di < DataSets.size(); di++)
    {
        for(int i = 0; i < DataSets[di].data.size(); i++)
        {
            sf::Vector2f dataCoord = CoordToWindowLocation(xAxis[i], DataSets[di].data[i], window);
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

            double dist = distSq(dataCoord, sf::Vector2f(mousePos.x, mousePos.y));
            if(dist < closestDataValueDistance){
                closestDataValueDistance = dist;
                closestDataValuePosition = dataCoord;
                closestDataValue = sf::Vector2f(xAxis[i], DataSets[di].data[i]);
            }
        }
    }

    if(closestDataValueDistance < 20 * 20) {
        sf::Text closestDataLabel;

        closestDataLabel.setFont(*font);
        closestDataLabel.setCharacterSize(15);
        closestDataLabel.setPosition(closestDataValuePosition.x, closestDataValuePosition.y);
        closestDataLabel.setString(
                "(X: " + ToString(closestDataValue.x, 2) + " | Y: " + ToString(closestDataValue.y, 2) + ")");

        sf::FloatRect fr = closestDataLabel.getLocalBounds();
        closestDataLabel.move(sf::Vector2f(-fr.width / 2, -2 * fr.height));

        sf::Vector2f pos = closestDataLabel.getPosition();
        sf::Vector2u wDim = window->getSize();
        if(pos.x < 0){
            pos.x = 0;
        }
        else if(pos.x + fr.width > wDim.x){
            pos.x = wDim.x - fr.width;
        }
        if(pos.y < 0){
            pos.y = 0;
        }
        else if(pos.y + fr.height > wDim.y){
            pos.y = wDim.y - fr.height;
        }
        closestDataLabel.setPosition(pos);

        window->draw(closestDataLabel);
    }
}