#include <unistd.h>
#include "Window.h"
#include "Graph.h"
#include "GUI.h"
#include <iostream>
#include <ctime>
#include <sstream>

using namespace Graph_lib;
using namespace std;

int get_Hour(){
	time_t t = time(0);
	struct tm * now = localtime( & t );
	return now->tm_hour;
}
string get_Min(){
	time_t t = time(0);
	struct tm * now = localtime( & t );
	stringstream ss;
	if(now->tm_min < 10)
		ss << "0"<< now->tm_min;
	else
		ss << now->tm_min;
	return ss.str();
}
string get_Sec(){
	time_t t = time(0);
	struct tm * now = localtime( & t );
	stringstream ss;
	if(now->tm_sec < 10)
		ss << "0"<< now->tm_sec ;
	else
		ss << now->tm_sec ;
	return ss.str();
}
string time_is(){
	stringstream ss;
	if(get_Hour() > 12) 		ss << (get_Hour()- 12) 	<< ":" << get_Min() << ":" << get_Sec() << " PM";
	else if (get_Hour() == 12) 	ss << get_Hour() 		<< ":" << get_Min() << ":" << get_Sec() << " PM";
	else if( get_Hour() == 0)	ss << "12"				<< ":" << get_Min()	<< ":" << get_Sec() << " AM";
	else						ss << get_Hour() 		<< ":" << get_Min() << ":" << get_Sec() << " AM";

	return ss.str();
}

struct My_Line : Graph_lib :: Line {
	My_Line(Point p1, Point p2);
    void set_pos(Point p){ set_point(0,p);}
};
My_Line::My_Line(Point p1, Point p2): Graph_lib :: Line(p1,p2){}

Point hand_pos(int i){
	long tick = time(0);
	float s_theta = 3.14 - (((tick % 60) / 60.0) * 6.28);
	float m_theta = 3.14 - (((tick % 3600) / 3600.0) * 6.28);
	float h_theta = 0 -(3.14/3.019) - (((tick % 43200) / 43200.0) * 6.28);
	int sx2 = (int)(250 + (sin(s_theta) * 190)),
			sy2 = (int)(250 + (cos(s_theta) * 190)),
			mx2 = (int)(250 + (sin(m_theta) * 190 * 0.88)),
			my2 = (int)(250 + (cos(m_theta) * 190 * 0.88)),
			hx2 = (int)(250 + (sin(h_theta) * 190 * 0.75)),
			hy2 = (int)(250 + (cos(h_theta) * 190 * 0.75));
	switch (i) {
		case 1:
			return Point(sx2,sy2); break;
		case 2:
			return Point(mx2,my2); break;
		case 3:
			return Point(hx2,hy2); break;
		default:
			cout<<"ERROR"<<endl;
			abort();
			break;
	}
	return Point(250,250);
}

class Clock_Window : Graph_lib :: Window  {
	bool button_pushed;
	Button clock_Menu_button, Analog_button, digital_button, quit_button;
    Text digital_time, top, right, bottom, left;
    Graph_lib :: Rectangle r1, r2;
    Graph_lib :: Circle c1, c2, c3;
    My_Line hs, hm, hh;

    static void cb_clock_Menu(Address, Address);
    void clock_Menu();
    static void cd_Analog(Address,Address);
    void Analog();
    static void cd_digital(Address, Address);
    void digital();
    static void cb_quit(Address, Address);
    void quit();
    static void callback(void *userdata);
    void my_redraw();

public:
    Clock_Window(Point xy, int w, int h, const string& title);
};

void Clock_Window::my_redraw(){
	digital_time.set_label(time_is());
	hs.set_pos(hand_pos(1));
	hm.set_pos(hand_pos(2));
	hh.set_pos(hand_pos(3));
	redraw();
}

void Clock_Window::callback(void *userdata) {
	Clock_Window *o = (Clock_Window*)userdata;
    o->my_redraw();
	Fl::repeat_timeout(.25, callback, userdata);
     }

Clock_Window::Clock_Window(Point xy, int w, int h, const string& title)
    :Window(xy,w,h,title),
	 button_pushed(false),
	 clock_Menu_button	(Point(420, 30 ), 80, 20, "Clock Menu", cb_clock_Menu),
	 Analog_button		(Point(420, 30 ), 80, 20, "Analog", cd_Analog),
	 digital_button		(Point(420, 50 ), 80, 20, "Digital", cd_digital),
	 quit_button		(Point(430, 0  ), 70, 20, "Quit", cb_quit),
	 digital_time		(Point(115, 265),time_is()),
	 top				(Point(242, 72 ),"12"),
	 right				(Point(435, 257),"3"),
	 bottom				(Point(246, 442),"6"),
	 left				(Point(57 , 257),"9"),
	 r1 				(Point(100, 180), 300, 140),
	 r2 				(Point(95 , 175), 310, 150),
	 c1 				(Point(250, 250), 200),
	 c2 				(Point(250, 250), 205),
	 c3 				(Point(250, 250), 3  ),
	 hs					(Point(250, 250), Point(250, 250)),
	 hm					(Point(250, 250), Point(250, 250)),
	 hh					(Point(250, 250), Point(250, 250))
	 {

	resizable(0);
	r1.set_color(Color::dark_magenta);
	r2.set_color(Color::dark_magenta);
	c1.set_color(Color::dark_magenta);
	c2.set_color(Color::dark_magenta);
	c3.set_color(Color::dark_magenta);
	c3.set_fill_color(Color::dark_magenta);
	hs.set_color(Color::red); hs.set_style(Line_style::dot);
	hm.set_style(Line_style::dash);
	digital_time.set_font(Font::times_bold);
	digital_time.set_font_size(50);

    attach(clock_Menu_button);
    attach(quit_button);
    Fl::add_timeout(0.25, callback, (void*)this);
}

void Clock_Window::cb_quit(Address, Address pw){
	reference_to<Clock_Window>(pw).quit();
}
void Clock_Window::quit(){
	hide();
	exit(0);
}

void Clock_Window::cb_clock_Menu(Address, Address pw){
	reference_to<Clock_Window>(pw).clock_Menu();
}
void Clock_Window::clock_Menu(){
	detach(clock_Menu_button);
	attach(Analog_button);
	attach(digital_button);
	redraw();
}

void Clock_Window::cd_Analog(Address, Address pw){
	reference_to<Clock_Window>(pw).Analog();
}
void Clock_Window::Analog(){
	detach(Analog_button);
	detach(digital_button);
	attach(clock_Menu_button);
	detach(digital_time);
	detach(r1);	detach(r2);
	hs.set_pos(hand_pos(1));
	hm.set_pos(hand_pos(2));
	hh.set_pos(hand_pos(3));
	attach(top);	attach(right);
	attach(bottom);	attach(left);
	attach(hs);	attach(hm);	attach(hh);
	attach(c1);	attach(c2);	attach(c3);
	redraw();
}

void Clock_Window::cd_digital(Address, Address pw){
	reference_to<Clock_Window>(pw).digital();
}
void Clock_Window::digital(){
	detach(digital_button);
	detach(Analog_button);
	attach(clock_Menu_button);
	detach(c1);		detach(c2);		detach(c3);
	detach(hs);		detach(hm);		detach(hh);
	detach(top);	detach(right);	detach(bottom);	detach(left);
	digital_time.set_label(time_is());
	attach(digital_time);
	attach(r1);		attach(r2);
	redraw();
}
int main() {
	Clock_Window win(Point(100,100),500,500,"Clock");
    return (Fl::run());
}

