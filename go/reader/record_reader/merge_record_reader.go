package record_reader

import (
	"github.com/apache/arrow/go/v12/arrow"
	"github.com/milvus-io/milvus-storage/go/file/fragment"
	"github.com/milvus-io/milvus-storage/go/io/fs"
	"github.com/milvus-io/milvus-storage/go/storage/options"
	"github.com/milvus-io/milvus-storage/go/storage/schema"
)

type MergeRecordReader struct {
	ref             int64
	schema          *schema.Schema
	options         *options.ReadOptions
	fs              fs.Fs
	scalarFragments fragment.FragmentVector
	vectorFragments fragment.FragmentVector
	deleteFragments fragment.DeleteFragmentVector
	record          arrow.Record
}

func (m MergeRecordReader) Retain() {
	//TODO implement me
	panic("implement me")
}

func (m MergeRecordReader) Release() {
	//TODO implement me
	panic("implement me")
}

func (m MergeRecordReader) Schema() *arrow.Schema {
	//TODO implement me
	panic("implement me")
}

func (m MergeRecordReader) Next() bool {
	//TODO implement me
	panic("implement me")
}

func (m MergeRecordReader) Record() arrow.Record {
	//TODO implement me
	panic("implement me")
}

func (m MergeRecordReader) Err() error {
	//TODO implement me
	panic("implement me")
}

func NewMergeRecordReader(
	s *schema.Schema,
	options *options.ReadOptions,
	f fs.Fs,
	scalarFragment fragment.FragmentVector,
	vectorFragment fragment.FragmentVector,
	deleteFragments fragment.DeleteFragmentVector) *MergeRecordReader {
	//TODO implement me
	panic("implement me")
}
