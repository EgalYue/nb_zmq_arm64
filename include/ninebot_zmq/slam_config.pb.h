// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ninebot_zmq/slam_config.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_ninebot_5fzmq_2fslam_5fconfig_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_ninebot_5fzmq_2fslam_5fconfig_2eproto

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
#include "ninebot_zmq/sensor_common.pb.h"
#include "ninebot_zmq/pose.pb.h"
#include "ninebot_zmq/camera.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_ninebot_5fzmq_2fslam_5fconfig_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_ninebot_5fzmq_2fslam_5fconfig_2eproto {
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
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_ninebot_5fzmq_2fslam_5fconfig_2eproto;
namespace Segway_proto {
class RobotExtParams;
class RobotExtParamsDefaultTypeInternal;
extern RobotExtParamsDefaultTypeInternal _RobotExtParams_default_instance_;
class SlamConfig;
class SlamConfigDefaultTypeInternal;
extern SlamConfigDefaultTypeInternal _SlamConfig_default_instance_;
}  // namespace Segway_proto
PROTOBUF_NAMESPACE_OPEN
template<> ::Segway_proto::RobotExtParams* Arena::CreateMaybeMessage<::Segway_proto::RobotExtParams>(Arena*);
template<> ::Segway_proto::SlamConfig* Arena::CreateMaybeMessage<::Segway_proto::SlamConfig>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace Segway_proto {

// ===================================================================

class RobotExtParams :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Segway_proto.RobotExtParams) */ {
 public:
  RobotExtParams();
  virtual ~RobotExtParams();

  RobotExtParams(const RobotExtParams& from);
  RobotExtParams(RobotExtParams&& from) noexcept
    : RobotExtParams() {
    *this = ::std::move(from);
  }

