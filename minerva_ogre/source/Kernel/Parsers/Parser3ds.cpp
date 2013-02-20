/*
 * Parser3ds.cpp
 *
 *  Created on: 14/02/2013
 *      Author: cesar
 */

#include <Kernel/Parsers/Parser3ds.h>

using namespace std;

Parser3ds::Parser3ds() {
}

void Parser3ds::loadModel(const boost::filesystem::path& file,
		MAORenderable3DModel& model) {

	Lib3dsFile *file3ds;
	file3ds = _load3dsFile(file);

	/* Load Textures / Materials */
	for (Lib3dsMaterial* mat = file3ds->materials; mat != NULL; mat =
			mat->next) {
		MAOMaterial mmat;

		mmat.name = std::string(mat->name);

		mmat.ambient.x = mat->ambient[0];
		mmat.ambient.y = mat->ambient[1];
		mmat.ambient.z = mat->ambient[2];

		mmat.diffuse.x = mat->diffuse[0];
		mmat.diffuse.y = mat->diffuse[1];
		mmat.diffuse.z = mat->diffuse[2];

		mmat.specular.x = mat->specular[0];
		mmat.specular.y = mat->specular[1];
		mmat.specular.z = mat->specular[2];

		mmat.transparency = mat->transparency;

		boost::filesystem::path pwd = file.parent_path();
		boost::filesystem::path texPath = pwd /= mat->texture1_map.name;

		if (string(mat->texture1_map.name) == "") {
			Logger::getInstance()->warning(
					"[Parser3ds] Material " + string(mat->name)
							+ " does not have texture associated.");
		} else {

			mmat.texPath = texPath;
			_loadResourceToMaterial(mmat);

		}

		model._materials.push_back(mmat);
	}

	/* Load Geometry */
	for (Lib3dsMesh* m = file3ds->meshes; m != NULL; m = m->next) {
		MAOMesh mmesh;

		/* It is necessary to calculate the normals */
		Lib3dsVector normals[m->faces * 3];
		lib3ds_mesh_calculate_normals(m, normals);

		/* Vertex list */
		//cout << "Vertex: " << m->points << endl;
		for (unsigned int i = 0; i < m->points; i++) {
			Lib3dsPoint v = m->pointL[i];

			MAOVector3 mv(v.pos[0], v.pos[1], v.pos[2]);

			//cout << "Vertex[" << i << "]: " << mv.x << "," << mv.y << ","
//					<< mv.z << endl;

			mv.x *= model.getProperty("size").getValue<float>();
			mv.y *= model.getProperty("size").getValue<float>();
			mv.z *= model.getProperty("size").getValue<float>();

			mmesh.vertex.push_back(mv);
		}

		/* UV list */
		//cout << "UV: " << m->texels << endl;
		for (unsigned int i = 0; i < m->texels; i++) {
			float u = m->texelL[i][0];
			float v = m->texelL[i][1];

			//cout << "UV[" << i << "]: " << u << "," << v << endl;
			MAOVector2 uv(u, v);
			mmesh.uv.push_back(uv);
		}

		/* Normals */
		//cout << "Faces: " << m->faces << endl;
		for (unsigned int i = 0; i < m->faces; i++) {
			float nx = normals[3 * i][0];
			float ny = normals[3 * i][1];
			float nz = normals[3 * i][2];

			MAOVector3 n(nx, ny, nz);
			mmesh.normals.push_back(n);
		}

		/* Faces list */
		for (unsigned int i = 0; i < m->faces; i++) {
			Lib3dsFace f = m->faceL[i];

			MAOFace mf;
			//cout << "== Face! [" << i << "]==" << endl;
			for (int j = 0; j < 3; j++) {
				mf.vertex[j].x = mmesh.vertex.at(f.points[j]).x;
				mf.vertex[j].y = mmesh.vertex.at(f.points[j]).y;
				mf.vertex[j].z = mmesh.vertex.at(f.points[j]).z;

				if (mmesh.uv.size() > 0) {
					mf.uv[j].x = mmesh.uv.at(f.points[j]).x;
					mf.uv[j].y = mmesh.uv.at(f.points[j]).y;
				}

				mf.normal[j].x = normals[i * 3 + j][0];
				mf.normal[j].y = normals[i * 3 + j][1];
				mf.normal[j].z = normals[i * 3 + j][2];
			}

			/* Load frames */

			mmesh.faces.push_back(mf);
		}

		/* Assign the material */
		std::string materialName = std::string(m->faceL[0].material);

		// Look for the material (This should be done by a Material Factory! TODO)
		int matId = -1;
		for (unsigned int i = 0; i < model._materials.size(); i++) {
			if (model._materials[i].name == materialName) {
				matId = i;
				break;
			}
		}

		if (matId == -1) {
			Logger::getInstance()->error(
					"[Parser3ds] Material not found for mesh!");
		} else {
			mmesh.materialId = matId;
		}

		model._meshes.push_back(mmesh);
	}

	/* Load to OpenGL :) */
	_generateCallList(model);

	// Dont forget to free it
	lib3ds_file_free(file3ds);
}

Lib3dsFile* Parser3ds::_load3dsFile(const boost::filesystem::path& file) {
	Lib3dsFile *file3ds;
	Lib3dsIo *io;

	Resource& r = ResourcesManager::getInstance()->getResource(file);

	file3ds = lib3ds_file_new();
	if (!file3ds) {
		Logger::getInstance()->error(
				"[Parser3ds] Error loading the 3ds file "
						+ file.generic_string());
		exit(-1);
	}

	std::istringstream stream(string(r.getData(), r.getSize()));

	io = lib3ds_io_new(&stream, Parser3ds::_IoErrorFunc, _IoSeekFunc,
			_IoTellFunc, _IoReadFunc, NULL);

	if (!io) {
		lib3ds_file_free(file3ds);
		Logger::getInstance()->error(
				"[Parser3ds] Error creating the 3ds buffer "
						+ file.generic_string());
		exit(-1);
	}

	if (!lib3ds_file_read(file3ds, io)) {
		delete file3ds;
		lib3ds_io_free(io);
		Logger::getInstance()->error(
				"[Parser3ds] Error reading the 3ds buffer "
						+ file.generic_string());
		exit(-1);
	}

	lib3ds_io_free(io);

	return file3ds;
}

Lib3dsBool Parser3ds::_IoErrorFunc(void *self) {
	stringstream *s = (stringstream*) self;
	return s->bad();
}

long Parser3ds::_IoSeekFunc(void *self, long offset, Lib3dsIoSeek origin) {
	stringstream *s = (stringstream*) self;
	ios_base::seekdir o;
	switch (origin) {
	case LIB3DS_SEEK_SET:
		o = ios_base::beg;
		break;
	case LIB3DS_SEEK_CUR:
		o = ios_base::cur;
		break;
	case LIB3DS_SEEK_END:
		o = ios_base::end;
		break;
	default:
		Logger::getInstance()->error("[Parser3ds] Error in SEEK function");
		return (0);
	}
	s->seekg(offset, o);
	return s->bad();
}

long Parser3ds::_IoTellFunc(void *self) {
	stringstream *s = (stringstream*) self;
	return s->tellg();
}

size_t Parser3ds::_IoReadFunc(void *self, void *buffer, size_t size) {
	stringstream *s = (stringstream*) self;
	s->read((char*) buffer, size);
	return s->gcount();
}

Parser3ds::~Parser3ds() {
}

