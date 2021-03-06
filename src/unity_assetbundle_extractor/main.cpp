#include "struct/assetbundle_reader.h"

int main()
{
	StringTable::LoadDefaultStringTable("strings.dat");

	FileReader fileReader("test5.1.assetbundle");

	AssetbundleReader assertbundleReader;
	assertbundleReader.ReadHeader(fileReader);
	
	auto headerSize = assertbundleReader.header.headerSize;
	DataReader content = std::move(fileReader.ReadData(headerSize));
	fileReader.Close();

	DataReader dataReader;
	if (assertbundleReader.header.IsCompressed())
		dataReader = content.Decompress();
	else
		dataReader = std::move(content);
	content.Close();

	auto assetFileList = assertbundleReader.ReadAssetFiles(dataReader);
	for (auto& keyValPair : assetFileList)
	{
		auto& entryInfo = keyValPair.first;
		auto& assetFile = keyValPair.second;
		dataReader.Seek(entryInfo.offset);
		assetFile.LoadAllObjects(dataReader, [&entryInfo](const ObjectInfo& objectInfo, DataReader& objectReader)
		{
			std::string path = "output/" + entryInfo.name + " - " + std::to_string(objectInfo.pathID);
			FileWriter writer(path);
			objectReader.WriteFile(writer, objectReader.Tell(), objectInfo.length);
			writer.Close();
		});
	}
}