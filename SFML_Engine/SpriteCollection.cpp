#include "SpriteCollection.h"
#include <iostream>
SpriteCollection::SpriteCollection() {}

SpriteCollection::SpriteCollection(sf::RenderWindow* pwindow, Graphics* pgraphics) {
	pGraphics = pgraphics;
	pWindow = pwindow;
}

void SpriteCollection::createSprite(std::string name, std::string path, int width, int height, int frames, float _scale){
	sprites.push_back(new Sprite(pWindow, name, path, width, height, frames, _scale));
}

void SpriteCollection::createSprite(std::string name, std::string path, float _scale){
	sprites.push_back(new Sprite(pWindow, name, path, _scale));
}

Sprite* SpriteCollection::getPointerFromName(std::string name) {
	for (int i = 0; i < sprites.size(); i++) {
		if (sprites[i]->getName().compare(name) == 0) {
			return sprites[i];
		}
	}
}

void SpriteCollection::setUseCamera(bool _useCamera) {
	useCamera = _useCamera;
}

void SpriteCollection::setPCamera(Camera* _pCamera) {
	pCamera = _pCamera;
}

void SpriteCollection::setOrderZ(bool _orderZ) {
	orderZ = _orderZ;
}

void SpriteCollection::addSpriteDraw(Sprite* pSprite, float x, float y, float z){
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(pSprite, x, y, z);
	currentDrawIndex++;
}

void SpriteCollection::addRectDraw(float x, float y, float w, float h, float z, sf::Color color) {
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(x, y, w, h, z, color);
	currentDrawIndex++; 
}

void SpriteCollection::addCircleDraw(float x, float y, float r, float z, sf::Color color) {
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(x, y, r, z, color);
	currentDrawIndex++;
}

void SpriteCollection::addAbsoluteSpriteDraw(Sprite* pSprite, float x, float y, float z) {
	if (currentAbsoluteDrawIndex >= maxAbsoluteSpriteDraws) {
		std::cout << "MAX NUMBER OF ABSOLUTESPRITEDRAWS REACHED!\n";
		return;
	}
	absoluteSpriteDraws[currentAbsoluteDrawIndex] = new SpriteDraw(pSprite, x, y, z);
	currentAbsoluteDrawIndex++;

}

void SpriteCollection::addAbsoluteRectDraw(float x, float y, float w, float h, float z, sf::Color color) {
	if (currentAbsoluteDrawIndex >= maxAbsoluteSpriteDraws) {
		std::cout << "MAX NUMBER OF ABSOLUTESPRITEDRAWS REACHED!\n";
		return;
	}
	absoluteSpriteDraws[currentAbsoluteDrawIndex] = new SpriteDraw(x, y, w, h, z, color);
	currentAbsoluteDrawIndex++;
}

void SpriteCollection::addAbsoluteCircleDraw(float x, float y, float r, float z, sf::Color color) {
	if (currentAbsoluteDrawIndex >= maxAbsoluteSpriteDraws) {
		std::cout << "MAX NUMBER OF ABSOLUTESPRITEDRAWS REACHED!\n";
		return;
	}
	absoluteSpriteDraws[currentAbsoluteDrawIndex] = new SpriteDraw(x, y, r, z, color);
	currentAbsoluteDrawIndex++;
}

void SpriteCollection::addTextDraw(int fontIndex, float x, float y, float z, std::string string, int fontSize, sf::Color color) {
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(fontIndex, x, y, z, string, fontSize, color);
	currentDrawIndex++;
}

