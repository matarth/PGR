#include "Scene.h"


Scene::Scene(void)
{
	this->activeCamera = NULL;
	this->terrain = NULL;
	this->skybox = NULL;
}


Scene::~Scene(void)
{
}

void Scene::drawScene(){

	glEnable(GL_DEPTH_TEST);
	glClearStencil(0);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	if(this->activeCamera == NULL){
		printf("ERROR: Scene has no active camera, therefore cannot be drawn.\n");
		return;
	}

	// **************************** drawing cycle *********************************

	glDisable(GL_STENCIL_TEST);
	if(this->skybox != NULL){
		this->drawSkyBox();
	}

	if(this->terrain != NULL){
		this->drawObject(this->terrain);
	}

	glEnable(GL_STENCIL_TEST);
	for(NewModel *model: this->models){
		glStencilFunc(GL_ALWAYS, model->modelID, 1);
		this->drawObject(model);
	}

	glutSwapBuffers();

}

void Scene::setActiveCamera(NewCamera *cam){
	this->activeCamera = cam;
}

void Scene::drawObject(NewModel *model){

	glUseProgram(model->shaderProgram);

	glm::mat4 pvm;
	glm::mat4 modelMatrix = model->getModelMatrix();
	glm::mat4 projectionMatrix = this->activeCamera->getProjectionMatrix();
	glm::mat4 viewMatrix = this->activeCamera->getViewMatrix();

	Light* spotLight = this->spotLights.front();
	Light* directionalLight = this->directionalLights.front();
	Light* pointLight = this->pointLights.front();

	pvm = projectionMatrix * viewMatrix * modelMatrix;


	GLuint matrixID = glGetUniformLocation(model->shaderProgram, "pvm");
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &(pvm[0][0]));

	GLuint colorVecLoc = glGetUniformLocation(model->shaderProgram, "barva");
	glUniform3f(colorVecLoc, model->color.x, model->color.y, model->color.z);

	glm::mat4 transformMatrix = this->activeCamera->getViewMatrix() * model->getModelMatrix();
	transformMatrix = glm::inverse(transformMatrix);
	transformMatrix = glm::transpose(transformMatrix);

	GLuint normalTranformationMatLoc = glGetUniformLocation(model->shaderProgram, "normalTransformationMat");
	glUniformMatrix4fv(normalTranformationMatLoc, 1,GL_FALSE, &(transformMatrix[0][0]));

	GLuint texTransformLoc = glGetUniformLocation(model->shaderProgram, "texTransform");
	glUniform2f(texTransformLoc, model->textureMovement.x, model->textureMovement.y);
	
	// ********** SPOT LIGHT **************

	GLuint spotLightIntensityLoc = glGetUniformLocation(model->shaderProgram, "spotIntensity");
	glUniform1f(spotLightIntensityLoc, spotLight->intensity);

	GLuint spotLightAngleLoc = glGetUniformLocation(model->shaderProgram, "spotAngle");
	glUniform1f(spotLightAngleLoc, spotLight->spotLightAngle);

	GLuint spotPositionLoc = glGetUniformLocation(model->shaderProgram, "spotPosition");
	glUniform3f(spotPositionLoc, spotLight->position.x, spotLight->position.y, spotLight->position.z);

	glm::vec3 lightDirection = spotLight->getDirection();
	GLuint spotLightDirectionLoc = glGetUniformLocation(model->shaderProgram, "spotDirection");
	glUniform3f(spotLightDirectionLoc, lightDirection.x, lightDirection.y, lightDirection.z);

	GLuint spotLightAmbientLoc = glGetUniformLocation(model->shaderProgram, "spotAmbient");
	glUniform3f(spotLightAmbientLoc, spotLight->ambient.x, spotLight->ambient.y, spotLight->ambient.z);

	GLuint spotLightSpecularLoc = glGetUniformLocation(model->shaderProgram, "spotSpecular");
	glUniform3f(spotLightSpecularLoc, spotLight->specular.x, spotLight->specular.y, spotLight->specular.z);

	GLuint spotLightDiffuseLoc = glGetUniformLocation(model->shaderProgram, "spotDiffuse");
	glUniform3f(spotLightDiffuseLoc, spotLight->diffuse.x, spotLight->diffuse.y, spotLight->diffuse.z);

	// *********** POINT LIGHT *******************

	GLuint pointLightIntensityLoc = glGetUniformLocation(model->shaderProgram, "pointIntensity");
	glUniform1f(pointLightIntensityLoc, pointLight->intensity);

	GLuint pointLightPositionLoc = glGetUniformLocation(model->shaderProgram, "pointPosition");
	glUniform3f(pointLightPositionLoc, pointLight->position.x, pointLight->position.y, pointLight->position.z);

	lightDirection = pointLight->getDirection();
	GLuint pointLightDirectionLoc = glGetUniformLocation(model->shaderProgram, "pointDirection");
	glUniform3f(pointLightDirectionLoc, lightDirection.x, lightDirection.y, lightDirection.z);

	GLuint pointLightAmbientLoc = glGetUniformLocation(model->shaderProgram, "pointAmbient");
	glUniform3f(pointLightAmbientLoc, pointLight->ambient.x, pointLight->ambient.y, pointLight->ambient.z);

	GLuint pointLightSpecularLoc = glGetUniformLocation(model->shaderProgram, "pointSpecular");
	glUniform3f(pointLightSpecularLoc, pointLight->specular.x, pointLight->specular.y, pointLight->specular.z);

	GLuint pointLightDiffuseLoc = glGetUniformLocation(model->shaderProgram, "pointDiffuse");
	glUniform3f(pointLightDiffuseLoc, pointLight->diffuse.x, pointLight->diffuse.y, spotLight->diffuse.z);

	// *************** DIRECTIONAL LIGHT *******************

	GLuint directionalLightIntensityLoc = glGetUniformLocation(model->shaderProgram, "directionalIntensity");
	glUniform1f(directionalLightIntensityLoc, directionalLight->intensity);

	lightDirection = directionalLight->position;
	GLuint directionalLightDirectionLoc = glGetUniformLocation(model->shaderProgram, "directionalDirection");
	glUniform3f(directionalLightDirectionLoc, lightDirection.x, lightDirection.y, lightDirection.z);

	GLuint directionalLightAmbientLoc = glGetUniformLocation(model->shaderProgram, "directionalAmbient");
	glUniform3f(directionalLightAmbientLoc, directionalLight->ambient.x, directionalLight->ambient.y, directionalLight->ambient.z);

	GLuint directionalLightSpecularLoc = glGetUniformLocation(model->shaderProgram, "directionalSpecular");
	glUniform3f(directionalLightSpecularLoc, directionalLight->specular.x, directionalLight->specular.y, directionalLight->specular.z);

	GLuint directionalLightDiffuseLoc = glGetUniformLocation(model->shaderProgram, "directionalDiffuse");
	glUniform3f(directionalLightDiffuseLoc, directionalLight->diffuse.x, directionalLight->diffuse.y, spotLight->diffuse.z);



	GLuint useTextureLocation = glGetUniformLocation(model->shaderProgram, "useTexture");
	if(model->useTexture){
		model->texSamplerLocation = glGetUniformBlockIndex(model->shaderProgram, "texSampler");
		glUniform1i(model->texSamplerLocation, 0);
		glBindTexture(GL_TEXTURE_2D, model->texture);
		glUniform1i(useTextureLocation, 1);
	}
	else{
		glUniform1i(useTextureLocation, 0);
	}

	GLuint cameraWorldPosLocation = glGetUniformLocation(model->shaderProgram, "cameraWorldPosition");
	glUniform3f(cameraWorldPosLocation, activeCamera->position.x, activeCamera->position.y, activeCamera->position.z);

	GLuint modelMatrixLoc = glGetUniformLocation(model->shaderProgram, "modelMatrix");
	glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &(modelMatrix[0][0]));

	GLuint viewMatrixLoc = glGetUniformLocation(model->shaderProgram, "viewMatrix");
	glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, &(viewMatrix[0][0]));

	GLuint projectionMatrixLoc = glGetUniformLocation(model->shaderProgram, "projectionMatrix");
	glUniformMatrix4fv(projectionMatrixLoc, 1, GL_FALSE, &(projectionMatrix[0][0]));

	GLuint materialAmbientLoc = glGetUniformLocation(model->shaderProgram, "materialAmbient");
	glUniform3f(materialAmbientLoc, model->materialAmbient.x, model->materialAmbient.y, model->materialAmbient.z);

	GLuint materialDiffuseLoc = glGetUniformLocation(model->shaderProgram, "materialDiffuse");
	glUniform3f(materialDiffuseLoc, model->materialDiffuse.x, model->materialDiffuse.y, model->materialDiffuse.z);

	GLuint materialSpecularLoc = glGetUniformLocation(model->shaderProgram, "materialSpecular");
	glUniform3f(materialSpecularLoc, model->materialSpecular.x, model->materialSpecular.y, model->materialSpecular.z);

	GLuint materialShineLoc = glGetUniformLocation(model->shaderProgram, "materialShininess");
	glUniform1f(materialShineLoc, model->materialShininess);


	glBindVertexArray(model->vao);
	//printf("%d %s\n", model->vao, model->dataFile);
	glDrawElements(GL_TRIANGLES, model->numberOfFaces*3, GL_UNSIGNED_INT, (void*)0);

	glBindVertexArray(0);
	glUseProgram(0);

}

