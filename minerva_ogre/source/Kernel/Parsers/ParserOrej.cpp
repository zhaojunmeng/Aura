/*
 * ParserOrej.cpp
 *
 *  Created on: 02/04/2011
 *      Author: cesar
 */

#include <Kernel/Parsers/ParserOrej.h>

using namespace std;

ParserOrej::ParserOrej() {
}

void ParserOrej::loadModel(const boost::filesystem::path& file,
		MAORenderable3DModel& model) {

	model._file = file;

	_loadTexture(file, model);
	_loadGeometry(file, model);
}

void ParserOrej::_loadTexture(const boost::filesystem::path& file,
		MAORenderable3DModel& model) {

	MAOMaterial mat;

	// Compatible formats
	string formats[] = { string(".ppm"), string(".tga"), string(".png"), string(
			".jpg") };

	// Get the file format
	boost::filesystem::path fileTex(file);


	// Formats supported
	for (int i = 0; i < 4; i++) {
		fileTex.replace_extension(formats[i]);
		mat.texPath = fileTex;
		if (_loadResourceToMaterial(mat))
			break;
	}

	model._materials.push_back(mat);
}

void ParserOrej::_loadGeometry(const boost::filesystem::path& file,
		MAORenderable3DModel& model) {
	std::stringstream stream;
	int nLine = 0;
	char line[256];
	list<MAOFace>::iterator ptrFace;
	bool processingUV = false;

	MAOMesh mesh;
	mesh.materialId = model._materials.size() - 1;

	Resource& r = ResourcesManager::getInstance()->getResource(file);
	stream << string(r.getData());

	if (stream.bad()) {
		Logger::getInstance()->error(
				"Error loading the Modelfile: " + file.string());
		throw "Error loading the OreJ file: " + file.string();
	}

	while (!stream.eof()) {
		stream.getline(line, 256);
		nLine++;

		switch (line[0]) {
		case '#':
			break;
		case 'f': {
			MAOFace f;
			int v1, v2, v3;

			sscanf(&line[2], "%d %d %d", &v1, &v2, &v3);

			if (v1 < 0 || v2 < 0 || v3 < 0) {
				Logger::getInstance()->error(
						"Format error in OreJ! Line: " + nLine);
				throw "Format error in OreJ! Line: " + nLine;
			}

			f.vertex[0].x = mesh.vertex[v1 -1].x;
			f.vertex[0].y = mesh.vertex[v1 -1].y;
			f.vertex[0].z = mesh.vertex[v1 -1].z;

			f.vertex[1].x = mesh.vertex[v2 -1].x;
			f.vertex[1].y = mesh.vertex[v2 -1].y;
			f.vertex[1].z = mesh.vertex[v2 -1].z;

			f.vertex[2].x = mesh.vertex[v3 -1].x;
			f.vertex[2].y = mesh.vertex[v3 -1].y;
			f.vertex[2].z = mesh.vertex[v3 -1].z;

			mesh.faces.push_back(f);

			break;
		}
		case 'v': {
			MAOVector3 v;

			sscanf(&line[2], "%f %f %f", &v.x, &v.y, &v.z);

			v.x *= model.getProperty("size").getValue<float>();
			v.y *= model.getProperty("size").getValue<float>();
			v.z *= model.getProperty("size").getValue<float>();

			mesh.vertex.push_back(v);

			break;
		}
		case 't': {
			if (!processingUV) { // Start assigning textures
				ptrFace = mesh.faces.begin();
				processingUV = true;
			}
			MAOVector2 uv[3];

			sscanf(&line[2], "%f %f %f %f %f %f", &uv[0].x, &uv[0].y, &uv[1].x,
					&uv[1].y, &uv[2].x, &uv[2].y);

			ptrFace->uv[0].x = uv[2].x;
			ptrFace->uv[0].y = uv[2].y;
			ptrFace->uv[1].x = uv[1].x;
			ptrFace->uv[1].y = uv[1].y;
			ptrFace->uv[2].x = uv[0].x;
			ptrFace->uv[2].y = uv[0].y;

			ptrFace++;

			break;
		}
		case 'm': {

			float* m = new float[16];
			sscanf(&line[2], "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",
					&m[0], &m[1], &m[2], &m[3], &m[4], &m[5], &m[6], &m[7],
					&m[8], &m[9], &m[10], &m[11], &m[12], &m[13], &m[14],
					&m[15]);
			mesh.animMatrix.push_back(m);

			break;
		}
		default:
			break;
		}
	}

	model._meshes.push_back(mesh);

	_generateCallList(model);
}

ParserOrej::~ParserOrej() {
}
