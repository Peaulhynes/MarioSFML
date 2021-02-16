#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

enum LoadingCodes
{
    LOADING_TEXTURE_CODE,
    LOADING_FONT_CODE
};

class AssetsManager
{

public:

    AssetsManager() = default;
    ~AssetsManager() = default;

    /* Load texture with name and filename. */
    void loadTexture(const std::string& name, const std::string& filename);

    /* Load font with name and filename. */
    void loadFont(const std::string& name, const std::string& filename);
    
    /* Get texture reference in memory with its name. */
    sf::Texture& getTRef(const std::string& texture);

    /* Get font reference in memory with its name. */
    sf::Font& getFRef(const std::string& font);
    
private:
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;
};

#endif 