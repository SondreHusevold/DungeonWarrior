#include "position.hpp"

position::position(int xpos, int ypos) : x_{xpos}, y_{ypos} {}

void position::set_x(int x){
	x_=x;
}

void position::set_y(int y){
	y_=y;
}
