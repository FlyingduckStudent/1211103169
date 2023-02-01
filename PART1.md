# Part 1

## Video Demo

Please provide the YouTube link to your [Video Demo](https://youtube.com).

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
11. Quit Function

### To Do

List all the features not yet done. Remove this section if there is no incomplete requirements.

8. Alien Control
9. Save Function
10. Load Function


## Additional Features

1. Error Handling (Partially Done)
2. Audio / Music (Later)
3. Game Score (Later)

## Contributions

### Kalla Deveshwara Rao A/L Rama Rao
    1. Zombie Attributes
    2. Zombie Creation
    3. Zombie Random Spawn
    4. Mostly Zombie related stuff

### Vimal Rich Selvam
    1.Gameboard Creation
    2.Game Object Creation
    3.Error Handling
    4.Mostly Board stuff

### Darwin A/L Radhakrishnan
    1. Alien Movement
    2. Alien Creation
    3. Alien Position
    4. Mostly Alien Related

## Problems Encountered & Solutions

Not much problems were encountered during the developtment of the game other than the logical aspect of zombie creation and gameboard creation. 

### Gameboard: 
We did not know that arrays in c++ is not dynamic. So we had to resort to vectors in this case. An obvious solution. Other than that, the gameboard does not print out Zombie characters properly, because we use "Z(number)" labeling method as an identifier for our zombies.

### Zombie: 
Initially we used vector to just print out the character "Z". We realised that to set zombie attributes, struct is the best solution

### Alien:
Had trouble trying to leave trail. Fixed it after messing around with the logic

