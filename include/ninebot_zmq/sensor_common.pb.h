// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ninebot_zmq/sensor_common.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_ninebot_5fzmq_2fsensor_5fcommon_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_ninebot_5fzmq_2fsensor_5fcommon_2eproto

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
#define PROTOBUF_INTERNAL_EXPORT_ninebot_5fzmq_2fsensor_5fcommon_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_ninebot_5fzmq_2fsensor_5fcommon_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[2]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_ninebot_5fzmq_2fsensor_5fcommon_2eproto;
namespace Segway_proto {
class Header;
class HeaderDefaultTypeInternal;
extern HeaderDefaultTypeInternal _Header_default_instance_;
class Timestamp;
class TimestampDefaultTypeInternal;
extern TimestampDefaultTypeInternal _Timestamp_default_instance_;
}  // namespace Segway_proto
PROTOBUF_NAMESPACE_OPEN
template<> ::Segway_proto::Header* Arena::CreateMaybeMessage<::Segway_proto::Header>(Arena*);
template<> ::Segway_proto::Timestamp* Arena::CreateMaybeMessage<::Segway_proto::Timestamp>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace Segway_proto {

// ===================================================================

class Timestamp :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Segway_proto.Timestamp) */ {
 public:
  Timestamp();
  virtual ~Timestamp();

  Timestamp(const Timestamp& from);
  Timestamp(Timestamp&& from) noexcept
    : Timestamp() {
    *this = ::std::move(from);
  }

