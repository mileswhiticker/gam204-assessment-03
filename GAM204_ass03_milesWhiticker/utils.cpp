#include <iostream>
#include <sstream>

#include "Renderer.h"
#include "App.h"

#include "utils.h"

namespace utils
{
	std::string dtos(double a_Val)
	{
		std::stringstream ss;
		ss << a_Val;
		std::string out = ss.str();
		return out;
	}
	//
	D3DXVECTOR3 QuatToVec3(D3DXQUATERNION a_Quat)
	{
		return D3DXVECTOR3(a_Quat.x,a_Quat.y,a_Quat.z);
	}
	D3DXQUATERNION Vec3ToQuat(D3DXVECTOR3 a_Vec3)
	{
		return D3DXQUATERNION(a_Vec3.x,a_Vec3.y,a_Vec3.z,0.0f);
	}
	double Vec3Mag(D3DXVECTOR3 a_Vec3)
	{
		return (double)sqrt(a_Vec3.x*a_Vec3.x + a_Vec3.y*a_Vec3.y + a_Vec3.z * a_Vec3.z);
	}
	//
	void keypress_q()
	{
		//
		App::GetInstance()->ModifyOrbitalRadius(-1.0f);
	}
	void keypress_a()
	{
		//
		App::GetInstance()->ModifyOrbitalRadius(1.0f);
	}
	void keypress_w()
	{
		//
		App::GetInstance()->ModifyOrbitalPeriod(-1.0f);
	}
	void keypress_s()
	{
		//
		App::GetInstance()->ModifyOrbitalPeriod(1.0f);
	}
	void keypress_e()
	{
		//
	}
	void keypress_d()
	{
		App::GetInstance()->ToggleDebugInfo();
	}
	void keypress_r()
	{
		//
	}
	void keypress_t()
	{
		//
	}
	//
	void keypress_1()
	{
		//
	}
	void keypress_2()
	{
		//
	}
	//
	void keypress_shift()
	{
		//
	}
	void keypress_ctrl()
	{
		//
	}
	void keypress_space()
	{
		//
	}
	void keypress_up()
	{
		//
	}
	void keypress_down()
	{
		//
	}
	void keypress_left()
	{
		//
	}
	void keypress_right()
	{
		//
	}
	void keypress_tab()
	{
		//
	}
	void keypress_alt()
	{
		//
	}
	//mouse view rotations
	void rotate_view_left(int x,int y)
	{
		//std::cout << "rotate_view_left()" << std::endl;
		Renderer::GetInstance()->m_ApplyViewYaw = 1;
	}
	void rotate_view_right(int x,int y)
	{
		//std::cout << "rotate_view_right()" << std::endl;
		Renderer::GetInstance()->m_ApplyViewYaw = -1;
	}
	void rotate_view_up(int x,int y)
	{
		//std::cout << "rotate_view_up()" << std::endl;
		Renderer::GetInstance()->m_ApplyViewPitch = 1;
	}
	void rotate_view_down(int x,int y)
	{
		//std::cout << "rotate_view_down()" << std::endl;
		Renderer::GetInstance()->m_ApplyViewPitch = -1;
	}
	//mouse view zoom
	void zoom_view_in()
	{
		//std::cout << "utils::zoom_view_in()" << std::endl;
		Renderer::GetInstance()->m_ApplyViewZoom = -1;
	}
	void zoom_view_out()
	{
		//std::cout << "utils::zoom_view_out()" << std::endl;
		Renderer::GetInstance()->m_ApplyViewZoom = 1;
	}
	//change rate of passage of time
	void increase_time_passage_rate()
	{
		//std::cout << "increase_time_passage_rate()" << std::endl;
		App::GetInstance()->m_TimePassageRate += 1;
	}
	void decrease_time_passage_rate()
	{
		//std::cout << "decrease_time_passage_rate()" << std::endl;
		App::GetInstance()->m_TimePassageRate -= 1;
	}
	//change size of solar bodies
	void increase_object_size()
	{
		//std::cout << "increase_object_size()" << std::endl;
		App::GetInstance()->ResizeBodies(1.5f);
	}
	void decrease_object_size()
	{
		//std::cout << "decrease_object_size()" << std::endl;
		App::GetInstance()->ResizeBodies(0.5f);
	}
	//change which planetary body is currently being viewed
	void increment_planet_viewing()
	{
		//std::cout << "utils::increment_planet_viewing()" << std::endl;
		App::GetInstance()->IncrPlanetaryFocus();
	}
	void decrement_planet_viewing()
	{
		//std::cout << "utils::decrement_planet_viewing()" << std::endl;
		App::GetInstance()->DecrPlanetaryFocus();
	}
}
