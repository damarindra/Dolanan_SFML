//
// Created by DamarIndra on 25-Jun-20.
//

#ifndef DOLANAN_TRANSFORM_H
#define DOLANAN_TRANSFORM_H

#include <SFML/Graphics/Transformable.hpp>

class Transform {

public:
	Transform();

	~Transform();

	void set_position(sf::Vector2f v);
	void set_position(float x, float y);
	void set_position_x(float x);
	void set_position_y(float y);
	sf::Vector2f get_position();

	void set_global_position(sf::Vector2f v);
	void set_global_position(float x, float y);
	sf::Vector2f get_global_position();

	inline Transform* get_parent() { return parent; }

protected:
	sf::Transform get_global_transform();

private:
	sf::Transform transform;
	Transform* parent;

	sf::Vector2f position;
	float rotation;
	sf::Vector2f scale;

	void update();


};


#endif //DOLANAN_TRANSFORM_H
