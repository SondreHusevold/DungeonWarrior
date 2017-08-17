/*
 * Base klasse for alt som skal ha en posisjon. Har (x, y) koordinater
*/

#ifndef POSITION_HPP
#define POSITION_HPP

class position{

    int x_;                         // X-position
    int y_;                         // Y-position

public:

	position(int x, int y);

	void set_x(int x);
	void set_y(int y);
    virtual ~position(){}

	inline int x(){
		return x_;
	} 
	inline int y(){
		return y_;
	}

};
#endif
