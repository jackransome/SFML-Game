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

void SpriteCollection::addImageDraw(TextureWrapper* pTexture, float x, float y, float z, float _w, float _h){
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(pTexture, x, y, z, 1);
	if (fullBrightMode) {
		spriteDraws[currentDrawIndex]->setFullBright();
	}
	spriteDraws[currentDrawIndex]->w = _w;
	spriteDraws[currentDrawIndex]->h = _h;
	spriteDraws[currentDrawIndex]->setPipeline(pipelineIndex);
	
	if (absoluteMode) {
		spriteDraws[currentDrawIndex]->absolute = true;
	}
	currentDrawIndex++;
	lastAbsolute = false;

}
void SpriteCollection::addImageDrawCut(TextureWrapper* pTexture, float x, float y, float z, int sX, int sY, int sW, int sH) {
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(pTexture, x, y, z, sX, sY, sW, sH, 1);
	if (fullBrightMode) {
		spriteDraws[currentDrawIndex]->setFullBright();
	}
	spriteDraws[currentDrawIndex]->w = sW;
	spriteDraws[currentDrawIndex]->h = sH;
	spriteDraws[currentDrawIndex]->setPipeline(pipelineIndex);
	if (absoluteMode) {
		spriteDraws[currentDrawIndex]->absolute = true;
	}
	currentDrawIndex++;
	lastAbsolute = false;

}
void SpriteCollection::addImageDraw(TextureWrapper* pTexture, float x, float y, float z, float scale, float _w, float _h) {
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(pTexture, x, y, z, scale);
	if (fullBrightMode) {
		spriteDraws[currentDrawIndex]->setFullBright();
	}
	spriteDraws[currentDrawIndex]->w = _w;
	spriteDraws[currentDrawIndex]->h = _h;
	spriteDraws[currentDrawIndex]->setPipeline(pipelineIndex);
	if (absoluteMode) {
		spriteDraws[currentDrawIndex]->absolute = true;
	}
	currentDrawIndex++;

	lastAbsolute = false;

}
void SpriteCollection::addImageDraw(TextureWrapper* pTexture, float x, float y, float z, float scale, float opacity, float _w, float _h) {
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(pTexture, x, y, z, scale, opacity);
	if (fullBrightMode) {
		spriteDraws[currentDrawIndex]->setFullBright();
	}
	spriteDraws[currentDrawIndex]->w = _w;
	spriteDraws[currentDrawIndex]->h = _h;
	spriteDraws[currentDrawIndex]->setPipeline(pipelineIndex);
	if (absoluteMode) {
		spriteDraws[currentDrawIndex]->absolute = true;
	}
	currentDrawIndex++;
	lastAbsolute = false;

}



void SpriteCollection::addImageDrawCut(TextureWrapper* pTexture, float x, float y, float z, int sX, int sY, int sW, int sH, float scale) {
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(pTexture, x, y, z, sX, sY, sW, sH, scale);
	if (fullBrightMode) {
		spriteDraws[currentDrawIndex]->setFullBright();
	}
	spriteDraws[currentDrawIndex]->w = sW*scale;
	spriteDraws[currentDrawIndex]->h = sX*scale;
	spriteDraws[currentDrawIndex]->setPipeline(pipelineIndex);
	if (absoluteMode) {
		spriteDraws[currentDrawIndex]->absolute = true;
	}
	currentDrawIndex++;
	lastAbsolute = false;

}

void SpriteCollection::addImageDrawCut(TextureWrapper* pTexture, float x, float y, float z, int sX, int sY, int sW, int sH, float scale, float opacity) {
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(pTexture, x, y, z, sX, sY, sW, sH, scale, opacity);
	if (fullBrightMode) {
		spriteDraws[currentDrawIndex]->setFullBright();
	}
	spriteDraws[currentDrawIndex]->w = sW*scale;
	spriteDraws[currentDrawIndex]->h = sH*scale;
	spriteDraws[currentDrawIndex]->setPipeline(pipelineIndex);
	if (absoluteMode) {
		spriteDraws[currentDrawIndex]->absolute = true;
	}
	currentDrawIndex++;
	lastAbsolute = false;

}

void SpriteCollection::addRotatedImageDraw(TextureWrapper* pTexture, float x, float y, float z, float scale, float rotation, float _w, float _h){
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(pTexture, x, y, z, scale);
	if (fullBrightMode) {
		spriteDraws[currentDrawIndex]->setFullBright();
	}
	spriteDraws[currentDrawIndex]->w = _w;
	spriteDraws[currentDrawIndex]->h = _h;
	spriteDraws[currentDrawIndex]->setRotation(rotation);
	spriteDraws[currentDrawIndex]->setPipeline(pipelineIndex);
	if (absoluteMode) {
		spriteDraws[currentDrawIndex]->absolute = true;
	}
	currentDrawIndex++;
	lastAbsolute = false;
}

