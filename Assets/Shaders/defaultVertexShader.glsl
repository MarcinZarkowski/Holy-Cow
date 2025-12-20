#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 TCInput;

out vec2 TexCoord;

uniform ivec2 ScreenDimensions;

void main(){
    TexCoord = TCInput;
    gl_Position = vec4(
        (2*aPos.x-ScreenDimensions.x)/(ScreenDimensions.x*1.0),
        (2*aPos.y-ScreenDimensions.y)/(ScreenDimensions.y*1.0),
        0.0,
        1.0
    );
}