  inline RobotExtParams& operator=(const RobotExtParams& from) {
    CopyFrom(from);
    return *this;
  }
  inline RobotExtParams& operator=(RobotExtParams&& from) noexcept {
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
  static const RobotExtParams& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const RobotExtParams* internal_default_instance() {
    return reinterpret_cast<const RobotExtParams*>(
               &_RobotExtParams_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(RobotExtParams* other);
  friend void swap(RobotExtParams& a, RobotExtParams& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline RobotExtParams* New() const final {
    return CreateMaybeMessage<RobotExtParams>(nullptr);
  }

  RobotExtParams* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<RobotExtParams>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const RobotExtParams& from);
  void MergeFrom(const RobotExtParams& from);
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
  void InternalSwap(RobotExtParams* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Segway_proto.RobotExtParams";
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
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_ninebot_5fzmq_2fslam_5fconfig_2eproto);
    return ::descriptor_table_ninebot_5fzmq_2fslam_5fconfig_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // float base_width = 1;
  void clear_base_width();
  static const int kBaseWidthFieldNumber = 1;
  float base_width() const;
  void set_base_width(float value);

  // float wheel_radius = 2;
  void clear_wheel_radius();
  static const int kWheelRadiusFieldNumber = 2;
  float wheel_radius() const;
  void set_wheel_radius(float value);

  // int32 wheel_resolution = 3;
  void clear_wheel_resolution();
  static const int kWheelResolutionFieldNumber = 3;
  ::PROTOBUF_NAMESPACE_ID::int32 wheel_resolution() const;
  void set_wheel_resolution(::PROTOBUF_NAMESPACE_ID::int32 value);

  // @@protoc_insertion_point(class_scope:Segway_proto.RobotExtParams)
 private:
  class HasBitSetters;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  float base_width_;
  float wheel_radius_;
  ::PROTOBUF_NAMESPACE_ID::int32 wheel_resolution_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_ninebot_5fzmq_2fslam_5fconfig_2eproto;
};
// -------------------------------------------------------------------

class SlamConfig :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Segway_proto.SlamConfig) */ {
 public:
  SlamConfig();
  virtual ~SlamConfig();

  SlamConfig(const SlamConfig& from);
  SlamConfig(SlamConfig&& from) noexcept
    : SlamConfig() {
    *this = ::std::move(from);
  }

  inline SlamConfig& operator=(const SlamConfig& from) {
    CopyFrom(from);
    return *this;
  }
  inline SlamConfig& operator=(SlamConfig&& from) noexcept {
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
  static const SlamConfig& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const SlamConfig* internal_default_instance() {
    return reinterpret_cast<const SlamConfig*>(
               &_SlamConfig_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(SlamConfig* other);
  friend void swap(SlamConfig& a, SlamConfig& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline SlamConfig* New() const final {
    return CreateMaybeMessage<SlamConfig>(nullptr);
  }

  SlamConfig* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<SlamConfig>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const SlamConfig& from);
  void MergeFrom(const SlamConfig& from);
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
  void InternalSwap(SlamConfig* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Segway_proto.SlamConfig";
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
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_ninebot_5fzmq_2fslam_5fconfig_2eproto);
    return ::descriptor_table_ninebot_5fzmq_2fslam_5fconfig_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string vision_map = 2;
  void clear_vision_map();
  static const int kVisionMapFieldNumber = 2;
  const std::string& vision_map() const;
  void set_vision_map(const std::string& value);
  void set_vision_map(std::string&& value);
  void set_vision_map(const char* value);
  void set_vision_map(const char* value, size_t size);
  std::string* mutable_vision_map();
  std::string* release_vision_map();
  void set_allocated_vision_map(std::string* vision_map);

  // string lidar_map = 3;
  void clear_lidar_map();
  static const int kLidarMapFieldNumber = 3;
  const std::string& lidar_map() const;
  void set_lidar_map(const std::string& value);
  void set_lidar_map(std::string&& value);
  void set_lidar_map(const char* value);
  void set_lidar_map(const char* value, size_t size);
  std::string* mutable_lidar_map();
  std::string* release_lidar_map();
  void set_allocated_lidar_map(std::string* lidar_map);

  // string map_id = 4;
  void clear_map_id();
  static const int kMapIdFieldNumber = 4;
  const std::string& map_id() const;
  void set_map_id(const std::string& value);
  void set_map_id(std::string&& value);
  void set_map_id(const char* value);
  void set_map_id(const char* value, size_t size);
  std::string* mutable_map_id();
  std::string* release_map_id();
  void set_allocated_map_id(std::string* map_id);

  // .Segway_proto.Header header = 1;
  bool has_header() const;
  void clear_header();
  static const int kHeaderFieldNumber = 1;
  const ::Segway_proto::Header& header() const;
  ::Segway_proto::Header* release_header();
  ::Segway_proto::Header* mutable_header();
  void set_allocated_header(::Segway_proto::Header* header);

  // .Segway_proto.CameraIntrinsics fisheye = 6;
  bool has_fisheye() const;
  void clear_fisheye();
  static const int kFisheyeFieldNumber = 6;
  const ::Segway_proto::CameraIntrinsics& fisheye() const;
  ::Segway_proto::CameraIntrinsics* release_fisheye();
  ::Segway_proto::CameraIntrinsics* mutable_fisheye();
  void set_allocated_fisheye(::Segway_proto::CameraIntrinsics* fisheye);

  // .Segway_proto.CameraExtrinsics fisheye_to_imu = 7;
  bool has_fisheye_to_imu() const;
  void clear_fisheye_to_imu();
  static const int kFisheyeToImuFieldNumber = 7;
  const ::Segway_proto::CameraExtrinsics& fisheye_to_imu() const;
  ::Segway_proto::CameraExtrinsics* release_fisheye_to_imu();
  ::Segway_proto::CameraExtrinsics* mutable_fisheye_to_imu();
  void set_allocated_fisheye_to_imu(::Segway_proto::CameraExtrinsics* fisheye_to_imu);

  // .Segway_proto.Pose3Dd T_V_I = 8;
  bool has_t_v_i() const;
  void clear_t_v_i();
  static const int kTVIFieldNumber = 8;
  const ::Segway_proto::Pose3Dd& t_v_i() const;
  ::Segway_proto::Pose3Dd* release_t_v_i();
  ::Segway_proto::Pose3Dd* mutable_t_v_i();
  void set_allocated_t_v_i(::Segway_proto::Pose3Dd* t_v_i);

  // .Segway_proto.Pose3Dd T_base_lidar = 9;
  bool has_t_base_lidar() const;
  void clear_t_base_lidar();
  static const int kTBaseLidarFieldNumber = 9;
  const ::Segway_proto::Pose3Dd& t_base_lidar() const;
  ::Segway_proto::Pose3Dd* release_t_base_lidar();
  ::Segway_proto::Pose3Dd* mutable_t_base_lidar();
  void set_allocated_t_base_lidar(::Segway_proto::Pose3Dd* t_base_lidar);

  // .Segway_proto.Pose3Dd fake_pose = 10;
  bool has_fake_pose() const;
  void clear_fake_pose();
  static const int kFakePoseFieldNumber = 10;
  const ::Segway_proto::Pose3Dd& fake_pose() const;
  ::Segway_proto::Pose3Dd* release_fake_pose();
  ::Segway_proto::Pose3Dd* mutable_fake_pose();
  void set_allocated_fake_pose(::Segway_proto::Pose3Dd* fake_pose);

  // .Segway_proto.RobotExtParams robot_ext_params = 11;
  bool has_robot_ext_params() const;
  void clear_robot_ext_params();
  static const int kRobotExtParamsFieldNumber = 11;
  const ::Segway_proto::RobotExtParams& robot_ext_params() const;
  ::Segway_proto::RobotExtParams* release_robot_ext_params();
  ::Segway_proto::RobotExtParams* mutable_robot_ext_params();
  void set_allocated_robot_ext_params(::Segway_proto::RobotExtParams* robot_ext_params);

  // bool init_by_set = 5;
  void clear_init_by_set();
  static const int kInitBySetFieldNumber = 5;
  bool init_by_set() const;
  void set_init_by_set(bool value);

  // @@protoc_insertion_point(class_scope:Segway_proto.SlamConfig)
 private:
  class HasBitSetters;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr vision_map_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr lidar_map_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr map_id_;
  ::Segway_proto::Header* header_;
  ::Segway_proto::CameraIntrinsics* fisheye_;
  ::Segway_proto::CameraExtrinsics* fisheye_to_imu_;
  ::Segway_proto::Pose3Dd* t_v_i_;
  ::Segway_proto::Pose3Dd* t_base_lidar_;
  ::Segway_proto::Pose3Dd* fake_pose_;
  ::Segway_proto::RobotExtParams* robot_ext_params_;
  bool init_by_set_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_ninebot_5fzmq_2fslam_5fconfig_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// RobotExtParams

// float base_width = 1;
inline void RobotExtParams::clear_base_width() {
  base_width_ = 0;
}
inline float RobotExtParams::base_width() const {
  // @@protoc_insertion_point(field_get:Segway_proto.RobotExtParams.base_width)
  return base_width_;
}
inline void RobotExtParams::set_base_width(float value) {
  
  base_width_ = value;
  // @@protoc_insertion_point(field_set:Segway_proto.RobotExtParams.base_width)
}

// float wheel_radius = 2;
inline void RobotExtParams::clear_wheel_radius() {
  wheel_radius_ = 0;
}
inline float RobotExtParams::wheel_radius() const {
  // @@protoc_insertion_point(field_get:Segway_proto.RobotExtParams.wheel_radius)
  return wheel_radius_;
}
inline void RobotExtParams::set_wheel_radius(float value) {
  
  wheel_radius_ = value;
  // @@protoc_insertion_point(field_set:Segway_proto.RobotExtParams.wheel_radius)
}

// int32 wheel_resolution = 3;
inline void RobotExtParams::clear_wheel_resolution() {
  wheel_resolution_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 RobotExtParams::wheel_resolution() const {
  // @@protoc_insertion_point(field_get:Segway_proto.RobotExtParams.wheel_resolution)
  return wheel_resolution_;
}
inline void RobotExtParams::set_wheel_resolution(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  wheel_resolution_ = value;
  // @@protoc_insertion_point(field_set:Segway_proto.RobotExtParams.wheel_resolution)
}

// -------------------------------------------------------------------

// SlamConfig

// .Segway_proto.Header header = 1;
inline bool SlamConfig::has_header() const {
  return this != internal_default_instance() && header_ != nullptr;
}
inline const ::Segway_proto::Header& SlamConfig::header() const {
  const ::Segway_proto::Header* p = header_;
  // @@protoc_insertion_point(field_get:Segway_proto.SlamConfig.header)
  return p != nullptr ? *p : *reinterpret_cast<const ::Segway_proto::Header*>(
      &::Segway_proto::_Header_default_instance_);
}
inline ::Segway_proto::Header* SlamConfig::release_header() {
  // @@protoc_insertion_point(field_release:Segway_proto.SlamConfig.header)
  
  ::Segway_proto::Header* temp = header_;
  header_ = nullptr;
  return temp;
}
inline ::Segway_proto::Header* SlamConfig::mutable_header() {
  
  if (header_ == nullptr) {
    auto* p = CreateMaybeMessage<::Segway_proto::Header>(GetArenaNoVirtual());
    header_ = p;
  }
  // @@protoc_insertion_point(field_mutable:Segway_proto.SlamConfig.header)
  return header_;
}
inline void SlamConfig::set_allocated_header(::Segway_proto::Header* header) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(header_);
  }
  if (header) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena = nullptr;
    if (message_arena != submessage_arena) {
      header = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, header, submessage_arena);
    }
    
  } else {
    
  }
  header_ = header;
  // @@protoc_insertion_point(field_set_allocated:Segway_proto.SlamConfig.header)
}

// string vision_map = 2;
inline void SlamConfig::clear_vision_map() {
  vision_map_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& SlamConfig::vision_map() const {
  // @@protoc_insertion_point(field_get:Segway_proto.SlamConfig.vision_map)
  return vision_map_.GetNoArena();
}
inline void SlamConfig::set_vision_map(const std::string& value) {
  
  vision_map_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Segway_proto.SlamConfig.vision_map)
}
inline void SlamConfig::set_vision_map(std::string&& value) {
  
  vision_map_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:Segway_proto.SlamConfig.vision_map)
}
inline void SlamConfig::set_vision_map(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  vision_map_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Segway_proto.SlamConfig.vision_map)
}
inline void SlamConfig::set_vision_map(const char* value, size_t size) {
  
  vision_map_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Segway_proto.SlamConfig.vision_map)
}
inline std::string* SlamConfig::mutable_vision_map() {
  
  // @@protoc_insertion_point(field_mutable:Segway_proto.SlamConfig.vision_map)
  return vision_map_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* SlamConfig::release_vision_map() {
  // @@protoc_insertion_point(field_release:Segway_proto.SlamConfig.vision_map)
  
  return vision_map_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void SlamConfig::set_allocated_vision_map(std::string* vision_map) {
  if (vision_map != nullptr) {
    
  } else {
    
  }
  vision_map_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), vision_map);
  // @@protoc_insertion_point(field_set_allocated:Segway_proto.SlamConfig.vision_map)
}

