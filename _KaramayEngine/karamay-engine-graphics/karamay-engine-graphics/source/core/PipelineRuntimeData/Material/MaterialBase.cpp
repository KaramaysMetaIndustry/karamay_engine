#include "MaterialBase.h"
#include "Core/SpicesRendererGlobal.h"

void MaterialBase::Install()
{
	if (AlbedoMap)
		AlbedoMap->Install();
		
	if (NormalMap)
		NormalMap->Install();
		
	if (MetalnessMap)
		MetalnessMap->Install();
		
	if (RoughnessMap)
		RoughnessMap->Install();		

	if (DisplacementMap)
		DisplacementMap->Install();

	if (AmbientOcclusionMap)
		AmbientOcclusionMap->Install();

	/*for (auto Pair : Maps)
	{
		auto Map = Pair.second;
		if (Map)
			Map->Install();
	}*/
}

void MaterialBase::Submit(PipelineBase* AssociatedPipeline)
{
	if (AssociatedPipeline)
	{
		if (AlbedoMap)
			AlbedoMap->Submit(AssociatedPipeline);

		if (NormalMap)
			NormalMap->Submit(AssociatedPipeline);

		if (MetalnessMap)
			MetalnessMap->Submit(AssociatedPipeline);

		if (RoughnessMap)
			RoughnessMap->Submit(AssociatedPipeline);

		if (DisplacementMap)
			DisplacementMap->Submit(AssociatedPipeline);

		if (AmbientOcclusionMap)
			AmbientOcclusionMap->Submit(AssociatedPipeline);
	}

	/*for (auto Pair : Maps)
	{
		auto Map = Pair.second;
		if (Map)
			Map->Submit(AssociatedPipeline);
	}*/
}

void MaterialBase::Uninstall()
{
	if (AlbedoMap)
		AlbedoMap->Uninstall();

	if (NormalMap)
		NormalMap->Uninstall();
	
	if (MetalnessMap)
		MetalnessMap->Uninstall();
	
	if (RoughnessMap)
		RoughnessMap->Uninstall();
	
	if (DisplacementMap)
		DisplacementMap->Uninstall();
	
	if (AmbientOcclusionMap)
		AmbientOcclusionMap->Uninstall();

	/*for (auto Pair : Maps)
	{
		auto Map = Pair.second;
		if (Map)
			Map->Uninstall();
	}*/
}

void MaterialBase::Load(const std::string& Directory)
{
	std::vector<std::string> Pathes;
	for (const auto& Entry : std::filesystem::directory_iterator(Directory))
	{
		Pathes.push_back(Entry.path().string());
	}

	Load(Pathes);
}

void MaterialBase::Load(const std::vector<std::string>& FilePathes)
{
	
	std::string AlbedoMapFilePath, MetalnessMapFilePath, 
		NormalMapFilePath, RoughnessMapFilePath, DisplacementMapFilePath, 
		AmbientOcclusionMapFilePath;

	for (auto FilePath : FilePathes)
	{
		if (FilePath.find("Color") != FilePath.npos)
			AlbedoMapFilePath = FilePath;
			
		if (FilePath.find("Normal") != FilePath.npos)
			NormalMapFilePath = FilePath;
		
		if (FilePath.find("Metalness") != FilePath.npos)
			MetalnessMapFilePath = FilePath;
			
		if (FilePath.find("Roughness") != FilePath.npos)
			RoughnessMapFilePath = FilePath;
			
		if (FilePath.find("Displacement") != FilePath.npos)
			DisplacementMapFilePath = FilePath;
			
		if (FilePath.find("AmbientOcclusion") != FilePath.npos)
			AmbientOcclusionMapFilePath = FilePath;
	}

	if (AlbedoMap == nullptr)
		AlbedoMap = Texture2DCreator->Create();
	AlbedoMap->LoadPixels(AlbedoMapFilePath);

	if (NormalMap == nullptr)
		NormalMap = Texture2DCreator->Create();
	NormalMap->LoadPixels(NormalMapFilePath);

	if (MetalnessMap == nullptr)
		MetalnessMap = Texture2DCreator->Create();
	MetalnessMap->LoadPixels(MetalnessMapFilePath);

	if (RoughnessMap == nullptr)
		RoughnessMap = Texture2DCreator->Create();
	RoughnessMap->LoadPixels(RoughnessMapFilePath);

	if (DisplacementMap == nullptr)
		DisplacementMap = Texture2DCreator->Create();
	DisplacementMap->LoadPixels(DisplacementMapFilePath);

	if (AmbientOcclusionMap == nullptr)
		AmbientOcclusionMap = Texture2DCreator->Create();
	AmbientOcclusionMap->LoadPixels(AmbientOcclusionMapFilePath);
}

bool MaterialBase::IsMaterialAvaliable()
{
	return false;
}

void MaterialBase::Restore()
{
}

void MaterialBase::MergeTextures()
{
}

MaterialBase::MaterialBase()
{
	Opacity = 1.0f;

	AlbedoMap = nullptr;
	NormalMap = nullptr;
	MetalnessMap = nullptr;
	RoughnessMap = nullptr;
	DisplacementMap = nullptr;
	AmbientOcclusionMap = nullptr;

	Maps.emplace("aldebo_map", nullptr);
	Maps.emplace("normal_map", nullptr);
	Maps.emplace("metalness_map", nullptr);
	Maps.emplace("roughness_map", nullptr);
	Maps.emplace("displacement_map", nullptr);
	Maps.emplace("ambient_occlusion_map", nullptr);
}

MaterialBase::~MaterialBase()
{
}
