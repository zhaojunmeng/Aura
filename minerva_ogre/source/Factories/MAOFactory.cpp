/*
 * MAOFactory.cpp
 *
 *  Created on: 20/02/2011
 *      Author: cesar
 */

#include <Factories/MAOFactory.h>

using namespace std;

MAOFactory::MAOFactory() {
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



MAORenderable3DModel& MAOFactory::addMAORenderable3DModel(std::string name,
		const float& size, const boost::filesystem::path& file, const std::string& nref) {
	if (!checkMAOName(name))
		throw "MAO name already exists: " + name;

	cout<<"Adding mao renderable: "<<name<<endl;
	MAORenderable3DModel* model = new MAORenderable3DModel(name, file, size);


	if (nref != "Null") {
		MAOPositionator3D& ref = getMAOPositionator3D(nref);
		model->setGlobalReference(ref);
	} else {
		Logger::getInstance()->out(
				"The MAO is a Class MAO (not instanciated one)!: " + name);
	}

	_vectorMAO.push_back(model);
	_vectorMAORenderable3D.push_back(model);

	return *model;
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
