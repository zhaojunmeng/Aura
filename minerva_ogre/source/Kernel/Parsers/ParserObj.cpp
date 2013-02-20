/*
 * ParserObj.cpp
 *
 *  Created on: 14/02/2013
 *      Author: cesar
 */

#include <Kernel/Parsers/ParserObj.h>

using namespace std;

ParserObj::ParserObj() {
}

void ParserObj::loadModel(const boost::filesystem::path& file,
		MAORenderable3DModel& model) {
	model._file = file;

	MAOMesh mesh;

	stringstream streamFile;

	Resource& r = ResourcesManager::getInstance()->getResource(file);
	streamFile << string(r.getData());

	if (streamFile.bad()) {
		Logger::getInstance()->error(
				"Error loading the Modelfile: " + file.string());
		throw "Error loading the Obj file: " + file.string();
	}

	while (!streamFile.eof()) {
		string line;
		getline(streamFile, line);
		stringstream streamLine;
		streamLine << line;

		string symbol;
		streamLine >> symbol;

		if (symbol == "v") { // Vertex
			MAOVector3 v;
			streamLine >> v.x;
			streamLine >> v.y;
			streamLine >> v.z;

			v.x *= model.getProperty("size").getValue<float>();
			v.y *= model.getProperty("size").getValue<float>();
			v.z *= model.getProperty("size").getValue<float>();

			mesh.vertex.push_back(v);
		} else if (symbol == "vt") { // Vertex texture
			MAOVector2 vt;
			streamLine >> vt.x;
			streamLine >> vt.y;

			mesh.uv.push_back(vt);
		} else if (symbol == "vn") { // Vertex normal
			MAOVector3 vn;
			streamLine >> vn.x;
			streamLine >> vn.y;
			streamLine >> vn.z;

			mesh.normals.push_back(vn);
		} else if (symbol == "f") { // Face
			MAOFace f;
			std::string index;

			getline(streamLine, index);
			stringstream streamindex;
			index = index.substr(1); // Removes the first blank

			int v, vt, vn;

			for (int i = 0; i <3 ; i++) {
				int pos = index.find(' ');
				string s = index.substr(0, pos);
				index = index.substr(pos + 1);

				_getFaceIndices(s, v, vt, vn);
				if (v > 0 && v <= mesh.vertex.size()) {
					f.vertex[i].x = mesh.vertex[v -1].x;
					f.vertex[i].y = mesh.vertex[v -1].y;
					f.vertex[i].z = mesh.vertex[v -1].z;
				}
				if (vt > 0 && vt <= mesh.uv.size()) {
					f.uv[i].x = mesh.uv[vt -1].x;
					f.uv[i].y = mesh.uv[vt -1].y;
				}
				if (vn > 0 && vn <= mesh.normals.size()) {
					f.normal[i].x = mesh.normals[vn - 1].x;
					f.normal[i].y = mesh.normals[vn - 1].y;
					f.normal[i].z = mesh.normals[vn - 1].z;
				}
			}

			mesh.faces.push_back(f);
		} else if (symbol == "mtllib") { // Declaring material
			boost::filesystem::path pwd = file.parent_path();

			std::string fname;
			streamLine >> fname;
			while (!streamLine.eof()) {
				string aux;
				streamLine >> aux;
				fname = fname + " " + aux;
			}
			// Deleting final spaces :/
			while(fname.at(fname.length()-1) == ' ') fname = fname.substr(0, fname.length() - 1);

			boost::filesystem::path path = pwd /= fname;

			ResourcesManager::getInstance()->addResource(path); //MTLIBFILE

			MAOMaterial mat;
			model._materials.push_back(mat);
			cout<<"Asignando ID: "<<model._materials.size() - 1;
			mesh.materialId = model._materials.size() - 1;
			_loadTextureFile(path, model._materials[mesh.materialId]);

		} else if (symbol == "usemtl") { // Using material

		} else if (symbol == "#") { // Comment
			/* Ignore it */
		} else {
			Logger::getInstance()->warning(
					"[ParserObj] Symbol not supported: " + symbol);
		}
	}

	//cout<<"Vertex: "<<mesh.vertex.size()<<endl;
	//cout<<"UV: "<<mesh.uv.size()<<endl;
	//cout<<"Faces: "<<mesh.faces.size()<<endl;

	model._meshes.push_back(mesh);

	_generateCallList(model);
}

void ParserObj::_loadTextureFile(const boost::filesystem::path& file,
		MAOMaterial& mat) {
	stringstream streamFile;

	Resource& r = ResourcesManager::getInstance()->getResource(file);
	streamFile << string(r.getData());

	if (streamFile.bad()) {
		Logger::getInstance()->error(
				"Error loading the Material lib file: " + file.string());
		throw "Error loading the Obj file: " + file.string();
	}

	while (!streamFile.eof()) {
		string line;
		getline(streamFile, line);
		stringstream streamLine;
		streamLine << line;

		string symbol;
		streamLine >> symbol;

		if (symbol == "map_Kd") {
			boost::filesystem::path pwd = file.parent_path();

			std::string fname;
			streamLine >> fname;
			while (!streamLine.eof()) {
				string aux;
				streamLine >> aux;
				fname = fname + " " + aux;
			}
			// Deleting final spaces :/
			while(fname.at(fname.length()-1) == ' ') fname = fname.substr(0, fname.length() - 1);

			boost::filesystem::path path = pwd /= fname;

			mat.texPath = path;
			_loadResourceToMaterial(mat);

		} else if (symbol == "#") { // Comment
			/* Ignore it */
		} else {
			Logger::getInstance()->warning(
					"[ParserObj] Symbol not supported: " + symbol);
		}
	}
}

void ParserObj::_getFaceIndices(std::string& line, int& v, int& vt, int& vn) {
	v = vt = vn = -1;
	int pos = 0;

	string number;
	pos = line.find("/");
	number = line.substr(0, pos);
	if (number.length() > 0)
		sscanf(number.c_str(), "%d", &v);
	line = line.substr(pos + 1);

	pos = line.find("/");
	number = line.substr(0, pos);
	if (number.length() > 0)
		sscanf(number.c_str(), "%d", &vt);
	line = line.substr(pos + 1);

	pos = line.find("/");
	number = line.substr(0, pos);
	if (number.length() > 0)
		sscanf(number.c_str(), "%d", &vn);
}

ParserObj::~ParserObj() {
}

