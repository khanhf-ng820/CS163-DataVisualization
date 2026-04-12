#include "Graph/VisualGraphVertex.h"




VisualGraphVertex::VisualGraphVertex() {}

VisualGraphVertex::VisualGraphVertex(int id)
	: id(id)
{}

VisualGraphVertex::VisualGraphVertex(int id, sf::Vector2f position)
	: id(id), position(position)
{}



int VisualGraphVertex::getID() const {
	return id;
}
