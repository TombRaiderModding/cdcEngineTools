#ifndef DRM_H
#define DRM_H

//Includes
#include <vector>

//Constants
const unsigned int DRM_MAX_SECTIONS = 16777215;

#define REPACK_MODE (1)

#if (TR7 || TRAE)
	#define DRM_VERSION (14)
#elif TR8
	#define DRM_VERSION (19)
#elif TRAS
	#define DRM_VERSION (21)
#else
	#error "Unsupported Game!"
#endif

struct Section
{
	unsigned int uiSize;
	unsigned char ucType;
	unsigned char ucUnk00;
	unsigned short usUnk01;
	unsigned int uiPackedData;
	unsigned int uiHash;
	unsigned int uiMask;
};

//Classes
class cDRM
{

public:
	cDRM();
	~cDRM();

	void ExtractSections(char* szFilePath);

private:
	char* m_filePath;
	unsigned int m_version;

#if TR8
	unsigned int m_nameSize;
	unsigned int m_paddingSize;
	unsigned int m_unk00;
	unsigned int m_unk01;
#elif TRAS
	unsigned int m_nameSize;
	unsigned int m_paddingSize;
	unsigned int m_unk00;
	unsigned int m_unk01;
	unsigned int m_unk02;
#endif

	unsigned int m_numSections;

	std::vector<Section> m_sections;
};

//Enums
enum SectionType
{
#if TR7
	GENERAL,
	EMPTY,
	ANIMATION,
	PUSHBUFFER_WC,
	PUSHBUFFER,
	TEXTURE,
	WAVE,
	DTPDATA,
	SCRIPT,
	SHADERLIB,
#elif TR8
	GENERAL,
	EMPTY,
	ANIMATION,
	PUSHBUFFER_WC,
	PUSHBUFFER,
	TEXTURE,
	WAVE,
	DTPDATA,
	SCRIPT,
	SHADERLIB,
	MATERIAL,
	OBJECT,
	RENDERRESOURCE,
	PDAMAP,
#endif
	NUM_SECTION_TYPES
};

#endif