void Scene::addModel(NewModel *model){
	model->modelID = this->models.size()+1;
	this->models.push_back(model);
}

NewModel* Scene::getModelById(int modelID){

	for(NewModel* nm: this->models){
		if(nm->modelID == modelID){
			return(nm);
		}
	}
	return(NULL);
}

void Scene::updateAnimations(float time){

	this->checkColisions();
	
	for(Light* l: this->pointLights){
		l->updateAnimation(time);
	}

	for(Light* l: this->directionalLights){
		l->updateAnimation(time);
	}

	for(Light* l: this->spotLights){
		l->updateAnimation(time);
	}

	activeCamera->updateAnimation(time);

	for(SceneObject* so: this->models){
		so->updateAnimation(time);
	}
}


void Scene::drawSkyBox(){

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->texture);

	// crate view rotation matrix by using view matrix with cleared translation
	glm::mat4 viewRotation = activeCamera->getViewMatrix();
	viewRotation[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	// vertex shader will translate screen space coordinates (NDC) using inverse PV matrix
	glm::mat4 invPV = glm::inverse(activeCamera->getProjectionMatrix() * viewRotation);
	// draw "skybox" rendering 2 triangles covering far plane
	glBindVertexArray(skybox->vao);
	glUseProgram(skybox->shaderProgram);
	GLint invPVLoc = glGetUniformLocation(skybox->shaderProgram, "invPV");
	glUniformMatrix4fv(invPVLoc, 1, GL_FALSE, glm::value_ptr(invPV));
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindVertexArray(0);
	glUseProgram(0);
	//glutSwapBuffers();

}


void Scene::checkColisions(){

	for(NewModel* m: this->models){

		if(abs(m->position.x > 50) || abs(m->position.y > 50) || abs(m->position.z > 50)){
			m->reset();
		}

		for(NewModel* n: this->models){
			if(m != n){
				if(glm::distance(m->position, n->position) < 1.0f){
//					printf("KOLIZE\n");
					m->color = glm::vec3(1.0f, 0.0f, 0.0f);
				}
			}
		}
	}

}


void Scene::addDirectionalLight(Light* l){
	this->directionalLights.push_back(l);
}

void Scene::addPointLight(Light* l){
	this->pointLights.push_back(l);
}

void Scene::addSpotLight(Light* l){
	this->spotLights.push_back(l);
}