#include "NewModel.h"
#include <fstream>
#include <string>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

void printVector2(glm::vec3 vector){
	printf("(%f, %f, %f)\n", vector.x, vector.y, vector.z);
}

void printMatrix2(glm::mat4 matrix){
	int ii;
	for(ii = 0; ii < 16; ii++){
		if(ii % 4 == 0)
			printf("\n");
		printf("%+.1f ", glm::value_ptr(matrix)[ii]);
	}

	printf("\n");
}


NewModel::NewModel(void)
{
}

NewModel::NewModel(char* objectFile){

	this->useTexture = false;
	this->reset();
	this->loadModelFromSource(objectFile);
	this->loadShaders();
	this->connectDataToShaders();
	this->dataFile = objectFile;
	this->size = 1.0f;
	this->isCamera = false;
	this->color = glm::vec3(0.0f);
}

void NewModel::addTexture(char* textureFile){
		
		this->texture = pgr::createTexture(textureFile);
		this->useTexture = true;
}

NewModel::~NewModel(void)
{
}

void NewModel::scale(float newSize){
	this->size = newSize;
}

glm::mat4 NewModel::getModelMatrix(){

	glm::mat4 ret = glm::mat4(1.0f);

	glm::mat4 rot = glm::toMat4(this->rotationQuaternion);

	

	ret = glm::translate(ret, this->position);
	ret *= rot;
	ret = glm::scale(ret, glm::vec3(this->size));

	return(ret);
}


void NewModel::init(){

}

bool NewModel::loadModelFromSource(char* fileName){

	Assimp::Importer importer;
	unsigned int ii;

	importer.SetPropertyInteger(AI_CONFIG_PP_PTV_NORMALIZE, 1);

	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);

	const aiScene *scene = importer.ReadFile(fileName,
		aiProcess_Triangulate
		| aiProcess_JoinIdenticalVertices 
		| aiProcess_PreTransformVertices
		| aiProcess_GenSmoothNormals
		);

	if(!scene){
		printf("Error while loading model from %s.\n", fileName);
		return(false);
	}

	aiMesh *mesh = scene->mMeshes[0]; // only one objetc in model

	this->numberOfFaces = mesh->mNumFaces;
	this->numberOfVertices = mesh->mNumVertices;

	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

	glBufferData(GL_ARRAY_BUFFER, 8*sizeof(float)*this->numberOfVertices, 0, GL_STATIC_DRAW);
	/* 
	8*float protoze: 2*float textura, 3*f vrchol a 3*f RGB barva
	ted je jedno v jakym poradi budeme data posilat na grafickou kartu, jen se to musi shodovat s poradim v metode Scene::connectDataToShaders
	*/
	// loads array of vertices to graphics card
	glBufferSubData(GL_ARRAY_BUFFER, 0, 3*sizeof(float)*this->numberOfVertices, mesh->mVertices);
	// loads array of vertex normals. atributy -> (glEnum, start position, size of data, what to load)
	glBufferSubData(GL_ARRAY_BUFFER, 3*sizeof(float)*this->numberOfVertices, 3*sizeof(float)*this->numberOfVertices, mesh->mNormals);
	float *texture = new float[2*this->numberOfVertices];

	if(mesh->HasTextureCoords(0)){

		for(ii = 0; ii < this->numberOfVertices; ii++){
			texture[2*ii] = (mesh->mTextureCoords[0])[ii].x;
			texture[2*ii + 1] = (mesh->mTextureCoords[0])[ii].y;
		}
	}

	// load texture coords.
	glBufferSubData(GL_ARRAY_BUFFER, 6*sizeof(float)*this->numberOfVertices, 2*sizeof(float)*this->numberOfVertices, texture);
	delete(texture);
	// 6*sizeof(float) protoze uz jsme predtim nahrali 3*sizeof(float) vrcholu (vertices) a 3*sizeof(float) normal.

	// https://www.youtube.com/watch?v=H8D-bJuRkTg&list=WL&index=43 :D



	unsigned int *indices = new unsigned int[this->numberOfFaces * 3];

	for(ii = 0; ii < this->numberOfFaces; ii++){
		indices[ii*3] = mesh->mFaces[ii].mIndices[0];
		indices[ii*3 + 1] = mesh->mFaces[ii].mIndices[1];
		indices[ii*3 + 2] = mesh->mFaces[ii].mIndices[2];
	}

	glGenBuffers(1, &this->eao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->eao);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3*sizeof(unsigned int)*this->numberOfFaces, indices, GL_STATIC_DRAW);

	delete(indices);



	printf("Model %s succesfully loaded.\n", fileName);

	return(true);

}

void NewModel::connectDataToShaders(){

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

	// load vertices to shader
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);	

	// load normals to shader
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(3*sizeof(float)*this->numberOfVertices));


	//load texture coord to shader
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2,2, GL_FLOAT, GL_FALSE, 0, (void*)(6*sizeof(float)*this->numberOfVertices));
}

void NewModel::loadShaders(){

	std::ifstream ifs("vertexShader.mt");
	std::string vertexShaderSrc((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

	this->vertexShaderSrc = vertexShaderSrc.c_str();


	std::ifstream ifs2("fragmentShader.mt");
	std::string fragmentShaderSrc((std::istreambuf_iterator<char>(ifs2)), (std::istreambuf_iterator<char>()));

	this->fragmentShaderSrc = fragmentShaderSrc.c_str();


	GLuint programID = glCreateProgram();
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	char const *vertexSrc = this->vertexShaderSrc.c_str();
	char const *fragmentSrc = this->fragmentShaderSrc.c_str();

	glShaderSource(vertexShaderID, 1, &vertexSrc, NULL);
	glCompileShader(vertexShaderID);
	glAttachShader(programID, vertexShaderID);

	glShaderSource(fragmentShaderID, 1, &fragmentSrc, NULL);
	glCompileShader(fragmentShaderID);
	glAttachShader(programID, fragmentShaderID);

	glLinkProgram(programID);	

	this->shaderProgram = programID;

}
