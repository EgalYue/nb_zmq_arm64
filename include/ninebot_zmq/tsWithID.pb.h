// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ninebot_zmq/tsWithID.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_ninebot_5fzmq_2ftsWithID_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_ninebot_5fzmq_2ftsWithID_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3008000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3008000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_ninebot_5fzmq_2ftsWithID_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_ninebot_5fzmq_2ftsWithID_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_ninebot_5fzmq_2ftsWithID_2eproto;
namespace Segway_proto {
class TsWithID;
class TsWithIDDefaultTypeInternal;
extern TsWithIDDefaultTypeInternal _TsWithID_default_instance_;
}  // namespace Segway_proto
PROTOBUF_NAMESPACE_OPEN
template<> ::Segway_proto::TsWithID* Arena::CreateMaybeMessage<::Segway_proto::TsWithID>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace Segway_proto {

// ===================================================================

class TsWithID :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Segway_proto.TsWithID) */ {
 public:
  TsWithID();
  virtual ~TsWithID();

  TsWithID(const TsWithID& from);
  TsWithID(TsWithID&& from) noexcept
    : TsWithID() {
    *this = ::std::move(from);
  }

  inline TsWithID& operator=(const TsWithID& from) {
    CopyFrom(from);
    return *this;
  }
  inline TsWithID& operator=(TsWithID&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const TsWithID& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const TsWithID* internal_default_instance() {
    return reinterpret_cast<const TsWithID*>(
               &_TsWithID_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(TsWithID* other);
  friend void swap(TsWithID& a, TsWithID& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline TsWithID* New() const final {
    return CreateMaybeMessage<TsWithID>(nullptr);
  }

  TsWithID* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<TsWithID>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const TsWithID& from);
  void MergeFrom(const TsWithID& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(TsWithID* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Segway_proto.TsWithID";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_ninebot_5fzmq_2ftsWithID_2eproto);
    return ::descriptor_table_ninebot_5fzmq_2ftsWithID_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // int64 time_stamp = 1;
  void clear_time_stamp();
  static const int kTimeStampFieldNumber = 1;
  ::PROTOBUF_NAMESPACE_ID::int64 time_stamp() const;
  void set_time_stamp(::PROTOBUF_NAMESPACE_ID::int64 value);

  // int64 frame_id = 2;
  void clear_frame_id();
  static const int kFrameIdFieldNumber = 2;
  ::PROTOBUF_NAMESPACE_ID::int64 frame_id() const;
  void set_frame_id(::PROTOBUF_NAMESPACE_ID::int64 value);

  // @@protoc_insertion_point(class_scope:Segway_proto.TsWithID)
 private:
  class HasBitSetters;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::int64 time_stamp_;
  ::PROTOBUF_NAMESPACE_ID::int64 frame_id_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_ninebot_5fzmq_2ftsWithID_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// TsWithID

// int64 time_stamp = 1;
inline void TsWithID::clear_time_stamp() {
  time_stamp_ = PROTOBUF_LONGLONG(0);
}
inline ::PROTOBUF_NAMESPACE_ID::int64 TsWithID::time_stamp() const {
  // @@protoc_insertion_point(field_get:Segway_proto.TsWithID.time_stamp)
  return time_stamp_;
}
inline void TsWithID::set_time_stamp(::PROTOBUF_NAMESPACE_ID::int64 value) {
  
  time_stamp_ = value;
  // @@protoc_insertion_point(field_set:Segway_proto.TsWithID.time_stamp)
}

// int64 frame_id = 2;
inline void TsWithID::clear_frame_id() {
  frame_id_ = PROTOBUF_LONGLONG(0);
}
inline ::PROTOBUF_NAMESPACE_ID::int64 TsWithID::frame_id() const {
  // @@protoc_insertion_point(field_get:Segway_proto.TsWithID.frame_id)
  return frame_id_;
}
inline void TsWithID::set_frame_id(::PROTOBUF_NAMESPACE_ID::int64 value) {
  
  frame_id_ = value;
  // @@protoc_insertion_point(field_set:Segway_proto.TsWithID.frame_id)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace Segway_proto

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_ninebot_5fzmq_2ftsWithID_2eproto