// string lidar_map = 3;
inline void SlamConfig::clear_lidar_map() {
  lidar_map_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& SlamConfig::lidar_map() const {
  // @@protoc_insertion_point(field_get:Segway_proto.SlamConfig.lidar_map)
  return lidar_map_.GetNoArena();
}
inline void SlamConfig::set_lidar_map(const std::string& value) {
  
  lidar_map_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Segway_proto.SlamConfig.lidar_map)
}
inline void SlamConfig::set_lidar_map(std::string&& value) {
  
  lidar_map_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:Segway_proto.SlamConfig.lidar_map)
}
inline void SlamConfig::set_lidar_map(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  lidar_map_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Segway_proto.SlamConfig.lidar_map)
}
inline void SlamConfig::set_lidar_map(const char* value, size_t size) {
  
  lidar_map_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Segway_proto.SlamConfig.lidar_map)
}
inline std::string* SlamConfig::mutable_lidar_map() {
  
  // @@protoc_insertion_point(field_mutable:Segway_proto.SlamConfig.lidar_map)
  return lidar_map_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* SlamConfig::release_lidar_map() {
  // @@protoc_insertion_point(field_release:Segway_proto.SlamConfig.lidar_map)
  
  return lidar_map_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void SlamConfig::set_allocated_lidar_map(std::string* lidar_map) {
  if (lidar_map != nullptr) {
    
  } else {
    
  }
  lidar_map_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), lidar_map);
  // @@protoc_insertion_point(field_set_allocated:Segway_proto.SlamConfig.lidar_map)
}

