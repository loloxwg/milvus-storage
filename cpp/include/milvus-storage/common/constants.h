#include <string>

namespace milvus_storage {

const int kReadBatchSize = 1024;

const std::string kManifestTempFileSuffix = ".manifest.tmp";
const std::string kManifestFileSuffix = ".manifest";
const std::string kManifestsDir = "versions";
const std::string kScalarDataDir = "scalar";
const std::string kVectorDataDir = "vector";
const std::string kDeleteDataDir = "delete";
const std::string kBlobDir = "blobs";
const std::string kParquetDataFileSuffix = ".parquet";
const std::string kOffsetFieldName = "__offset";

}  // namespace milvus_storage
