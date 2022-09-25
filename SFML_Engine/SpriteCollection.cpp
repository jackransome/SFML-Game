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
	spriteDraws[currentDrawIndex]->setShader(lightingShader);
	currentDrawIndex++;
	lastAbsolute = false;
}
void SpriteCollection::addImageDraw(Image* pImage, float x, float y, float z, int sX, int sY, int sW, int sH) {
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(pImage, x, y, z, sX, sY, sW, sH, 1);
	spriteDraws[currentDrawIndex]->setShader(lightingShader);
	currentDrawIndex++;
	lastAbsolute = false;
}
void SpriteCollection::addImageDraw(Image* pImage, float x, float y, float z, float scale) {
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(pImage, x, y, z, scale);
	spriteDraws[currentDrawIndex]->setShader(lightingShader);
	currentDrawIndex++;
	lastAbsolute = false;
}
void SpriteCollection::addImageDraw(Image* pImage, float x, float y, float z, float scale, float opacity) {
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(pImage, x, y, z, scale, opacity);
	spriteDraws[currentDrawIndex]->setShader(lightingShader);
	currentDrawIndex++;
	lastAbsolute = false;
}

void SpriteCollection::addImageDraw(Image* pImage, float x, float y, float z, int sX, int sY, int sW, int sH, float scale) {
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(pImage, x, y, z, sX, sY, sW, sH, scale);
	spriteDraws[currentDrawIndex]->setShader(lightingShader);
	currentDrawIndex++;
	lastAbsolute = false;
}

void SpriteCollection::addImageDraw(Image* pImage, float x, float y, float z, int sX, int sY, int sW, int sH, float scale, float opacity) {
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(pImage, x, y, z, sX, sY, sW, sH, scale, opacity);
	spriteDraws[currentDrawIndex]->setShader(lightingShader);
	currentDrawIndex++;
	lastAbsolute = false;
}

void SpriteCollection::addRotatedImageDraw(Image* pImage, float x, float y, float z, float scale, float rotation){
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(pImage, x, y, z, scale);
	spriteDraws[currentDrawIndex]->setShader(lightingShader);
	spriteDraws[currentDrawIndex]->setRotation(rotation);
	currentDrawIndex++;
	lastAbsolute = false;
}

void SpriteCollection::addRotatedImageDraw(Image* pImage, float x, float y, float z, float scale, float opacity, float rotation){
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(pImage, x, y, z, scale, opacity);
	spriteDraws[currentDrawIndex]->setShader(lightingShader);
	spriteDraws[currentDrawIndex]->setRotation(rotation);
	currentDrawIndex++;
	lastAbsolute = false;
}

void SpriteCollection::addRotatedImageDraw(Image* pImage, float x, float y, float z, float scale, float opacity, float rotation, float rx, float ry){
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(pImage, x, y, z, scale, opacity);
	spriteDraws[currentDrawIndex]->setShader(lightingShader);
	spriteDraws[currentDrawIndex]->setRotation(rotation);
	spriteDraws[currentDrawIndex]->setRPoint(rx, ry);
	currentDrawIndex++;
	lastAbsolute = false;
}

void SpriteCollection::addRotatedImageDraw(Image* pImage, float x, float y, float z, int sX, int sY, int sW, int sH, float scale, float rotation){
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(pImage, x, y, z, sX, sY, sW, sH, scale);
	spriteDraws[currentDrawIndex]->setShader(lightingShader);
	spriteDraws[currentDrawIndex]->setRotation(rotation);
	currentDrawIndex++;
	lastAbsolute = false;
}

void SpriteCollection::addRotatedImageDraw(Image* pImage, float x, float y, float z, int sX, int sY, int sW, int sH, float scale, float rotation, float rx, float ry) {
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(pImage, x, y, z, sX, sY, sW, sH, scale);
	spriteDraws[currentDrawIndex]->setShader(lightingShader);
	spriteDraws[currentDrawIndex]->setRotation(rotation);
	spriteDraws[currentDrawIndex]->setRPoint(rx, ry);
	currentDrawIndex++;
	lastAbsolute = false;
}

