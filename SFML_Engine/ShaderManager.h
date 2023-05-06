#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <memory>

class ShaderManager {
public:
    bool loadShader(const std::string& name, const std::string& path, sf::Shader::Type type) {
        auto shader = std::make_unique<sf::Shader>();
        if (shader->loadFromFile(path, type)) {
            shaders[name] = std::move(shader);
            return true;
        }
        std::cout << "SHADER " + name + " unable to be loaded\n";
        return false;
    }

    sf::Shader* getShader(const std::string& name) {
        auto it = shaders.find(name);
        if (it != shaders.end()) {
            return it->second.get();
        }
        return nullptr;
    }

private:
    std::unordered_map<std::string, std::unique_ptr<sf::Shader>> shaders;
};