  inline Timestamp& operator=(const Timestamp& from) {
    CopyFrom(from);
    return *this;
  }
  inline Timestamp& operator=(Timestamp&& from) noexcept {
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
  static const Timestamp& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Timestamp* internal_default_instance() {
    return reinterpret_cast<const Timestamp*>(
               &_Timestamp_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(Timestamp* other);
  friend void swap(Timestamp& a, Timestamp& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Timestamp* New() const final {
    return CreateMaybeMessage<Timestamp>(nullptr);
  }

  Timestamp* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Timestamp>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const Timestamp& from);
  void MergeFrom(const Timestamp& from);
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
  void InternalSwap(Timestamp* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Segway_proto.Timestamp";
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
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_ninebot_5fzmq_2fsensor_5fcommon_2eproto);
    return ::descriptor_table_ninebot_5fzmq_2fsensor_5fcommon_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // int64 time_stamp = 1;
  void clear_time_stamp();
  static const int kTimeStampFieldNumber = 1;
  ::PROTOBUF_NAMESPACE_ID::int64 time_stamp() const;
  void set_time_stamp(::PROTOBUF_NAMESPACE_ID::int64 value);

  // @@protoc_insertion_point(class_scope:Segway_proto.Timestamp)
 private:
  class HasBitSetters;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::int64 time_stamp_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_ninebot_5fzmq_2fsensor_5fcommon_2eproto;
};
// -------------------------------------------------------------------

class Header :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Segway_proto.Header) */ {
 public:
  Header();
  virtual ~Header();

  Header(const Header& from);
  Header(Header&& from) noexcept
    : Header() {
    *this = ::std::move(from);
  }

  inline Header& operator=(const Header& from) {
    CopyFrom(from);
    return *this;
  }
  inline Header& operator=(Header&& from) noexcept {
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
  static const Header& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Header* internal_default_instance() {
    return reinterpret_cast<const Header*>(
               &_Header_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(Header* other);
  friend void swap(Header& a, Header& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Header* New() const final {
    return CreateMaybeMessage<Header>(nullptr);
  }

  Header* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Header>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const Header& from);
  void MergeFrom(const Header& from);
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
  void InternalSwap(Header* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Segway_proto.Header";
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
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_ninebot_5fzmq_2fsensor_5fcommon_2eproto);
    return ::descriptor_table_ninebot_5fzmq_2fsensor_5fcommon_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string frame_id = 3;
  void clear_frame_id();
  static const int kFrameIdFieldNumber = 3;
  const std::string& frame_id() const;
  void set_frame_id(const std::string& value);
  void set_frame_id(std::string&& value);
  void set_frame_id(const char* value);
  void set_frame_id(const char* value, size_t size);
  std::string* mutable_frame_id();
  std::string* release_frame_id();
  void set_allocated_frame_id(std::string* frame_id);

  // .Segway_proto.Timestamp stamp = 2;
  bool has_stamp() const;
  void clear_stamp();
  static const int kStampFieldNumber = 2;
  const ::Segway_proto::Timestamp& stamp() const;
  ::Segway_proto::Timestamp* release_stamp();
  ::Segway_proto::Timestamp* mutable_stamp();
  void set_allocated_stamp(::Segway_proto::Timestamp* stamp);

  // uint32 seq = 1;
  void clear_seq();
  static const int kSeqFieldNumber = 1;
  ::PROTOBUF_NAMESPACE_ID::uint32 seq() const;
  void set_seq(::PROTOBUF_NAMESPACE_ID::uint32 value);

  // @@protoc_insertion_point(class_scope:Segway_proto.Header)
 private:
  class HasBitSetters;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr frame_id_;
  ::Segway_proto::Timestamp* stamp_;
  ::PROTOBUF_NAMESPACE_ID::uint32 seq_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_ninebot_5fzmq_2fsensor_5fcommon_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Timestamp

// int64 time_stamp = 1;
inline void Timestamp::clear_time_stamp() {
  time_stamp_ = PROTOBUF_LONGLONG(0);
}
inline ::PROTOBUF_NAMESPACE_ID::int64 Timestamp::time_stamp() const {
  // @@protoc_insertion_point(field_get:Segway_proto.Timestamp.time_stamp)
  return time_stamp_;
}
inline void Timestamp::set_time_stamp(::PROTOBUF_NAMESPACE_ID::int64 value) {
  
  time_stamp_ = value;
  // @@protoc_insertion_point(field_set:Segway_proto.Timestamp.time_stamp)
}

// -------------------------------------------------------------------

// Header

// uint32 seq = 1;
inline void Header::clear_seq() {
  seq_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 Header::seq() const {
  // @@protoc_insertion_point(field_get:Segway_proto.Header.seq)
  return seq_;
}
inline void Header::set_seq(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  
  seq_ = value;
  // @@protoc_insertion_point(field_set:Segway_proto.Header.seq)
}

// .Segway_proto.Timestamp stamp = 2;
inline bool Header::has_stamp() const {
  return this != internal_default_instance() && stamp_ != nullptr;
}
inline void Header::clear_stamp() {
  if (GetArenaNoVirtual() == nullptr && stamp_ != nullptr) {
    delete stamp_;
  }
  stamp_ = nullptr;
}
inline const ::Segway_proto::Timestamp& Header::stamp() const {
  const ::Segway_proto::Timestamp* p = stamp_;
  // @@protoc_insertion_point(field_get:Segway_proto.Header.stamp)
  return p != nullptr ? *p : *reinterpret_cast<const ::Segway_proto::Timestamp*>(
      &::Segway_proto::_Timestamp_default_instance_);
}
inline ::Segway_proto::Timestamp* Header::release_stamp() {
  // @@protoc_insertion_point(field_release:Segway_proto.Header.stamp)
  
  ::Segway_proto::Timestamp* temp = stamp_;
  stamp_ = nullptr;
  return temp;
}
inline ::Segway_proto::Timestamp* Header::mutable_stamp() {
  
  if (stamp_ == nullptr) {
    auto* p = CreateMaybeMessage<::Segway_proto::Timestamp>(GetArenaNoVirtual());
    stamp_ = p;
  }
  // @@protoc_insertion_point(field_mutable:Segway_proto.Header.stamp)
  return stamp_;
}
inline void Header::set_allocated_stamp(::Segway_proto::Timestamp* stamp) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == nullptr) {
    delete stamp_;
  }
  if (stamp) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena = nullptr;
    if (message_arena != submessage_arena) {
      stamp = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, stamp, submessage_arena);
    }
    
  } else {
    
  }
  stamp_ = stamp;
  // @@protoc_insertion_point(field_set_allocated:Segway_proto.Header.stamp)
}

// string frame_id = 3;
inline void Header::clear_frame_id() {
  frame_id_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& Header::frame_id() const {
  // @@protoc_insertion_point(field_get:Segway_proto.Header.frame_id)
  return frame_id_.GetNoArena();
}
inline void Header::set_frame_id(const std::string& value) {
  
  frame_id_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Segway_proto.Header.frame_id)
}
inline void Header::set_frame_id(std::string&& value) {
  
  frame_id_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:Segway_proto.Header.frame_id)
}
inline void Header::set_frame_id(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  frame_id_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Segway_proto.Header.frame_id)
}
inline void Header::set_frame_id(const char* value, size_t size) {
  
  frame_id_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Segway_proto.Header.frame_id)
}
inline std::string* Header::mutable_frame_id() {
  
  // @@protoc_insertion_point(field_mutable:Segway_proto.Header.frame_id)
  return frame_id_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* Header::release_frame_id() {
  // @@protoc_insertion_point(field_release:Segway_proto.Header.frame_id)
  
  return frame_id_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void Header::set_allocated_frame_id(std::string* frame_id) {
  if (frame_id != nullptr) {
    
  } else {
    
  }
  frame_id_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), frame_id);
  // @@protoc_insertion_point(field_set_allocated:Segway_proto.Header.frame_id)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace Segway_proto

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_ninebot_5fzmq_2fsensor_5fcommon_2eproto