void SpriteCollection::addRectDraw(float x, float y, float w, float h, float z, sf::Color color) {
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(x, y, w, h, z, color);
	spriteDraws[currentDrawIndex]->setShader(lightingShader);
	currentDrawIndex++; 
	lastAbsolute = false;
}

void SpriteCollection::addCircleDraw(float x, float y, float r, float z, sf::Color color) {
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(x, y, r, z, color);
	spriteDraws[currentDrawIndex]->setShader(lightingShader);
	currentDrawIndex++;
	lastAbsolute = false;
}

void SpriteCollection::addAbsoluteImageDraw(Image* pImage, float x, float y, float z) {
	if (currentAbsoluteDrawIndex >= maxAbsoluteSpriteDraws) {
		std::cout << "MAX NUMBER OF ABSOLUTESPRITEDRAWS REACHED!\n";
		return;
	}
	absoluteSpriteDraws[currentAbsoluteDrawIndex] = new SpriteDraw(pImage, x, y, z, 1);
	currentAbsoluteDrawIndex++;
	lastAbsolute = true;
}

void SpriteCollection::addAbsoluteImageDraw(Image* pImage, float x, float y, float z, int sX, int sY, int sW, int sH) {
	if (currentAbsoluteDrawIndex >= maxAbsoluteSpriteDraws) {
		std::cout << "MAX NUMBER OF ABSOLUTESPRITEDRAWS REACHED!\n";
		return;
	}
	absoluteSpriteDraws[currentAbsoluteDrawIndex] = new SpriteDraw(pImage, x, y, z, sX, sY, sW, sH, 1);
	currentAbsoluteDrawIndex++;
	lastAbsolute = true;
}

void SpriteCollection::addAbsoluteImageDraw(Image* pImage, float x, float y, float z, float scale) {
	if (currentAbsoluteDrawIndex >= maxAbsoluteSpriteDraws) {
		std::cout << "MAX NUMBER OF ABSOLUTESPRITEDRAWS REACHED!\n";
		return;
	}
	absoluteSpriteDraws[currentAbsoluteDrawIndex] = new SpriteDraw(pImage, x, y, z, scale);
	currentAbsoluteDrawIndex++;
	lastAbsolute = true;
}

void SpriteCollection::addAbsoluteImageDraw(Image* pImage, float x, float y, float z, float scale, float opacity) {
	if (currentAbsoluteDrawIndex >= maxAbsoluteSpriteDraws) {
		std::cout << "MAX NUMBER OF ABSOLUTESPRITEDRAWS REACHED!\n";
		return;
	}
	absoluteSpriteDraws[currentAbsoluteDrawIndex] = new SpriteDraw(pImage, x, y, z, scale, opacity);
	currentAbsoluteDrawIndex++;
	lastAbsolute = true;
}

void SpriteCollection::addAbsoluteImageDraw(Image* pImage, float x, float y, float z, int sX, int sY, int sW, int sH, float scale) {
	if (currentAbsoluteDrawIndex >= maxAbsoluteSpriteDraws) {
		std::cout << "MAX NUMBER OF ABSOLUTESPRITEDRAWS REACHED!\n";
		return;
	}
	absoluteSpriteDraws[currentAbsoluteDrawIndex] = new SpriteDraw(pImage, x, y, z, sX, sY, sW, sH, scale);
	currentAbsoluteDrawIndex++;
	lastAbsolute = true;
}

void SpriteCollection::addAbsoluteImageDraw(Image* pImage, float x, float y, float z, int sX, int sY, int sW, int sH, float scale, float opacity) {
	if (currentAbsoluteDrawIndex >= maxAbsoluteSpriteDraws) {
		std::cout << "MAX NUMBER OF ABSOLUTESPRITEDRAWS REACHED!\n";
		return;
	}
	absoluteSpriteDraws[currentAbsoluteDrawIndex] = new SpriteDraw(pImage, x, y, z, sX, sY, sW, sH, scale, opacity);
	currentAbsoluteDrawIndex++;
	lastAbsolute = true;
}

