#ifndef ObjSprite_h
#define ObjSprite_h

#include"CONSTANTS.h"

class ObjSprite
{
private:
	int size_w, size_h, frame_time, frame_speed, frame_idx, alpha;
	vector<sf::Sprite*>frame;
public:
	int angle;
	sf::Sprite* frame_cur;
	ObjSprite();
	~ObjSprite();
	ObjSprite(sf::Texture* tx, int tx_idx, int nf_col, int nf_row, int idx_row);

	void Rotate_Frame();
	void Rotate(int degree);
	void RotateTo(int degree);
	void Update();
	void UpdateAlpha() {
		for (int i = 0; i < frame.size(); i++) {
			frame.at(i)->setColor(sf::Color(255, 255, 255, this->alpha));
		}
	}
	void SetSpeed(float speed);
	void ClearSprite();
	void SetSprite(sf::Texture* tx, int tx_idx, int nf_col, int nf_row, int idx_row, int type);
	void SetPosition(int xx, int yy);
	void SetOrigin(sf::Vector2f origin);
	void SetScale(sf::Vector2f scale);
	void ResetSpeed();
	sf::Sprite FrameIdx(int idx);
	int OutOfScreenHor();
	int OutOfScreenVer();
	void SetAlpha(int alpha);
	int GetAlpha() {
		return alpha;
	}
	sf::Vector2f GetSize() {
		return sf::Vector2f((float)size_w, (float)size_h);
	}
	sf::Vector2f GetOrigin() {
		return frame_cur->getOrigin();
	}

	void Animate_Idle();
	bool Animate_FadeOut();
};

#endif


