//
// Created by DamarIndra on 25-Jun-20.
//

#include "Transform.h"

Transform::Transform(){}

Transform::~Transform() {

}

void Transform::update() {

}

sf::Vector2f Transform::get_position() {
	return position;
}

void Transform::set_position(sf::Vector2f v) {
	transform.translate(v - position);
	position = v;
}

void Transform::set_position(float x, float y) {
	transform.translate(x - position.x, y - position.y);
	position.x = x;
	position.y = y;
}

void Transform::set_position_x(float x) {
	transform.translate(x - position.x, 0);
	position.x = x;
}

void Transform::set_position_y(float y) {
	transform.translate(0, y - position.y);
	position.y = y;
}

void Transform::set_global_position(sf::Vector2f v){
	auto matrix = get_global_transform().getMatrix();
	auto local_position = sf::Vector2f(matrix[12], matrix[13]);
	transform.translate(v - local_position);
	position = local_position;
}

void Transform::set_global_position(float x, float y){
	auto matrix = get_global_transform().getMatrix();
	auto local_position = sf::Vector2f(matrix[12], matrix[13]);
	transform.translate(x - local_position.x, y - local_position.y);
	position = local_position;

}

sf::Vector2f Transform::get_global_position(){
	auto matrix = get_global_transform().getMatrix();
	return sf::Vector2f(matrix[12], matrix[13]);
}

sf::Transform Transform::get_global_transform(){
	sf::Transform combined = transform;

	if(parent != nullptr){
		combined *= parent->get_global_transform();
	}

	return combined;
}
