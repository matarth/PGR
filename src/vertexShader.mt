#version 330 core

uniform mat4 pvm;
uniform mat4 normalTransformationMat; // matrix used to transform vertex-normal vectors from MODEL space to CAMERA space;
uniform vec3 barva;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 cameraWorldPosition;

layout (location = 0)	in vec3 vertexPosition;
layout	(location = 1)	in vec3 vertexNormal;
layout (location = 2) in vec2 texCoord;

out vec3 normal_c;
out vec3 position_c;
out vec2 texCoord_v;

out vec3 vertexPosition_w;

out vec3 fragmentColor;
out float distanceFromCamera;

void main() {
	
	gl_Position = pvm * vec4(vertexPosition, 1.0f);

	fragmentColor = barva;
	fragmentColor = vec3(0.0);

	position_c = (viewMatrix * modelMatrix * vec4(vertexPosition, 1.0)).xyz;
	texCoord_v = texCoord;
	normal_c = normalize(normalTransformationMat * vec4(vertexNormal, 0.0)).xyz;

	vertexPosition_w = (modelMatrix * vec4(vertexPosition, 1.0)).xyz;

	distanceFromCamera = length(vertexPosition_w - cameraWorldPosition);
}