#include "Detect.h"
#include "DRM.h"

//All detections
std::vector<SectionDetect*> SectionDetect::s_detections{
	new ModelDetect(),
	new ClothDetect(),
	new MeshDetect(),
	new ObjectDetect(),
	new LevelDetect(),
	new ScriptDetect()
};

//Detect the file extension for a section
char* SectionDetect::GetExtension(std::ifstream& ifs, Section* section)
{
	for (auto detection : s_detections)
	{
		//Store the current cursor
		std::streampos pos = ifs.tellg();

		//Seek past relocations
		ifs.seekg((section->uiPackedData >> 0x8) * 0x8, SEEK_CUR);

		auto detect = detection->Detect(ifs, section);

		//Seek back
		ifs.seekg(pos);

		if (detect)
		{
			return detection->GetExtension();
		}
	}

	//No extension found
	return nullptr;
}