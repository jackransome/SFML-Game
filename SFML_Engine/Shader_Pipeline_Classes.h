#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class RenderingPipeline {
public:
    std::vector<sf::Shader*> stages;
    int length = 0;
    bool wholeScreen;

    RenderingPipeline(bool wholeScreen = false) : wholeScreen(wholeScreen) {}

    void addStage(sf::Shader* stage) {
        stages.push_back(stage);
        length++;
    }

    void execute(const sf::Sprite& inputSprite, sf::RenderTarget* finalOutputTarget, const sf::Transform& transform) {
        //finalOutputTarget->draw(inputSprite, transform);
        //return;
        //get the size of the area that the first pass should run on
        sf::Vector2u inputSize;

        //depends on if you want to do a pass that writes to a screen sized texture first
        if (wholeScreen) {
            inputSize = finalOutputTarget->getSize();
        }
        else {
            inputSize = sf::Vector2u(inputSprite.getTextureRect().width, inputSprite.getTextureRect().height);
        }

        //if you want to write to a screen sized texture first, do that (using transform, so dont transform later)
        sf::RenderTexture inputTexture;
        if (wholeScreen) {
            inputTexture.create(inputSize.x, inputSize.y);
            inputTexture.clear(sf::Color(0, 0, 0, 0));
            inputTexture.draw(inputSprite, transform);
            inputTexture.display();
        }

        //create currentInput

        sf::RenderTexture* currentInput = new sf::RenderTexture();
        currentInput->create(inputSize.x, inputSize.y);

        //loop through stages
        sf::RenderStates renderStates;
        
        sf::Sprite tempSprite;

        //if (inputSprite.getScale() == sf::Vector2f(1.1, 1.1)) {
        //    int x = 10;
        //    int y = 10;
        //    const sf::Texture* texture = inputSprite.getTexture();
        //    // Convert the texture to an image
        //    sf::Image image = texture->copyToImage();

        //    // Get the color of the pixel at the given coordinates
        //    if (x < image.getSize().x && y < image.getSize().y) {
        //        sf::Color color = image.getPixel(x, y);

        //        // Print the RGBA values
        //        std::cout << "RGBA("
        //            << static_cast<int>(color.r) << ", "
        //            << static_cast<int>(color.g) << ", "
        //            << static_cast<int>(color.b) << ", "
        //            << static_cast<int>(color.a) << ")"
        //            << std::endl;
        //    }
        //    else {
        //        std::cerr << "Coordinates are out of bounds." << std::endl;
        //    }
        //}

        //if there is only one stage, just write directly to the final target
        if (stages.size() == 1) {
            if (wholeScreen) {
                //no need to transform as that was already done, just use the shader to write to the output


                tempSprite.setTexture(inputTexture.getTexture());

                //need to flip the sprite apparently?
                //tempSprite.setTextureRect(sf::IntRect(0, static_cast<int>(tempOutput.getSize().y), static_cast<int>(tempOutput.getSize().x), -static_cast<int>(tempOutput.getSize().y)));

                //draw to final target
                finalOutputTarget->draw(tempSprite, stages[0]);



                delete currentInput;
                return;
            }
            else {
                //not wholeScreen
                //need to both transform and apply shader

                renderStates = sf::RenderStates::Default;
                renderStates.transform = transform;
                renderStates.shader = stages[0];
                finalOutputTarget->draw(inputSprite, renderStates);
                delete currentInput;
                return;
            }
        }

        //create tempOutput
        sf::RenderTexture tempOutput;
        tempOutput.create(inputSize.x, inputSize.y);
        
        for (size_t i = 0; i < stages.size(); ++i) {
            const auto& stage = stages[i];
            bool isFinalStage = (i == stages.size() - 1);

            //clear tempOutput
            tempOutput.clear(sf::Color(0, 0, 0, 0));

            if (i == 0) {
                //if there is only one stage, just write directly to the final target

                if (wholeScreen) {
                    tempOutput.draw(sf::Sprite(inputTexture.getTexture()), stage);
                }
                else {
                    tempOutput.draw(inputSprite, stage);
                }
            }
            else {
                tempOutput.draw(sf::Sprite(currentInput->getTexture()), stage);
            }

            //is this needed?
            tempOutput.display();

            if (!isFinalStage) {
                //if not the final stage, write tempOutput to currentInput
                currentInput->clear(sf::Color(0, 0, 0, 0));
                currentInput->draw(sf::Sprite(tempOutput.getTexture()));
                currentInput->display();
            }
            else if (finalOutputTarget) {
                //if it is the final stage
                if (wholeScreen) {
                    //just draw if already transformed
                    finalOutputTarget->draw(sf::Sprite(tempOutput.getTexture()));
                }
                else {
                    //have to transform if not already done
                    finalOutputTarget->draw(sf::Sprite(tempOutput.getTexture()), transform);
                }

                // Check if finalOutputTarget is an sf::RenderWindow or an sf::RenderTexture and call display()
                if (sf::RenderWindow* window = dynamic_cast<sf::RenderWindow*>(finalOutputTarget)) {
                    //window->display();
                }
                else if (sf::RenderTexture* renderTexture = dynamic_cast<sf::RenderTexture*>(finalOutputTarget)) {
                    //renderTexture->display();
                }
            }
        }
        delete currentInput;
    }
};

