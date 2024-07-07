#ifndef DETECT_H
#define DETECT_H

#include "File.h"
#include "DRM.h"

#include <fstream>
#include <vector>

struct Section;

//Detects specific sections and returns an extension
class SectionDetect
{
public:
	virtual char* GetExtension() = 0;
	virtual bool Detect(std::ifstream& ifs, Section* section) = 0;

	//Get the extension for a section
	static char* GetExtension(std::ifstream& ifs, Section* section);

private:
	static std::vector<SectionDetect*> s_detections;
};

//Detects a section with the Model structure
class ModelDetect : public SectionDetect
{
public:
	char* GetExtension()
	{
		return ".tr7aemesh";
	}

	bool Detect(std::ifstream& ifs, Section* section)
	{
		return ReadUInt(ifs) == 0x4C20453;
	}
};

//Detects a cloth section
class ClothDetect : public SectionDetect
{
public:
	char* GetExtension()
	{
		return ".cloth";
	}

	bool Detect(std::ifstream& ifs, Section* section)
	{
		return ReadUInt(ifs) == 8;
	}
};

//Detects a next generation mesh section
class MeshDetect : public SectionDetect
{
public:
	char* GetExtension()
	{
		return ".tr7mesh";
	}

	bool Detect(std::ifstream& ifs, Section* section)
	{
		//Skip past data header
		ifs.seekg(16, SEEK_CUR);

		return section->ucType == DTPDATA && ReadUInt(ifs) == '9DCP';
	}
};

//Detects the object section (first section)
class ObjectDetect : public SectionDetect
{
public:
	char* GetExtension()
	{
		return ".obj";
	}

	bool Detect(std::ifstream& ifs, Section* section)
	{
		ifs.seekg(168, SEEK_CUR);

		//First section with not the level version number
		return section->uiIndex == 0 && section->ucType == GENERAL && ReadUInt(ifs) != 0x4C204BB;
	}
};

//Detects the level section (first section)
class LevelDetect : public SectionDetect
{
	char* GetExtension()
	{
		return ".level";
	}

	bool Detect(std::ifstream& ifs, Section* section)
	{
		//Seek to version number
		ifs.seekg(168, SEEK_CUR);

		return section->uiIndex == 0 && section->ucType == GENERAL && ReadUInt(ifs) == 0x4C204BB;
	}
};

//Detects the script executable in Legend
class ScriptDetect : public SectionDetect
{
	char* GetExtension()
	{
		return ".dll";
	}

	bool Detect(std::ifstream& ifs, Section* section)
	{
		return ReadUShort(ifs) == 'ZM';
	}
};

#endif