1-1: main.cpp DwindlingGalaxies.cpp
	@g++ main.cpp DwindlingGalaxies.cpp -lsfml-graphics -lsfml-window -lsfml-system -o game
	@clear
	@./game

1-2: main.cpp DwindlingGalaxies.cpp GameEntity.cpp
	@g++ main.cpp DwindlingGalaxies.cpp GameEntity.cpp -lsfml-graphics -lsfml-window -lsfml-system -o game
	@clear
	@./game	

2-1: main.cpp DwindlingGalaxies.cpp GameEntity.cpp Player.cpp
	@g++ main.cpp DwindlingGalaxies.cpp GameEntity.cpp Player.cpp -lsfml-graphics -lsfml-window -lsfml-system -o game
	@./game	
	@clear

2-2: main.cpp DwindlingGalaxies.cpp GameEntity.cpp Player.cpp Laser.cpp
	@g++ main.cpp DwindlingGalaxies.cpp GameEntity.cpp Player.cpp Laser.cpp -lsfml-graphics -lsfml-window -lsfml-system -o game
	@./game	
	@clear

3-1: main.cpp DwindlingGalaxies.cpp GameEntity.cpp Player.cpp Laser.cpp GameMenu.cpp
	@g++ main.cpp DwindlingGalaxies.cpp GameEntity.cpp Player.cpp Laser.cpp GameMenu.cpp -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -o game
	@./game
	@clear

3-2: main.cpp DwindlingGalaxies.cpp GameEntity.cpp Player.cpp Laser.cpp GameMenu.cpp Alien.cpp
	@g++ main.cpp DwindlingGalaxies.cpp GameEntity.cpp Player.cpp Laser.cpp GameMenu.cpp Alien.cpp -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -o game
	@./game
	@clear

4-1: main.cpp DwindlingGalaxies.cpp GameEntity.cpp Player.cpp Laser.cpp GameMenu.cpp Lives.cpp Alien.cpp
	@g++ main.cpp DwindlingGalaxies.cpp GameEntity.cpp Player.cpp Laser.cpp GameMenu.cpp Lives.cpp Alien.cpp -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -o game
	@./game
	@clear

5-1: main.cpp DwindlingGalaxies.cpp GameEntity.cpp Player.cpp Laser.cpp GameMenu.cpp Lives.cpp Alien.cpp PowerUp.cpp FasterFiring.cpp ExtraLive.cpp
	@g++ main.cpp DwindlingGalaxies.cpp GameEntity.cpp Player.cpp Laser.cpp GameMenu.cpp Lives.cpp Alien.cpp PowerUp.cpp FasterFiring.cpp ExtraLive.cpp -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -o game
	@./game
	@clear

test: unitTest.cpp DwindlingGalaxies.cpp GameEntity.cpp Player.cpp Laser.cpp GameMenu.cpp Lives.cpp Alien.cpp PowerUp.cpp FasterFiring.cpp ExtraLive.cpp Talz.cpp Helghast.cpp MondoShawn.cpp
	@g++ unitTest.cpp DwindlingGalaxies.cpp GameEntity.cpp Player.cpp Laser.cpp GameMenu.cpp Lives.cpp Alien.cpp PowerUp.cpp FasterFiring.cpp ExtraLive.cpp Talz.cpp Helghast.cpp MondoShawn.cpp -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -o test
	@clear
	@./test

play: main.cpp DwindlingGalaxies.cpp GameEntity.cpp Player.cpp Laser.cpp GameMenu.cpp Lives.cpp Alien.cpp PowerUp.cpp FasterFiring.cpp ExtraLive.cpp Talz.cpp Helghast.cpp MondoShawn.cpp
	@g++ main.cpp DwindlingGalaxies.cpp GameEntity.cpp Player.cpp Laser.cpp GameMenu.cpp Lives.cpp Alien.cpp PowerUp.cpp FasterFiring.cpp ExtraLive.cpp Talz.cpp Helghast.cpp MondoShawn.cpp -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -o game
	@./game.exe
	@clear
