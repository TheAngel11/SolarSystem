#version 330

in vec3 v_color;
in vec2 v_uv;

uniform vec3 u_color;
uniform sampler2D u_texture;

out vec4 fragColor;

void main(void)
{
    vec4 texture_color = texture(u_texture, v_uv);

    if ( texture_color.x == 1.0 && texture_color.y == 1.0 && texture_color.z == 1.0)
         discard;

    fragColor =  vec4(texture_color.xyz, 1.0);
    
}