// string map_id = 4;
inline void SlamConfig::clear_map_id() {
  map_id_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& SlamConfig::map_id() const {
  // @@protoc_insertion_point(field_get:Segway_proto.SlamConfig.map_id)
  return map_id_.GetNoArena();
}
inline void SlamConfig::set_map_id(const std::string& value) {
  
  map_id_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Segway_proto.SlamConfig.map_id)
}
inline void SlamConfig::set_map_id(std::string&& value) {
  
  map_id_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:Segway_proto.SlamConfig.map_id)
}
inline void SlamConfig::set_map_id(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  map_id_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Segway_proto.SlamConfig.map_id)
}
inline void SlamConfig::set_map_id(const char* value, size_t size) {
  
  map_id_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Segway_proto.SlamConfig.map_id)
}
inline std::string* SlamConfig::mutable_map_id() {
  
  // @@protoc_insertion_point(field_mutable:Segway_proto.SlamConfig.map_id)
  return map_id_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* SlamConfig::release_map_id() {
  // @@protoc_insertion_point(field_release:Segway_proto.SlamConfig.map_id)
  
  return map_id_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void SlamConfig::set_allocated_map_id(std::string* map_id) {
  if (map_id != nullptr) {
    
  } else {
    
  }
  map_id_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), map_id);
  // @@protoc_insertion_point(field_set_allocated:Segway_proto.SlamConfig.map_id)
}

