#include "Transformable.h"

Transformable::Transformable(glm::vec3 translate, glm::vec3 scale, glm::vec3 rotate)
	: Positionable(translate), _scale(scale), _rotate(rotate)
{}
