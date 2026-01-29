#pragma once
#include <vector>
#include "zones.hpp"

std::vector<sf::Vector2f> Zone::calculPositionCarte(size_t count)
{
    std::vector<sf::Vector2f> positions;
    if (count == 0) return positions;

    float totalWidth =
        count * largeurcarte +
        (count - 1) * espace;

    float startX =
        aire.left +
        (aire.width - totalWidth) / 2.f;

    float y = aire.top;

    for (size_t i = 0; i < count; ++i) {
        positions.emplace_back(
            startX + i * (largeurcarte + espace),
            y
        );
    }

    return positions;
};