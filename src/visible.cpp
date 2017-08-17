#include "visible.hpp"
visible::visible(char icon, std::string info, int x, int y):position(x, y), icon_{icon}, info_{info}, visible_{false}, accessable_{false}, moveable_{false}{}
char visible::get_icon(){
	return icon_;
}
void visible::set_icon(char c){
	icon_=c;
}
void visible::set_visible(bool v){
	visible_=v;
}
void visible::set_accessable(bool a){
	accessable_=a;
}
void visible::set_moveable(bool m){
	moveable_=m;
}

void visible::set_info(std::string newinfo){
    info_ = newinfo;
}
bool visible::is_accessable(){
	return accessable_;
}
bool visible::is_moveable(){
	return moveable_;
}
bool visible::is_visible(){
	return visible_;
}
std::string visible::to_string(){//hva er dette?
	return info_;
}
