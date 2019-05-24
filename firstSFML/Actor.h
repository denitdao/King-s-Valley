#include "pch.h"
//

class Actor : public Block {
protected:
	t_direcrion dir;
	float yJumpSpeed = gravity_speed;
public:
	int xMap, yMap;
	sf::Vector2f respawnPos = {100.f,100.f};
	bool coinAmountIncrease = false;
	bool inJump = false;
	bool onLeftStair = false;
	bool onRightStair = false;
	bool upArrowPressed = false;
	bool downArrowPressed = false;
	bool leftArrowPressed = false;
	bool rightArrowPressed = false;
	Actor(sf::Vector2f size) : Block(size) { //
		object.setFillColor(sf::Color::Blue);
		dir = none;
	}
	void moveOn(sf::Vector2f distance) {
		distance.x *= dir;
		object.move(distance);
		sprite.move(distance);
	}
	void respawn() {
		inJump = false;
		onLeftStair = false;
		onRightStair = false;
		upArrowPressed = false;
		downArrowPressed = false;
		setPos(respawnPos);
	}
	void setDir(enum direction d) {
		dir = d;
	}
	void initJumpSpeed() {
		yJumpSpeed = gravity_speed;
	}
	void jump() {
		std::cout << "inJump - " << ((inJump) ? "true" : "false") << std::endl;
		if (inJump == true) {
			lockJump = true;
			moveOn({ x_move_speed, yJumpSpeed });
			std::cout << "Jumping on { " << x_move_speed << " ; " << yJumpSpeed << " }" << std::endl;
			yJumpSpeed += jump_change_step;
			if (yJumpSpeed >= 10)
				yJumpSpeed = 0;
		}
		else {
			if (!onLeftStair && !onRightStair) {
				std::cout << "Falling down, Y  " << -gravity_speed << std::endl;
				moveOn({ 0, -gravity_speed });
				lockJump = true;
			}
			if (collision == bColl) {
				initJumpSpeed();
			}
		}
		if (collision == bColl || collision == tColl || collision == rColl || collision == lColl) {
			inJump = false;
		}
	}
	// more acc values can be decreased
	int checkCollision(Block &obj2) {
		int t = 0;
		t_texture objSkin = obj2.getTexture();
		if (objSkin == noTexture)
			return t;
		float deltaX = this->getSenter().x - obj2.getSenter().x;
		float deltaY = this->getSenter().y - obj2.getSenter().y;
		float intersectX = abs(deltaX) - (this->getSize().x / 2 + obj2.getSize().x / 2); // < 0
		float intersectY = abs(deltaY) - (this->getSize().y / 2 + obj2.getSize().y / 2); // < 0
			
		if (objSkin != stairLeft && objSkin != stairRight) {
			if (intersectX < 0.0f && intersectY < 0.0f) {
				if (objSkin == bot)
					return 2;
				if (objSkin == coin) {
					obj2.hideCoin();
					coinAmountIncrease = true;
					return 0;                              
				}
				std::cout << "Colliding | intersectX = " << intersectX << "| intersectY = " << intersectY << std::endl;
				if (intersectY < intersectX) {
					if (deltaX < 0) { // right intersect
						collision = rColl;
						std::cout << "right intersect, move X on " << intersectX << std::endl;
						if (!onLeftStair && !onRightStair)
							setPos({ obj2.getSenter().x - (this->getSize().x + obj2.getSize().x / 2) , this->getCoord().y });
					}
					if (deltaX > 0) { // left intersect
						collision = lColl;
						
						std::cout << "left intersect, move X on " << intersectX << std::endl;
						if (!onLeftStair && !onRightStair)
							setPos({ obj2.getSenter().x + obj2.getSize().x / 2, this->getCoord().y });
					}
				}
				else {
					if (deltaY < 0) { // bottom intersect
						collision = bColl;
						if (objSkin == bot)
							respawn();
						lockJump = false;
						std::cout << "bottom intersect, move Y on " << intersectY << std::endl;
						//							Now check if we are near/on the stair
						switch (objSkin) {
						case stairLeftUnder: {
							cout << "\n\nChecking stairLeftUnder\n\n" << endl;
							if (obj2.getSenter().x - x_move_speed <= this->getCoord().x && obj2.getSenter().x >= this->getCoord().x) { // senter of stair block = left side + 1 of the player
								cout << "\n\nSenter\n\n" << endl;
								if (onLeftStair) {
									if (this->dir == toright) {
										onLeftStair = false;
										cout << "\n\nPlayer is now onLeftStair = F A L S E\n\n" << endl;
									}

								}
								else { // not on stair
									if (this->dir == toleft && this->upArrowPressed) {
										onLeftStair = true;
										setPos({ obj2.getSenter().x - x_move_speed, this->getCoord().y }); // for more accurate process
										cout << "\n\nPlayer is now onLeftStair = T R U E\n\n" << endl;
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
							cout << "\n\nChecking stairLeftTop\n\n" << endl;
							if (obj2.getSenter().x - x_move_speed <= this->getCoord().x && obj2.getSenter().x >= this->getCoord().x) { // senter of stair block = left side of the player
								cout << "\n\nSenter\n\n" << endl;
								if (onLeftStair) {
									if (this->dir == toleft) {
										onLeftStair = false;
										cout << "\n\nPlayer is now onLeftStair = F A L S E\n\n" << endl;
									}
								}
								else { // not on stair
									if (this->dir == toright && this->downArrowPressed) {
										onLeftStair = true;
										setPos({ obj2.getSenter().x - x_move_speed, this->getCoord().y });  // for more accurate process
										cout << "\n\nPlayer is now onLeftStair = T R U E\n\n" << endl;
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
							cout << "\n\nChecking stairRightUnder\n\n" << endl;
							if (obj2.getSenter().x <= this->getCoord().x + this->getSize().x && obj2.getSenter().x + x_move_speed >= this->getCoord().x + this->getSize().x) { // senter of stair block = right side of the player
								cout << "\n\nSenter\n\n" << endl;
								if (onRightStair) {
									if (this->dir == toleft) {
										onRightStair = false;
										cout << "\n\nPlayer is now onRightStair = F A L S E\n\n" << endl;
									}
								}
								else { // not on stair
									if (this->dir == toright && this->upArrowPressed) {
										onRightStair = true;
										setPos({ obj2.getSenter().x - this->getSize().x + x_move_speed, this->getCoord().y }); // for more accurate process
										cout << "\n\nPlayer is now onRightStair = T R U E\n\n" << endl; ///!!!!!!!!!!!!!!!!!!!
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
							cout << "\n\nChecking stairRightTop\n\n" << endl;
							if (obj2.getSenter().x <= this->getCoord().x + this->getSize().x && obj2.getSenter().x + x_move_speed >= this->getCoord().x + this->getSize().x) { // senter of stair block = right side of the player
								cout << "\n\nSenter\n\n" << endl;
								if (onRightStair) {
									if (this->dir == toright) {
										onRightStair = false;
										cout << "\n\nPlayer is now onRightStair = F A L S E\n\n" << endl;
									}
								}
								else { // not on stair
									if (this->dir == toleft && this->downArrowPressed) {
										onRightStair = true;
										setPos({ obj2.getSenter().x - this->getSize().x - x_move_speed, this->getCoord().y }); // for more accurate process
										cout << "\n\nPlayer is now onRightStair = T R U E\n\n" << endl;
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
							cout << "Checking default" << endl;
							if (!onLeftStair && !onRightStair)
								setPos({ this->getCoord().x , obj2.getSenter().y - (this->getSize().y + obj2.getSize().y / 2) });
							else if (intersectY > -x_move_speed) { // inters Y small
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
						std::cout << "top intersect, move Y on " << -intersectY << std::endl;
						setPos({ this->getCoord().x, obj2.getSenter().y + obj2.getSize().y / 2 });
					}
				}
				return 1;
			}
		}
		
		std::cout << "Not colliding" << std::endl;
		return 0;
	}
};
