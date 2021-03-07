#version 330

#define COUNT 10

in vec2 texcoord;
in vec3 world_position;
in vec3 world_normal;

uniform sampler2D texture_in;
uniform float time;
uniform int isSkySphere;
uniform int isFlame;
uniform int spin;
uniform int speed;

uniform vec3 light_direction[COUNT];
uniform vec3 light_position[COUNT];
uniform vec3 light_color[COUNT];
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform float border;
uniform int material_shininess;

uniform int spot[COUNT];
uniform int type;
uniform float angle[COUNT];

layout(location = 0) out vec4 out_color;

void main()
{
	vec3 N = normalize(world_normal);
	vec3 L[COUNT];
	vec3 V = normalize(eye_position - world_position);

	float ambient_light = 0.25;

	float diffuse_light[COUNT];

	float specular_light[COUNT];

	vec4 out_light = vec4(vec3(0), 1);
	float light = 0;

	for (int i = 0; i < COUNT; i++) {
		if (light_position[i].z  >= -border && light_position[i].z <= border) {
			L[i] = normalize(light_position[i] - world_position);

			specular_light[i] = 0;

			diffuse_light[i] = material_kd * max (dot(N,L[i]), 0);

			if (diffuse_light[i] > 0)
			{
				vec3 R = reflect(-L[i], N);
				specular_light[i] = pow(max(0, dot(V, R)), material_shininess) * material_ks;
			}

			if (spot[i] == 1) {
				float cut_off = radians(angle[i]);
				float spot_light = dot(-L[i], light_direction[i]);
				float spot_light_limit = cos(cut_off);

				if (spot_light > spot_light_limit)
				{
					float linear_att = (spot_light - spot_light_limit) / (1.0f - spot_light_limit);
					float light_att_factor = pow(linear_att, 2);

					light = ambient_light + light_att_factor * max(diffuse_light[i] + specular_light[i], 0);
				} else {
					light = ambient_light;
				}
			} else {
				float d = distance(world_position, light_position[i]);
				float att = 1 / (1.0 + 0.1 * d + 0.01 * d * d);
				
				light = ambient_light + att * diffuse_light[i] + specular_light[i];
			}
		}

		out_light += vec4(light * light_color[i], 1);
	}
	
	if (spin == 1 ) {
		out_color = texture2D(texture_in, texcoord + vec2(time / speed, 0));
	} else if (isSkySphere == 1) {
		out_color = texture2D(texture_in, texcoord + vec2(time / 100, 0));
	} else if (isFlame == 1){
		out_color = texture2D(texture_in, texcoord + vec2(0, time));
	} else {
		out_color = texture2D(texture_in, texcoord);
	}

	if (type != 3 && type != 10 && out_light.rgb != vec3(0)) {
		out_color *= out_light;
	}

}