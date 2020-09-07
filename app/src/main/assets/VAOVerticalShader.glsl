#version 300 es
layout(location = 0) in vec4 inPosition;
layout(location = 1) in vec4 in_Color;
out vec4 v_Color;
void main(){
    v_Color = in_Color ;
    gl_Position = inPosition ;
}