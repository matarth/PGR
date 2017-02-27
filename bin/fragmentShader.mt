#version 330 core
in vec3 fragmentColor;
in vec3 position_c;
in vec3 normal_c;
in vec2 texCoord_v;
in vec3 vertexPosition_w;

in float distanceFromCamera;

in vec2 texCoord;

uniform vec2 texTransform;
uniform int useTexture;
uniform sampler2D texSampler;
uniform mat4 viewMatrix;


// SPOT LIGHT
uniform vec3 spotAmbient;
uniform vec3 spotSpecular;
uniform vec3 spotDiffuse;
uniform vec3 spotDirection;
uniform float spotAngle;
uniform vec3 spotPosition;
uniform float spotIntensity;

uniform vec3 materialAmbient;
uniform vec3 materialSpecular;
uniform vec3 materialDiffuse;
uniform float materialShininess;

// DIRECTIONAL LIGHT
uniform vec3 directionalAmbient;
uniform vec3 directionalSpecular;
uniform vec3 directionalDiffuse;
uniform vec3 directionalDirection;
uniform float directionalIntensity;

//POINT LIGHT
uniform vec3 pointAmbient;
uniform vec3 pointSpecular;
uniform vec3 pointDiffuse;
uniform vec3 pointPosition;
uniform float pointIntensity;



out vec4 color;

vec4 pointLightAddition(){

	vec3 ret = vec3(0.0);
	vec3 pointPosition_c = (viewMatrix * vec4(pointPosition, 1.0)).xyz;

	vec3 L = normalize(pointPosition_c - position_c);
	vec3 R = reflect(-L, normal_c);
	vec3 V = normalize(-position_c);

	float NdotL = max(dot(normal_c, L), 0.0);
	float RdotV = max(dot(R,V), 0.0);

	ret += pointAmbient * materialAmbient * pointIntensity;
	ret += pointDiffuse * materialDiffuse * NdotL * pointIntensity;
	ret += pointSpecular * materialSpecular * pow(RdotV, materialShininess) * pointIntensity;

	return(vec4(ret, 1.0));

}

vec4 directionalLightAddition(){

	vec3 ret = vec3(0.0);
	vec3 directionalDirection_c = (viewMatrix * vec4(directionalDirection, 0.0)).xyz;

	vec3 L = normalize(directionalDirection_c);
	vec3 R = reflect(-L, normal_c);
	vec3 V = normalize(-position_c);

	float NdotL = max(dot(normal_c, L), 0.0);
	float RdotV = max(dot(R,V), 0.0);

	ret += directionalAmbient * materialAmbient * directionalIntensity;
	ret += directionalDiffuse * materialDiffuse * NdotL * directionalIntensity;
	ret += directionalSpecular * materialSpecular * pow(RdotV, materialShininess) * directionalIntensity;

	return(vec4(ret, 1.0));
}

vec4 spotLightAddition(){

	vec3 ret = vec3(0.0);
	vec3 spotPosition_c = (viewMatrix * vec4(spotPosition, 1.0)).xyz;
	vec3 spotDirection_c = (viewMatrix * vec4(spotDirection, 0.0)).xyz;

	vec3 L = normalize(spotPosition_c - position_c);
	vec3 R = reflect(-L, normal_c);
	vec3 V = normalize(-position_c);

	float NdotL = max(dot(L,normal_c), 0.0);
	float RdotV = max(dot(R,V), 0.0);
	float cosAlpha = max(dot(-L, spotDirection_c), 0.0);


	if(cosAlpha > spotAngle){ // vertex is inside the spot light cone
		ret += spotAmbient * materialAmbient * spotIntensity;
		ret += spotDiffuse * materialDiffuse * NdotL * spotIntensity;
		ret += spotSpecular * materialSpecular * pow(RdotV, materialShininess) * spotIntensity;
		ret *= 10*pow(cosAlpha, 50.0);
	}

	return(vec4(ret, 1.0));
}


void main() {


	float fogEnd = 70.0f;
	float fogBegin = 50.0f;

	vec3 diffuse = vec3(1.0f);
	vec3 normal = normalize(normal_c);

	vec4 texAddition = texture(texSampler, texCoord_v + texTransform);
	color = vec4(0.0);
	color = vec4(fragmentColor, 1.0f);
	
	color += pointLightAddition();
	color += spotLightAddition();
	color += directionalLightAddition();

	if(useTexture == 1){
		color = color * texAddition.xyzw;
	}

	float f = 1.0-clamp( (fogEnd-distanceFromCamera)/(fogEnd-fogBegin), 0.0, 1.0);
	color = mix(color,vec4(0.2f), f);
}