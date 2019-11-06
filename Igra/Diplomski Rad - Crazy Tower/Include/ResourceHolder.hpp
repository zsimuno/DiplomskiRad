#ifndef RESOURCEHOLDER_HPP
#define RESOURCEHOLDER_HPP

#include <map>
#include <string>
#include <memory>
#include <cassert>
#include <stdexcept>

template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
	void load(Identifier id, const std::string& filename);
	Resource& get(Identifier id);
	const Resource& get(Identifier id) const;
	
private:
	std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};


#include "ResourceHolder.inl"

#endif // RESOURCEHOLDER_HPP