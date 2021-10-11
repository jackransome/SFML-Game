#include "SpriteCollection.h"
#include <iostream>
SpriteCollection::SpriteCollection() {}

SpriteCollection::SpriteCollection(sf::RenderWindow* pwindow, Graphics* pgraphics) {
	pGraphics = pgraphics;
	pWindow = pwindow;
}

void SpriteCollection::loadImage(std::string name, std::string path){
	images.push_back(new Image(pWindow, name, path));
}

Image* SpriteCollection::getPointerFromName(std::string name) {
	for (int i = 0; i < images.size(); i++) {
		if (images[i]->getName().compare(name) == 0) {
			return images[i];
		}
	}
	std::cout << "NO SUCH IMAGE: " << name << "\n";
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

void SpriteCollection::addImageDraw(Image* pImage, float x, float y, float z){
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(pImage, x, y, z, 1);
	currentDrawIndex++;
}
void SpriteCollection::addImageDraw(Image* pImage, float x, float y, float z, int sX, int sY, int sW, int sH) {
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(pImage, x, y, z, sX, sY, sW, sH, 1);
	currentDrawIndex++;
}
void SpriteCollection::addImageDraw(Image* pImage, float x, float y, float z, float scale) {
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(pImage, x, y, z, scale);
	currentDrawIndex++;
}
void SpriteCollection::addImageDraw(Image* pImage, float x, float y, float z, int sX, int sY, int sW, int sH, float scale) {
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(pImage, x, y, z, sX, sY, sW, sH, scale);
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

void SpriteCollection::addAbsoluteImageDraw(Image* pImage, float x, float y, float z) {
	if (currentAbsoluteDrawIndex >= maxAbsoluteSpriteDraws) {
		std::cout << "MAX NUMBER OF ABSOLUTESPRITEDRAWS REACHED!\n";
		return;
	}
	absoluteSpriteDraws[currentAbsoluteDrawIndex] = new SpriteDraw(pImage, x, y, z, 1);
	currentAbsoluteDrawIndex++;
}

void SpriteCollection::addAbsoluteImageDraw(Image* pImage, float x, float y, float z, int sX, int sY, int sW, int sH) {
	if (currentAbsoluteDrawIndex >= maxAbsoluteSpriteDraws) {
		std::cout << "MAX NUMBER OF ABSOLUTESPRITEDRAWS REACHED!\n";
		return;
	}
	absoluteSpriteDraws[currentAbsoluteDrawIndex] = new SpriteDraw(pImage, x, y, z, sX, sY, sW, sH, 1);
	currentAbsoluteDrawIndex++;
}

void SpriteCollection::addAbsoluteImageDraw(Image* pImage, float x, float y, float z, float scale) {
	if (currentAbsoluteDrawIndex >= maxAbsoluteSpriteDraws) {
		std::cout << "MAX NUMBER OF ABSOLUTESPRITEDRAWS REACHED!\n";
		return;
	}
	absoluteSpriteDraws[currentAbsoluteDrawIndex] = new SpriteDraw(pImage, x, y, z, scale);
	currentAbsoluteDrawIndex++;
}

void SpriteCollection::addAbsoluteImageDraw(Image* pImage, float x, float y, float z, int sX, int sY, int sW, int sH, float scale) {
	if (currentAbsoluteDrawIndex >= maxAbsoluteSpriteDraws) {
		std::cout << "MAX NUMBER OF ABSOLUTESPRITEDRAWS REACHED!\n";
		return;
	}
	absoluteSpriteDraws[currentAbsoluteDrawIndex] = new SpriteDraw(pImage, x, y, z, sX, sY, sW, sH, scale);
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
				spriteDraws[i]->pImage->draw(temp.x, temp.y, spriteDraws[i]->scale);
			}
			else if (spriteDraws[i]->type == 1) {
				spriteDraws[i]->pImage->drawSection(temp.x, temp.y, spriteDraws[i]->sX, spriteDraws[i]->sY, spriteDraws[i]->sW, spriteDraws[i]->sH, spriteDraws[i]->scale);
			}
			else if (spriteDraws[i]->type == 2) {
				pGraphics->drawRect(temp.x, temp.y, spriteDraws[i]->w, spriteDraws[i]->h, spriteDraws[i]->color);
			}
			else if (spriteDraws[i]->type == 3) {
				pGraphics->drawCircle(temp.x, temp.y, spriteDraws[i]->r, spriteDraws[i]->color);
			}
			else if (spriteDraws[i]->type == 4) {
				drawText(spriteDraws[i]->fontIndex, temp.x, temp.y, spriteDraws[i]->string, spriteDraws[i]->fontSize, spriteDraws[i]->color);
			}
		}
		else {
			if (spriteDraws[i]->type == 0) {
				spriteDraws[i]->pImage->draw(spriteDraws[i]->x, spriteDraws[i]->y, spriteDraws[i]->scale);
			}
			else if (spriteDraws[i]->type == 1) {
				spriteDraws[i]->pImage->drawSection(spriteDraws[i]->x, spriteDraws[i]->y, spriteDraws[i]->sX, spriteDraws[i]->sY, spriteDraws[i]->sW, spriteDraws[i]->sH, spriteDraws[i]->scale);
			}
			else if (spriteDraws[i]->type == 2) {
				pGraphics->drawRect(spriteDraws[i]->x, spriteDraws[i]->y, spriteDraws[i]->w, spriteDraws[i]->h, spriteDraws[i]->color);
			}
			else if (spriteDraws[i]->type == 3) {
				pGraphics->drawCircle(spriteDraws[i]->x, spriteDraws[i]->y, spriteDraws[i]->r, spriteDraws[i]->color);
			}
			else if (spriteDraws[i]->type == 4) {
				drawText(spriteDraws[i]->fontIndex, spriteDraws[i]->x, spriteDraws[i]->y, spriteDraws[i]->string, spriteDraws[i]->fontSize, spriteDraws[i]->color);
			}
		}
	}
	for (int i = 0; i < currentAbsoluteDrawIndex; i++) {
		if (absoluteSpriteDraws[i]->type == 0) {
			absoluteSpriteDraws[i]->pImage->draw(absoluteSpriteDraws[i]->x, absoluteSpriteDraws[i]->y, spriteDraws[i]->scale);
		}
		else if (absoluteSpriteDraws[i]->type == 1) {
			absoluteSpriteDraws[i]->pImage->drawSection(absoluteSpriteDraws[i]->x, absoluteSpriteDraws[i]->y, absoluteSpriteDraws[i]->sX, absoluteSpriteDraws[i]->sY, absoluteSpriteDraws[i]->sW, absoluteSpriteDraws[i]->sH, spriteDraws[i]->scale);
		}
		else if (absoluteSpriteDraws[i]->type == 2) {
			pGraphics->drawRect(absoluteSpriteDraws[i]->x, absoluteSpriteDraws[i]->y, absoluteSpriteDraws[i]->w, absoluteSpriteDraws[i]->h, absoluteSpriteDraws[i]->color);
		}
		else if (absoluteSpriteDraws[i]->type == 3) {
			pGraphics->drawCircle(absoluteSpriteDraws[i]->x, absoluteSpriteDraws[i]->y, absoluteSpriteDraws[i]->r, absoluteSpriteDraws[i]->color);
		}
		else if (absoluteSpriteDraws[i]->type == 4) {
			drawText(absoluteSpriteDraws[i]->fontIndex, absoluteSpriteDraws[i]->x, absoluteSpriteDraws[i]->y, absoluteSpriteDraws[i]->string, absoluteSpriteDraws[i]->fontSize, absoluteSpriteDraws[i]->color);
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

void SpriteCollection::addFont(std::string path) {
	sf::Font temp;
	if (!temp.loadFromFile(path)) {
		std::cout << "ERROR LOADING FONT\n";
	}
	fonts.push_back(temp);
}

void SpriteCollection::clearSpriteDraws() {
	for (int i = 0; i < currentDrawIndex; i++) {
		delete spriteDraws[i];
	}
	for (int i = 0; i < currentAbsoluteDrawIndex; i++) {
		delete absoluteSpriteDraws[i];
	}

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
