/*
 * MAOFactory.h
 *
 *  Created on: 20/02/2011
 *      Author: cesar
 */

#ifndef MAOFACTORY_H_
#define MAOFACTORY_H_

#include <string>

#include <Factories/TrackingMethodFactory.h>
#include <Kernel/Logger.h>
#include <Kernel/Singleton.h>
#include <Kernel/Parsers/ParserOrej.h>
#include <Kernel/Parsers/ParserObj.h>
#include <Kernel/Parsers/Parser3ds.h>
#include <MAO/MAOPositionator3D.h>
#include <MAO/MAOMark.h>
#include <MAO/MAOMarksGroup.h>
#include <MAO/MAO.h>
#include <MAO/MAORenderable3D.h>
#include <MAO/MAORenderable3DLine.h>
#include <MAO/MAORenderable2D.h>
#include <MAO/MAORenderable2DText.h>
#include <MAO/MAORenderable2DImage.h>
#include <MAO/MAORenderable3DModel.h>
#include <MAO/MAORenderable3DPath.h>

class MAOFactory: public Singleton<MAOFactory> {
public:
	MAOFactory();
	virtual ~MAOFactory();

	/* Adds */
	MAOMark& addMAOMark(std::string name, const boost::filesystem::path& path,
			const float& size);
	MAOMarksGroup& addMAOMarksGroup(std::string name);
	MAORenderable2DText& addMAORenderable2DText(std::string name,
			const boost::filesystem::path&, const int& ptSize,
			const std::string& text, const int& x = 0, const int& y = 0,
			const int& style = 0);
	MAORenderable2DImage& addMAORenderable2DImage(std::string name,
			const boost::filesystem::path& filePath, const int& x, const int& y,
			const int& width, const int& height);
	MAORenderable3DLine& addMAORenderable3DLine(std::string name,
			const float& size, int r, int g, int b);
	MAORenderable3DLine& addMAORenderable3DLine(std::string name,
			const float& size, int r, int g, int b, std::string& nMao1,
			std::string& nMao2);
	MAORenderable3DModel& addMAORenderable3DModel(std::string name,
			const float& size, const boost::filesystem::path& file, const std::string& nref);
	MAORenderable3DPath& addMAORenderable3DPath(std::string name,
			const float& size, int r, int g, int b, std::string& nref);

	//Instantiated
	void addInstMAORenderable3D(MAORenderable3D& mao, int timeToExpire = -1);

	/* Getters */
	MAO& getMAO(std::string name);
	MAOPositionator3D& getMAOPositionator3D(std::string name);
	MAOMark& getMAOMark(std::string name);
	MAOMarksGroup& getMAOMarksGroup(std::string name);
	MAORenderable3D& getMAORenderable3D(std::string name);
	MAORenderable2D& getMAORenderable2D(std::string name);
	MAOProperty& findProperty(const std::string& maoName, const std::string& propertyName);

	std::vector<MAORenderable3D*>& getVectorMAORenderable3D();
	std::vector<MAORenderable2D*>& getVectorMAORenderable2D();
	std::vector<MAOPositionator3D*>& getVectorMAOPositionator3D();
	std::vector<MAORenderable3D*>& getVectorInstMAORenderable3D();

private:
	/* It checks if the name exists */
	bool checkMAOName(std::string name);

	std::vector<MAO*> _vectorMAO;
	std::vector<MAOPositionator3D*> _vectorMAOPositionator3D;
	std::vector<MAOMark*> _vectorMAOMark;
	std::vector<MAOMarksGroup*> _vectorMAOMarksGroup;
	std::vector<MAORenderable3D*> _vectorMAORenderable3D;
	std::vector<MAORenderable2D*> _vectorMAORenderable2D;
	std::vector<MAORenderable3D*> _vectorInstMAORenderable3D;
};

#endif /* MAOFACTORY_H_ */
