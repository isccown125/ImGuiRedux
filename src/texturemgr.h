#pragma once
#include "pch.h"

struct TextureInfo {
  public:
    std::string path;
    void *pTexture;
    unsigned int lastAccessed; // last time when the texture was accessed (seconds)

    TextureInfo() {};
};

/*
    Handles loading, unloading images.
    Scripts get a handle (1-based index into textureList), never a pointer: script ints are 32-bit (a 64-bit
    pointer got truncated) and vector elements move when the list grows (old pointers dangled).
    Slots are never erased, so a handle stays valid for the whole session.
*/
class TextureMgr {
  private:
    static inline std::vector<TextureInfo> textureList;

  public:
    TextureMgr() = delete;
    TextureMgr(TextureMgr&) = delete;

    // Returns the texture of a handle, loading it on first use; nullptr for a bad handle or a failed load
    static void* GetTexture(int handle);

    // Releases the texture; the handle stays valid and reloads on next use
    static void FreeTexture(int handle);

    // Loads texture, handles different backends
    static void LoadTexture(TextureInfo &info);

    // Registers an image path (same path = same handle), returns its handle
    static int LoadTextureFromPath(const char *path);
};
