// src/tools/tool_registry.cpp — YOU IMPLEMENT (spec §4.3).
//
// A hand-written hash table. No std::unordered_map / std::map / std::set.
// Every function below is a stub so the starter compiles. Replace each body.

#include "tools/tool_registry.h"
#include <cstdint>
#include <utility>

ToolRegistry::ToolRegistry() : buckets_(8), count_(0) {}
ToolRegistry::~ToolRegistry() = default; // unique_ptrs in your buckets free the tools

std::size_t ToolRegistry::index_for(std::string_view key, std::size_t nbuckets) noexcept
{
    return hash(key) & (nbuckets - 1);
}

void ToolRegistry::grow()
{
    std::size_t new_count = buckets_.size() * 2;
    std::vector<std::vector<Entry>> new_buckets(new_count);
    for (std::vector<Entry> &bucket : buckets_)
    {
        for (Entry &e : bucket)
        {
            std::size_t idx = index_for(e.key, new_count);
            new_buckets[idx].push_back(std::move(e));
        }
    }
    buckets_ = std::move(new_buckets);
}

std::size_t ToolRegistry::hash(std::string_view key) noexcept
{
    std::uint64_t h = 1469598103934665603ULL;
    for (unsigned char c : key)
    {
        h ^= c;
        h *= 1099511628211ULL;
    }
    return static_cast<std::size_t>(h);
}

bool ToolRegistry::add(std::unique_ptr<Tool> tool)
{
    if (!tool)
    {
        return false;
    }
    std::string key = tool->name();
    if (find(key) != nullptr)
    {
        return false;
    }
    if (count_ + 1 > buckets_.size())
    {
        grow();
    }
    std::size_t idx = index_for(key, buckets_.size());
    buckets_[idx].push_back(Entry{std::move(key), std::move(tool)});
    count_++;
    return true;
}

Tool *ToolRegistry::find(std::string_view name) const
{
    std::size_t idx = index_for(name, buckets_.size());
    const std::vector<Entry> &bucket = buckets_[idx];
    for (const Entry &e : bucket)
    {
        if (e.key == name)
        {
            return e.tool.get();
        }
    }
    return nullptr;
}

std::size_t ToolRegistry::size() const noexcept
{
    return count_;
}

void ToolRegistry::for_each(const std::function<void(const Tool &)> &fn) const
{
    for (const std::vector<Entry> &bucket : buckets_)
    {
        for (const Entry &e : bucket)
        {
            fn(*e.tool);
        }
    }
}

std::size_t ToolRegistry::bucket_count() const noexcept
{
    return buckets_.size();
}

double ToolRegistry::load_factor() const noexcept
{
    return static_cast<double>(count_) / static_cast<double>(buckets_.size());
}

std::size_t ToolRegistry::max_probe_length() const
{
    std::size_t longest = 0;
    for (const std::vector<Entry> &bucket : buckets_)
    {
        if (bucket.size() > longest)
        {
            longest = bucket.size();
        }
    }
    return longest;
}
