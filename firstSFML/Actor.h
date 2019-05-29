#include "pch.h"
//

class Actor : public Block {
protected:
	t_direcrion dir; // enum of entity's direction
	float yJumpSpeed = GRAVITY_SPEED; // falling speed
	sf::Vector2f respawnPos; // coords of the respawn
	bool isPlayer = false; // entity is bot or player
public:
	int xMap, yMap; // coords of an area where entity located
	bool coinAmountIncrease = false; // should we increase coin amount ?
	bool inJump = false;
	bool onLeftStair = false;
	bool onRightStair = false;
	bool upArrowPressed = false;
	bool downArrowPressed = false;
	bool leftArrowPressed = false;
	bool rightArrowPressed = false;
	// create shape
	Actor(sf::Vector2f size) : Block(size) { 
		dir = none;
	}
	// move entity on a distance
	void moveOn(sf::Vector2f distance) { 
		distance.x *= dir;
		object.move(distance);
		sprite.move(distance);
	}
	// initialize respawnPos
	void setRespawn(sf::Vector2i coord) { 
		respawnPos = {coord.x * BLOCK_SIZE_X, coord.y * BLOCK_SIZE_Y - BLOCK_SIZE_Y };
	}
	// move player to the respawnPos
	void respawn() { 
		inJump = false;
		onLeftStair = false;
		onRightStair = false;
		upArrowPressed = false;
		downArrowPressed = false;
		setPos(respawnPos);
	}
	// initialize direction enum
	void setDir(enum direction d) { 
		dir = d;
	}
	// set falling speed value to max
	void initJumpSpeed() { 
		yJumpSpeed = GRAVITY_SPEED;
	}
	// jump or fall
	void jump() { 
		myLog(Logger::DEBUG) << "inJump - " << ((inJump) ? "true" : "false") << endl;

		if (inJump == true) {
			lockJump = true;
			moveOn({ X_MOVE_SPEED, yJumpSpeed }); // continue jump
			myLog(Logger::DEBUG) << "Jumping on { " << X_MOVE_SPEED << " ; " << yJumpSpeed << " }" << endl;
			yJumpSpeed += JUMP_CHANGE_STEP; // change Oy speed value
			if (yJumpSpeed >= -GRAVITY_SPEED * 2) // limit falling speed
				yJumpSpeed = -GRAVITY_SPEED * 2;
		}
		else {
			if (!onLeftStair && !onRightStair) { // unable to jump or fall being on the stair
				myLog(Logger::DEBUG) << "Falling down, Y  " << -GRAVITY_SPEED << std::endl;
				moveOn({ 0, -GRAVITY_SPEED }); // fall down
				lockJump = true;
			}
			if (collision == bColl) { // if we are on the ground
				initJumpSpeed();
			}
		}
		if (collision == bColl || collision == tColl || collision == rColl || collision == lColl) {
			inJump = false; // stop jumping if we have any contact with surface
		}
	}
	// check entitiy's collision with an object
	// empty texture - 4 | coin - 3 | bot - 2 | shape - 1 | no collision - 0
	int checkCollision(Block &obj2) { 
		t_texture objSkin = obj2.getTexture();
		if (objSkin == noTexture) // do not collide with empty blocks
			return 4;
		float deltaX = this->getSenter().x - obj2.getSenter().x;
		float deltaY = this->getSenter().y - obj2.getSenter().y;
		float intersectX = abs(deltaX) - (this->getSize().x / 2 + obj2.getSize().x / 2); // < 0
		float intersectY = abs(deltaY) - (this->getSize().y / 2 + obj2.getSize().y / 2); // < 0
			
		if (objSkin != stairLeft && objSkin != stairRight) { 
			if (intersectX < 0.0f && intersectY < 0.0f) {
				if (objSkin == bot) // colliding with a mummy
					return 2;
				if (objSkin == coin) {
					if (isPlayer) { // player collides with a coin
						obj2.hideCoin();
						coinAmountIncrease = true;
						return 3;                              
					}
					return 0;
				}
				myLog(Logger::DEBUG) << "Colliding | intersectX = " << intersectX << "| intersectY = " << intersectY << endl;
				if (intersectY < intersectX) { // move in the direction of higher intersect
					if (deltaX < 0) { // right intersect
						collision = rColl;
						myLog(Logger::DEBUG) << "right intersect, move X on " << intersectX << endl;
						if (!onLeftStair && !onRightStair)
							setPos({ obj2.getSenter().x - (this->getSize().x + obj2.getSize().x / 2) , this->getCoord().y });
					}
					if (deltaX > 0) { // left intersect
						collision = lColl;
						
						myLog(Logger::DEBUG) << "left intersect, move X on " << intersectX << endl;
						if (!onLeftStair && !onRightStair)
							setPos({ obj2.getSenter().x + obj2.getSize().x / 2, this->getCoord().y });
					}
				}
				else {
					if (deltaY < 0) { // bottom intersect
						collision = bColl;
						lockJump = false;
						myLog(Logger::DEBUG) << "bottom intersect, move Y on " << intersectY << std::endl;
						//							Now check if we are near/on the stair
						switch (objSkin) {
						case stairLeftUnder: {
							myLog(Logger::DEBUG) << "\n\nChecking stairLeftUnder\n\n" << endl;
							if (obj2.getSenter().x - X_MOVE_SPEED <= this->getCoord().x && obj2.getSenter().x >= this->getCoord().x) { // senter of stair block = left side + 1 of the player
								myLog(Logger::DEBUG) << "\n\nSenter\n\n" << endl;
								if (onLeftStair) {
									if (this->dir == toright) {
										onLeftStair = false;
										myLog(Logger::DEBUG) << "\n\nPlayer is now onLeftStair = F A L S E\n\n" << endl;
									}

								}
								else { // not on stair
									if (this->dir == toleft && this->upArrowPressed) {
										onLeftStair = true;
										setPos({ obj2.getSenter().x - X_MOVE_SPEED, this->getCoord().y }); // for more accurate process
										myLog(Logger::DEBUG) << "\n\nPlayer is now onLeftStair = T R U E\n\n" << endl;
										break;
									}
									else
										onLeftStair = false;
								}
							}
							setPos({ this->getCoord().x , obj2.getSenter().y - (this->getSize().y + obj2.getSize().y / 2) });
							break;
						}
						case stairLeftTop: {
							myLog(Logger::DEBUG) << "\n\nChecking stairLeftTop\n\n" << endl;
							if (obj2.getSenter().x - X_MOVE_SPEED <= this->getCoord().x && obj2.getSenter().x >= this->getCoord().x) { // senter of stair block = left side of the player
								myLog(Logger::DEBUG) << "\n\nSenter\n\n" << endl;
								if (onLeftStair) {
									if (this->dir == toleft) {
										onLeftStair = false;
										myLog(Logger::DEBUG) << "\n\nPlayer is now onLeftStair = F A L S E\n\n" << endl;
									}
								}
								else { // not on stair
									if (this->dir == toright && this->downArrowPressed) {
										onLeftStair = true;
										setPos({ obj2.getSenter().x - X_MOVE_SPEED, this->getCoord().y });  // for more accurate process
										myLog(Logger::DEBUG) << "\n\nPlayer is now onLeftStair = T R U E\n\n" << endl;
										break;
									}
									else
										onLeftStair = false;
								}
							}
							setPos({ this->getCoord().x , obj2.getSenter().y - (this->getSize().y + obj2.getSize().y / 2) });
							break;
						}
						case stairRightUnder: {
							myLog(Logger::DEBUG) << "\n\nChecking stairRightUnder\n\n" << endl;
							if (obj2.getSenter().x <= this->getCoord().x + this->getSize().x && obj2.getSenter().x + X_MOVE_SPEED >= this->getCoord().x + this->getSize().x) { // senter of stair block = right side of the player
								myLog(Logger::DEBUG) << "\n\nSenter\n\n" << endl;
								if (onRightStair) {
									if (this->dir == toleft) {
										onRightStair = false;
										myLog(Logger::DEBUG) << "\n\nPlayer is now onRightStair = F A L S E\n\n" << endl;
									}
								}
								else { // not on stair
									if (this->dir == toright && this->upArrowPressed) {
										onRightStair = true;
										setPos({ obj2.getSenter().x - this->getSize().x + X_MOVE_SPEED, this->getCoord().y }); // for more accurate process
										myLog(Logger::DEBUG) << "\n\nPlayer is now onRightStair = T R U E\n\n" << endl; ///!!!!!!!!!!!!!!!!!!!
										break;
									}
									else
										onRightStair = false;
								}
							}
							setPos({ this->getCoord().x , obj2.getSenter().y - (this->getSize().y + obj2.getSize().y / 2) });
							break;
						}
						case stairRightTop: {
							myLog(Logger::DEBUG) << "\n\nChecking stairRightTop\n\n" << endl;
							if (obj2.getSenter().x <= this->getCoord().x + this->getSize().x && obj2.getSenter().x + X_MOVE_SPEED >= this->getCoord().x + this->getSize().x) { // senter of stair block = right side of the player
								myLog(Logger::DEBUG) << "\n\nSenter\n\n" << endl;
								if (onRightStair) {
									if (this->dir == toright) {
										onRightStair = false;
										myLog(Logger::DEBUG) << "\n\nPlayer is now onRightStair = F A L S E\n\n" << endl;
									}
								}
								else { // not on stair
									if (this->dir == toleft && this->downArrowPressed) {
										onRightStair = true;
										setPos({ obj2.getSenter().x - this->getSize().x - X_MOVE_SPEED, this->getCoord().y }); // for more accurate process
										myLog(Logger::DEBUG) << "\n\nPlayer is now onRightStair = T R U E\n\n" << endl;
										break;
									}
									else
										onRightStair = false;
								}
							}
							setPos({ this->getCoord().x , obj2.getSenter().y - (this->getSize().y + obj2.getSize().y / 2) });
							break;
						}
						case stairLeft: {
							// do nothing
							break;
						}
						case stairRight: {
							// do nothing
							break;
						}
						default: {
							myLog(Logger::DEBUG) << "Checking default" << endl;
							if (!onLeftStair && !onRightStair)
								setPos({ this->getCoord().x , obj2.getSenter().y - (this->getSize().y + obj2.getSize().y / 2) });
							else if (intersectY > -X_MOVE_SPEED) { // inters Y small
								onLeftStair = false;
								onRightStair = false;
							}
							break;
						}
						}
					}
					if (deltaY > 0) { // top intersect
						collision = tColl;
						if (objSkin == bot)
							respawn();
						myLog(Logger::DEBUG) << "top intersect, move Y on " << -intersectY << std::endl;
						setPos({ this->getCoord().x, obj2.getSenter().y + obj2.getSize().y / 2 });
					}
				}
				return 1;
			}
		}
		
		myLog(Logger::DEBUG) << "Not colliding" << std::endl;
		return 0;
	}
};