void SpriteCollection::addAbsoluteRectDraw(float x, float y, float w, float h, float z, sf::Color color) {
	if (currentAbsoluteDrawIndex >= maxAbsoluteSpriteDraws) {
		std::cout << "MAX NUMBER OF ABSOLUTESPRITEDRAWS REACHED!\n";
		return;
	}
	absoluteSpriteDraws[currentAbsoluteDrawIndex] = new SpriteDraw(x, y, w, h, z, color);
	currentAbsoluteDrawIndex++;
	lastAbsolute = true;
}

void SpriteCollection::addAbsoluteCircleDraw(float x, float y, float r, float z, sf::Color color) {
	if (currentAbsoluteDrawIndex >= maxAbsoluteSpriteDraws) {
		std::cout << "MAX NUMBER OF ABSOLUTESPRITEDRAWS REACHED!\n";
		return;
	}
	absoluteSpriteDraws[currentAbsoluteDrawIndex] = new SpriteDraw(x, y, r, z, color);
	currentAbsoluteDrawIndex++;
	lastAbsolute = true;
}

void SpriteCollection::addTextDraw(int fontIndex, float x, float y, float z, std::string string, int fontSize, sf::Color color) {
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(fontIndex, x, y, z, string, fontSize, color);
	currentDrawIndex++;
	lastAbsolute = false;
}

