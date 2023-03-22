#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class RenderingPipeline {
public:
    std::vector<sf::Shader> stages;

    void addStage(const sf::Shader& stage) {
        stages.push_back(stage);
    }

    void execute(sf::RenderTexture* input, sf::RenderTarget* finalOutputTarget) {
        sf::RenderTexture* currentInput = input;

        for (size_t i = 0; i < stages.size(); ++i) {
            const auto& stage = stages[i];
            bool isFinalStage = (i == stages.size() - 1);

            sf::RenderTexture tempOutput;
            tempOutput.create(input->getSize().x, input->getSize().y);
            tempOutput.clear();
            tempOutput.draw(sf::Sprite(currentInput->getTexture()), &stage);
            tempOutput.display();

            if (!isFinalStage) {
                currentInput = &tempOutput;
            }
            else if (finalOutputTarget) {
                finalOutputTarget->clear();
                finalOutputTarget->draw(sf::Sprite(tempOutput.getTexture()));

                // Check if finalOutputTarget is an sf::RenderWindow or an sf::RenderTexture and call display()
                if (sf::RenderWindow* window = dynamic_cast<sf::RenderWindow*>(finalOutputTarget)) {
                    window->display();
                }
                else if (sf::RenderTexture* renderTexture = dynamic_cast<sf::RenderTexture*>(finalOutputTarget)) {
                    renderTexture->display();
                }
            }
        }
    }
};

class MultiPipeline {
public:
    std::vector<std::shared_ptr<RenderingPipeline>> pipelines;

    void addPipeline(const std::shared_ptr<RenderingPipeline>& pipeline) {
        pipelines.push_back(pipeline);
    }

    void executeAll(sf::RenderTexture* input, sf::RenderTarget* finalOutputTarget) {
        for (const auto& pipeline : pipelines) {
            pipeline->execute(input, finalOutputTarget);
        }
    }
};

class MultiPipelineManager {
public:
    std::vector<std::shared_ptr<MultiPipeline>> multiPipelines;

    void addMultiPipeline(const std::shared_ptr<MultiPipeline>& multiPipeline) {
        multiPipelines.push_back(multiPipeline);
    }

    void executeMultiPipeline(size_t index, sf::RenderTexture* input, sf::RenderTarget* finalOutputTarget) {
        if (index < multiPipelines.size()) {
            multiPipelines[index]->executeAll(input, finalOutputTarget);
        }
    }

    void executeWithTransform(size_t index, const sf::Texture& input, sf::RenderTarget* finalOutputTarget, float x, float y, float scale, float rotation, bool applyBefore) {
        if (index >= multiPipelines.size()) {
            return;
        }

        sf::RenderTexture intermediateTexture;
        intermediateTexture.create(finalOutputTarget->getSize().x, finalOutputTarget->getSize().y);

        if (applyBefore) {
            // Apply transformations before executing the pipeline
            intermediateTexture.clear(sf::Color(0, 0, 0, 0));
            sf::Sprite inputSprite(input);
            inputSprite.setPosition(x, y);
            inputSprite.setScale(scale, scale);
            inputSprite.setRotation(rotation);
            intermediateTexture.draw(inputSprite);
            intermediateTexture.display();

            sf::RenderTexture inputRenderTexture;
            inputRenderTexture.create(intermediateTexture.getSize().x, intermediateTexture.getSize().y);
            inputRenderTexture.draw(sf::Sprite(intermediateTexture.getTexture()));
            inputRenderTexture.display();

            multiPipelines[index]->executeAll(&inputRenderTexture, finalOutputTarget);
        }
        else {
            // Execute the pipeline and then apply transformations
            sf::RenderTexture inputRenderTexture;
            inputRenderTexture.create(input.getSize().x, input.getSize().y);
            inputRenderTexture.draw(sf::Sprite(input));
            inputRenderTexture.display();

            multiPipelines[index]->executeAll(&inputRenderTexture, &intermediateTexture);
            intermediateTexture.display();
            sf::Sprite outputSprite(intermediateTexture.getTexture());
            outputSprite.setPosition(x, y);
            outputSprite.setScale(scale, scale);
            outputSprite.setRotation(rotation);
            finalOutputTarget->draw(outputSprite);
        }
    }

    void executeWithTransform(size_t index, sf::Texture* inputTexture, sf::RenderTarget* finalOutputTarget, float posX, float posY, float scale, float rotation, float rotationCenterX, float rotationCenterY, bool applyBefore) {
        if (index >= multiPipelines.size()) {
            return;
        }

        sf::RenderTexture inputRenderTexture;
        inputRenderTexture.create(inputTexture->getSize().x, inputTexture->getSize().y);
        inputRenderTexture.clear(sf::Color(0, 0, 0, 0));
        inputRenderTexture.draw(sf::Sprite(*inputTexture));
        inputRenderTexture.display();

        sf::RenderTexture intermediateTexture;
        intermediateTexture.create(finalOutputTarget->getSize().x, finalOutputTarget->getSize().y);

        sf::Sprite inputSprite(inputRenderTexture.getTexture());

        // Create a transform that rotates, scales and translates the image around a specific point
        sf::Transform transform;
        transform.translate(rotationCenterX, rotationCenterY);
        transform.rotate(rotation);
        transform.translate(-rotationCenterX, -rotationCenterY);
        transform.scale(scale, scale);
        transform.translate(posX, posY);

        if (applyBefore) {
            // Apply transform before executing the pipeline
            intermediateTexture.clear(sf::Color(0, 0, 0, 0));
            intermediateTexture.draw(inputSprite, transform);
            intermediateTexture.display();
            multiPipelines[index]->executeAll(&intermediateTexture, finalOutputTarget);
        }
        else {
            // Execute the pipeline and then apply transform
            multiPipelines[index]->executeAll(&inputRenderTexture, &intermediateTexture);
            intermediateTexture.display();
            finalOutputTarget->draw(sf::Sprite(intermediateTexture.getTexture()), transform);
        }
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
    const sf::Texture& getTexture() const {
        return texture;
    }

    std::string getName() {
        return name;
    }

private:
    sf::Texture texture;
    std::string name;
};