class MultiPipeline {
public:
    std::vector<std::shared_ptr<RenderingPipeline>> pipelines;

    void addPipeline(const std::shared_ptr<RenderingPipeline>& pipeline) {
        pipelines.push_back(pipeline);
    }


    void executeAll(const sf::Sprite& inputSprite, sf::RenderTarget* finalOutputTarget, const sf::Transform& transform) {

        for (const auto& pipeline : pipelines) {
            pipeline->execute(inputSprite, finalOutputTarget, transform);
            return;
        }
    }
};

class MultiPipelineManager {
public:
    std::vector<std::shared_ptr<MultiPipeline>> multiPipelines;

    std::vector<sf::Shader*> blendShaders;

    void addBlendShader(sf::Shader* blendShader) {
        blendShaders.push_back(blendShader);
    }

    void blendTextures(int blendShaderIndex, sf::Texture in1, sf::Texture in2, sf::RenderTarget* target) {
        blendShaders[blendShaderIndex]->setUniform("texture2", in2);
        
        sf::RenderStates renderStates = sf::RenderStates::Default;
        renderStates.shader = blendShaders[blendShaderIndex];
        sf::Shader::bind(blendShaders[blendShaderIndex]);
        target->draw(sf::Sprite(in1), renderStates);
    }

    void addMultiPipeline(const std::shared_ptr<MultiPipeline>& multiPipeline) {
        multiPipelines.push_back(multiPipeline);
    }

    void executeWithTransform(size_t index, const sf::Texture* inputTexture, sf::RenderTarget* finalOutputTarget, float posX, float posY, float width, float height, float scale, float rotation, float transparency) {
        executeWithTransform(index, inputTexture, finalOutputTarget, posX, posY, scale, rotation, width/2, height/2, transparency, false, 0, 0, 0, 0);
        //THIS
    }

    void executeWithTransform(size_t index, const sf::Texture* inputTexture, sf::RenderTarget* finalOutputTarget, float posX, float posY, float scale) {
        executeWithTransform(index, inputTexture, finalOutputTarget, posX, posY, scale, 0, 0, 0, 1.0f, false, 0, 0, 0, 0);
    }

    void executeWithTransform(size_t index, const sf::Texture* inputTexture, sf::RenderTarget* finalOutputTarget, float posX, float posY, float scale, float rotation, float rotationCenterX, float rotationCenterY) {
        executeWithTransform(index, inputTexture, finalOutputTarget, posX, posY, scale, rotation, rotationCenterX, rotationCenterY, 1.0f, false, 0, 0, 0, 0);
    }