// bool init_by_set = 5;
inline void SlamConfig::clear_init_by_set() {
  init_by_set_ = false;
}
inline bool SlamConfig::init_by_set() const {
  // @@protoc_insertion_point(field_get:Segway_proto.SlamConfig.init_by_set)
  return init_by_set_;
}
inline void SlamConfig::set_init_by_set(bool value) {
  
  init_by_set_ = value;
  // @@protoc_insertion_point(field_set:Segway_proto.SlamConfig.init_by_set)
}

// .Segway_proto.CameraIntrinsics fisheye = 6;
inline bool SlamConfig::has_fisheye() const {
  return this != internal_default_instance() && fisheye_ != nullptr;
}
inline const ::Segway_proto::CameraIntrinsics& SlamConfig::fisheye() const {
  const ::Segway_proto::CameraIntrinsics* p = fisheye_;
  // @@protoc_insertion_point(field_get:Segway_proto.SlamConfig.fisheye)
  return p != nullptr ? *p : *reinterpret_cast<const ::Segway_proto::CameraIntrinsics*>(
      &::Segway_proto::_CameraIntrinsics_default_instance_);
}
inline ::Segway_proto::CameraIntrinsics* SlamConfig::release_fisheye() {
  // @@protoc_insertion_point(field_release:Segway_proto.SlamConfig.fisheye)
  
  ::Segway_proto::CameraIntrinsics* temp = fisheye_;
  fisheye_ = nullptr;
  return temp;
}
inline ::Segway_proto::CameraIntrinsics* SlamConfig::mutable_fisheye() {
  
  if (fisheye_ == nullptr) {
    auto* p = CreateMaybeMessage<::Segway_proto::CameraIntrinsics>(GetArenaNoVirtual());
    fisheye_ = p;
  }
  // @@protoc_insertion_point(field_mutable:Segway_proto.SlamConfig.fisheye)
  return fisheye_;
}
inline void SlamConfig::set_allocated_fisheye(::Segway_proto::CameraIntrinsics* fisheye) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(fisheye_);
  }
  if (fisheye) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena = nullptr;
    if (message_arena != submessage_arena) {
      fisheye = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, fisheye, submessage_arena);
    }
    
  } else {
    
  }
  fisheye_ = fisheye;
  // @@protoc_insertion_point(field_set_allocated:Segway_proto.SlamConfig.fisheye)
}

// .Segway_proto.CameraExtrinsics fisheye_to_imu = 7;
inline bool SlamConfig::has_fisheye_to_imu() const {
  return this != internal_default_instance() && fisheye_to_imu_ != nullptr;
}
inline const ::Segway_proto::CameraExtrinsics& SlamConfig::fisheye_to_imu() const {
  const ::Segway_proto::CameraExtrinsics* p = fisheye_to_imu_;
  // @@protoc_insertion_point(field_get:Segway_proto.SlamConfig.fisheye_to_imu)
  return p != nullptr ? *p : *reinterpret_cast<const ::Segway_proto::CameraExtrinsics*>(
      &::Segway_proto::_CameraExtrinsics_default_instance_);
}
inline ::Segway_proto::CameraExtrinsics* SlamConfig::release_fisheye_to_imu() {
  // @@protoc_insertion_point(field_release:Segway_proto.SlamConfig.fisheye_to_imu)
  
  ::Segway_proto::CameraExtrinsics* temp = fisheye_to_imu_;
  fisheye_to_imu_ = nullptr;
  return temp;
}
inline ::Segway_proto::CameraExtrinsics* SlamConfig::mutable_fisheye_to_imu() {
  
  if (fisheye_to_imu_ == nullptr) {
    auto* p = CreateMaybeMessage<::Segway_proto::CameraExtrinsics>(GetArenaNoVirtual());
    fisheye_to_imu_ = p;
  }
  // @@protoc_insertion_point(field_mutable:Segway_proto.SlamConfig.fisheye_to_imu)
  return fisheye_to_imu_;
}
inline void SlamConfig::set_allocated_fisheye_to_imu(::Segway_proto::CameraExtrinsics* fisheye_to_imu) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(fisheye_to_imu_);
  }
  if (fisheye_to_imu) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena = nullptr;
    if (message_arena != submessage_arena) {
      fisheye_to_imu = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, fisheye_to_imu, submessage_arena);
    }
    
  } else {
    
  }
  fisheye_to_imu_ = fisheye_to_imu;
  // @@protoc_insertion_point(field_set_allocated:Segway_proto.SlamConfig.fisheye_to_imu)
}

