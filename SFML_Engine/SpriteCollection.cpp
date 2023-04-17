#include "SpriteCollection.h"
#include <iostream>
SpriteCollection::SpriteCollection() {}

SpriteCollection::SpriteCollection(sf::RenderWindow* pwindow, Graphics* pgraphics, MultiPipelineManager* _multiPipelineManager) {
	pGraphics = pgraphics;
	pWindow = pwindow;
	multiPipelineManager = _multiPipelineManager;
}

void SpriteCollection::loadTexture(std::string name, std::string path){
	textureWrappers.push_back(new TextureWrapper(name, path));
}

TextureWrapper* SpriteCollection::getPointerFromName(std::string name) {
	for (int i = 0; i < textureWrappers.size(); i++) {
		if (textureWrappers[i]->getName().compare(name) == 0) {
			return textureWrappers[i];
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

void SpriteCollection::addImageDraw(TextureWrapper* pTexture, float x, float y, float z){
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(pTexture, x, y, z, 1);
	if (fullBrightMode) {
		spriteDraws[currentDrawIndex]->setFullBright();
	}
	spriteDraws[currentDrawIndex]->setPipeline(pipelineIndex);
	currentDrawIndex++;
	lastAbsolute = false;
}
void SpriteCollection::addImageDraw(TextureWrapper* pTexture, float x, float y, float z, int sX, int sY, int sW, int sH) {
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(pTexture, x, y, z, sX, sY, sW, sH, 1);
	if (fullBrightMode) {
		spriteDraws[currentDrawIndex]->setFullBright();
	}
	spriteDraws[currentDrawIndex]->setPipeline(pipelineIndex);
	currentDrawIndex++;
	lastAbsolute = false;
}
void SpriteCollection::addImageDraw(TextureWrapper* pTexture, float x, float y, float z, float scale) {
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(pTexture, x, y, z, scale);
	if (fullBrightMode) {
		spriteDraws[currentDrawIndex]->setFullBright();
	}
	spriteDraws[currentDrawIndex]->setPipeline(pipelineIndex);
	currentDrawIndex++;
	lastAbsolute = false;
}
void SpriteCollection::addImageDraw(TextureWrapper* pTexture, float x, float y, float z, float scale, float opacity) {
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(pTexture, x, y, z, scale, opacity);
	if (fullBrightMode) {
		spriteDraws[currentDrawIndex]->setFullBright();
	}
	spriteDraws[currentDrawIndex]->setPipeline(pipelineIndex);
	currentDrawIndex++;
	lastAbsolute = false;
}

void SpriteCollection::addImageDraw(TextureWrapper* pTexture, float x, float y, float z, int sX, int sY, int sW, int sH, float scale) {
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(pTexture, x, y, z, sX, sY, sW, sH, scale);
	if (fullBrightMode) {
		spriteDraws[currentDrawIndex]->setFullBright();
	}
	spriteDraws[currentDrawIndex]->setPipeline(pipelineIndex);
	currentDrawIndex++;
	lastAbsolute = false;
}

void SpriteCollection::addImageDraw(TextureWrapper* pTexture, float x, float y, float z, int sX, int sY, int sW, int sH, float scale, float opacity) {
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(pTexture, x, y, z, sX, sY, sW, sH, scale, opacity);
	if (fullBrightMode) {
		spriteDraws[currentDrawIndex]->setFullBright();
	}
	spriteDraws[currentDrawIndex]->setPipeline(pipelineIndex);
	currentDrawIndex++;
	lastAbsolute = false;
}

void SpriteCollection::addRotatedImageDraw(TextureWrapper* pTexture, float x, float y, float z, float scale, float rotation){
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(pTexture, x, y, z, scale);
	if (fullBrightMode) {
		spriteDraws[currentDrawIndex]->setFullBright();
	}
	spriteDraws[currentDrawIndex]->setRotation(rotation);
	spriteDraws[currentDrawIndex]->setPipeline(pipelineIndex);
	currentDrawIndex++;
	lastAbsolute = false;
}

void SpriteCollection::addRotatedImageDraw(TextureWrapper* pTexture, float x, float y, float z, float scale, float opacity, float rotation){
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(pTexture, x, y, z, scale, opacity);
	if (fullBrightMode) {
		spriteDraws[currentDrawIndex]->setFullBright();
	}
	spriteDraws[currentDrawIndex]->setRotation(rotation);
	spriteDraws[currentDrawIndex]->setPipeline(pipelineIndex);
	currentDrawIndex++;
	lastAbsolute = false;
}

void SpriteCollection::addRotatedImageDraw(TextureWrapper* pTexture, float x, float y, float z, float scale, float opacity, float rotation, float rx, float ry){
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(pTexture, x, y, z, scale, opacity);
	if (fullBrightMode) {
		spriteDraws[currentDrawIndex]->setFullBright();
	}
	spriteDraws[currentDrawIndex]->setRotation(rotation);
	spriteDraws[currentDrawIndex]->setRPoint(rx, ry);
	spriteDraws[currentDrawIndex]->setPipeline(pipelineIndex);
	currentDrawIndex++;
	lastAbsolute = false;
}

void SpriteCollection::addRotatedImageDraw(TextureWrapper* pTexture, float x, float y, float z, int sX, int sY, int sW, int sH, float scale, float rotation){
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(pTexture, x, y, z, sX, sY, sW, sH, scale);
	if (fullBrightMode) {
		spriteDraws[currentDrawIndex]->setFullBright();
	}
	spriteDraws[currentDrawIndex]->setRotation(rotation);
	spriteDraws[currentDrawIndex]->setPipeline(pipelineIndex);
	currentDrawIndex++;
	lastAbsolute = false;
}

void SpriteCollection::addRotatedImageDraw(TextureWrapper* pTexture, float x, float y, float z, int sX, int sY, int sW, int sH, float scale, float rotation, float rx, float ry) {
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(pTexture, x, y, z, sX, sY, sW, sH, scale);
	if (fullBrightMode) {
		spriteDraws[currentDrawIndex]->setFullBright();
	}
	spriteDraws[currentDrawIndex]->setRotation(rotation);
	spriteDraws[currentDrawIndex]->setRPoint(rx, ry);
	spriteDraws[currentDrawIndex]->setPipeline(pipelineIndex);
	currentDrawIndex++;
	lastAbsolute = false;
}

void SpriteCollection::addRectDraw(float x, float y, float w, float h, float z, sf::Color color) {
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(x, y, w, h, z, color);
	if (fullBrightMode) {
		spriteDraws[currentDrawIndex]->setFullBright();
	}
	spriteDraws[currentDrawIndex]->pTexture = getPointerFromName("white_rect");
	spriteDraws[currentDrawIndex]->setPipeline(pipelineIndex);
	currentDrawIndex++; 
	lastAbsolute = false;
}

void SpriteCollection::addCircleDraw(float x, float y, float r, float z, sf::Color color) {
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(x, y, r, z, color);
	if (fullBrightMode) {
		spriteDraws[currentDrawIndex]->setFullBright();
	}
	spriteDraws[currentDrawIndex]->setPipeline(pipelineIndex);
	currentDrawIndex++;
	lastAbsolute = false;
}

void SpriteCollection::addAbsoluteImageDraw(TextureWrapper* pTexture, float x, float y, float z) {
	if (currentAbsoluteDrawIndex >= maxAbsoluteSpriteDraws) {
		std::cout << "MAX NUMBER OF ABSOLUTESPRITEDRAWS REACHED!\n";
		return;
	}
	absoluteSpriteDraws[currentAbsoluteDrawIndex] = new SpriteDraw(pTexture, x, y, z, 1);
	if (fullBrightMode) {
		absoluteSpriteDraws[currentAbsoluteDrawIndex]->setFullBright();
	}
	spriteDraws[currentDrawIndex]->setPipeline(pipelineIndex);
	currentAbsoluteDrawIndex++;
	lastAbsolute = true;
}

void SpriteCollection::addAbsoluteImageDraw(TextureWrapper* pTexture, float x, float y, float z, int sX, int sY, int sW, int sH) {
	if (currentAbsoluteDrawIndex >= maxAbsoluteSpriteDraws) {
		std::cout << "MAX NUMBER OF ABSOLUTESPRITEDRAWS REACHED!\n";
		return;
	}
	absoluteSpriteDraws[currentAbsoluteDrawIndex] = new SpriteDraw(pTexture, x, y, z, sX, sY, sW, sH, 1);
	if (fullBrightMode) {
		absoluteSpriteDraws[currentAbsoluteDrawIndex]->setFullBright();
	}
	spriteDraws[currentDrawIndex]->setPipeline(pipelineIndex);
	currentAbsoluteDrawIndex++;
	lastAbsolute = true;
}

void SpriteCollection::addAbsoluteImageDraw(TextureWrapper* pTexture, float x, float y, float z, float scale) {
	if (currentAbsoluteDrawIndex >= maxAbsoluteSpriteDraws) {
		std::cout << "MAX NUMBER OF ABSOLUTESPRITEDRAWS REACHED!\n";
		return;
	}
	absoluteSpriteDraws[currentAbsoluteDrawIndex] = new SpriteDraw(pTexture, x, y, z, scale);
	if (fullBrightMode) {
		absoluteSpriteDraws[currentAbsoluteDrawIndex]->setFullBright();
	}
	spriteDraws[currentDrawIndex]->setPipeline(pipelineIndex);
	currentAbsoluteDrawIndex++;
	lastAbsolute = true;
}

void SpriteCollection::addAbsoluteImageDraw(TextureWrapper* pTexture, float x, float y, float z, float scale, float opacity) {
	if (currentAbsoluteDrawIndex >= maxAbsoluteSpriteDraws) {
		std::cout << "MAX NUMBER OF ABSOLUTESPRITEDRAWS REACHED!\n";
		return;
	}
	absoluteSpriteDraws[currentAbsoluteDrawIndex] = new SpriteDraw(pTexture, x, y, z, scale, opacity);
	if (fullBrightMode) {
		absoluteSpriteDraws[currentAbsoluteDrawIndex]->setFullBright();
	}
	spriteDraws[currentDrawIndex]->setPipeline(pipelineIndex);
	currentAbsoluteDrawIndex++;
	lastAbsolute = true;
}

void SpriteCollection::addAbsoluteImageDraw(TextureWrapper* pTexture, float x, float y, float z, int sX, int sY, int sW, int sH, float scale) {
	if (currentAbsoluteDrawIndex >= maxAbsoluteSpriteDraws) {
		std::cout << "MAX NUMBER OF ABSOLUTESPRITEDRAWS REACHED!\n";
		return;
	}
	absoluteSpriteDraws[currentAbsoluteDrawIndex] = new SpriteDraw(pTexture, x, y, z, sX, sY, sW, sH, scale);
	if (fullBrightMode) {
		absoluteSpriteDraws[currentAbsoluteDrawIndex]->setFullBright();
	}
	spriteDraws[currentDrawIndex]->setPipeline(pipelineIndex);
	currentAbsoluteDrawIndex++;
	lastAbsolute = true;
}

void SpriteCollection::addAbsoluteImageDraw(TextureWrapper* pTexture, float x, float y, float z, int sX, int sY, int sW, int sH, float scale, float opacity) {
	if (currentAbsoluteDrawIndex >= maxAbsoluteSpriteDraws) {
		std::cout << "MAX NUMBER OF ABSOLUTESPRITEDRAWS REACHED!\n";
		return;
	}
	absoluteSpriteDraws[currentAbsoluteDrawIndex] = new SpriteDraw(pTexture, x, y, z, sX, sY, sW, sH, scale, opacity);
	if (fullBrightMode) {
		absoluteSpriteDraws[currentAbsoluteDrawIndex]->setFullBright();
	}
	spriteDraws[currentDrawIndex]->setPipeline(pipelineIndex);
	currentAbsoluteDrawIndex++;
	lastAbsolute = true;
}

void SpriteCollection::addAbsoluteRectDraw(float x, float y, float w, float h, float z, sf::Color color) {
	if (currentAbsoluteDrawIndex >= maxAbsoluteSpriteDraws) {
		std::cout << "MAX NUMBER OF ABSOLUTESPRITEDRAWS REACHED!\n";
		return;
	}
	absoluteSpriteDraws[currentAbsoluteDrawIndex] = new SpriteDraw(x, y, w, h, z, color);
	if (fullBrightMode) {
		absoluteSpriteDraws[currentAbsoluteDrawIndex]->setFullBright();
	}
	spriteDraws[currentDrawIndex]->setPipeline(pipelineIndex);
	currentAbsoluteDrawIndex++;
	lastAbsolute = true;
}

void SpriteCollection::addAbsoluteCircleDraw(float x, float y, float r, float z, sf::Color color) {
	if (currentAbsoluteDrawIndex >= maxAbsoluteSpriteDraws) {
		std::cout << "MAX NUMBER OF ABSOLUTESPRITEDRAWS REACHED!\n";
		return;
	}
	absoluteSpriteDraws[currentAbsoluteDrawIndex] = new SpriteDraw(x, y, r, z, color);
	if (fullBrightMode) {
		absoluteSpriteDraws[currentAbsoluteDrawIndex]->setFullBright();
	}
	spriteDraws[currentDrawIndex]->setPipeline(pipelineIndex);
	currentAbsoluteDrawIndex++;
	lastAbsolute = true;
}

void SpriteCollection::addTextDraw(int fontIndex, float x, float y, float z, std::string string, int fontSize, sf::Color color) {
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(fontIndex, x, y, z, string, fontSize, color);
	if (fullBrightMode) {
		spriteDraws[currentDrawIndex]->setFullBright();
	}
	spriteDraws[currentDrawIndex]->setPipeline(pipelineIndex);
	currentDrawIndex++;
	lastAbsolute = false;
}

void SpriteCollection::addAbsoluteTextDraw(int fontIndex, float x, float y, float z, std::string string, int fontSize, sf::Color color) {
	if (currentAbsoluteDrawIndex >= maxAbsoluteSpriteDraws) {
		std::cout << "MAX NUMBER OF ABSOLUTESPRITEDRAWS REACHED!\n";
		return;
	}
	absoluteSpriteDraws[currentAbsoluteDrawIndex] = new SpriteDraw(fontIndex, x, y, z, string, fontSize, color);
	if (fullBrightMode) {
		absoluteSpriteDraws[currentAbsoluteDrawIndex]->setFullBright();
	}
	spriteDraws[currentDrawIndex]->setPipeline(pipelineIndex);
	currentAbsoluteDrawIndex++;
	lastAbsolute = true;
}

void SpriteCollection::drawAll() {
	if (toBlink) {
		pGraphics->drawRect(0, 0, 3000, 3000, sf::Color::Black);
		toBlink = false;
		clearSpriteDraws();
		return;
	}
	sendLightDataToShader();
	if (orderZ) {
		orderByZ();
	}
	glm::vec2 temp;

	sf::RenderTexture lit;
	lit.create(pWindow->getSize().x, pWindow->getSize().y);
	lit.clear(sf::Color(0, 0, 0, 0));
	sf::RenderTexture unlit;
	unlit.create(pWindow->getSize().x, pWindow->getSize().y);
	unlit.clear(sf::Color(0, 0, 0, 0));
	sf::RenderTexture* RTSel = &unlit;


	for (int i = 0; i < currentDrawIndex; i++) {
		if (spriteDraws[i]->fullBright) {
			RTSel = &unlit;
		}
		else {
			RTSel = &lit;
		}
		// type 0 = image, 1 = image section, 2 = rectangle, 3 = circle, 4 = text
		if (useCamera) {
			temp = pCamera->transformPosition(glm::vec2(spriteDraws[i]->x, spriteDraws[i]->y));
		}
		else {
			temp = glm::vec2(spriteDraws[i]->x, spriteDraws[i]->y);
		}
		if (spriteDraws[i]->type == 0) {
			if (spriteDraws[i]->rotationPoint) {
				multiPipelineManager->executeWithTransform(spriteDraws[i]->pipelineIndex, spriteDraws[i]->pTexture->getTexture(), RTSel, temp.x, temp.y, spriteDraws[i]->scale, spriteDraws[i]->rotation, spriteDraws[i]->rx, spriteDraws[i]->ry, spriteDraws[i]->opacity, false, 0, 0, 0, 0);
			}
			else {
				multiPipelineManager->executeWithTransform(spriteDraws[i]->pipelineIndex, spriteDraws[i]->pTexture->getTexture(), RTSel, temp.x, temp.y, spriteDraws[i]->scale, 0, spriteDraws[i]->opacity);
			}
		}
		else if (spriteDraws[i]->type == 1) {
			if (spriteDraws[i]->rotationPoint) {
				multiPipelineManager->executeWithTransform(spriteDraws[i]->pipelineIndex, spriteDraws[i]->pTexture->getTexture(), RTSel, temp.x, temp.y, spriteDraws[i]->scale, spriteDraws[i]->rotation, spriteDraws[i]->rx, spriteDraws[i]->ry, spriteDraws[i]->opacity, true, spriteDraws[i]->sX, spriteDraws[i]->sY, spriteDraws[i]->sW, spriteDraws[i]->sH);
			}
			else {
				multiPipelineManager->executeWithTransform(spriteDraws[i]->pipelineIndex, spriteDraws[i]->pTexture->getTexture(), RTSel, temp.x, temp.y, spriteDraws[i]->scale, spriteDraws[i]->opacity, spriteDraws[i]->rotation, spriteDraws[i]->sX, spriteDraws[i]->sY, spriteDraws[i]->sW, spriteDraws[i]->sH);
			}
			
		}
		else if (spriteDraws[i]->type == 2) {
			multiPipelineManager->executeWithRectangle(spriteDraws[i]->pipelineIndex, RTSel, temp.x, temp.y, spriteDraws[i]->w, spriteDraws[i]->h, sf::Color(spriteDraws[i]->color.r, spriteDraws[i]->color.g, spriteDraws[i]->color.b, spriteDraws[i]->color.a));
		}
		else if (spriteDraws[i]->type == 3) {
			pGraphics->drawCircle(temp.x, temp.y, spriteDraws[i]->r, spriteDraws[i]->color);
		}
		else if (spriteDraws[i]->type == 4) {
			drawText(spriteDraws[i]->fontIndex, temp.x, temp.y, spriteDraws[i]->string, spriteDraws[i]->fontSize, spriteDraws[i]->color, RTSel);
		}

	}
	for (int i = 0; i < currentAbsoluteDrawIndex; i++) {
		if (absoluteSpriteDraws[i]->type == 0) {
			multiPipelineManager->executeWithTransform(spriteDraws[i]->pipelineIndex, spriteDraws[i]->pTexture->getTexture(), RTSel, absoluteSpriteDraws[i]->x, absoluteSpriteDraws[i]->y, spriteDraws[i]->scale, 0, spriteDraws[i]->opacity);
		}
		else if (absoluteSpriteDraws[i]->type == 1) {
			multiPipelineManager->executeWithTransform(spriteDraws[i]->pipelineIndex, spriteDraws[i]->pTexture->getTexture(), RTSel, absoluteSpriteDraws[i]->x, absoluteSpriteDraws[i]->y, spriteDraws[i]->scale, spriteDraws[i]->opacity, spriteDraws[i]->sX, spriteDraws[i]->sY, spriteDraws[i]->sW, spriteDraws[i]->sH);
		}
		else if (absoluteSpriteDraws[i]->type == 2) {
			multiPipelineManager->executeWithRectangle(spriteDraws[i]->pipelineIndex, RTSel, absoluteSpriteDraws[i]->x, absoluteSpriteDraws[i]->y, spriteDraws[i]->w, spriteDraws[i]->h, sf::Color(spriteDraws[i]->color.r, spriteDraws[i]->color.g, spriteDraws[i]->color.b, spriteDraws[i]->color.a));
		}
		else if (absoluteSpriteDraws[i]->type == 3) {
			pGraphics->drawCircle(absoluteSpriteDraws[i]->x, absoluteSpriteDraws[i]->y, absoluteSpriteDraws[i]->r, absoluteSpriteDraws[i]->color);
		}
		else if (absoluteSpriteDraws[i]->type == 4) {
			drawText(absoluteSpriteDraws[i]->fontIndex, absoluteSpriteDraws[i]->x, absoluteSpriteDraws[i]->y, absoluteSpriteDraws[i]->string, absoluteSpriteDraws[i]->fontSize, absoluteSpriteDraws[i]->color, &unlit);
		}
	}

	lit.display();
	unlit.display();
	//multiPipelineManager->executeWithTransform(1, &lit.getTexture(), pWindow, 0, 0, 1);
	sf::RenderTexture intermediate;
	sf::RenderTexture intermediate2;
	intermediate.create(pWindow->getSize().x, pWindow->getSize().y);
	intermediate2.create(pWindow->getSize().x, pWindow->getSize().y);
	sf::RenderTexture bloom;
	bloom.create(pWindow->getSize().x, pWindow->getSize().y);
	bloom.clear(sf::Color(0, 0, 0, 1));
	
	
	multiPipelineManager->executeWithTransform(pipelineIndex, &lit.getTexture(), &intermediate, 0, 0, 1);
	intermediate.display();
	multiPipelineManager->executeWithTransform(2, &intermediate.getTexture(), &bloom, 0, 0, 1);
	//unlit.display();

	//multiPipelineManager->executeWithTransform(0, &unlit.getTexture(), &intermediate, 0, 0, 1);

	intermediate.display();
	bloom.display();

	multiPipelineManager->blendTextures(0, intermediate.getTexture(), bloom.getTexture(), &intermediate2);
	intermediate2.display();
	multiPipelineManager->blendTextures(0, intermediate2.getTexture(), unlit.getTexture(), pWindow);

	clearSpriteDraws();
}

void SpriteCollection::drawText(int fontIndex, float x, float y, std::string string, int fontSize, sf::Color color, sf::RenderTexture* target) {
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

	target->draw(text);
}

void SpriteCollection::addFont(std::string path) {
	sf::Font temp;
	if (!temp.loadFromFile(path)) {
		std::cout << "ERROR LOADING FONT\n";
	}
	fonts.push_back(temp);
}

void SpriteCollection::setLightShader(sf::Shader *shader) {
	lightingShader = shader;
}

void SpriteCollection::drawLightSource(glm::vec2 position, glm::vec3 colour, float intensity, int type, bool absolute) {
	if (numLights >= maxLights) {
		std::cout << "MAX LIGHTS REACHED\n";
		return;
	}
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
	for (int i = 0; i < numLights; i++) {
		lightPositions[i] = sf::Glsl::Vec2(lightPositions[i].x - pCamera->getPosition().x + *pWindowW / 2, -lightPositions[i].y + pCamera->getPosition().y + *pWindowH / 2);
	}
	lightingShader->setUniform("numLights", (float)numLights);
	lightingShader->setUniformArray("lightPositions", lightPositions, 100);
	lightingShader->setUniformArray("lightColours", lightColours, 100);
	lightingShader->setUniformArray("lightIntensities", lightIntensities, 100);
	lightingShader->setUniformArray("lightTypes", lightTypes, 100);
	numLights = 0;
	lightingShader->setUniform("ambientLightLevel", 0.05f);
	lightingShader->setUniform("ambientLightColour", sf::Glsl::Vec3(255,255,255));
	lightingShader->setUniform("time", (float)(frame % 30));
	lightingShader->setUniform("noiseIntensity", 0.5f);

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

void SpriteCollection::setWindowDimensions(int* w, int* h){
	pWindowW = w;
	pWindowH = h;
}

void SpriteCollection::setFullBrightMode(bool _mode){
	fullBrightMode = _mode;
}

void SpriteCollection::blink(){
	toBlink = true;
}

void SpriteCollection::setPipelineIndex(int index){
	pipelineIndex = index;
}

void SpriteCollection::setFrame(int _frame){
	frame = _frame;
}
