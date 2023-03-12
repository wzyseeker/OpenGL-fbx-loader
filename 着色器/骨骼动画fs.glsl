#version 450 core

in vec2 ftexuv;
in vec3 fposw;
in vec3 fnormalw;
out vec4 fcolor;

uniform vec4 dlight_diffuse;
uniform vec3 dlight_direction;

uniform vec4 mat_diffuse;
uniform vec3 mat_emissive;
uniform vec3 mat_ambient;
uniform float mat_specular;
uniform float mat_power;
uniform float mat_reflect;

uniform vec3 eyeposw;
uniform sampler2D tex;

void main()
{
	vec3 toeyew = normalize(eyeposw - fposw);

	vec3 lightvec = normalize(dlight_direction);
	float front = max(dot(-lightvec, fnormalw), 0.0f);

	vec3 diffuse = front * mat_diffuse.rgb * dlight_diffuse.rgb;

	float spec = pow(max(dot(reflect(lightvec, fnormalw), toeyew), 0.0f), mat_specular);

	vec3 specular = texture2D(tex, ftexuv).rgb * mat_ambient + diffuse * spec;
	
	fcolor = vec4(specular, mat_diffuse.a);
}