 #version 140
  
  uniform samplerCube skyboxSampler;
  in vec3 texCoord_v;
  out vec4 color_f;
  
  void main() {

	  float fogBegin = 70.0;
	  float fogEnd = 50.0;
	  float distanceFromCamera = 60.0;

    color_f = texture(skyboxSampler, texCoord_v);
  }