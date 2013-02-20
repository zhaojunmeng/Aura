/*
 * MAOFactory.cpp
 *
 *  Created on: 20/02/2011
 *      Author: cesar
 */

#include <Factories/MAOFactory.h>

MAOFactory::MAOFactory() {
	_vectorMAO = std::vector<MAO*>();
	_vectorMAOPositionator3D = std::vector<MAOPositionator3D*>();
	_vectorMAOMark = std::vector<MAOMark*>();
	_vectorMAOMarksGroup = std::vector<MAOMarksGroup*>();
	_vectorMAORenderable3D = std::vector<MAORenderable3D*>();

}

/* ADDS */
MAOMark& MAOFactory::addMAOMark(std::string name,const boost::filesystem::path& path,
		const float& size) {
	if (!checkMAOName(name))
		throw "MAO name already exists: " + name;

	MAOMark* mark = new MAOMark(name, path, size);
	_vectorMAO.push_back(mark);
	_vectorMAOPositionator3D.push_back(mark);
	_vectorMAOMark.push_back(mark);

	TrackingMethodFactory::getInstance()->getTrackingMethodARTK().addMAOMark(
			*mark);

	return *mark;

}

MAOMarksGroup& MAOFactory::addMAOMarksGroup(std::string name) {
	if (!checkMAOName(name))
		throw "MAO name already exists: " + name;

	MAOMarksGroup* marksGroup = new MAOMarksGroup(name);
	_vectorMAO.push_back(marksGroup);
	_vectorMAOPositionator3D.push_back(marksGroup);
	_vectorMAOMarksGroup.push_back(marksGroup);

	TrackingMethodFactory::getInstance()->getTrackingMethodARTK().addMAOMarksGroup(
			*marksGroup);

	return *marksGroup;

}

MAORenderable2DText& MAOFactory::addMAORenderable2DText(std::string name,
		const boost::filesystem::path& fontPath, const int& ptSize, const std::string& text,
		const int& x, const int& y, const int& style) {
	if (!checkMAOName(name))
		throw "MAO name already exists: " + name;

	MAORenderable2DText* mao = new MAORenderable2DText(name, fontPath, ptSize,
			text, x, y, style);
	_vectorMAO.push_back(mao);
	_vectorMAORenderable2D.push_back(mao);

	return *mao;
}

MAORenderable2DImage& MAOFactory::addMAORenderable2DImage(std::string name,
		const boost::filesystem::path& filePath, const int& x, const int& y,
		const int& width, const int& height) {
	if (!checkMAOName(name))
		throw "MAO name already exists: " + name;

	MAORenderable2DImage* mao = new MAORenderable2DImage(name, filePath, x, y,
			width, height);
	_vectorMAO.push_back(mao);
	_vectorMAORenderable2D.push_back(mao);

	return *mao;
}

MAORenderable3DLine& MAOFactory::addMAORenderable3DLine(std::string name,
		const float& size, int r, int g, int b) {
	if (!checkMAOName(name))
		throw "MAO name already exists: " + name;

	MAORenderable3DLine* line = new MAORenderable3DLine(name, size, r, g, b);
	_vectorMAO.push_back(line);
	_vectorMAOPositionator3D.push_back(line);
	_vectorMAORenderable3D.push_back(line);

	return *line;
}

MAORenderable3DLine& MAOFactory::addMAORenderable3DLine(std::string name,
		const float& size, int r, int g, int b, std::string& nMao1,
		std::string& nMao2) {
	if (!checkMAOName(name))
		throw "MAO name already exists: " + name;

	MAOPositionator3D& mao1 = getMAOPositionator3D(nMao1);
	MAOPositionator3D& mao2 = getMAOPositionator3D(nMao2);

	MAORenderable3DLine* line = new MAORenderable3DLine(name, size, r, g, b,
			mao1, mao2);
	_vectorMAO.push_back(line);
	_vectorMAOPositionator3D.push_back(line);
	_vectorMAORenderable3D.push_back(line);

	return *line;
}

MAORenderable3DModel& MAOFactory::addMAORenderable3DModel(std::string name,
		const float& size, const boost::filesystem::path& file, const std::string& nref) {
	if (!checkMAOName(name))
		throw "MAO name already exists: " + name;

	MAORenderable3DModel* model = new MAORenderable3DModel(name, file, size);

	Parser *parser = NULL;

	// Get the file format
	std::string format = file.extension().string();
	std::cout<<"Format: "<<format<<std::endl;

	if (format == ".orj") {
		Logger::getInstance()->out("Recognized file format " + format);
		parser = ParserOrej::getInstance();
	} else if (format == ".obj") {
		Logger::getInstance()->out("Recognized file format " + format);
		parser = ParserObj::getInstance();
	}else if (format == ".3ds") {
		Logger::getInstance()->out("Recognized file format " + format);
		parser = Parser3ds::getInstance();
	}else {
		Logger::getInstance()->error(
				"MAORenderable3DModel: unrecognized file format of: " + file.generic_string());
		exit(-1);
	}

	parser->loadModel(file, *model);

	_vectorMAO.push_back(model);
	_vectorMAOPositionator3D.push_back(model);
	_vectorMAORenderable3D.push_back(model);

	if (nref != "Null") {
		MAOPositionator3D& ref = getMAOPositionator3D(nref);
		model->setGlobalReference(ref);
	} else {
		Logger::getInstance()->out(
				"The MAO is a Class MAO (not instanciated one)!: " + name);
	}

	return *model;
}

