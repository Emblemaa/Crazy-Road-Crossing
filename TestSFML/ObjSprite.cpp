#include "ObjSprite.h"

// PROJECT - CLASS - OBJECT FUNCTION
// CONSTRUCTORS & DESTRUCTOR

ObjSprite::ObjSprite() {
	size_w = 0;
	size_h = 0;
	//frame_speed = FRAMESPEED * GAMESPEED;
	frame_idx = 0;
	frame_cur = nullptr;
	angle = 0;
	frame_time = 0;
	alpha = 255;
}

ObjSprite::~ObjSprite() {
	for (int i = 0; i < frame.size(); i++) {
		delete frame.at(i);
		frame.at(i) = nullptr;
	}
	frame_cur = nullptr;
}

ObjSprite::ObjSprite(sf::Texture* tx, int tx_idx, int nf_col, int nf_row, int idx_row) {
	sf::Vector2u v = tx[tx_idx].getSize();
	size_w = v.x / nf_col;
	size_h = v.y / nf_row;

	sf::Sprite* tSprite;
	for (int i = 0; i < nf_col; i++) {
		tSprite = nullptr;
		tSprite = new sf::Sprite;
		tSprite->setTexture(tx[tx_idx]);
		tSprite->setTextureRect(sf::IntRect(i * size_w,
			idx_row * size_h, size_w, size_h));
		tSprite->setOrigin(sf::Vector2f((float)size_w / 2.f, (float)size_h / 2.f));
		frame.push_back(tSprite);
	}

	//frame_speed = FRAMESPEED * GAMESPEED;
	frame_idx = 0;
	angle = 0;
	frame_cur = frame.at(0);
	frame_time = 0;
	alpha = 255;
}

// FUNCTIONS

void ObjSprite::Rotate_Frame() {
	for (int i = 0; i < frame.size(); i++) {
		frame.at(i)->setRotation(angle);
	}
}

void ObjSprite::Rotate(int degree) {
	angle += degree;
	Rotate_Frame();
}

void ObjSprite::RotateTo(int degree) {
	angle %= degree;
	Rotate_Frame();
}

void ObjSprite::Update() {
	/*frame_speed = FRAMESPEED * GAMESPEED;*/
	Rotate_Frame();
	UpdateAlpha();
	if (frame_time < frame_speed) {
		frame_time++;
	}
	else {

		if (frame_idx == frame.size() - 1) {
			frame_idx = 0;
		}
		else frame_idx++;
		frame_cur = frame.at(frame_idx);

		frame_time = 0;
	}
}

void ObjSprite::SetSpeed(float speed) {
	//frame_speed = speed * FRAMESPEED * GAMESPEED;
}

void ObjSprite::ClearSprite() {
	int ii = frame.size();
	for (int i = 0; i < ii; i++) {
		frame.pop_back();
	}
}

void ObjSprite::SetSprite(sf::Texture* tx, int tx_idx, int nf_col, int nf_row, int idx_row, int type) {
	sf::Vector2u v = tx[tx_idx].getSize();
	size_w = v.x / nf_col;
	size_h = v.y / nf_row;

	ClearSprite();
	sf::Sprite* tSprite;
	for (int i = 0; i < nf_col; i++) {
		tSprite = nullptr;
		tSprite = new sf::Sprite;
		tSprite->setTexture(tx[tx_idx]);
		tSprite->setTextureRect(sf::IntRect(i * size_w,
			idx_row * size_h, size_w, size_h));
		tSprite->setOrigin(sf::Vector2f((float)size_w / 2.f, (float)size_h / 2.f));
		frame.push_back(tSprite);
	}
	if (type == 0) {
		frame_idx = 0;
		frame_cur = frame.at(0);
	}
}

void ObjSprite::SetPosition(int xx, int yy) {
	for (int i = 0; i < frame.size(); i++) {
		frame.at(i)->setPosition(sf::Vector2f(xx, yy));
	}
}

void ObjSprite::SetOrigin(sf::Vector2f origin) {
	for (int i = 0; i < frame.size(); i++) {
		frame.at(i)->setOrigin(origin);
	}
}

void ObjSprite::SetScale(sf::Vector2f scale) {
	for (int i = 0; i < frame.size(); i++) {
		frame.at(i)->setScale(scale);
	}
}

void ObjSprite::ResetSpeed() {
	//frame_speed = FRAMESPEED * GAMESPEED;
}

sf::Sprite ObjSprite::FrameIdx(int idx) {
	return (*frame.at(idx));
}

int ObjSprite::OutOfScreenVer() {
	if (frame_cur->getPosition().y + (float)size_h / 2.f < 0) return -1;
	//if (frame_cur->getPosition().y - (float)size_h / 2.f > RESO_HEIGHT) return 3;
}

int ObjSprite::OutOfScreenHor() {
	if (frame_cur->getPosition().x + (float)size_w / 2.f < 0) return -1;
	//if (frame_cur->getPosition().x - (float)size_w / 2.f > RESO_WIDTH) return 1;
}

void ObjSprite::SetAlpha(int alpha) {
	this->alpha = alpha;
}

void ObjSprite::Animate_Idle() {
	frame_idx = 0;
	frame_speed = 0;
	frame_cur = frame.at(frame_idx);
}

bool ObjSprite::Animate_FadeOut() {
	alpha -= 1;
	if (alpha < 0) {
		alpha = 255;
		return true;
	}
	return false;
}