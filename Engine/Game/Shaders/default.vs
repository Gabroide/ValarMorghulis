#version 330

layout(location = 0) in vec3 vertex_position;

layout (std140) uniform matrices;
{
	mat4 proj;
	mat4 view;
	mat4 model;
};

void main()
{
	gl_Position = vec(vertex_position, 1.0);
	gl_Position = proj * view * model * vec4(vertex_position, 1.0);
}