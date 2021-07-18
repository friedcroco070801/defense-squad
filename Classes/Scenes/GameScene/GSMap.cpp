#include "GSMap.h"
#include "AppDelegate.h"
#include "Components/GSFlag.h"
#include "Components/GSBrick.h"
#include <functional>

USING_NS_CC;

bool GSMap::init() {
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	return true;
}
void GSMap::createMap(LevelModel *level) {
	int a = level->getMap().size();
	int b = level->getMap()[0].size(); 

	auto mapImage = Sprite::create("sprites/MapLayer/khonggian.png");
	mapImage->setContentSize(Size(WIDTH,HEIGHT));
	mapImage->setContentSize(Size(SIZE_OF_SQUARE*COLUMNN, SIZE_OF_SQUARE*ROWW));
	mapImage->setAnchorPoint(Vec2(0,0));
	positionCell temp;
	mapImage->setPosition(Vec2(GRASS_POSITION_LEFT,GRASS_POSITION_BOTTOM));

	auto map = level->getMap();
	std::function<bool(int, int)> checkPath = [&map](int i, int j) -> bool {
		return (map[i][j] == 5 || map[i][j] == 1 || map[i][j] == 2);
	};

	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++) {
			temp.x = i;
			temp.y = j;
			if (checkPath(i, j)) {
				// auto enemyWay = Sprite::create("sprites/MapLayer/black.png");
				// enemyWay->setContentSize(Size(SIZE_OF_SQUARE, SIZE_OF_SQUARE));
				// enemyWay->setPosition(ROW_COLUMN_TO_POSITION(temp));
				// this->addChild(enemyWay);

				// Draw bricks
				bool left, right, up, down;
				left = right = up = down = false;
				
				if (i > 0) {
					if (checkPath(i - 1, j)) left = true;
				}
				if (i < a - 1) {
					if (checkPath(i + 1, j)) right = true;
				}
				if (j > 0) {
					if (checkPath(i, j - 1)) down = true;
				}
				if (j < b - 1) {
					if (checkPath(i, j + 1)) up = true;
				}

				auto brick = GSBrick::create();
				brick->setContentSize(Size(SIZE_OF_SQUARE, SIZE_OF_SQUARE));
				brick->setPosition(ROW_COLUMN_TO_POSITION(temp));
				this->addChild(brick);
				brick->putPiecesIntoPlace(left, right, up, down);

				// Draw endpoint of the path
				auto endPaths = level->getEndPaths();
				for (auto it = endPaths.begin(); it != endPaths.end(); it++) {
					if ((*it)[0] == i && (*it)[1] == j) {
						auto flag = GSFlag::create();
						flag->setAnchorPoint(Vec2(0.75f, 0.125f));
						flag->setPosition(ROW_COLUMN_TO_POSITION(temp));
						flag->flutterAnimate();
						this->addChild(flag);
					}
				}
			}
		}
	}
	this->addChild(mapImage,-1);
}