// .Segway_proto.Pose3Dd T_V_I = 8;
inline bool SlamConfig::has_t_v_i() const {
  return this != internal_default_instance() && t_v_i_ != nullptr;
}
inline const ::Segway_proto::Pose3Dd& SlamConfig::t_v_i() const {
  const ::Segway_proto::Pose3Dd* p = t_v_i_;
  // @@protoc_insertion_point(field_get:Segway_proto.SlamConfig.T_V_I)
  return p != nullptr ? *p : *reinterpret_cast<const ::Segway_proto::Pose3Dd*>(
      &::Segway_proto::_Pose3Dd_default_instance_);
}
inline ::Segway_proto::Pose3Dd* SlamConfig::release_t_v_i() {
  // @@protoc_insertion_point(field_release:Segway_proto.SlamConfig.T_V_I)
  
  ::Segway_proto::Pose3Dd* temp = t_v_i_;
  t_v_i_ = nullptr;
  return temp;
}
inline ::Segway_proto::Pose3Dd* SlamConfig::mutable_t_v_i() {
  
  if (t_v_i_ == nullptr) {
    auto* p = CreateMaybeMessage<::Segway_proto::Pose3Dd>(GetArenaNoVirtual());
    t_v_i_ = p;
  }
  // @@protoc_insertion_point(field_mutable:Segway_proto.SlamConfig.T_V_I)
  return t_v_i_;
}
inline void SlamConfig::set_allocated_t_v_i(::Segway_proto::Pose3Dd* t_v_i) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(t_v_i_);
  }
  if (t_v_i) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena = nullptr;
    if (message_arena != submessage_arena) {
      t_v_i = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, t_v_i, submessage_arena);
    }
    
  } else {
    
  }
  t_v_i_ = t_v_i;
  // @@protoc_insertion_point(field_set_allocated:Segway_proto.SlamConfig.T_V_I)
}

// .Segway_proto.Pose3Dd T_base_lidar = 9;
inline bool SlamConfig::has_t_base_lidar() const {
  return this != internal_default_instance() && t_base_lidar_ != nullptr;
}
inline const ::Segway_proto::Pose3Dd& SlamConfig::t_base_lidar() const {
  const ::Segway_proto::Pose3Dd* p = t_base_lidar_;
  // @@protoc_insertion_point(field_get:Segway_proto.SlamConfig.T_base_lidar)
  return p != nullptr ? *p : *reinterpret_cast<const ::Segway_proto::Pose3Dd*>(
      &::Segway_proto::_Pose3Dd_default_instance_);
}
inline ::Segway_proto::Pose3Dd* SlamConfig::release_t_base_lidar() {
  // @@protoc_insertion_point(field_release:Segway_proto.SlamConfig.T_base_lidar)
  
  ::Segway_proto::Pose3Dd* temp = t_base_lidar_;
  t_base_lidar_ = nullptr;
  return temp;
}
inline ::Segway_proto::Pose3Dd* SlamConfig::mutable_t_base_lidar() {
  
  if (t_base_lidar_ == nullptr) {
    auto* p = CreateMaybeMessage<::Segway_proto::Pose3Dd>(GetArenaNoVirtual());
    t_base_lidar_ = p;
  }
  // @@protoc_insertion_point(field_mutable:Segway_proto.SlamConfig.T_base_lidar)
  return t_base_lidar_;
}
inline void SlamConfig::set_allocated_t_base_lidar(::Segway_proto::Pose3Dd* t_base_lidar) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(t_base_lidar_);
  }
  if (t_base_lidar) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena = nullptr;
    if (message_arena != submessage_arena) {
      t_base_lidar = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, t_base_lidar, submessage_arena);
    }
    
  } else {
    
  }
  t_base_lidar_ = t_base_lidar;
  // @@protoc_insertion_point(field_set_allocated:Segway_proto.SlamConfig.T_base_lidar)
}

