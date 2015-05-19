#version 330 core
in vec3 P;
in vec3 N;
in vec2 uv;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
out vec4 Nn;
void main() {
   mat4 modelView = viewMatrix * modelMatrix;
   mat4 modelViewProjection = projectionMatrix * modelView;
   gl_Position = modelViewProjection * vec4(P, 1.0);
   //Nn = normalize(viewMatrix * vec4(N, 0.0));
   Nn = vec4(N, 0.0);
}