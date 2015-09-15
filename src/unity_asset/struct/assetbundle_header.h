#ifndef _ASSETBUNDLE_HEADER_H_
#define _ASSETBUNDLE_HEADER_H_

#include <cstdint>
#include <string>
#include <vector>
#include <utility>
#include "struct/unity_version.h"
#include "utils/data_reader.h"

class AssetbundleHeader
{
	static const std::string signatureWeb;
	static const std::string signatureRaw;

public:
	std::string signature;
	uint32_t streamVersion = 0;
	UnityVersion playerVersion;
	UnityVersion engineVersion;
	int32_t minimumStreamedBytes = 0;
	int32_t headerSize = 0;
	int32_t numberOfLevelsToDownload = 0;
	std::vector<std::pair<uint32_t, uint32_t> > levelByteEnd;
	int32_t completeFileSize = 0;
	int32_t fileInfoHeaderSize = 0;
	bool isCompressed = false;

public:
	AssetbundleHeader() = default;

	int Read(DataReader& reader);
};

#endif //!_ASSETBUNDLE_HEADER_H_