void SpriteCollection::addAbsoluteTextDraw(int fontIndex, float x, float y, float z, std::string string, int fontSize, sf::Color color) {
	if (currentAbsoluteDrawIndex >= maxAbsoluteSpriteDraws) {
		std::cout << "MAX NUMBER OF ABSOLUTESPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentAbsoluteDrawIndex] = new SpriteDraw(fontIndex, x, y, z, string, fontSize, color);
	currentAbsoluteDrawIndex++;
	lastAbsolute = true;
}

void SpriteCollection::drawAll() {
	sendLightDataToShader();
	if (orderZ) {
		orderByZ();
	}
	glm::vec2 temp;
	for (int i = 0; i < currentDrawIndex; i++) {

		if (spriteDraws[i]->type < 2) {
			spriteDraws[i]->pImage->addShader(shaders[0]->shader);
			for (int j = 0; j < spriteDraws[i]->numShaders; j++) {
				spriteDraws[i]->pImage->addShader(spriteDraws[i]->shaders[j]);
			}
			if (spriteDraws[i]->pImage->getName() == "decoration_rover_tracks_1") {
				int r = 6;
			}
			spriteDraws[i]->pImage->setRotation(spriteDraws[i]->rotation);
			if (spriteDraws[i]->rotationPoint) {
				spriteDraws[i]->pImage->setRPoint(spriteDraws[i]->rx, spriteDraws[i]->ry);
			}
		}
		if (useCamera) {
			temp = pCamera->transformPosition(glm::vec2(spriteDraws[i]->x, spriteDraws[i]->y));
		}
		else {
			temp = glm::vec2(spriteDraws[i]->x, spriteDraws[i]->y);
		}
		if (spriteDraws[i]->type == 0) {
			if (spriteDraws[i]->opacity < 1) {
				spriteDraws[i]->pImage->draw(temp.x, temp.y, spriteDraws[i]->scale, spriteDraws[i]->opacity);
			} else {
				spriteDraws[i]->pImage->draw(temp.x, temp.y, spriteDraws[i]->scale);
			}
		}
		else if (spriteDraws[i]->type == 1) {
			if (spriteDraws[i]->opacity < 1) {
				spriteDraws[i]->pImage->drawSection(temp.x, temp.y, spriteDraws[i]->sX, spriteDraws[i]->sY, spriteDraws[i]->sW, spriteDraws[i]->sH, spriteDraws[i]->scale, spriteDraws[i]->opacity);
			} else {
				
				spriteDraws[i]->pImage->drawSection(temp.x, temp.y, spriteDraws[i]->sX, spriteDraws[i]->sY, spriteDraws[i]->sW, spriteDraws[i]->sH, spriteDraws[i]->scale);
			}
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
	for (int i = 0; i < currentAbsoluteDrawIndex; i++) {
		if (absoluteSpriteDraws[i]->type == 0) {
			if (absoluteSpriteDraws[i]->opacity < 1) {
				absoluteSpriteDraws[i]->pImage->draw(absoluteSpriteDraws[i]->x, absoluteSpriteDraws[i]->y, spriteDraws[i]->scale, spriteDraws[i]->opacity);
			}
			else {
				absoluteSpriteDraws[i]->pImage->draw(absoluteSpriteDraws[i]->x, absoluteSpriteDraws[i]->y, spriteDraws[i]->scale);
			}
		}
		else if (absoluteSpriteDraws[i]->type == 1) {
			if (absoluteSpriteDraws[i]->opacity < 1) {
				absoluteSpriteDraws[i]->pImage->drawSection(absoluteSpriteDraws[i]->x, absoluteSpriteDraws[i]->y, absoluteSpriteDraws[i]->sX, absoluteSpriteDraws[i]->sY, absoluteSpriteDraws[i]->sW, absoluteSpriteDraws[i]->sH, spriteDraws[i]->scale, spriteDraws[i]->opacity);
			}
			else {
				absoluteSpriteDraws[i]->pImage->drawSection(absoluteSpriteDraws[i]->x, absoluteSpriteDraws[i]->y, absoluteSpriteDraws[i]->sX, absoluteSpriteDraws[i]->sY, absoluteSpriteDraws[i]->sW, absoluteSpriteDraws[i]->sH, spriteDraws[i]->scale);
			}
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

void SpriteCollection::setShader(sf::Shader *shader) {
	lightingShader = shader;
}

void SpriteCollection::addShader(std::string name, sf::Shader* shader){
	if (nextShaderIndex >= maxShaders) {
		std::cout << "MAX SHADERS REACHED\n";
		return;
	}
	shaders[nextShaderIndex] = new shaderWrapper(name, shader);
	nextShaderIndex++;
}

void SpriteCollection::drawLightSource(glm::vec2 position, glm::vec3 colour, float intensity, int type, bool absolute) {
	lightColours[numLights] = sf::Glsl::Vec3(colour.r, colour.g, colour.b);
	lightPositions[numLights] = sf::Glsl::Vec2(position.x, position.y);

	lightIntensities[numLights] = intensity;
	lightTypes[numLights] = type;
	numLights++;
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

void SpriteCollection::sendLightDataToShader(){
	int temp = windowW;
	for (int i = 0; i < numLights; i++) {
		lightPositions[i] = sf::Glsl::Vec2(lightPositions[i].x - pCamera->getPosition().x + windowW / 2, -lightPositions[i].y + pCamera->getPosition().y + windowH / 2);
	}
	shaders[0]->shader->setUniform("numLights", (float)numLights);
	shaders[0]->shader->setUniformArray("lightPositions", lightPositions, 100);
	shaders[0]->shader->setUniformArray("lightColours", lightColours, 100);
	shaders[0]->shader->setUniformArray("lightIntensities", lightIntensities, 100);
	shaders[0]->shader->setUniformArray("lightTypes", lightTypes, 100);
	numLights = 0;
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

void SpriteCollection::setWindowDimensions(int w, int h){
	windowW = w;
	windowH = h;
}

void SpriteCollection::addShaderToLast(std::string shader){

	if (!lastAbsolute) {
		if (currentDrawIndex == 0) {
			return;
		}
		for (int i = 0; i < nextShaderIndex; i++) {
			if (shaders[i]->name.compare(shader) == 0) {
				spriteDraws[currentDrawIndex - 1]->addShader(shaders[i]->shader);
				return;
			}
		}
	}
	else {
		if (currentAbsoluteDrawIndex == 0) {
			return;
		}
		for (int i = 0; i < nextShaderIndex; i++) {
			if (shaders[i]->name.compare(shader) == 0) {
				spriteDraws[currentDrawIndex - 1]->addShader(shaders[i]->shader);
				return;
			}
		}
	}
	std::cout << "shader not found\n";
}
