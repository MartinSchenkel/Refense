#version 130
#define PI 3.1415926535897932384626433832795

// More samples => effect becomes more intense (due to more samples taken)
const int samplecount = 32;
// Higher sample radius => image becomes less distinct (due to samples being taken at a greater distance from the origin)
const float sampleradius = 0.005;
uniform sampler2D u_texture; 

void main(){
	vec2 uv = gl_TexCoord[0].xy;
    vec4 color = texture(u_texture, uv);
    int samples = 1;
    float offset = gl_TexCoord[0].x + (gl_TexCoord[0].y * 1920);
    for(int i = 0; i < samplecount; i++){
        float lerp = float(samplecount) / float(i);
        float angle = offset + lerp;
        float radius = sampleradius * sin(lerp * PI);
        vec2 samplefrom = vec2(uv.x + sin(angle) * radius, uv.y + cos(angle) * radius);
        if(samplefrom.x >= 0.0 && samplefrom.x < 1.0 && samplefrom.y >= 0.0 && samplefrom.y < 1.0){
        	color += texture(u_texture, samplefrom);
            samples++;
        }
    }
    float div = float(samples);
	gl_FragColor = vec4(color.r / div, color.g / div, color.b / div, 1.0);
}	