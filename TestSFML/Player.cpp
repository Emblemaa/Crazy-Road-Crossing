#include "Player.h"

Player::Player()
{
	player.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
	player.setPosition(PLAY_WINDOW_WIDTH / 2 - player.getSize().x / 2, LOWEST_LANE_Y + GAP/1.1 - player.getSize().y);
	player.setFillColor(sf::Color::Red);
	sb_fxsk = nullptr;
}

Player::Player(sf::SoundBuffer* sb, int vol_sfx)
{
	player.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
	player.setPosition(PLAY_WINDOW_WIDTH / 2 - player.getSize().x / 2, LOWEST_LANE_Y + GAP/1.1 - player.getSize().y);
	player.setFillColor(sf::Color::Red);

	sb_fxsk = new sf::Sound[5];
	for (int i = 0; i < 5; i++) {
		if (i >= 3) {
			sb_fxsk[i].setBuffer(sb[i + 2]);
		}
		else sb_fxsk[i].setBuffer(sb[i]);
		sb_fxsk[i].setVolume((float)vol_sfx * 10.f);
	}
}

void Player::move(const sf::Event& ev)
{
    if (ev.type == sf::Event::KeyPressed)
    {
        if (ev.key.code == sf::Keyboard::W && player.getPosition().y - PLAYER_SPEED_Y > 0)
        {
            player.move({ 0, -PLAYER_SPEED_Y* 1.01 });
        }
        else if (ev.key.code == sf::Keyboard::A && player.getPosition().x - PLAYER_SPEED_X > 0)
        {
            player.move({ -PLAYER_SPEED_X, 0 });
        }
        else if (ev.key.code == sf::Keyboard::S && player.getPosition().y + PLAYER_SPEED_Y < PLAY_WINDOW_HEIGHT - player.getSize().y)
        {
            player.move({ 0, PLAYER_SPEED_Y });
        }
        else if (ev.key.code == sf::Keyboard::D && player.getPosition().x + PLAYER_SPEED_X < PLAY_WINDOW_WIDTH - player.getSize().x)
        {
            player.move({ PLAYER_SPEED_X, 0 });
        }
    }
}

void Player::render(sf::RenderWindow* window)
{
    window->draw(player);
}

sf::FloatRect Player::get_bound()
{
    return player.getGlobalBounds();
}

bool Player::win()
{
    return player.getPosition().y <= LOWEST_LANE_Y - (LANE_NUMBER - 1) * GAP - PLAYER_SIZE;
}

void Player::set_initial_position()
{
	player.setPosition(PLAY_WINDOW_WIDTH / 2 - player.getSize().x / 2, LOWEST_LANE_Y + GAP/1.1 - player.getSize().y);
}

void Player::save_position(std::ofstream& out)
{
    float px = player.getPosition().x;
    float py = player.getPosition().y;
    out << px << " " << py << '\n';
}

void Player::load_position(std::ifstream& in)
{
    sf::Vector2f p;
    in >> p.x >> p.y;
    player.setPosition(p);
}