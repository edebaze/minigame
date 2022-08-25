cmake_minimum_required(VERSION 3.23)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        untitled
        src/main.cpp
        src/objects/champions/Player.cpp
        src/objects/champions/Player.h
        src/objects/champions/classes/enums/ClassType.h
        src/objects/game/engine/GameMaster.cpp
        src/objects/game/engine/GameMaster.h
        src/objects/champions/spells/Spell.cpp
        src/objects/champions/spells/Spell.h
        src/objects/champions/spells/enums/SpellsList.h
        src/objects/champions/classes/enums/ClassTypeUtils.h
        src/objects/champions/spells/Boost.cpp
        src/objects/champions/spells/Boost.h
        src/objects/champions/items/Item.cpp
        src/objects/champions/items/Item.h
        src/objects/champions/items/enums/Emplacements.h
        src/objects/champions/items/Item.cpp
        src/objects/champions/items/Item.h
        src/objects/champions/items/enums/ItemList.h
        src/objects/game/rendering/Renderer.cpp
        src/objects/game/rendering/Renderer.h
        src/objects/game/rendering/enums/Colors.h
        src/objects/game/rendering/enums/Colors.cpp
        src/objects/champions/upgrades/Upgrade.cpp
        src/objects/champions/upgrades/Upgrade.h)
