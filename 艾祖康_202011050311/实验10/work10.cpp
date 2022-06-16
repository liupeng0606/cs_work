#include <windows.h>
#include <GL/glut.h>
#include<stdlib.h>
#include<math.h>
#include <stdio.h>
varying vec3 light,view;
uniform sampler2D textureID;

float height(vec3 color)
{
    float avg=(color.r+color.g)/2.0;
    return mix(avg, .5, .985);


}
vec3 modNormal(vec2 point)
{
    vec2 d0=vec2(0, 0.001);
    vec2 d1=vec2(-0.000866,-0.0005);
    vec2 d2=vec2(0.000866,-0.0005);

    vec2 p0=point +d0;
    vec2 p1=point +d1;
    vec2 p3=point +d2;

    float h0=height(vec3(texture2D(textureID,p0)));
    float h1=height(vec3(texture2D(textureID,p1)));
    float h2=height(vec3(texture2D(textureID,p2)));

    vec3 v0=vec3(d0,h0);
    vec3 v1=vec3(d1,h0);
    vec3 v2=vec3(d2,h0);

    return normalize(vec3(cross(v1-v0,v2-v0)));
}

void main()
{
    vec4 base=texture2D(textureID,gl_TexCoord[0].st);
    vec3 bump=modNormal(gl_TexCoord[0].st);
    vec4 color=gl_LightSource[0].ambient*base;

    float NdotL=max(dot(bump,light),0.0);
    color+=NdotL*(gl_LightSource[0].diffuse*base);

    gl_FragColor=color;
}



