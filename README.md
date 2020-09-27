Next state will be complete when:
Players kill Enemies to get XP / Loot
Players upgrade worn items to better items
Players can sell gear and store wealth between runs - requires clean recall

a clean recall is 'client said it bailed before it died'


add Classes:
Inventory<Item[4]>
Item: level
Weapon
Armor
Ring
Ability

protocol expansion:
From a Specification, generate classes to implement Protocol with expectation of user customization via augmented classes
* do not check generated protocol into source control
* save protocol definition in source control and generate it at build time

new protocol:
>LOGIN username
>PASSWORD password
<HELLO player\_id:int player_name:str

>INFOP player\_id
<PLAYERINFO skin\_id:int pet_id:int weapon_id:int special_id:int armor_id:int ring_id:int

#room is a list of enemies, in a certain order.  Multiple enemies can be combat active at once.
# list of lists of enemies*, move on to next room (on it's own port) when this room is cleared
#
<ENTER room\_id
>INFOR room\_id
<ROOMINFO room_name
<NEWENEMY monster_id monster_type

>ATTACK monster\_id


<UPDATE player\_id:int
>MOVE position:x,y

<FIRE 

Armor("Cotton Shirt");
Armor("Leather Armor");
Armor("Chainmail");
Armor("Plate");

Enemy("slug");
Enemy("goblin");
Enemy("orc");
Enemy("troll");
Enemy("HUNNYBADGER");

Weapon("stick");
Weapon("dagger");
Weapon("rapier");
Weapon("sword");
Weapon("arrow");
Weapon("grenade");

world = Map(20, 20);
world.entrance(10, 10);

# To Serve a Full Game:
# 100-200 instances running, on different ports
# port-per-server, only servers can talk to CentralDispatch to get new servers created.
# Server slots are re-used when CentralDispatch can no longer talk to service on that port

#CentralDispatch
#Heartbeat
#GameLobby (nexus)
# key pops -> room portal
#servers -> portal to active spacestations
#Room Servers



old stuff here
==============

use https://github.com/davidkristola/fluent-hsm-cpp

SPECS:
JOINED THE SERVER means you get a TICK from the server every 250ms

client commands
===============
HELO myname -- JOIN THE SERVER as myname
SWING targetid -- swing at target by id
GOODBYE -- disconnect from the server (clean)

server commands
===============
WELCOME targetid -- server recognizes you and bids you welcome
TICK tickid -- heartbeat
MONSTER typeid targetid -- a monster has appeared!
