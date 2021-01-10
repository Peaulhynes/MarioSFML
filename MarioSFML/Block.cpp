#include "Block.h"

Block::Block(sf::Vector2f size, sf::Texture* texture) {
	block.setSize(size);
	block.setTexture(texture);
}

Block::~Block(){}