#include "game_machine.hpp"

#include <boost/sml.hpp>
#include <eventpp/callbacklist.h>
#include <sstream>
#include <variant>

#include "enemy.hpp"
#include "player.hpp"
#include "random_selector.hpp"

using namespace Coelacanth;
namespace sml = boost::sml;

namespace {
struct Tick {};
using GameEvent = std::variant<Tick>;

struct CombatState {};
struct EnemyDiedState {};

struct GameTransitions {
  auto operator()() const {
    using namespace sml;
    auto enemy_died_during_combat = [](GameMachine& machine) {
      for(auto player : machine.players) {
        player->hit(*machine.enemy);
        if(machine.enemy->stats.is_dead()) {
          LOG(INFO) << "LETHAL BLOW!";
          return true;
        }
      }

      if(machine.players.size()) {
        auto target = random_selector<Player*> (machine.players);
        machine.enemy->hit(*target);
        if(target->stats.is_dead()) {
          LOG(INFO) << "PLAYER KILLED!";
        }
      }

      return false;
    };
    auto refresh_enemy = [](GameMachine& machine) {
      delete machine.enemy;
      machine.create_enemy();
    };
    return make_transition_table(
      *state<CombatState> + event<Tick> [enemy_died_during_combat] = state<EnemyDiedState>,
       state<EnemyDiedState> + event<Tick> / refresh_enemy = state<CombatState>
    );
  }
};
}

struct GameMachine::Impl {
  explicit Impl(GameMachine& machine) : sm(machine) {
    events.append([this](const GameEvent& event) {
      std::visit([this](const auto& typed_event) {
        sm.process_event(typed_event);
      }, event);
    });
  }

  void publish(const GameEvent& event) {
    events(event);
  }

  sml::sm<GameTransitions> sm;
  eventpp::CallbackList<void(const GameEvent&)> events;
};

GameMachine::GameMachine()
  : enemy(nullptr), impl_(std::make_unique<Impl>(*this))
{
  create_enemy();
}

GameMachine::~GameMachine()
{
  delete enemy;
}

void GameMachine::tick()
{
  impl_->publish(Tick{});
}

void GameMachine::create_enemy()
{
  enemy = new Enemy("Slug");
  enemy->stats.xp = 5;
  enemy->stats.attack = 5;
  enemy->stats.health = 50;
}

void GameMachine::add_player(Player *player)
{
  players.push_back(player);
}

bool GameMachine::is_combat() const
{
  return impl_->sm.is(sml::state<CombatState>);
}

bool GameMachine::is_enemy_died() const
{
  return impl_->sm.is(sml::state<EnemyDiedState>);
}
