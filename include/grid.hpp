#pragma once

#include <algorithm>
#include <cmath>
#include <vector>
#include <SFML/Graphics.hpp>


struct Grid
{
    float cellSize;
    float min_x, min_y;
    int cols, rows;
    std::vector<std::vector<int>> cells;

    Grid(float min_x, float min_y, float width, float height, float cellSize):
        min_x(min_x),
        min_y(min_y),
        cellSize(cellSize),
        cols(static_cast<int>(std::ceil(width / cellSize))),
        rows(static_cast<int>(std::ceil(height / cellSize))),
        cells(static_cast<std::size_t>(cols * rows)) {}


    void clear () {
        for(auto &c : cells) c.clear();
    }

    void insert(int id, sf::Vector2f pos) {
        const int cx = std::clamp(
            static_cast<int>(std::floor((pos.x - min_x) / cellSize)),
            0,
            cols - 1);
        const int cy = std::clamp(
            static_cast<int>(std::floor((pos.y - min_y) / cellSize)),
            0,
            rows - 1);
        cells[cy * cols + cx].push_back(id);
    }
};
