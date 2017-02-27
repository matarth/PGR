#include "SkyBox.h"
#include <fstream>
#include <ostream>
#include <stdio.h>

std::string farplaneVtxShaderSrc =
	"#version 330\n"
	"uniform mat4 invPV;\n"
	"in vec2 screenCoord;\n"
	"out vec3 texCoord_v;\n"
	"void main() {\n"
	"  vec4 farplaneCoord = vec4(screenCoord, 0.9999, 1.0);\n"
	"  vec4 worldViewCoord = invPV * farplaneCoord;\n"
	"  texCoord_v = worldViewCoord.xyz / worldViewCoord.w;\n"
	"  gl_Position = farplaneCoord;\n"
	"}\n"
	;


std::string farplaneFragShaderSrc =
	"#version 330\n"
	"uniform samplerCube skybox;\n"
	"in vec3 texCoord_v;\n"
	"out vec4 color_f;\n"
	"void main() {\n"
	"  color_f = texture(skybox, texCoord_v);\n"
	"}\n"
	;


bool SkyBox::loadCubeMap(char * baseFileName ) {
   glActiveTexture(GL_TEXTURE0);

  glGenTextures(1, &this->texture);
  glBindTexture(GL_TEXTURE_CUBE_MAP, this->texture);

  const char * suffixes[] = { "posx", "negx", "posy", "negy", "posz", "negz" };
  GLuint targets[] = {
    GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
    GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
    GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
  };

  for( int i = 0; i < 6; i++ ) {
    std::string texName = std::string(baseFileName) + "_" + suffixes[i] + ".jpg";
    if(!pgr::loadTexImage2D(texName, targets[i])) {
	  printf("WRRR\n");
      return false;
    }
  }

  glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
  glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

  // unbind the texture (just in case someone will mess up with texture calls later)
  glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
  CHECK_GL_ERROR();
  return true;
}


SkyBox::SkyBox(void)
{
	this->reset();

	// opengl setup
  glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glPointSize(5.0f);


  GLuint farplaneShaders [] = {
    pgr::createShaderFromSource(GL_VERTEX_SHADER, farplaneVtxShaderSrc),
    pgr::createShaderFromSource(GL_FRAGMENT_SHADER, farplaneFragShaderSrc),
    0
  };
  this->shaderProgram = pgr::createProgram(farplaneShaders);

  static const float screenCoords[] = {
    -1.0f, -1.0f,
    1.0f, -1.0f,
    -1.0f, 1.0f,
    1.0f, 1.0f
  };
  // buffer for far plane rendering
  glGenBuffers(1, &this->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(screenCoords), screenCoords, GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // handles to vertex shader inputs
  GLint farplaneSceenCoordLoc = glGetAttribLocation(this->shaderProgram, "screenCoord");
  GLint skyboxLoc = glGetUniformLocation(this->shaderProgram, "skybox");
  glUseProgram(this->shaderProgram);
  glUniform1i(skyboxLoc, 0);

  glGenVertexArrays(1, &this->vao);
  glBindVertexArray(this->vao);
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
  glEnableVertexAttribArray(farplaneSceenCoordLoc);
  glVertexAttribPointer(farplaneSceenCoordLoc, 2, GL_FLOAT, GL_FALSE, 0, 0);

  glBindVertexArray(0);
  glUseProgram(0);
  CHECK_GL_ERROR();

  if(!loadCubeMap("data\\skybox\\skyboxtexture")) {
    printf("GRRR\n");
    return;
  }

  return;

}


SkyBox::~SkyBox(void)
{


}

void SkyBox::loadShaders(){
}

glm::mat4 SkyBox::getModelMatrix(){
	return(glm::mat4(1.0));
}
