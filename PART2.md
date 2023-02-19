# Part 2

## Video Demo

Group 5 || Mr. Ban Kar Weng || Alien Vs Zombie || T14L 
[Video Demo](https://www.youtube.com/watch?v=lejH1EOlQVI).

## Minimum Requirements

1. Game Play Menu
2. Game Board Creation
3. Game Object Creation
4. Zombie Creation
5. Setting Zombie Attributes
6. Alien Creation
7. Setting Alien Pos and Attributes
8. Alien Control
9. Save Function
10. Load Function
11. Quit Function

### Completed

List all the features completed.

1. Game Play Menu
2. Game Board Creation
3. Game Object Creation
4. Zombie Creation
5. Setting Zombie Attributes
6. Alien Creation
7. Setting Alien Pos and Attributes
8. ALien Control
9. Save Function
10. Load Function
11. Quit Function


## Additional Features

1. Error Handling 
2. Audio / Music 
3. New Game Object k

## Contributions

### Kalla Deveshwara Rao A/L Rama Rao
    1. Zombie Attributes
    2. Zombie Creation
    3. Zombie Random Spawn
    4. Mostly Zombie related stuff
    5. Zombie attack
    6. Zombie movement
    7. Zombie behaviour (after reaching 0 hp)
    8. Error handling (Advanced feature)
    9. Loading

### Vimal Rich Selvam
    1.Gameboard Creation
    2.Game Object Creation
    3.Music (Advanced feature)
    4.Changing trail to game objects
    5.Game help layout
    6.Saving and loading
    7.Quit function
    8.Mostly Board stuff


### Darwin A/L Radhakrishnan
    1. Alien Movement
    2. Alien Creation
    3. Alien Position
    4. Arrow Changes in the board
    5. Alien Attack
    6. Alien detecting all powerups and board objects 
    7. New game object k (Advanced feature)
    8. Mostly Alien Related

## Problems Encountered & Solutions

Not much problems were encountered during the developtment of the game other than the logical aspect of zombie creation and gameboard creation. 

### Gameboard: 
1. Loading the saved data for zombies from a txt file and starting a game from that data

Solution: We utilised .push_back to push the data in from the back, this allowed us to keep the zombie stats in place

2. The game couldn't handle string properly when loaded from a save file

Solution : to_string was the solution used to handle that problem

### Zombie: 
1. Zombies were moving diagonally. 

Solution: Gave zombies a randomizer that will either move horizontally or vertically

2. Zombies will sometimes replace the alien and sometimes overlap each other

Solution: Made an unallowed coordinates vector that stores all the used/reserved coordinates

### Alien:
1. Had trouble with Alien picking up all the powerups and game objects. 

Solution : Manage to create new functions so that Alien can detect the objects and work on it. 

2. Alien moving out of bounds and causing segmentation error

Solution : Created a function that will keep it from doing so
