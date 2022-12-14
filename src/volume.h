
#ifndef VOLUME_H
#define VOLUME_H

#include "includes.h"
#include "framework.h"
#include <map>
#include <string>


enum VolType : uint8
{
	VL_VOL,
	PVM_VOL,
	PNG_VOL
};

//Class to represent a volume
class Volume
{
public:
	unsigned int width;
	unsigned int height;
	unsigned int depth;

	float widthSpacing;
	float heightSpacing;
	float depthSpacing;

	unsigned int voxelBytes;	//1, 2 or 4
	unsigned int voxelChannels;	//1, 2, 3 or 4
	unsigned int voxelType;		//0: unsigned int, 1: int, 2: float, 3: other

	Uint8* data; //bytes with the pixel information

	//volumes manager
	static std::map<std::string, Volume*> sVolumesLoaded;

	Volume();
	Volume(unsigned int w, unsigned int h, unsigned int d, unsigned int channels = 1, unsigned int bytes = 1, unsigned int type = 0);
	~Volume();

	unsigned int getTextureFormat();
	unsigned int getTextureType();
	unsigned int getTextureInternalFormat();

	void resize(int w, int h, int d, unsigned int channels = 1, unsigned int bytes = 1);
	void clear();

	//Carefull using too large files as it may crash the app
	bool loadVL(const char* filename);
	bool loadPVM(const char* filename);
	bool loadPNG(const char* filename, unsigned int rows = 16, unsigned int columns = 16);

	//Slow methods
	void fillSphere();
	void fillNoise(float frequency, int octaves, unsigned int seed, unsigned int channel = 1); //Channel 1 for R to 4 for A
	void fillWorleyNoise(unsigned int cellsPerSide = 4, unsigned int channel = 1); //Channel 1 for R to 4 for A

	//load using the manager (caching loaded ones to avoid reloading them)
	static Volume* Get(const char* filename, VolType type);
	void setName(const char* name) { sVolumesLoaded[name] = this; }
};

#endif