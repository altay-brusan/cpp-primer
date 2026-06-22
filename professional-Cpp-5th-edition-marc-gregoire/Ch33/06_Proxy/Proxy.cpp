/*
 * Chapter 33 - Proxy Pattern
 *
 * Demonstrates the Proxy pattern. PlayerProxy implements the same IPlayer
 * interface as the real Player and stands in for it, forwarding calls to the
 * wrapped object while adding behavior - here, checking for network connectivity
 * before sending an instant message and returning a graceful "offline" reply
 * when there is none. Client code (informWinner) talks only to the IPlayer
 * interface and is unaware it is dealing with a proxy.
 *
 * Key notes:
 *   - The proxy owns the real subject via a unique_ptr<IPlayer>.
 *   - Contains main(); run as a standalone program.
 */

#include <print>
#include <memory>
#include <string>
#include <string_view>
#include <utility>

using namespace std;

class IPlayer
{
public:
	virtual ~IPlayer() = default; // Always virtual destructor.
	virtual string getName() const = 0;
	// Sends an instant message to the player over the network and
	// returns the reply as a string.
	virtual string sendInstantMessage(string_view message) const = 0;
};




class Player : public IPlayer
{
public:
	string getName() const override;
	// Network connectivity is required.
	// Throws an exception if network connection is down.
	string sendInstantMessage(string_view message) const override;
};

string Player::getName() const
{
	return "Player1";
}

string Player::sendInstantMessage(string_view message) const
{
	// ...
	return "yes";
}




class PlayerProxy : public IPlayer
{
public:
	// Create a PlayerProxy, taking ownership of the given player.
	explicit PlayerProxy(unique_ptr<IPlayer> player);
	string getName() const override;
	// Network connectivity is optional.
	string sendInstantMessage(string_view message) const override;

private:
	bool hasNetworkConnectivity() const;
	unique_ptr<IPlayer> m_player;
};

PlayerProxy::PlayerProxy(unique_ptr<IPlayer> player)
	: m_player{ move(player) }
{
}

string PlayerProxy::getName() const
{
	return m_player->getName();
}

string PlayerProxy::sendInstantMessage(string_view message) const
{
	if (hasNetworkConnectivity()) { return m_player->sendInstantMessage(message); }
	else { return "The player has gone offline."; }
}

bool PlayerProxy::hasNetworkConnectivity() const
{
	// Figure out whether we have network connectivity...
	return true;
}




bool informWinner(const IPlayer& player)
{
	auto result{ player.sendInstantMessage("You have won! Play again?") };
	if (result == "yes") {
		println("{} wants to play again.", player.getName());
		return true;
	} else {
		// The player said no, or is offline.
		println("{} does not want to play again.", player.getName());
		return false;
	}
}

int main()
{
	PlayerProxy playerProxy{ make_unique<Player>() };
	informWinner(playerProxy);
}
