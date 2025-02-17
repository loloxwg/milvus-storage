#include "storage/space.h"
#include "common/log.h"
#include "filter/constant_filter.h"

#include <memory>
#include <type_traits>
#include <arrow/type.h>
#include <arrow/type_fwd.h>
#include <arrow/array/builder_binary.h>
#include <arrow/array/builder_primitive.h>
#include <arrow/util/key_value_metadata.h>
#include <gtest/gtest.h>
#include "test_util.h"
#include "arrow/table.h"

namespace milvus_storage {
/**
 * @brief Test Space::Write
 *
 */
TEST(SpaceTest, SpaceWriteReadTest) {
  auto arrow_schema = CreateArrowSchema({"pk_field", "ts_field", "vec_field"},
                                        {arrow::int64(), arrow::int64(), arrow::fixed_size_binary(10)});

  auto schema_options = std::make_shared<SchemaOptions>();
  schema_options->primary_column = "pk_field";
  schema_options->version_column = "ts_field";
  schema_options->vector_column = "vec_field";

  auto schema = std::make_shared<Schema>(arrow_schema, schema_options);
  ASSERT_STATUS_OK(schema->Validate());

  auto uri = "file:///tmp/";
  ASSERT_AND_ASSIGN(auto space, Space::Open(uri, Options{schema, -1}));

  arrow::Int64Builder pk_builder;
  ASSERT_STATUS_OK(pk_builder.Append(1));
  ASSERT_STATUS_OK(pk_builder.Append(2));
  ASSERT_STATUS_OK(pk_builder.Append(3));
  arrow::Int64Builder ts_builder;
  ASSERT_STATUS_OK(ts_builder.Append(1));
  ASSERT_STATUS_OK(ts_builder.Append(2));
  ASSERT_STATUS_OK(ts_builder.Append(3));
  arrow::FixedSizeBinaryBuilder vec_builder(arrow::fixed_size_binary(10));
  ASSERT_STATUS_OK(vec_builder.Append("1234567890"));
  ASSERT_STATUS_OK(vec_builder.Append("1234567890"));
  ASSERT_STATUS_OK(vec_builder.Append("1234567890"));

  std::shared_ptr<arrow::Array> pk_array;
  ASSERT_STATUS_OK(pk_builder.Finish(&pk_array));
  std::shared_ptr<arrow::Array> ts_array;
  ASSERT_STATUS_OK(ts_builder.Finish(&ts_array));
  std::shared_ptr<arrow::Array> vec_array;
  ASSERT_STATUS_OK(vec_builder.Finish(&vec_array));

  auto rec_batch = arrow::RecordBatch::Make(arrow_schema, 3, {pk_array, ts_array, vec_array});
  auto reader = arrow::RecordBatchReader::Make({rec_batch}, arrow_schema).ValueOrDie();

  auto write_option = WriteOption{10};
  space->Write(reader.get(), &write_option);

  std::unique_ptr<Filter> filter = std::make_unique<ConstantFilter>(EQUAL, "pk_field", Value::Int64(1));
  auto read_options = std::make_shared<ReadOptions>();
  read_options->filters.push_back(std::move(filter));
  read_options->columns.emplace_back("pk_field");
  auto res_reader = space->Read(read_options);
  ASSERT_AND_ARROW_ASSIGN(auto table, res_reader->ToTable());
  auto pk_chunk_arr = table->GetColumnByName("pk_field");
  ASSERT_EQ(pk_chunk_arr->length(), 1);
  auto pk_chunk = pk_chunk_arr->chunk(0);
  ASSERT_EQ(pk_chunk->length(), 1);
  auto pk_arr = dynamic_cast<arrow::Int64Array*>(pk_chunk.get());
  ASSERT_EQ(1, pk_arr->Value(0));
}
/**
 * @brief Test Space::Read
 *  TODO: need to implement Next function
 */
TEST(SpaceTest, SpaceReadTest) {}

/**
 * @brief Test Space::Delete
 *  TODO: need to implement
 */
TEST(SpaceTest, SpaceDeleteTest) {}

}  // namespace milvus_storage
