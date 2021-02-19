#include "AssetsManager.h"

void AssetsManager::loadTexture(const std::string& name, const std::string& filename)
{
    /* Load the texture */
    sf::Texture texture;
    if (!texture.loadFromFile(filename))
        exit(LoadingCodes::LOADING_TEXTURE_CODE);

    /* Add it to the list of textures */
    this->textures[name] = texture;
}

void AssetsManager::loadFont(const std::string& name, const std::string& filename)
{
    /* Load the font */
    sf::Font font;
    if (!font.loadFromFile(filename))
        exit(LoadingCodes::LOADING_FONT_CODE);

    /* Add it to the list of fonts */
    this->fonts[name] = font;
}

void AssetsManager::loadMap(const std::string& name, const std::string& filename)
{   
    /* Add map to the list of maps */
    this->maps[name] = filename;
}

sf::Texture& AssetsManager::getTRef(const std::string& texture)
{
    return this->textures.at(texture);
}

sf::Font& AssetsManager::getFRef(const std::string& font)
{
    return this->fonts.at(font);
}

std::string& AssetsManager::getMRef(const std::string& map)
{
    return this->maps.at(map);
}