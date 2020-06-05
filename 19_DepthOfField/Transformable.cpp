#include "Transformable.h"
#include <assert.h>
#include <gtc/matrix_access.hpp>

Transformable::Transformable(glm::vec3 translate, glm::vec3 scale, glm::mat3 rotate)
	: Positionable(translate), _scale(scale), _rotate(rotate)
{}

void Transformable::setFromMatrix(glm::mat4 transformation)
{
	glm::vec3 translate = glm::vec3(glm::column(transformation, 3));
	glm::vec3 scale = glm::vec3(
		glm::length(glm::vec3(glm::column(transformation, 0))),
		glm::length(glm::vec3(glm::column(transformation, 1))),
		glm::length(glm::vec3(glm::column(transformation, 2)))
	);
	glm::mat3 rotate = glm::mat3(
		glm::vec3(glm::column(transformation, 0)) / scale.x,
		glm::vec3(glm::column(transformation, 1)) / scale.y,
		glm::vec3(glm::column(transformation, 2)) / scale.z
	);

	this->setPosition(translate);
	this->setScale(scale);
	this->setRotation(rotate);

	/*float sy = std::sqrtf(std::powf(rotate[1][2], 2) + std::powf(rotate[2][2], 2));
	glm::vec3 rot = glm::vec3(0);
	if (sy < 1e-6) {
		std::cout << "SINGULAR" << std::endl;
	}
	//std::atan2f(rotate[1][2], rotate[2][2]),
	//std::atan2f(-rotate[0][2], sy),
	//std::atan2f(rotate[0][1], rotate[0][0])
	else {
		rot = glm::vec3(
			std::atan2f(-rotate[0][2], sy),
			std::atan2f(rotate[0][1], rotate[0][0]),
			std::atan2f(rotate[1][2], rotate[2][2])
		);
	}

	rot = glm::degrees(rot);
	std::cout << glm::to_string(rot) << std::endl;

	this->setPosition(translate);
	this->setScale(scale);
	this->setRotation(rot);*/
}