void SpriteCollection::addRotatedImageDraw(TextureWrapper* pTexture, float x, float y, float z, float scale, float opacity, float rotation, float _w, float _h){
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(pTexture, x, y, z, scale, opacity);
	if (fullBrightMode) {
		spriteDraws[currentDrawIndex]->setFullBright();
	}
	spriteDraws[currentDrawIndex]->w = _w;
	spriteDraws[currentDrawIndex]->h = _h;
	spriteDraws[currentDrawIndex]->setRotation(rotation);
	spriteDraws[currentDrawIndex]->setPipeline(pipelineIndex);
	if (absoluteMode) {
		spriteDraws[currentDrawIndex]->absolute = true;
	}
	currentDrawIndex++;
	lastAbsolute = false;

}

void SpriteCollection::addRotatedImageDraw(TextureWrapper* pTexture, float x, float y, float z, float scale, float opacity, float rotation, float rx, float ry, float _w, float _h){
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(pTexture, x, y, z, scale, opacity);
	if (fullBrightMode) {
		spriteDraws[currentDrawIndex]->setFullBright();
	}
	spriteDraws[currentDrawIndex]->w = _w;
	spriteDraws[currentDrawIndex]->h = _h;
	spriteDraws[currentDrawIndex]->setRotation(rotation);
	spriteDraws[currentDrawIndex]->setRPoint(rx, ry);
	spriteDraws[currentDrawIndex]->setPipeline(pipelineIndex);
	if (absoluteMode) {
		spriteDraws[currentDrawIndex]->absolute = true;
	}
	currentDrawIndex++;
	lastAbsolute = false;

}

void SpriteCollection::addRotatedImageDrawCut(TextureWrapper* pTexture, float x, float y, float z, int sX, int sY, int sW, int sH, float scale, float rotation){
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(pTexture, x, y, z, sX, sY, sW, sH, scale);
	if (fullBrightMode) {
		spriteDraws[currentDrawIndex]->setFullBright();
	}
	spriteDraws[currentDrawIndex]->w = sW*scale;
	spriteDraws[currentDrawIndex]->h = sH * scale;
	spriteDraws[currentDrawIndex]->setRotation(rotation);
	spriteDraws[currentDrawIndex]->setPipeline(pipelineIndex);
	if (absoluteMode) {
		spriteDraws[currentDrawIndex]->absolute = true;
	}
	currentDrawIndex++;
	lastAbsolute = false;

}

void SpriteCollection::addRotatedImageDrawCut(TextureWrapper* pTexture, float x, float y, float z, int sX, int sY, int sW, int sH, float scale, float rotation, float rx, float ry) {
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(pTexture, x, y, z, sX, sY, sW, sH, scale);
	if (fullBrightMode) {
		spriteDraws[currentDrawIndex]->setFullBright();
	}
	spriteDraws[currentDrawIndex]->w = sW*scale;
	spriteDraws[currentDrawIndex]->h = sH*scale;
	spriteDraws[currentDrawIndex]->setRotation(rotation);
	spriteDraws[currentDrawIndex]->setRPoint(rx, ry);
	spriteDraws[currentDrawIndex]->setPipeline(pipelineIndex);
	if (absoluteMode) {
		spriteDraws[currentDrawIndex]->absolute = true;
	}
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
	spriteDraws[currentDrawIndex]->setPipeline(pipelineIndex);
	if (absoluteMode) {
		spriteDraws[currentDrawIndex]->absolute = true;
	}
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
	spriteDraws[currentDrawIndex]->w = r * 2;
	spriteDraws[currentDrawIndex]->h = r * 2;
	spriteDraws[currentDrawIndex]->setPipeline(pipelineIndex);
	if (absoluteMode) {
		spriteDraws[currentDrawIndex]->absolute = true;
	}
	currentDrawIndex++;
	lastAbsolute = false;

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
	if (absoluteMode) {
		spriteDraws[currentDrawIndex]->absolute = true;
	}
	currentDrawIndex++;
	lastAbsolute = false;

}

