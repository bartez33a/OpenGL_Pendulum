#pragma once
#include <glad\glad.h>
#include <memory>
#include <math.h>
#include <vector>
#include <iostream>
#include "../headers/VAO.h"
#include "../headers/VBO.h"

class Pendulum
{
	//pendulum state
	float x0, y0;
	float pos_x, pos_y;
	float length;
	float radius;
	float theta_zero;
	float theta;
	const float grav = 9.81;

	//drawing
	unsigned int VBO_pend;
	unsigned int VAO_pend;
	unsigned int VBO_line;
	unsigned int VAO_line;
	unsigned int N_of_circle_points;

public:
	//Constructor creates pendulum swinging down (x0, y0), calculates theta zero and calls initialize_opengl()
	Pendulum(float r, float l, float angle);
	//Destructor deletes opengl buffers
	~Pendulum();

	//draw line and pendulum
	void draw_pendulum();
	//creates vertices data for pendulum and line
	void initialize_opengl();
	//calculate new position of pendulum
	void calculate_new_pos(float time);
	//getter for private variables
	unsigned int get_VAO_pend() const;
	unsigned int get_VAO_line() const;
	unsigned int get_VBO_pend() const;
	unsigned int get_VBO_line() const;
	unsigned int get_N_of_circle_points() const;

	float get_x_translate() const;
	float get_y_translate() const;
	float get_z_translate() const;
	float get_theta() const;
	float get_length() const;
};

