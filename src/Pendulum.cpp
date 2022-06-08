#include "../headers/Pendulum.h"

//r - radius, l - length, angle - start angle in degrees
Pendulum::Pendulum(float r, float l, float angle) : radius{ r }, length{ l }
{
	//calculate theta_zero [rad]
	theta_zero = angle * 3.14f / 180.0f; //deg to rad
	//drawing with angle = 0.0f
	x0 = 0.0f;
	y0 = 1.0f - length;
	//call initialize opengl fcn
	initialize_opengl();
}


Pendulum::~Pendulum()
{
	//delete VAOs and VBOs
	glDeleteVertexArrays(1, &VAO_pend);
	glDeleteBuffers(1, &VBO_pend);
	
	glDeleteVertexArrays(1, &VAO_line);
	glDeleteBuffers(1, &VBO_line);
}

// draw line and pendulum
void Pendulum::draw_pendulum()
{
	glBindVertexArray(VAO_pend);
	glDrawArrays(GL_LINE_STRIP_ADJACENCY, 0, N_of_circle_points);

	glBindVertexArray(VAO_line);
	glDrawArrays(GL_LINE_STRIP, 0, 2);
}

//create pendulum (circle) and line
void Pendulum::initialize_opengl()
{
	N_of_circle_points = 1000;
	struct vertex
	{
		float x, y, z;
	};

	std::vector<vertex> vertices;
	
	//calculate vertices
	for (int i = 0; i < N_of_circle_points; i++)
	{
		vertex tmp;
		//circle as points
		float angle_rad = 2.0f * 3.14f * i / N_of_circle_points;

		//coord of point i of N of pendulum
		//pendulum swing down (theta = 0)
		tmp.x = cos(angle_rad) * radius + x0; //offset x0, y0
		tmp.y = sin(angle_rad) * radius + y0;
		tmp.z = 0.0f;
		
		vertices.push_back(tmp);
	}
	
	//OpenGL
	//generate vertex array object
	glGenVertexArrays(1, &VAO_pend);

	// bind buffers and use them
	glBindVertexArray(VAO_pend);
	// VBO
	glGenBuffers(1, &VBO_pend);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_pend);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(vertex), &vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//unbind buffers
	//VAO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

//	// draw line
	//first point of line is in the middle of upper part of screen
	//second point is in the middle of pendulum 
	float vertices_line [] = {
		0.0f, 1.0f, 0.0f,
		x0, y0, 0.0f
	};

	glGenVertexArrays(1, &VAO_line);

	// bind buffers and use them
	glBindVertexArray(VAO_line);
	// VBO
	glGenBuffers(1, &VBO_line);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_line);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_line), vertices_line, GL_STATIC_DRAW);

	//set line width
	glLineWidth(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//unbind buffers
	//VAO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//calculating new pos of pendulum
void Pendulum::calculate_new_pos(float time)
{
	theta = theta_zero * cos(sqrt(grav / length) * time);
	pos_x = length * sin(theta);
	pos_y = - (length * cos(theta) ) + 1.0f;
}

unsigned int Pendulum::get_VAO_pend() const
{
	return VAO_pend;
}

unsigned int Pendulum::get_VAO_line() const
{
	return VAO_line;
}

unsigned int Pendulum::get_VBO_pend() const
{
	return VBO_pend;
}

unsigned int Pendulum::get_VBO_line() const
{
	return VBO_line;
}

unsigned int Pendulum::get_N_of_circle_points() const
{
	return N_of_circle_points;
}

//for translation matrix
//we subtract x0 pos
float Pendulum::get_x_translate() const
{
	return pos_x - x0;
}

//for translation matrix
//we subtract y0 pos
float Pendulum::get_y_translate() const
{
	return pos_y - y0;
}

float Pendulum::get_z_translate() const
{
	return 0.0f;
}

float Pendulum::get_theta() const
{
	return theta;
}

float Pendulum::get_length() const
{
	return length;
}
