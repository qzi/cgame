//////////////////////////////////////////////////////////////////////////
//  the model using the library of  assimp
//////////////////////////////////////////////////////////////////////////


#ifndef CMODEL_H
#define CMODEL_H

#include <map>
#include <string>
#include "assimp.h"
#include "assimp.hpp"	//OO version Header!

class CModel{
public:
	CModel();
	~CModel();

	void	Color4f(const struct aiColor4D *color);
	void	set_float4(float f[4], float a, float b, float c, float d);
	void	color4_to_float4(const struct aiColor4D *c, float f[4]);


	bool	InitialModel( const char * basepath, const char * modelname );
	bool	Import3DFromFile( const std::string& pFile);
	int		LoadGLTextures( const aiScene* scene );
	void	apply_material(const struct aiMaterial *mtl);
	void	recursive_render (const struct aiScene *sc, const struct aiNode* nd, float scale);
	void	drawAiScene(const aiScene* scene);
	void	Render();
	
	// log and debug
	void	createAILogger();
	void	logInfo(std::string logString);
	void	destroyAILogger();
	bool	abortMessage(const char* abortMessage);

public:
	std::string								m_BasePath;		// the default base path of the file
	std::string								m_ModelName;		// the file name
	float									m_Scale;		// the rate of scale
	bool									m_bInitialized;	// is Initalized;

private:	
	std::map<std::string, unsigned int*>	m_textureIdMap;	// map image filenames to textureIds
	unsigned int*							m_textureIds;		// pointer to texture Array
	const aiScene* 							m_scene;			// the global Assimp scene object
	Assimp::Importer						m_importer;		// Create an instance of the Importer class

};

#endif	// CMODEL_H