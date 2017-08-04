#version 330 core

in vec2 tex_coord;
out vec4 frag_color;

uniform sampler2D tex;

void main()
{
    vec4 c = texture(tex, tex_coord);
    if (c.a < 0.5) discard;

    frag_color = vec4(c.rgb, 1);

}