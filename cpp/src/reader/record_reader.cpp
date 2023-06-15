#include "reader/record_reader.h"

namespace milvus_storage {
std::unique_ptr<arrow::RecordBatchReader> RecordReader::MakeRecordReader(const DefaultSpace& space,
                                                                         std::shared_ptr<ReadOptions>& options) {
  // TODO: Implement a common optimization method. For now we just enumerate few plans.
  std::set<std::string> related_columns;
  for (auto& column : options->columns) {
    related_columns.insert(column);
  }
  for (auto& filter : options->filters) {
    related_columns.insert(filter->get_column_name());
  }
}

bool RecordReader::only_contain_scalar_columns(const DefaultSpace& space,
                                               const std::set<std::string>& related_columns) {
  for (auto& column : related_columns) {
    if (space.schema_->options()->vector_column == column) {
      return false;
    }
  }
  return true;
}

bool RecordReader::only_contain_vector_columns(const DefaultSpace& space,
                                               const std::set<std::string>& related_columns) {
  for (auto& column : related_columns) {
    if (space.schema_->options()->vector_column != column && space.schema_->options()->primary_column != column &&
        space.schema_->options()->version_column != column) {
      return false;
    }
  }
  return true;
}

bool RecordReader::filters_only_contain_pk_and_version(const DefaultSpace& space, const std::vector<Filter*>& filters) {
  for (auto& filter : filters) {
    if (filter->get_column_name() != space.schema_->options()->primary_column &&
        filter->get_column_name() != space.schema_->options()->version_column) {
      return false;
    }
  }
  return true;
}

}  // namespace milvus_storage
