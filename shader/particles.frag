#version 450 core

layout(location = 0) out vec4 color;

layout(location = 0) in VertexBlock
{
    vec3 color;
    vec3 pos;
    vec3 normal;
} frag_in;

const vec4 lightPosition = vec4(0.0, 0.0, 0.0, 0.0); //vec4(0.0, -800.0, -1000.0, 0.0);
const vec3 lightIntensity = vec3(1.0, 1.0, 1.0);
const vec3 ka = vec3(0.1, 0.1, 0.1);
const vec3 ks = vec3(0.8, 0.8, 0.8);
const float shininess = 50.0;

vec3 ads()
{
    // return vec3(1.0, 0.0, 0.0);
    // return frag_in.color;
   vec3 n = normalize( frag_in.normal );
   vec3 s = normalize( vec3(lightPosition) - frag_in.pos );
   vec3 v = normalize( -frag_in.pos );
   vec3 h = normalize( v + s );
   return lightIntensity * (ka +
                            frag_in.color * max( dot(s, frag_in.normal ), 0.0 ) +
                            ks * pow( max( dot( h, n ), 0.0 ), shininess ) );
}


void main(void)
{
    // color = vec4(1.0, 0.0, 0.0, 1.0);
    // color = vec4(frag_in.normal, 1.0);
    // color = vec4(frag_in.color, 1.0);
    color = vec4(mix(ads(), frag_in.normal, 0.5), 1.0);
}
