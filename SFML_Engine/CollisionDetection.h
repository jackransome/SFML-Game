#pragma once
#include "Math.h"
#include <vector>
#include <GLM/glm.hpp>
#include "BoundingBox.h"
//class which has all methods needed for collision detection used in the game, the standard paramater for an object that is going to be tested is BoundingBox

class CollisionDetection
{
public:
	CollisionDetection();
	~CollisionDetection();
	static bool pointRectangleIntersect(glm::vec2 _point, BoundingBox* _boundingBox);
	static bool CheckRectangleIntersect(glm::vec4* _rect1, glm::vec4* _rect2);
	static bool CheckRectangleIntersect(BoundingBox* _rect1, BoundingBox* _rect2);
	static void correctPosition(glm::vec4* _rect1, glm::vec4* _rect2);
	static bool correctPosition(BoundingBox* bb1, BoundingBox* bb2);
	static bool isCheckRequired(BoundingBox* bb1, BoundingBox* bb2);
	static bool checkParallel(glm::vec2 _p1, glm::vec2 _p2, glm::vec2 _p3, glm::vec2 _p4);
	static glm::vec2 getLineIntersect(glm::vec2 _p1, glm::vec2 _p2, glm::vec2 _p3, glm::vec2 _p4);
	static bool lineRectCollision(glm::vec2 _p1, glm::vec2 _p2, BoundingBox* _boundingBox);
	static glm::vec2 getLineRectCollision(glm::vec2 _p1, glm::vec2 _p2, BoundingBox* _boundingBox);
	static float getDistance(glm::vec2 p1, glm::vec2 p2);
	static bool isBetween(float _1, float _2, float _3);
	static bool doLinesColide(glm::vec2 _p1, glm::vec2 _p2, glm::vec2 _p3, glm::vec2 _p4);
	static float getAngle(glm::vec2 _p1, glm::vec2 _p2);
	static float getDistBetween(float _1, float _2);
private:
	static bool test1(glm::vec4* _rect1, glm::vec4* _rect2);
	static bool test2(glm::vec4* _rect1, glm::vec4* _rect2);
	static bool test3(glm::vec4* _rect1, glm::vec4* _rect2);
	static bool test4(glm::vec4* _rect1, glm::vec4* _rect2);
	static bool test5(glm::vec4* _rect1, glm::vec4* _rect2);
	static bool test6(glm::vec4* _rect1, glm::vec4* _rect2);
	static bool test7(glm::vec4* _rect1, glm::vec4* _rect2);
	static bool test8(glm::vec4* _rect1, glm::vec4* _rect2);
	static int getSide(glm::vec4* _rect1, glm::vec4* _rect2);
};