#ifndef UTILS_H
#define UTILS_H

namespace utils
{
	std::string dtos(double a_Val);
	D3DXVECTOR3 QuatToVec3(D3DXQUATERNION a_Quat);
	D3DXQUATERNION Vec3ToQuat(D3DXVECTOR3 a_Vec3);
	double Vec3Mag(D3DXVECTOR3 a_Vec3);
	//
	void keypress_q();
	void keypress_a();
	void keypress_w();
	void keypress_s();
	void keypress_e();
	void keypress_d();
	void keypress_r();
	void keypress_t();
	//
	void keypress_1();
	void keypress_2();
	//
	void keypress_space();
	void keypress_ctrl();
	void keypress_shift();
	void keypress_up();
	void keypress_down();
	void keypress_left();
	void keypress_right();
	void keypress_tab();
	void keypress_alt();
	//
	void rotate_view_left(int x,int y);
	void rotate_view_right(int x,int y);
	void rotate_view_up(int x,int y);
	void rotate_view_down(int x,int y);
	//
	void zoom_view_in();
	void zoom_view_out();
	//
	void increase_time_passage_rate();
	void decrease_time_passage_rate();
	//
	void increase_object_size();
	void decrease_object_size();
	//
	void increment_planet_viewing();
	void decrement_planet_viewing();
};

#endif