void SpriteCollection::addAbsoluteTextDraw(int fontIndex, float x, float y, float z, std::string string, int fontSize, sf::Color color) {
	if (currentAbsoluteDrawIndex >= maxAbsoluteSpriteDraws) {
		std::cout << "MAX NUMBER OF ABSOLUTESPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentAbsoluteDrawIndex] = new SpriteDraw(fontIndex, x, y, z, string, fontSize, color);
	currentAbsoluteDrawIndex++;
}

void SpriteCollection::drawAll() {
	if (orderZ) {
		orderByZ();
	}
	glm::vec2 temp;
	for (int i = 0; i < currentDrawIndex; i++) {
		if (useCamera) {
			temp = pCamera->transformPosition(glm::vec2(spriteDraws[i]->x, spriteDraws[i]->y));
			if (spriteDraws[i]->type == 0) {
				spriteDraws[i]->pSprite->draw(temp.x, temp.y);
			}
			else if (spriteDraws[i]->type == 1) {
				pGraphics->drawRect(temp.x, temp.y, spriteDraws[i]->w, spriteDraws[i]->h, spriteDraws[i]->color);
			}
			else if (spriteDraws[i]->type == 2) {
				pGraphics->drawCircle(temp.x, temp.y, spriteDraws[i]->r, spriteDraws[i]->color);
			}
			else if (spriteDraws[i]->type == 3) {
				drawText(spriteDraws[i]->fontIndex, temp.x, temp.y, spriteDraws[i]->string, spriteDraws[i]->fontSize, spriteDraws[i]->color);
			}
		}
		else {
			if (spriteDraws[i]->type == 0) {
				spriteDraws[i]->pSprite->draw(spriteDraws[i]->x, spriteDraws[i]->y);
			}
			else if (spriteDraws[i]->type == 1) {
				pGraphics->drawRect(spriteDraws[i]->x, spriteDraws[i]->y, spriteDraws[i]->w, spriteDraws[i]->h, spriteDraws[i]->color);
			}
			else if (spriteDraws[i]->type == 2) {
				pGraphics->drawCircle(spriteDraws[i]->x, spriteDraws[i]->y, spriteDraws[i]->r, spriteDraws[i]->color);
			}
			else if (spriteDraws[i]->type == 3) {
				drawText(spriteDraws[i]->fontIndex, spriteDraws[i]->x, spriteDraws[i]->y, spriteDraws[i]->string, spriteDraws[i]->fontSize, spriteDraws[i]->color);
			}
		}
	}
	for (int i = 0; i < currentAbsoluteDrawIndex; i++) {
		if (absoluteSpriteDraws[i]->type == 0) {
			absoluteSpriteDraws[i]->pSprite->draw(absoluteSpriteDraws[i]->x, absoluteSpriteDraws[i]->y);
		}
		else if (absoluteSpriteDraws[i]->type == 1) {
			pGraphics->drawRect(absoluteSpriteDraws[i]->x, absoluteSpriteDraws[i]->y, absoluteSpriteDraws[i]->w, absoluteSpriteDraws[i]->h, absoluteSpriteDraws[i]->color);
		}
		else {
			pGraphics->drawCircle(absoluteSpriteDraws[i]->x, absoluteSpriteDraws[i]->y, absoluteSpriteDraws[i]->r, absoluteSpriteDraws[i]->color);
		}
	}
	clearSpriteDraws();
}

void SpriteCollection::drawText(int fontIndex, float x, float y, std::string string, int fontSize, sf::Color color) {
	sf::Text text;

	// select the font
	text.setFont(fonts[fontIndex]); // font is a sf::Font

	// set the string to display
	text.setString(string);

	// set the character size
	text.setCharacterSize(fontSize); // in pixels, not points!

	// set the color
	text.setFillColor(color);

	// set the text style
	text.setStyle(sf::Text::Regular);

	text.setPosition(x, y);

	pWindow->draw(text);
}

void SpriteCollection::addFont(std::string name) {
	sf::Font temp;
	if (!temp.loadFromFile("Taurus-Mono-Outline-Regular.ttf")) {
		std::cout << "ERROR LOADING FONT\n";
	}
	fonts.push_back(temp);
}

void SpriteCollection::clearSpriteDraws() {
	currentDrawIndex = 0;
	currentAbsoluteDrawIndex = 0;
}

void SpriteCollection::orderByZ() {
	SpriteDraw *temp;
	for (int i = 0; i < currentDrawIndex; i++) {
		for (int j = 0; j < currentDrawIndex - 1 - i; j++) {
			if (spriteDraws[j]->z > spriteDraws[j + 1]->z) {
				temp = spriteDraws[j + 1];
				spriteDraws[j + 1] = spriteDraws[j];
				spriteDraws[j] = temp;;
			}
		}
	}
}
