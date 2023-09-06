// Code generated by ObjectBox; DO NOT EDIT.

#pragma once

#include <cstdbool>
#include <cstdint>

#include "flatbuffers/flatbuffers.h"
#include "objectbox.h"
#include "objectbox.hpp"

struct Dir; 
struct File; 

struct Dir_;

struct Dir {
    obx_id id;
    obx_id child_dirs;
    obx_id child_files;

    struct _OBX_MetaInfo {
        static constexpr obx_schema_id entityId() { return 1; }
    
        static void setObjectId(Dir& object, obx_id newId) { object.id = newId; }
    
        /// Write given object to the FlatBufferBuilder
        static void toFlatBuffer(flatbuffers::FlatBufferBuilder& fbb, const Dir& object);
    
        /// Read an object from a valid FlatBuffer
        static Dir fromFlatBuffer(const void* data, size_t size);
    
        /// Read an object from a valid FlatBuffer
        static std::unique_ptr<Dir> newFromFlatBuffer(const void* data, size_t size);
    
        /// Read an object from a valid FlatBuffer
        static void fromFlatBuffer(const void* data, size_t size, Dir& outObject);
    };
};

struct Dir_ {
    static const obx::Property<Dir, OBXPropertyType_Long> id;
    static const obx::RelationProperty<Dir, Dir> child_dirs;
    static const obx::RelationProperty<Dir, File> child_files;
};


struct File_;

struct File {
    obx_id id;
    std::string filename;
    std::string content;

    struct _OBX_MetaInfo {
        static constexpr obx_schema_id entityId() { return 2; }
    
        static void setObjectId(File& object, obx_id newId) { object.id = newId; }
    
        /// Write given object to the FlatBufferBuilder
        static void toFlatBuffer(flatbuffers::FlatBufferBuilder& fbb, const File& object);
    
        /// Read an object from a valid FlatBuffer
        static File fromFlatBuffer(const void* data, size_t size);
    
        /// Read an object from a valid FlatBuffer
        static std::unique_ptr<File> newFromFlatBuffer(const void* data, size_t size);
    
        /// Read an object from a valid FlatBuffer
        static void fromFlatBuffer(const void* data, size_t size, File& outObject);
    };
};

struct File_ {
    static const obx::Property<File, OBXPropertyType_Long> id;
    static const obx::Property<File, OBXPropertyType_String> filename;
    static const obx::Property<File, OBXPropertyType_String> content;
};
