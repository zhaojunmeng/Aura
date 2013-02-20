/*
 * Parser.cpp
 *
 *  Created on: 04/02/2013
 *      Author: cesar
 */

#include <Kernel/Parsers/Parser.h>

using namespace std;

Parser::Parser() {
}

bool Parser::_loadResourceToMaterial(MAOMaterial& mat) {
	SDL_Surface* img = NULL;
	SDL_RWops *rw = NULL;
	GLenum textureFormat;

	try {
		Resource& r = ResourcesManager::getInstance()->getResource(mat.texPath);

		rw = SDL_RWFromMem((void*) r.getData(), r.getSize());
		img = IMG_Load_RW(rw, 1);
	} catch (std::string& e) {
		if (img != NULL)
			SDL_FreeSurface(img);
		return false;
	}

	if (img == NULL) {
		Logger::getInstance()->error(
				"Error Loading the texture: " + mat.texPath.generic_string());
		Logger::getInstance()->error(IMG_GetError());
		return false;
	}

	ResourcesManager::getInstance()->addResource(mat.texPath);

	switch (img->format->BytesPerPixel) {
	case 4: //With alpha channel
		if (img->format->Rmask == 0x000000ff) {
			textureFormat = GL_RGBA;
		} else {
			textureFormat = GL_BGRA;
		}
		break;

	case 3: // Without alpha channel
		if (img->format->Rmask == 0x000000ff) {
			textureFormat = GL_RGB;
		} else {
			textureFormat = GL_BGR;
		}
		break;
	default:
		Logger::getInstance()->error(
				"Error determining the texture format. Bytes per pixel: "
						+ img->format->BitsPerPixel);
	}

	// Create the texture id
	glGenTextures(1, &mat.texId);
	mat.texHeight = img->h;

	if (mat.texId == GL_INVALID_OPERATION) {
		Logger::getInstance()->error("Error processing an OreJ texture");
		throw "Error processing an OreJ texture";
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, mat.texId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, img->format->BytesPerPixel, img->w, img->h,
			0, textureFormat, GL_UNSIGNED_BYTE, img->pixels);

	SDL_FreeSurface(img);
	return true;
}

void Parser::_generateCallList(MAORenderable3DModel& model) {

	list<MAOMesh>::iterator meshPtr;
	for (meshPtr = model._meshes.begin(); meshPtr != model._meshes.end();
			++meshPtr) {
		meshPtr->idListMesh = glGenLists(1);
		glNewList(meshPtr->idListMesh, GL_COMPILE);

		/* Here is where is fixed the "Origin problem"
		 * OpenGl uses a bottom-left and Blender uses an upper-left origin!
		 */
		list<MAOFace>::iterator facePtr;
		for (facePtr = meshPtr->faces.begin(); facePtr != meshPtr->faces.end();
				facePtr++) {
			glBegin(GL_TRIANGLES);
			if (meshPtr->materialId != -1){
				glTexCoord2f(facePtr->uv[0].x, model._materials[meshPtr->materialId].texHeight - facePtr->uv[0].y);
			}
			glNormal3f(facePtr->normal[0].x, facePtr->normal[0].y,
					facePtr->normal[0].z);
			glVertex3f(facePtr->vertex[0].x, facePtr->vertex[0].y,
					facePtr->vertex[0].z);

			if (meshPtr->materialId != -1)
				glTexCoord2f(facePtr->uv[1].x,
						model._materials[meshPtr->materialId].texHeight - facePtr->uv[1].y);
			glNormal3f(facePtr->normal[1].x, facePtr->normal[1].y,
					facePtr->normal[1].z);
			glVertex3f(facePtr->vertex[1].x, facePtr->vertex[1].y,
					facePtr->vertex[1].z);

			if (meshPtr->materialId != -1)
				glTexCoord2f(facePtr->uv[2].x,
						model._materials[meshPtr->materialId].texHeight - facePtr->uv[2].y);
			glNormal3f(facePtr->normal[2].x, facePtr->normal[2].y,
					facePtr->normal[2].z);
			glVertex3f(facePtr->vertex[2].x, facePtr->vertex[2].y,
					facePtr->vertex[2].z);

			glEnd();
		}
		glEndList();
	}
}

Parser::~Parser() {
}

