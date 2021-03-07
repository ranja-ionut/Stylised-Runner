#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float time;
uniform float death;
uniform int type;

out vec2 texcoord;
out vec3 world_position;
out vec3 world_normal;

float rand(in vec3 co){
    return fract(sin(dot(co.xyz ,vec3(12.34,56.78,910.1112))) * 13141.516);
}

void main()
{
	texcoord = v_texture_coord;

	vec3 wiggled = v_position;

	if (type == 2 || type == 4) { // player death
		wiggled = - death * 0.5 * rand(v_position) * v_normal;
	}

	gl_Position = Projection * View * Model * vec4(wiggled, 1.0);

	if (type == 3) { // GUI
		gl_Position = Model * vec4(v_position.x, v_position.y, 0.0, 1.0);
	}

	world_position = (Model * vec4(v_position, 1.0)).xyz;
	world_normal = (Model * vec4(v_normal, 0.0)).xyz;
}