    void executeWithTransform(size_t index, const sf::Texture* inputTexture, sf::RenderTarget* finalOutputTarget, float posX, float posY, float scale, float transparency, int rectLeft, int rectTop, int rectWidth, int rectHeight) {
        executeWithTransform(index, inputTexture, finalOutputTarget, posX, posY, scale, 0, 0, 0, transparency, true, rectLeft, rectTop, rectWidth, rectHeight);
    }
    void executeWithTransform(size_t index, const sf::Texture* inputTexture, sf::RenderTarget* finalOutputTarget, float posX, float posY, float scale, float transparency, float rotation, int rectLeft, int rectTop, int rectWidth, int rectHeight) {
        executeWithTransform(index, inputTexture, finalOutputTarget, posX, posY, scale, rotation, (rectWidth * scale) / 2, (rectHeight * scale) / 2, transparency, true, rectLeft, rectTop, rectWidth, rectHeight);
    }
    void executeWithTransform(size_t index, const sf::Texture* inputTexture, sf::RenderTarget* finalOutputTarget, float posX, float posY, float scale, float rotation, float rotationCenterX, float rotationCenterY, float transparency, bool useTextureRect, int rectLeft, int rectTop, int rectWidth, int rectHeight) {
        if (index >= multiPipelines.size()) {
            return;
        }

        sf::Sprite inputSprite(*inputTexture);

        // Set the transparency of the sprite
        inputSprite.setColor(sf::Color(255, 255, 255, transparency * 255));

        if (useTextureRect) {
            inputSprite.setTextureRect(sf::IntRect(rectLeft, rectTop, rectWidth, rectHeight));
        }
        inputSprite.setPosition(posX, posY);
        inputSprite.setScale(scale, scale);

        // Create a transform that rotates, scales and translates the image around a specific point
        sf::Transform transform;
        transform.rotate(rotation, sf::Vector2f(posX + rotationCenterX, posY + rotationCenterY));
        if (index == 0) {
            finalOutputTarget->draw(inputSprite, transform);
            return;
        }

        multiPipelines[index]->executeAll(inputSprite, finalOutputTarget, transform);
    }

    void executeWithRectangle(size_t index, sf::RenderTarget* finalOutputTarget, float posX, float posY, float width, float height, const sf::Color& color) {
        if (width < 1 || height < 1) {
            return;
        }
        executeWithRectangle(index, finalOutputTarget, posX, posY, width, height, color, 0, 0, 0);
    }

    void executeWithRectangle(size_t index, sf::RenderTarget* finalOutputTarget, float posX, float posY, float width, float height, const sf::Color& color, float rotation, float rotationCenterX, float rotationCenterY) {
        if (index >= multiPipelines.size()) {
            return;
        }

        sf::RenderTexture rectangleRenderTexture;
        rectangleRenderTexture.create(width, height);
        rectangleRenderTexture.clear(sf::Color(0, 0, 0, 0));

        sf::RectangleShape rectangle(sf::Vector2f(width, height));
        rectangle.setFillColor(color);
        rectangle.setOrigin(width / 2.f, height / 2.f);

        // Define a custom blend mode
        sf::BlendMode blendMode(sf::BlendMode::One,     // Keep the source RGB values
            sf::BlendMode::Zero,    // Ignore the destination RGB values
            sf::BlendMode::Add,     // Add the source and destination RGB values
            sf::BlendMode::One,     // Keep the source alpha value
            sf::BlendMode::Zero,    // Ignore the destination alpha value
            sf::BlendMode::Add);    // Add the source and destination alpha values

    // Draw the rectangle with the custom blend mode
        rectangleRenderTexture.draw(rectangle, blendMode);
        rectangleRenderTexture.display();


        sf::Sprite inputSprite(rectangleRenderTexture.getTexture());
        inputSprite.setPosition(posX, posY);
        inputSprite.setScale(2, 2);

        // Create a transform that rotates and translates the rectangle around a specific point
        sf::Transform transform;

        if (rotation) transform.rotate(rotation, sf::Vector2f(posX + rotationCenterX, posY + rotationCenterY));




        multiPipelines[index]->executeAll(inputSprite, finalOutputTarget, transform);
    }
};

class TextureWrapper {
public:
    //constructor to set name and load from file
    TextureWrapper(std::string _name, const std::string& filename) {
        name = _name;
        texture.loadFromFile(filename);
    }

    // Load texture from memory
    bool loadFromMemory(const void* data, std::size_t size) {
        return texture.loadFromMemory(data, size);
    }

    // Load texture from image
    bool loadFromImage(const sf::Image& image) {
        return texture.loadFromImage(image);
    }

    // Get the size of the texture
    sf::Vector2u getSize() const {
        return texture.getSize();
    }

    // Get the underlying sf::Texture
    const sf::Texture* getTexture() const {
        return &texture;
    }

    std::string getName() {
        return name;
    }

private:
    sf::Texture texture;
    std::string name;
};