// .Segway_proto.Pose3Dd fake_pose = 10;
inline bool SlamConfig::has_fake_pose() const {
  return this != internal_default_instance() && fake_pose_ != nullptr;
}
inline const ::Segway_proto::Pose3Dd& SlamConfig::fake_pose() const {
  const ::Segway_proto::Pose3Dd* p = fake_pose_;
  // @@protoc_insertion_point(field_get:Segway_proto.SlamConfig.fake_pose)
  return p != nullptr ? *p : *reinterpret_cast<const ::Segway_proto::Pose3Dd*>(
      &::Segway_proto::_Pose3Dd_default_instance_);
}
inline ::Segway_proto::Pose3Dd* SlamConfig::release_fake_pose() {
  // @@protoc_insertion_point(field_release:Segway_proto.SlamConfig.fake_pose)
  
  ::Segway_proto::Pose3Dd* temp = fake_pose_;
  fake_pose_ = nullptr;
  return temp;
}
inline ::Segway_proto::Pose3Dd* SlamConfig::mutable_fake_pose() {
  
  if (fake_pose_ == nullptr) {
    auto* p = CreateMaybeMessage<::Segway_proto::Pose3Dd>(GetArenaNoVirtual());
    fake_pose_ = p;
  }
  // @@protoc_insertion_point(field_mutable:Segway_proto.SlamConfig.fake_pose)
  return fake_pose_;
}
inline void SlamConfig::set_allocated_fake_pose(::Segway_proto::Pose3Dd* fake_pose) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(fake_pose_);
  }
  if (fake_pose) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena = nullptr;
    if (message_arena != submessage_arena) {
      fake_pose = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, fake_pose, submessage_arena);
    }
    
  } else {
    
  }
  fake_pose_ = fake_pose;
  // @@protoc_insertion_point(field_set_allocated:Segway_proto.SlamConfig.fake_pose)
}

// .Segway_proto.RobotExtParams robot_ext_params = 11;
inline bool SlamConfig::has_robot_ext_params() const {
  return this != internal_default_instance() && robot_ext_params_ != nullptr;
}
inline void SlamConfig::clear_robot_ext_params() {
  if (GetArenaNoVirtual() == nullptr && robot_ext_params_ != nullptr) {
    delete robot_ext_params_;
  }
  robot_ext_params_ = nullptr;
}
inline const ::Segway_proto::RobotExtParams& SlamConfig::robot_ext_params() const {
  const ::Segway_proto::RobotExtParams* p = robot_ext_params_;
  // @@protoc_insertion_point(field_get:Segway_proto.SlamConfig.robot_ext_params)
  return p != nullptr ? *p : *reinterpret_cast<const ::Segway_proto::RobotExtParams*>(
      &::Segway_proto::_RobotExtParams_default_instance_);
}
inline ::Segway_proto::RobotExtParams* SlamConfig::release_robot_ext_params() {
  // @@protoc_insertion_point(field_release:Segway_proto.SlamConfig.robot_ext_params)
  
  ::Segway_proto::RobotExtParams* temp = robot_ext_params_;
  robot_ext_params_ = nullptr;
  return temp;
}
inline ::Segway_proto::RobotExtParams* SlamConfig::mutable_robot_ext_params() {
  
  if (robot_ext_params_ == nullptr) {
    auto* p = CreateMaybeMessage<::Segway_proto::RobotExtParams>(GetArenaNoVirtual());
    robot_ext_params_ = p;
  }
  // @@protoc_insertion_point(field_mutable:Segway_proto.SlamConfig.robot_ext_params)
  return robot_ext_params_;
}
inline void SlamConfig::set_allocated_robot_ext_params(::Segway_proto::RobotExtParams* robot_ext_params) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == nullptr) {
    delete robot_ext_params_;
  }
  if (robot_ext_params) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena = nullptr;
    if (message_arena != submessage_arena) {
      robot_ext_params = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, robot_ext_params, submessage_arena);
    }
    
  } else {
    
  }
  robot_ext_params_ = robot_ext_params;
  // @@protoc_insertion_point(field_set_allocated:Segway_proto.SlamConfig.robot_ext_params)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace Segway_proto

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_ninebot_5fzmq_2fslam_5fconfig_2eproto