MAORenderable3DPath& MAOFactory::addMAORenderable3DPath(std::string name,
		const float& size, int r, int g, int b, std::string& nref) {
	if (!checkMAOName(name))
		throw "MAO name already exists: " + name;

	MAORenderable3DPath* path = new MAORenderable3DPath(name, size, r, g, b);
	_vectorMAO.push_back(path);
	_vectorMAOPositionator3D.push_back(path);
	_vectorMAORenderable3D.push_back(path);

	if (nref != "Null") {
		MAOPositionator3D& ref = getMAOPositionator3D(nref);
		path->setGlobalReference(ref);
	} else {
		Logger::getInstance()->out(
				"The MAO is a Class MAO (not instanciated one)!: " + name);
	}

	return *path;
}

/** INSTANTIATED **/
/*If time is -1, the MAO lives forever ;) */
void MAOFactory::addInstMAORenderable3D(MAORenderable3D& mao,
		int timeToExpire) {

	mao.setTimeToExpire(timeToExpire);

	_vectorInstMAORenderable3D.push_back(&mao);
}

/* GETTERS */
MAO& MAOFactory::getMAO(std::string name) {
	for (unsigned int i = 0; i < _vectorMAO.size(); i++) {
		if (name == _vectorMAO.at(i)->getName()) {
			return *_vectorMAO.at(i);
		}
	}
	Logger::getInstance()->error("Not found the MAO " + name);
	Logger::getInstance()->warning(
			"Maybe the MAO is not the proper type for some MLB?");
	throw "MAO not found!";
}

MAOPositionator3D& MAOFactory::getMAOPositionator3D(std::string name) {
	for (unsigned int i = 0; i < _vectorMAOPositionator3D.size(); i++) {
		if (name == _vectorMAOPositionator3D.at(i)->getName()) {
			return *_vectorMAOPositionator3D.at(i);
		}
	}
	Logger::getInstance()->error("Not found the MAO " + name);
	Logger::getInstance()->warning(
			"Maybe the MAO is not the proper type for some MLB?");
	throw "MAO not found!";

}

MAOMark& MAOFactory::getMAOMark(std::string name) {
	for (unsigned int i = 0; i < _vectorMAOMark.size(); i++) {
		if (name == _vectorMAOMark.at(i)->getName()) {
			return *_vectorMAOMark.at(i);
		}
	}
	Logger::getInstance()->error("Not found the MAO " + name);
	Logger::getInstance()->warning(
			"Maybe the MAO is not the proper type for some MLB?");
	throw "MAO not found!";
}

MAOMarksGroup& MAOFactory::getMAOMarksGroup(std::string name) {
	for (unsigned int i = 0; i < _vectorMAOMarksGroup.size(); i++) {
		if (name == _vectorMAOMarksGroup.at(i)->getName()) {
			return *_vectorMAOMarksGroup.at(i);
		}
	}
	Logger::getInstance()->error("Not found the MAO " + name);
	Logger::getInstance()->warning(
			"Maybe the MAO is not the proper type for some MLB?");
	throw "MAO not found!";
}

MAORenderable3D& MAOFactory::getMAORenderable3D(std::string name) {
	for (unsigned int i = 0; i < _vectorMAORenderable3D.size(); i++) {
		if (name == _vectorMAORenderable3D.at(i)->getName()) {
			return *_vectorMAORenderable3D.at(i);
		}
	}
	//Logger::getInstance()->error("Not found the MAO " + name);
	Logger::getInstance()->warning(
			"Maybe the MAO is not the proper type for some MLB?");
	throw "MAO not found!";
}

MAORenderable2D& MAOFactory::getMAORenderable2D(std::string name) {
	for (unsigned int i = 0; i < _vectorMAORenderable2D.size(); i++) {
		if (name == _vectorMAORenderable2D.at(i)->getName()) {
			return *_vectorMAORenderable2D.at(i);
		}
	}
	Logger::getInstance()->error("Not found the MAO " + name);
	Logger::getInstance()->warning(
			"Maybe the MAO is not the proper type for some MLB?");
	throw "MAO not found!";
}

std::vector<MAORenderable3D*>& MAOFactory::getVectorMAORenderable3D() {
	return _vectorMAORenderable3D;
}

std::vector<MAORenderable2D*>& MAOFactory::getVectorMAORenderable2D() {
	return _vectorMAORenderable2D;
}

std::vector<MAOPositionator3D*>& MAOFactory::getVectorMAOPositionator3D() {
	return _vectorMAOPositionator3D;
}

std::vector<MAORenderable3D*>& MAOFactory::getVectorInstMAORenderable3D() {
	return _vectorInstMAORenderable3D;
}

MAOProperty& MAOFactory::findProperty(const std::string& maoName,
		const std::string& propertyName) {

	for (unsigned int i = 0; i < _vectorMAO.size(); i++) {
		MAO* m = _vectorMAO.at(i);
		if (m->getName() == maoName) {
			MAOProperty& p = m->getProperty(propertyName);
			return p;
		}
	}

	throw "Property in " + maoName + " does not exist: " + propertyName;
}

/* PRIVATE METHODS */
bool MAOFactory::checkMAOName(std::string name) {
	for (unsigned int i = 0; i < _vectorMAO.size(); i++) {
		if (name == _vectorMAO.at(i)->getName()) {
			Logger::getInstance()->error(
					"The name " + name + " already exists!");
			return false;
		}
	}

	return true;
}

MAOFactory::~MAOFactory() {
	for (unsigned int i = 0; i < _vectorMAO.size(); i++)
		delete _vectorMAO.at(i);

	for (unsigned int i = 0; i < _vectorInstMAORenderable3D.size(); i++)
		delete _vectorInstMAORenderable3D.at(i);

}