void SpriteCollection::drawAll() {
	if (toBlink) {
		//pGraphics->drawRect(0, 0, 3000, 3000, sf::Color::Black);
		//addAbsoluteRectDraw(0, 0, 4000, 4000, 10000000, sf::Color::Black);
		toBlink = false;
		//clearSpriteDraws();
		//return;
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
	sf::RenderTexture* RTSel = &lit;

	glm::vec2 cameraPos = pCamera->getPosition() - glm::vec2(*pWindowW/2 + 100, *pWindowH/2 + 100);
	glm::vec2 viewDim = glm::vec2(*pWindowW + 200, *pWindowH + 200);
	for (int i = 0; i < currentDrawIndex; i++) {
		if (spriteDraws[i]->absolute) {
			continue;
		}
		//make sure the sprite is actually on screen at least partially
		if (spriteDraws[i]->x > cameraPos.x + viewDim.x || spriteDraws[i]->x + spriteDraws[i]->w < cameraPos.x || spriteDraws[i]->y > cameraPos.y + viewDim.y || spriteDraws[i]->y + spriteDraws[i]->h < cameraPos.y) {
			continue;
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
		else if (spriteDraws[i]->type == 5) {
			multiPipelineManager->executeWithTransform(spriteDraws[i]->pipelineIndex, spriteDraws[i]->pRaster, RTSel, temp.x, temp.y, 1, 0, spriteDraws[i]->opacity);
		}
	}
	lit.display();
	sf::RenderTexture intermediate;
	intermediate.create(pWindow->getSize().x, pWindow->getSize().y);
	multiPipelineManager->executeWithTransform(1, &lit.getTexture(), &intermediate, 0, 0, 1);

	RTSel = &intermediate;
	for (int i = 0; i < currentDrawIndex; i++) {
		if (!spriteDraws[i]->absolute) {
			continue;
		}
		//make sure the sprite is actually on screen at least partially
		if (spriteDraws[i]->x > 0 + viewDim.x || spriteDraws[i]->x + spriteDraws[i]->w < 0 || spriteDraws[i]->y > 0 + viewDim.y || spriteDraws[i]->y + spriteDraws[i]->h < 0) {
			continue;
		}
		// type 0 = image, 1 = image section, 2 = rectangle, 3 = circle, 4 = text
		temp = glm::vec2(spriteDraws[i]->x, spriteDraws[i]->y);
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
		else if (spriteDraws[i]->type == 5) {
			multiPipelineManager->executeWithTransform(spriteDraws[i]->pipelineIndex, spriteDraws[i]->pRaster, RTSel, temp.x, temp.y, 1, 0, spriteDraws[i]->opacity);
		}
	}

	intermediate.display();
	multiPipelineManager->blendTextures(0, intermediate.getTexture(), unlit.getTexture(), pWindow);
	//multiPipelineManager->executeWithTransform(0, &intermediate.getTexture(), pWindow, 0, 0, 1);
	clearSpriteDraws();
	return;

	unlit.display();
	//multiPipelineManager->executeWithTransform(1, &lit.getTexture(), pWindow, 0, 0, 1);
	
	sf::RenderTexture intermediate2;
	intermediate.create(pWindow->getSize().x, pWindow->getSize().y);
	intermediate2.create(pWindow->getSize().x, pWindow->getSize().y);

	if (!bloomMode) {
		//multiPipelineManager->executeWithTransform(pipelineIndex, &lit.getTexture(), pWindow, 0, 0, 1);
		multiPipelineManager->executeWithTransform(pipelineIndex, &lit.getTexture(), &intermediate, 0, 0, 1);
		intermediate.display();
		//multiPipelineManager->executeWithTransform(pipelineIndex, &unlit.getTexture(), pWindow, 0, 0, 1);
		multiPipelineManager->blendTextures(0, intermediate.getTexture(), unlit.getTexture(), pWindow);
		clearSpriteDraws();
		return;
	}

	sf::RenderTexture bloom;
	bloom.create(pWindow->getSize().x, pWindow->getSize().y);
	
	
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

void SpriteCollection::drawLightSource(glm::vec2 p1, glm::vec3 colour, float intensity, float type) {
	if (numPointLights >= maxPointLights) {
		std::cout << "MAX POINT LIGHTS REACHED\n";
		return;
	}
	pointLightPositions[numPointLights].x = p1.x;
	pointLightPositions[numPointLights].y = p1.y;
	pointLightColours[numPointLights].x = colour.x;
	pointLightColours[numPointLights].y = colour.y;
	pointLightColours[numPointLights].z = colour.z;
	pointLightIntensities[numPointLights] = intensity;
	pointLightTypes[numPointLights] = type;
	numPointLights++;
}

void SpriteCollection::drawBeamLight(glm::vec2 p1, glm::vec2 p2, glm::vec3 colour, float intensity, float type){
	if (numBeamLights >= maxBeamLights) {
		std::cout << "MAX BEAM LIGHTS REACHED\n";
		return;
	}
	beamLightPositions1[numBeamLights].x = p1.x;
	beamLightPositions1[numBeamLights].y = p1.y;
	beamLightPositions2[numBeamLights].x = p2.x;
	beamLightPositions2[numBeamLights].y = p2.y;
	beamLightColours[numBeamLights].x = colour.x;
	beamLightColours[numBeamLights].y = colour.y;
	beamLightColours[numBeamLights].z = colour.z;
	beamLightIntensities[numBeamLights] = intensity;
	beamLightTypes[numBeamLights] = type;
	numBeamLights++;
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
	for (int i = 0; i < numPointLights; i++) {
		pointLightPositions[i] = sf::Glsl::Vec2(pointLightPositions[i].x - pCamera->getPosition().x + *pWindowW / 2, -pointLightPositions[i].y + pCamera->getPosition().y + *pWindowH / 2);
	}
	lightingShader->setUniform("numPointLights", (float)numPointLights);
	lightingShader->setUniformArray("pointLightPositions", pointLightPositions, 100);
	lightingShader->setUniformArray("pointLightColours", pointLightColours, 100);
	lightingShader->setUniformArray("pointLightIntensities", pointLightIntensities, 100);
	lightingShader->setUniformArray("pointLightTypes", pointLightTypes, 100);
	numPointLights = 0;

	for (int i = 0; i < numBeamLights; i++) {
		beamLightPositions1[i] = sf::Glsl::Vec2(beamLightPositions1[i].x - pCamera->getPosition().x + *pWindowW / 2, -beamLightPositions1[i].y + pCamera->getPosition().y + *pWindowH / 2);
		beamLightPositions2[i] = sf::Glsl::Vec2(beamLightPositions2[i].x - pCamera->getPosition().x + *pWindowW / 2, -beamLightPositions2[i].y + pCamera->getPosition().y + *pWindowH / 2);
	}
	lightingShader->setUniform("numBeamLights", (float)numBeamLights);
	lightingShader->setUniformArray("beamLightPositions1", beamLightPositions1, 50);
	lightingShader->setUniformArray("beamLightPositions2", beamLightPositions2, 50);
	lightingShader->setUniformArray("beamLightColours", beamLightColours, 50);
	lightingShader->setUniformArray("beamLightIntensities", beamLightIntensities, 50);
	lightingShader->setUniformArray("beamLightTypes", beamLightTypes, 50);
	
	numBeamLights = 0;

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

sf::Texture SpriteCollection::rasterizeStack(int size, float w, float h){
	sf::RenderTexture rt;
	rt.create(w, h);
	glm::vec2 drawPoint = glm::vec2(spriteDraws[currentDrawIndex - size]->x, spriteDraws[currentDrawIndex - size]->y);
	glm::vec2 temp;
	glm::vec2 rPoint;

	for (int i = currentDrawIndex - size; i < currentDrawIndex; i++) {
		temp = glm::vec2(spriteDraws[i]->x, spriteDraws[i]->y) - drawPoint + glm::vec2(w/2, h/2);
		rPoint = glm::vec2(spriteDraws[i]->rx, spriteDraws[i]->ry) - drawPoint;
		if (spriteDraws[i]->rotationPoint) {
			multiPipelineManager->executeWithTransform(spriteDraws[i]->pipelineIndex, spriteDraws[i]->pTexture->getTexture(), &rt, temp.x, temp.y, spriteDraws[i]->scale, spriteDraws[i]->rotation, rPoint.x, rPoint.y, spriteDraws[i]->opacity, true, spriteDraws[i]->sX, spriteDraws[i]->sY, spriteDraws[i]->sW, spriteDraws[i]->sH);
		}
		else {
			multiPipelineManager->executeWithTransform(spriteDraws[i]->pipelineIndex, spriteDraws[i]->pTexture->getTexture(), &rt, temp.x, temp.y, spriteDraws[i]->scale, spriteDraws[i]->opacity, spriteDraws[i]->rotation, spriteDraws[i]->sX, spriteDraws[i]->sY, spriteDraws[i]->sW, spriteDraws[i]->sH);
		}
	}
	currentDrawIndex -= size;
	rt.display();
	return rt.getTexture();
}

void SpriteCollection::drawRasterization(sf::Texture* texture, float z, float x, float y, float w, float h){
	if (currentDrawIndex >= maxSpriteDraws) {
		std::cout << "MAX NUMBER OF SPRITEDRAWS REACHED!\n";
		return;
	}
	spriteDraws[currentDrawIndex] = new SpriteDraw(texture, x, y, z, w, h);
	if (fullBrightMode) {
		spriteDraws[currentDrawIndex]->setFullBright();
	}
	spriteDraws[currentDrawIndex]->setPipeline(pipelineIndex);
	if (absoluteMode) {
		spriteDraws[currentDrawIndex]->absolute = true;
	}
	currentDrawIndex++;
	lastAbsolute = false;

}

void SpriteCollection::setAbsoluteMode(bool mode){
	absoluteMode = mode;
}
