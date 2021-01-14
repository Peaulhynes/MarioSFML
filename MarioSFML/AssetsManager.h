#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class AssetsManager
{

public:

    AssetsManager() = default;
    ~AssetsManager() = default;

    std::map<std::string, sf::Texture> getTextures();
    std::map<std::string, sf::Font> getFonts();

    void loadTexture(const std::string& name, const std::string& filename);
    void loadFont(const std::string& name, const std::string& filename);
    
    sf::Texture& getTRef(const std::string& texture);
    sf::Font& getFRef(const std::string& font);
    
private:
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;
};

#endif 