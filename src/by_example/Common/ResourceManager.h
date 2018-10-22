#pragma once
#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Utilities.h"

template<typename  Derived, typename T>
class ResourceManager
{
public:
	ResourceManager(const std::string& pathFile)
	{
		LoadPaths(pathFile);
	}

	virtual ~ResourceManager()
	{
		PurgeResources();
	}

	T* GetResource(const std::string& id)
	{
		auto res = Find(id);
		return res ? res->first : nullptr;
	}

	std::string GetPath(const std::string& id)
	{
		auto path = m_paths.find(id);
		return path != m_paths.end() ? path->second : "";
	}

	bool RequireResource(const std::string& id)
	{
		auto res = Find(id);
		if(res)
		{
			++res->second;
			return true;
		}
		auto path = m_paths.find(id);
		if(path == m_paths.end()) return false;
		T* resource = Load(path->second);
		if(!resource) return false;
		m_resources.emplace(id, std::make_pair(resource, 1));
		return true;
	}

	bool ReleaseResource(const std::string& id)
	{
		auto res = Find(id);
		if(!res) return false;
		--res->second;
		if(!res->second) Unload(id);
		return true;
	}

	void PurgeResources()
	{
		while(m_resources.begin() != m_resources.end())
		{
			delete m_resources.begin()->second.first;
			m_resources.erase(m_resources.begin());
		}
	}

	// Curiously recurring Template Pattern
	T* Load(const std::string& path)
	{
		return static_cast<Derived*>(this)->Load(path);
	}

private:

	std::unordered_map<std::string, std::pair<T*, unsigned int>> m_resources;
	std::unordered_map<std::string, std::string> m_paths;

	std::pair<T*, unsigned int>* Find(const std::string& id)
	{
		auto it = m_resources.find(id);
		return it != m_resources.end() ? &it->second : nullptr;
	}

	bool Unload(const std::string& id)
	{
		auto it = m_resources.find(id);
		if(it == m_resources.end()) return false;
		delete it->second.first;
		m_resources.erase(it);
		return true;
	}

	void LoadPaths(const std::string& pathFile)
	{
		std::ifstream paths;
		// paths.open(Utils::GetWorkingDirectory() + pathFile);
		paths.open(pathFile);
		if(paths.is_open())
		{
			std::string line;
			while(std::getline(paths, line))
			{
				std::stringstream keyStream(line);
				std::string pathName;
				std::string path;
				keyStream >> pathName;
				keyStream >> path;
				m_paths.emplace(pathName, path);
			}
			paths.close();
			return;
		}
		std::cerr << "! Failed loading the path file: " << pathFile << std::endl;
	}
};
