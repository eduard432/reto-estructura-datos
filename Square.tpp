#pragma once
#include "Square.h"

unsigned int Square::getId() const {
    return id;
}

string Square::getName() const {
    return name;
}

float Square::getProbability() const {
    return probabilty;
}

bool Square::getVisited() const {
    return visited;
}

bool Square::operator==(const Square& other) const {
    return id == other.id &&
           name == other.name &&
           probabilty == other.probabilty &&
           visited == other.visited;
}