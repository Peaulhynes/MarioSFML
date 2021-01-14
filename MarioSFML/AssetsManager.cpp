#include "AssetsManager.h"
#include "ErrorCodes.h"

std::map<std::string, sf::Texture> AssetsManager::getTextures() {
    return textures;
}
std::map<std::string, sf::Font> AssetsManager::getFonts() {
    return fonts;
}

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

sf::Texture& AssetsManager::getTRef(const std::string& texture)
{
    return this->textures.at(texture);
}

sf::Font& AssetsManager::getFRef(const std::string& font)
{
    return this->fonts.at(font);
}